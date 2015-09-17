/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include <ffw.h>
#include <algorithm>

#include "exportBlueprint.h"
#include "blockConfig.h"
#include "loadMeta.h"
#include "chunkTempLoader.h"
#include "chunkLoader.h"
#include "chunkHeader.h"
#include "blockConstructor.h"
#include "polygonFiltering.h"
#include "blockExtractor.h"
#include "blockVerticeData.h"
#include "materialExport.h"

static bool recursiveMetaLoader(const sm2obj::exportBlueprintArgs& Args, sm2obj::entityInfoStruct* Output, const std::string& SubFolder);
static void recursiveMetaDump(const sm2obj::exportBlueprintArgs& Args, sm2obj::entityInfoStruct* Output, int Indent);
static bool recursiveChunkLoader(const sm2obj::exportBlueprintArgs& Args, sm2obj::entityInfoStruct* Input, const std::string& OutputTemp, int& FileIndex);
static void recursiveChunkExport(const sm2obj::exportBlueprintArgs& Args, sm2obj::entityInfoStruct* Input, const std::string& InputOutputTemp, sm2obj::threadInfoStruct* Threads, int& Progress, int ProgressTotal);
static bool mergeVertices(const sm2obj::exportBlueprintArgs& Args, sm2obj::entityInfoStruct* Input, const std::string& InputOutputTemp, ffw::file* Output, bool SplitTextures, bool ExportUvMaps);
static void generateEntityQueue(const sm2obj::exportBlueprintArgs& Args, sm2obj::entityInfoStruct* Input, std::vector<sm2obj::entityInfoStruct*>* Output);
static void* processChunk(void* ThreadInfoPtr);

///=============================================================================
bool sm2obj::exportBlueprint(const exportBlueprintArgs& Args){
	std::cout << ">>> exportBlueprint" << std::endl;
	clearBlockConfig();
    ffw::file objOutput;
    ffw::file mtlOutput;
    entityInfoStruct entityRoot;
    entityRoot.name = Args.outputName;
    entityRoot.path = "";
    entityRoot.pos.set(8.0f, 8.0f, 8.0f);
    entityRoot.dockModule.set(8.0f, 8.0f, 8.0f);
    entityRoot.parent = NULL;
    //entityRoot.model.translate(-8.0f, -8.0f, -8.0f);
    threadInfoStruct* threads;

    // Load block types
    if(!loadBlockTypes(Args, Args.inputConfigFolder + "\\BlockTypes.properties")){
        Args.callbackTerminate(false); return false;
    }

    // Load block config
    if(!loadBlockConfig(Args, Args.inputConfigFolder + "\\BlockConfig.xml")){
        Args.callbackTerminate(false); return false;
    }

    // Open OBJ file for wirting
    if(!objOutput.open(Args.outputFolder + "\\" + Args.outputName + ".obj", false, true, true)){
        Args.callbackLogError("Failed to open OBJ file for writing! Make sure the path: " + Args.outputFolder + " is valid!");
        Args.callbackTerminate(false); return false;
    }

    // Open MTL file for writing
    if(!mtlOutput.open(Args.outputFolder + "\\" + Args.outputName + ".mtl", false, true, true)){
        Args.callbackLogError("Failed to open MTL file for writing! Make sure the path: " + Args.outputFolder + " is valid!");
        Args.callbackTerminate(false); return false;
    }

    // Load all attachments
    if(Args.exportAttachments){
        Args.callbackLogInfo("Loading attached ships and turrets...");
        if(!recursiveMetaLoader(Args, &entityRoot, "")){
            Args.callbackTerminate(false); return false;
        }
    }

    // Dump information about attachments
    Args.callbackLogDebug("Blueprint root:");
    recursiveMetaDump(Args, &entityRoot, 0);

    std::string tempFolder = ffw::getExecutablePath() + "\\temp";

    // Load chunk headers and export decompressed chunks to temp folder
    Args.callbackLogInfo("Loading chunks...");
    int fileIndex = 0;
    ffw::createDirectory(tempFolder);
    if(!recursiveChunkLoader(Args, &entityRoot, ffw::getExecutablePath() + "\\temp", fileIndex)){
        Args.callbackTerminate(false); return false;
    }

    // Create threads
    threads = new threadInfoStruct[Args.numOfThreads];
    for(int i = 0; i < Args.numOfThreads; i++){
        threads[i].thread.bindFunction(&processChunk);
    }

    // Export chunks
    int progress = 0;
    int progressTotal = fileIndex;
    recursiveChunkExport(Args, &entityRoot, tempFolder, threads, progress, progressTotal);

    // Delete threads
    delete[] threads;
    if(stopExport)return false;

    // Generate queue
    std::vector<entityInfoStruct*> entityQueue;
    generateEntityQueue(Args, &entityRoot, &entityQueue);

    if(stopExport)return false;

    // Export vertices
    progress = 0;
    uint64_t indicesOffset = 0;
    uint64_t texPosOffset = 0;
    sm2obj::chunkBufferStruct* chunkRawBuffer = new sm2obj::chunkBufferStruct;
    
	//recursiveVerticesExport(&entityRoot, tempFolder, progress, progressTotal, Args.exportMaterials, !Args.useAtlas, Args.exportUV, &totalExportedIndices);
    for(auto& entity : entityQueue){
        chunkRawBuffer->extractedMaterialsList.clear();
        for(auto& chunk : entity->chunks){
            progress++;
            Args.callbackLogInfo("Generating vertices: " + ffw::valToString(progress) + " out of: " + ffw::valToString(progressTotal));
            Args.callbackProgress(progress, progressTotal);
            // Load a temp block to memory
            sm2obj::loadRawBlocks(Args, tempFolder, chunkRawBuffer, chunk.fileIndex);
            // Export block block to temp as indices and vertices
            sm2obj::extractBlocks(Args, tempFolder, chunkRawBuffer, chunk.fileIndex, &indicesOffset, &texPosOffset);
        }

        if(!Args.useAtlas)texPosOffset += 4;
        else texPosOffset += chunkRawBuffer->extractedMaterialsList.size()*4;

        if(Args.useAtlas){
            for(auto i : chunkRawBuffer->extractedMaterialsList)entity->extractedTiles.push_back(i.x);
        } else {
            for(auto i : chunkRawBuffer->extractedMaterialsList)entity->extractedMaterials.push_back(i);
        }
    }
	delete chunkRawBuffer;

    if(stopExport)return false;

    // Merge files
    Args.callbackLogInfo("Merging vertices and indices into a single file...");

    objOutput.writeLine("# SM2OBJ");
    if(Args.exportMaterials)objOutput.writeLine("mtllib " + Args.outputName + ".mtl");

    //recursiveVerticesMerge(&entityRoot, tempFolder, &objOutput, !Args.useAtlas, Args.exportUV);
    for(auto& entity : entityQueue){
        mergeVertices(Args, entity, tempFolder, &objOutput, !Args.useAtlas, Args.exportUV);
    }

    if(stopExport)return false;

    Args.callbackLogInfo("Creating material file...");

    // Export materials
    if(Args.exportMaterials && Args.useAtlas){
        Args.callbackLogDebug("Exporting altas materials");
        Args.callbackLogDebug("Creating 3 materials...");
        createMaterialAtlas(Args, &mtlOutput);
    } else if(Args.exportMaterials){
        Args.callbackLogDebug("Exporting block materials");
        std::vector<ffw::vec2i> materialList;

        for(auto& entity : entityQueue){
            for(auto& mat :entity->extractedMaterials){
                // Find if material is already added
                bool found = false;
                for(auto& item : materialList){
                    if(item == mat){
                        found = true;
                        break;
                    }
                }
                if(found)continue;
                // Add to list
                materialList.push_back(mat);
            }
        }

        Args.callbackLogDebug("Creating " + ffw::valToString(materialList.size()) + " materials...");

        mtlOutput.writeLine("# SM2OBJ\n");
        for(auto& mat : materialList){
            const blockInfoStruct* block = findBlock(mat.x);
            if(block == NULL)continue;
            createMaterialTile(Args, &mtlOutput, block, mat.y);
        }
    }

    Args.callbackTerminate(true);
	return true;
}

///=============================================================================
bool recursiveMetaLoader(const sm2obj::exportBlueprintArgs& Args, sm2obj::entityInfoStruct* Output, const std::string& SubFolder){
    if(!loadMeta(Args, Output, Args.inputFolder + SubFolder + "\\meta.smbpm", Args.outputName)){
       return false;
    }

    for(auto& item : Output->attachments){
        if(!recursiveMetaLoader(Args, &item, item.path)){
            return false;
        }
    }

    return true;
}

///=============================================================================
void recursiveMetaDump(const sm2obj::exportBlueprintArgs& Args, sm2obj::entityInfoStruct* Output, int Indent){
    std::string ind;
    ind.resize(Indent, ' ');

    Args.callbackLogDebug(ind + "> Name: " + Output->name);
    Args.callbackLogDebug(ind + "> Path: " + Output->path);
    //Args.callbackLogDebug(ind + "> Position: " + ffw::valToString(Output->pos.x) + ", " + ffw::valToString(Output->pos.y) + ", " + ffw::valToString(Output->pos.z));
    //Args.callbackLogDebug(ind + "> Orientation: " + ffw::valToString(Output->orientation.x) + ", " + ffw::valToString(Output->orientation.y) + ", " + ffw::valToString(Output->orientation.z));
    Args.callbackLogDebug(ind + "> Dock module position: " + ffw::valToString(Output->dockModule.x) + ", " + ffw::valToString(Output->dockModule.y) + ", " + ffw::valToString(Output->dockModule.z));
    for(auto& item : Output->attachments){
        recursiveMetaDump(Args, &item, Indent+2);
    }
}

///=============================================================================
bool recursiveChunkLoader(const sm2obj::exportBlueprintArgs& Args, sm2obj::entityInfoStruct* Input, const std::string& OutputTemp, int& FileIndex){
    std::vector<std::string> allFiles;

    // Open target directory
    ffw::directory dir;
    if(!dir.open(Args.inputFolder + Input->path + "\\DATA")){
        Args.callbackLogError("Failed to open folder: " + Args.inputFolder + "\\" + Input->path + " The program might not have permission to do it!");
        return false;
    }

    if(sm2obj::stopExport)return false;

    // Include all files that match
    for(const auto& file : dir.getFiles()){
        std::string extension;
        ffw::getFilePathProperties(file, NULL, NULL, &extension);
        if(extension != "smd2")continue;

        allFiles.push_back(file);
    }

    if(sm2obj::stopExport)return false;

    // Load all files
    for(const auto& file : allFiles){
        if(sm2obj::stopExport)return false;
        ffw::file fileInput;

        Args.callbackLogDebug("Reading file: " + file);

        // Get file position from file name
        size_t pos = file.find('.');
        if(pos == std::string::npos){
            Args.callbackLogError("Error while retrieving file position from file name! Expected dot with coordinates!");
            return false;
        }

        // Get position as tokens
        std::vector<std::string> tokens = ffw::getTokens(file.substr(pos+1, file.size()-pos-6), '.');
        if(tokens.size() != 3){
            Args.callbackLogError("Error while retrieving file position from file name! Wrong coordinates!");
            return false;
        }

        // Convert position to integers
        ffw::vec3i filePos;
        try {
            filePos.x = ffw::stringToVal<int>(tokens[0]);
            filePos.y = ffw::stringToVal<int>(tokens[1]);
            filePos.z = ffw::stringToVal<int>(tokens[2]);
            filePos *= 256;
        } catch (std::exception e){
            Args.callbackLogError("Error while retrieving file position from file name! Wrong coordinates!");
            return false;
        }

        // Print file position
        Args.callbackLogDebug("File position: " + tokens[0] + ", " + tokens[1] + ", " + tokens[2]);

        // Open a file
        if(!fileInput.open(Args.inputFolder + Input->path + "\\DATA\\" + file, true, false, false)){
            Args.callbackLogError("Failed to open file: " + Args.inputFolder + Input->path + "\\DATA\\" + file);
            return false;\
        }

        // Check if file is big enough to contain header
        size_t fileSize = fileInput.getSize();
        if(fileSize < size_t(4+32768+16384)){
            Args.callbackLogError("File is invalid! File is too small. Expected at least 49156 bytes.");
            return false;
        }

        // Load header
        int chunkIndex[SM2OBJ_CHUNK_SIZE];
        int totalChunks = 0;
        if(!sm2obj::loadChunkHeader(&fileInput, &chunkIndex[0], &totalChunks)){
            //ffw::logError() << "Failed to load chunk header!";
            return false;
        }

        // Remember the file offset
        size_t fileOffset = fileInput.getPos();

        Args.callbackLogDebug("Total chunks: " + ffw::valToString(totalChunks));
        //fileChunksTotal += totalChunks;

        // Sort indexes
        // We need to load chunks ordered
        std::sort(std::begin(chunkIndex), std::end(chunkIndex));

        // Load all chunks
        uint32_t chunkData[16][16][16];
        ffw::vec3i chunkPos;
        for(int i = 0; i < SM2OBJ_CHUNK_SIZE; i++){
            if(sm2obj::stopExport)return false;
            if(chunkIndex[i] < 0)continue;
            Args.callbackLogDebug("Loading chunk index: " + ffw::valToString(chunkIndex[i]));

            // Load chunk
            fileInput.gotoPos(fileOffset + chunkIndex[i]*5120);
            if(!sm2obj::loadChunk(Args, &fileInput, fileOffset, chunkIndex[i], chunkData, &chunkPos)){
                continue;
            }

            // Save decompressed raw chunk data to temp folder
            if(!sm2obj::saveTempChunk(OutputTemp, FileIndex, &chunkData[0][0][0])){
                Args.callbackLogWarning("Error while saving chunk to temp! Make sure the program has permissions to create files!");
                continue;
            }

            // Add chunk to list
            Input->chunks.push_back({chunkPos, filePos, FileIndex});
            FileIndex++;
        }
    }
    if(sm2obj::stopExport)return false;

    for(auto& item : Input->attachments){
        if(sm2obj::stopExport)return false;
        if(!recursiveChunkLoader(Args, &item, OutputTemp, FileIndex))return false;
    }

    return true;
}

///=============================================================================
void recursiveChunkExport(const sm2obj::exportBlueprintArgs& Args, sm2obj::entityInfoStruct* Input, const std::string& InputOutputTemp, sm2obj::threadInfoStruct* Threads, int& Progress, int ProgressTotal){
    Args.callbackLogDebug("Exporting: " + Input->name + " from: " + Input->path);

    // export chunks one by one
    for(auto& chunk : Input->chunks){
        if(sm2obj::stopExport)break;
        // Find an empty thread
        while(true){
            bool found = false;
            // Loop through all threads
            for(int i = 0; i < Args.numOfThreads; i++){
                // We can lock a thread only of it has finished
                if(Threads[i].mut.tryLock()){
                    // We found an empty thread, bind information and run it
                    Progress++;
                    //progress(processedChunks, fileChunksTotal);
                    Args.callbackLogInfo("Processing chunk: " + ffw::valToString(Progress) + " out of: " + ffw::valToString(ProgressTotal));
                    Args.callbackProgress(Progress, ProgressTotal);
                    // Where are raw chunks stored
                    Threads[i].tempFolder = InputOutputTemp;
                    // Unlock mutex
                    Threads[i].mut.unlock();
                    // Always join even if thread has stopped
                    Threads[i].thread.join();
                    // Bind chunk
                    Threads[i].chunkPtr = &chunk;
                    // Set matrix
                    Threads[i].entityPtr = Input;
					// Copy arguments
					Threads[i].Args = Args;
                    // Start
                    Threads[i].thread.start(&Threads[i]);
                    // Wait 100ms and go to next chunk
                    ffw::usleep(100000);
                    found = true;
                    break;
                }
            }
            // An empty thread was not found, wait and then try again
            if(found)break;
            ffw::usleep(100000);
        }
    }

    Args.callbackLogDebug("Waiting for threads...");
    // Join all threads
    for(int i = 0; i < Args.numOfThreads; i++){
        Threads[i].thread.join();
    }

    for(auto& item : Input->attachments){
        if(sm2obj::stopExport)break;
        recursiveChunkExport(Args, &item, InputOutputTemp, Threads, Progress, ProgressTotal);
    }
}

///=============================================================================
void constructRotation(sm2obj::entityInfoStruct* Parent, ffw::mat4x4f* Matrix){
    while(Parent != NULL){
        Matrix->rotate(Parent->orientation);
        Parent = Parent->parent;
    }
}

///=============================================================================
void* processChunk(void* ThreadInfoPtr){
    // Get pointer to the thread info struct
    sm2obj::threadInfoStruct* threadInfo = static_cast<sm2obj::threadInfoStruct*>(ThreadInfoPtr);
    // Lock this thread
    threadInfo->mut.lock();
    // Get chunk pointer
    sm2obj::chunkInfoStruct* chunk = threadInfo->chunkPtr;

    // Load chunk from file
    uint32_t chunkData[16][16][16];
    if(!sm2obj::loadTempChunk(threadInfo->tempFolder, chunk->fileIndex, &chunkData[0][0][0])){
        threadInfo->Args.callbackLogWarning("Error loading chunk file index: " + ffw::valToString(chunk->fileIndex));
        threadInfo->mut.unlock();
        return NULL;
    }

    // Reset buffer A
    threadInfo->chunkBufferA.indicesCount = 0;
    threadInfo->chunkBufferA.verticesCount = 0;
    threadInfo->chunkBufferA.indicesOffset = 0;

    // Build blocks by looking through all XYZ positions in chunk
    ffw::vec3i posRel;
    for(posRel.z = 0; posRel.z < 16; posRel.z++){
        for(posRel.y = 0; posRel.y < 16; posRel.y++){
            for(posRel.x = 0; posRel.x < 16; posRel.x++){
                if(chunkData[posRel.z][posRel.y][posRel.x] == 0)continue;

                buildBlock(threadInfo->Args, posRel, chunk->pos, chunk->posFile, chunkData, &threadInfo->chunkBufferA);
            }
        }
    }

    // Reset buffer B
    threadInfo->chunkBufferB.indicesCount = 0;
    threadInfo->chunkBufferB.verticesCount = 0;
    threadInfo->chunkBufferB.indicesOffset = 0;

    // Filter polygons that occupies same space
    removeDuplicatedFaces(&threadInfo->chunkBufferA, &threadInfo->chunkBufferB);

    // Now the data is in buffer B
    // We will use buffer A as a output
    threadInfo->chunkBufferA.indicesCount = 0;
    threadInfo->chunkBufferA.verticesCount = 0;
    threadInfo->chunkBufferA.indicesOffset = 0;

    // Remove duplicated vertices
    removeDuplicatedVertices(&threadInfo->chunkBufferB, &threadInfo->chunkBufferA);

    // Transform vertices
    ffw::vec3f translation(-8.0f, -8.0f, -8.0f);
    //ffw::vec3f dockOffset = threadInfo->entityPtr->dockModule - ffw::vec3f(8.0f, 8.0f, 8.0f);
    //translation -= dockOffset;

    /*ffw::mat4 m;
    ffw::vec3f globalPos;

    sm2obj::entityInfoStruct* entity = threadInfo->entityPtr;
    std::vector<sm2obj::entityInfoStruct*> entityStack;
    while(entity != NULL){
        entityStack.push_back(entity);
        entity = entity->parent;
    }

    if(entityStack.size() > 0){
        for(int i = entityStack.size()-1; i >= 0; i--){
            m.rotate(entityStack[i]->orientation);
        }
    }

    ffw::mat4 mr;
    entity = threadInfo->entityPtr;
    while(entity != NULL){

        ffw::vec3f pos = (entity->pos - ffw::vec3f(8.0f, 8.0f, 8.0f));
        ffw::vec3f dockModule;
        ffw::vec3f offset = entity->dockOffset;
        //std::cout << "pos: " << pos << std::endl;
        //std::cout << "dockOffset: " << offset << std::endl;

        //ffw::vec4f v;
        ffw::mat4 rr;
        constructRotation(entity, &rr);

        entity = entity->parent;

        if(entity != NULL){
            dockModule = (entity->dockModule - ffw::vec3f(8.0f, 8.0f, 8.0f));
            ffw::mat4 mr;

            constructRotation(entity, &mr);

            ffw::vec4f v;
            v.x = pos.x;
            v.y = pos.y;
            v.z = pos.z;
            v = mr * v;
            pos.x = v.x;
            pos.y = v.y;
            pos.z = v.z;

            v.x = offset.x;
            v.y = offset.y;
            v.z = offset.z;
            v.w = 1.0f;
            v = mr * v;
            offset.x = v.x;
            offset.y = v.y;
            offset.z = v.z;

            v.x = dockModule.x;
            v.y = dockModule.y;
            v.z = dockModule.z;
            v.w = 1.0f;
            v = mr * v;
            dockModule.x = v.x;
            dockModule.y = v.y;
            dockModule.z = v.z;
        }
        globalPos -= dockModule;
        globalPos += pos + offset;
    }*/

    for(uint32_t i = 0; i < threadInfo->chunkBufferA.verticesCount; i++){
        threadInfo->chunkBufferA.vertices[i] += translation;
        /*ffw::vec4f v;

        v.x = threadInfo->chunkBufferA.vertices[i].x;
        v.y = threadInfo->chunkBufferA.vertices[i].y;
        v.z = threadInfo->chunkBufferA.vertices[i].z;
        v.w = 1.0f;
        v = m * v;
        threadInfo->chunkBufferA.vertices[i].x = v.x;
        threadInfo->chunkBufferA.vertices[i].y = v.y;
        threadInfo->chunkBufferA.vertices[i].z = v.z;
        threadInfo->chunkBufferA.vertices[i] += globalPos;*/
    }

    // Now the data is in buffer A
    // Save it to temp file
    saveRawBlocks(threadInfo->Args, threadInfo->tempFolder, &threadInfo->chunkBufferA, chunk->fileIndex);

    threadInfo->Args.callbackLogDebug("Chunk index: " + ffw::valToString(chunk->fileIndex) + " exported!");

    // Unlock this thread
    threadInfo->mut.unlock();
    return NULL;
}

///=============================================================================
void generateEntityQueue(const sm2obj::exportBlueprintArgs& Args, sm2obj::entityInfoStruct* Input, std::vector<sm2obj::entityInfoStruct*>* Output){
    Output->push_back(Input);

    for(auto& item : Input->attachments){
        generateEntityQueue(Args, &item, Output);
    }
}

///=============================================================================
bool mergeVertices(const sm2obj::exportBlueprintArgs& Args, sm2obj::entityInfoStruct* Input, const std::string& InputOutputTemp, ffw::file* Output, bool SplitTextures, bool ExportUvMaps){
    Output->writeLine("o " + Input->name);

    for(auto& chunk : Input->chunks){
        ffw::file vertices;

        // Open chunk temp file which contains vertices
        if(!vertices.open(InputOutputTemp + "\\chunk-temp-" + ffw::valToString(chunk.fileIndex) + ".vertices", false, false, false)){
            Args.callbackLogError("Error failed to open vertex temp data! Index: " + ffw::valToString(chunk.fileIndex));
            return false;
        }

        // Read whole file and put contents in output OBJ
        std::string temp;
        while(!vertices.eof()){
            vertices.readLine(&temp);
            if(temp.size() == 0)continue;
            Output->writeLine(temp);
        }
    }
    if(sm2obj::stopExport)return false;

    // Export UVs
    if(ExportUvMaps && SplitTextures){
        for(int i = 0; i < 4; i++){
            Output->writeLine("vt " + ffw::valToString(sm2obj::globalTextureUvs[i].x, 6) + " " + ffw::valToString(sm2obj::globalTextureUvs[i].y, 6));
        }
    } else if(ExportUvMaps){
        for(const auto& tile : Input->extractedTiles){
            int atlasId = tile / 256;
            int posY = tile / 16;
            int posX = tile - posY*16;
            posY -= atlasId*16;
            ffw::vec2f tilePos(posX / 16.0f, posY / 16.0f);
            tilePos.y = 1.0f - tilePos.y - 0.0625f;

            for(int i = 0; i < 4; i++){
                ffw::vec2f uvs = sm2obj::globalTextureUvs[i];
                uvs.y = 1.0f - uvs.y;
                ffw::vec2f texPos = uvs * ffw::vec2f(0.052734375f, 0.052734375f) + tilePos + 0.0048828125f;
                Output->writeLine("vt " + ffw::valToString(texPos.x, 10) + " " + ffw::valToString(texPos.y, 10));
            }
        }
    }
    if(sm2obj::stopExport)return false;

    // Shading off
    Output->writeLine("s off");

    // Do the same for indices
    for(auto& chunk : Input->chunks){
        ffw::file indices;

        // Open chunk temp file which contains indices
        if(!indices.open(InputOutputTemp + "\\chunk-temp-" + ffw::valToString(chunk.fileIndex) + ".indices", false, false, false)){
            Args.callbackLogError("Error failed to open indice temp data! Index: " + ffw::valToString(chunk.fileIndex));
            return false;
        }

        // Read whole file and put contents in output OBJ
        std::string temp;
        while(!indices.eof()){
            indices.readLine(&temp);
            if(temp.size() == 0)continue;
            Output->writeLine(temp);
        }
    }

    return true;
}
