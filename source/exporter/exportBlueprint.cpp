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

static bool recursiveMetaLoader(sm2obj::entityInfoStruct* Output, const std::string& InputFolder, const std::string& SubFolder, const std::string& OutputName);
static void recursiveMetaDump(sm2obj::entityInfoStruct* Output, int Indent);
static bool recursiveChunkLoader(sm2obj::entityInfoStruct* Input, const std::string& InputFolder, const std::string& OutputTemp, int& FileIndex);
static void recursiveChunkExport(sm2obj::entityInfoStruct* Input, const std::string& InputOutputTemp, sm2obj::threadInfoStruct* Threads, int NumOfThreads, int& Progress, int ProgressTotal);
static bool mergeVertices(sm2obj::entityInfoStruct* Input, const std::string& InputOutputTemp, ffw::file* Output, bool SplitTextures, bool ExportUvMaps);
static void generateEntityQueue(sm2obj::entityInfoStruct* Input, std::vector<sm2obj::entityInfoStruct*>* Output);
static void* processChunk(void* ThreadInfoPtr);

///=============================================================================
bool sm2obj::exportBlueprint(const std::string& InputConfigFolder, const std::string& InputFolder,
                             const std::string& OutputFolder, const std::string& OutputName,
                             bool ExportUV, bool UseAtlas, bool ExportMaterials,
                             bool ExportDiffuse, bool ExportAlpha, bool ExportNormals, bool ExportEmissive,
                             bool SpecularHighlight, int NumOfThreads, bool ExportAttachments){
    clearBlockConfig();
    ffw::file objOutput;
    ffw::file mtlOutput;
    entityInfoStruct entityRoot;
    entityRoot.name = OutputName;
    entityRoot.path = "";
    entityRoot.pos.set(8.0f, 8.0f, 8.0f);
    entityRoot.dockModule.set(8.0f, 8.0f, 8.0f);
    entityRoot.parent = NULL;
    //entityRoot.model.translate(-8.0f, -8.0f, -8.0f);
    threadInfoStruct* threads;

    // Load block types
    if(!loadBlockTypes(InputConfigFolder + "\\BlockTypes.properties")){
        TERMINATE(false);
    }

    // Load block config
    if(!loadBlockConfig(InputConfigFolder + "\\BlockConfig.xml")){
        TERMINATE(false);
    }

    // Open OBJ file for wirting
    if(!objOutput.open(OutputFolder + "\\" + OutputName + ".obj", false, true, true)){
        LOG_ERROR("Failed to open OBJ file for writing! Make sure the path: " + OutputFolder + " is valid!");
        TERMINATE(false);
    }

    // Open MTL file for writing
    if(!mtlOutput.open(OutputFolder + "\\" + OutputName + ".mtl", false, true, true)){
        LOG_ERROR("Failed to open MTL file for writing! Make sure the path: " + OutputFolder + " is valid!");
        TERMINATE(false);
    }

    // Load all attachments
    if(ExportAttachments){
        LOG_INFO("Loading attached ships and turrets...");
        if(!recursiveMetaLoader(&entityRoot, InputFolder, "", OutputName)){
            TERMINATE(false);
        }
    }

    // Dump information about attachments
    LOG_DEBUG("Blueprint root:");
    recursiveMetaDump(&entityRoot, 0);

    std::string tempFolder = ffw::getExecutablePath() + "\\temp";

    // Load chunk headers and export decompressed chunks to temp folder
    LOG_INFO("Loading chunks...");
    int fileIndex = 0;
    ffw::createDirectory(tempFolder);
    if(!recursiveChunkLoader(&entityRoot, InputFolder, ffw::getExecutablePath() + "\\temp", fileIndex)){
        TERMINATE(false);
    }

    // Create threads
    threads = new threadInfoStruct[NumOfThreads];
    for(int i = 0; i < NumOfThreads; i++){
        threads[i].thread.bindFunction(&processChunk);
    }

    // Export chunks
    int progress = 0;
    int progressTotal = fileIndex;
    recursiveChunkExport(&entityRoot, tempFolder, threads, NumOfThreads, progress, progressTotal);

    // Delete threads
    delete[] threads;

    // Generate queue
    std::vector<entityInfoStruct*> entityQueue;
    generateEntityQueue(&entityRoot, &entityQueue);

    // Export vertices
    progress = 0;
    uint64_t indicesOffset = 0;
    uint64_t texPosOffset = 0;
    sm2obj::chunkBufferStruct chunkRawBuffer;
    //recursiveVerticesExport(&entityRoot, tempFolder, progress, progressTotal, ExportMaterials, !UseAtlas, ExportUV, &totalExportedIndices);
    for(auto& entity : entityQueue){
        chunkRawBuffer.extractedMaterialsList.clear();
        for(auto& chunk : entity->chunks){
            progress++;
            LOG_INFO("Generating vertices: " + ffw::valToString(progress) + " out of: " + ffw::valToString(progressTotal));
            PROGRESS(progress, progressTotal);
            // Load a temp block to memory
            sm2obj::loadRawBlocks(tempFolder, &chunkRawBuffer, chunk.fileIndex);
            // Export block block to temp as indices and vertices
            sm2obj::extractBlocks(tempFolder, &chunkRawBuffer, chunk.fileIndex, ExportMaterials, !UseAtlas, ExportUV, &indicesOffset, &texPosOffset);
        }

        if(!UseAtlas)texPosOffset += 4;
        else texPosOffset += chunkRawBuffer.extractedMaterialsList.size()*4;

        if(UseAtlas){
            for(auto i : chunkRawBuffer.extractedMaterialsList)entity->extractedTiles.push_back(i.x);
        } else {
            for(auto i : chunkRawBuffer.extractedMaterialsList)entity->extractedMaterials.push_back(i);
        }
    }

    // Merge files
    LOG_INFO("Merging vertices and indices into a single file...");

    objOutput.writeLine("# SM2OBJ");
    if(ExportMaterials)objOutput.writeLine("mtllib " + OutputName + ".mtl");

    //recursiveVerticesMerge(&entityRoot, tempFolder, &objOutput, !UseAtlas, ExportUV);
    for(auto& entity : entityQueue){
        mergeVertices(entity, tempFolder, &objOutput, !UseAtlas, ExportUV);
    }

    LOG_INFO("Creating material file...");

    // Export materials
    if(ExportMaterials && UseAtlas){
        LOG_DEBUG("Exporting altas materials");
        LOG_DEBUG("Creating 3 materials...");
        createMaterialAtlas(&mtlOutput, ExportDiffuse, ExportNormals, ExportAlpha, ExportEmissive, SpecularHighlight);
    } else if(ExportMaterials){
        LOG_DEBUG("Exporting block materials");
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

        LOG_DEBUG("Creating " + ffw::valToString(materialList.size()) + " materials...");

        mtlOutput.writeLine("# SM2OBJ\n");
        for(auto& mat : materialList){
            const blockInfoStruct* block = findBlock(mat.x);
            if(block == NULL)continue;
            createMaterialTile(&mtlOutput, block, mat.y, ExportDiffuse, ExportNormals, ExportAlpha, ExportEmissive, SpecularHighlight);
        }
    }

    TERMINATE(true);
}

///=============================================================================
bool recursiveMetaLoader(sm2obj::entityInfoStruct* Output, const std::string& InputFolder, const std::string& SubFolder, const std::string& OutputName){
    if(!loadMeta(Output, InputFolder + SubFolder + "\\meta.smbpm", OutputName)){
       return false;
    }

    for(auto& item : Output->attachments){
        if(!recursiveMetaLoader(&item, InputFolder, "\\" + item.path, OutputName)){
            return false;
        }
    }

    return true;
}

///=============================================================================
void recursiveMetaDump(sm2obj::entityInfoStruct* Output, int Indent){
    std::string ind;
    ind.resize(Indent, ' ');

    LOG_DEBUG(ind + "> Name: " + Output->name);
    LOG_DEBUG(ind + "> Path: " + Output->path);
    //LOG_DEBUG(ind + "> Position: " + ffw::valToString(Output->pos.x) + ", " + ffw::valToString(Output->pos.y) + ", " + ffw::valToString(Output->pos.z));
    //LOG_DEBUG(ind + "> Orientation: " + ffw::valToString(Output->orientation.x) + ", " + ffw::valToString(Output->orientation.y) + ", " + ffw::valToString(Output->orientation.z));
    LOG_DEBUG(ind + "> Dock module position: " + ffw::valToString(Output->dockModule.x) + ", " + ffw::valToString(Output->dockModule.y) + ", " + ffw::valToString(Output->dockModule.z));
    for(auto& item : Output->attachments){
        recursiveMetaDump(&item, Indent+2);
    }
}

///=============================================================================
bool recursiveChunkLoader(sm2obj::entityInfoStruct* Input, const std::string& InputFolder, const std::string& OutputTemp, int& FileIndex){
    std::vector<std::string> allFiles;

    // Open target directory
    ffw::directory dir;
    if(!dir.open(InputFolder + Input->path + "\\DATA")){
        LOG_ERROR("Failed to open folder: " + InputFolder + "\\" + Input->path + " The program might not have permission to do it!");
        return false;
    }

    // Include all files that match
    for(const auto& file : dir.getFiles()){
        std::string extension;
        ffw::getFilePathProperties(file, NULL, NULL, &extension);
        if(extension != "smd2")continue;

        allFiles.push_back(file);
    }

    // Load all files
    for(const auto& file : allFiles){
        ffw::file fileInput;

        LOG_DEBUG("Reading file: " + file);

        // Get file position from file name
        size_t pos = file.find('.');
        if(pos == std::string::npos){
            LOG_ERROR("Error while retrieving file position from file name! Expected dot with coordinates!");
            return false;
        }

        // Get position as tokens
        std::vector<std::string> tokens = ffw::getTokens(file.substr(pos+1, file.size()-pos-6), '.');
        if(tokens.size() != 3){
            LOG_ERROR("Error while retrieving file position from file name! Wrong coordinates!");
            return false;
        }

        // Convert position to integers
        ffw::vec3i filePos;
        try {
            filePos.x = ffw::stringToVal<int>(tokens[0]);
            filePos.y = ffw::stringToVal<int>(tokens[1]);
            filePos.z = ffw::stringToVal<int>(tokens[2]);
            filePos *= 256;
        } catch (std::exception& e){
            LOG_ERROR("Error while retrieving file position from file name! Wrong coordinates!");
            return false;
        }

        // Print file position
        LOG_DEBUG("File position: " + tokens[0] + ", " + tokens[1] + ", " + tokens[2]);

        // Open a file
        if(!fileInput.open(InputFolder + Input->path + "\\DATA\\" + file, true, false, false)){
            LOG_ERROR("Failed to open file: " + InputFolder + Input->path + "\\DATA\\" + file);
            return false;\
        }

        // Check if file is big enough to contain header
        size_t fileSize = fileInput.getSize();
        if(fileSize < size_t(4+32768+16384)){
            LOG_ERROR("File is invalid! File is too small. Expected at least 49156 bytes.");
            return false;
        }

        // Load header
        int chunkIndex[SM2OBJ_CHUNK_SIZE];
        int totalChunks = 0;
        if(!sm2obj::loadChunkHeader(&fileInput, &chunkIndex[0], &totalChunks)){
            //ffw::logger().error() << "Failed to load chunk header!";
            return false;
        }

        // Remember the file offset
        size_t fileOffset = fileInput.getPos();

        LOG_DEBUG("Total chunks: " + ffw::valToString(totalChunks));
        //fileChunksTotal += totalChunks;

        // Sort indexes
        // We need to load chunks ordered
        std::sort(std::begin(chunkIndex), std::end(chunkIndex));

        // Load all chunks
        uint32_t chunkData[16][16][16];
        ffw::vec3i chunkPos;
        for(int i = 0; i < SM2OBJ_CHUNK_SIZE; i++){
            if(chunkIndex[i] < 0)continue;
            LOG_DEBUG("Loading chunk index: " + ffw::valToString(chunkIndex[i]));

            // Load chunk
            fileInput.gotoPos(fileOffset + chunkIndex[i]*5120);
            if(!sm2obj::loadChunk(&fileInput, fileOffset, chunkIndex[i], chunkData, &chunkPos)){
                continue;
            }

            // Save decompressed raw chunk data to temp folder
            if(!sm2obj::saveTempChunk(OutputTemp, FileIndex, &chunkData[0][0][0])){
                LOG_WARNING("Error while saving chunk to temp! Make sure the program has permissions to create files!");
                continue;
            }

            // Add chunk to list
            Input->chunks.push_back({chunkPos, filePos, FileIndex});
            FileIndex++;
        }
    }

    for(auto& item : Input->attachments){
        if(!recursiveChunkLoader(&item, InputFolder, OutputTemp, FileIndex))return false;
    }

    return true;
}

///=============================================================================
void recursiveChunkExport(sm2obj::entityInfoStruct* Input, const std::string& InputOutputTemp, sm2obj::threadInfoStruct* Threads, int NumOfThreads, int& Progress, int ProgressTotal){
    LOG_DEBUG("Exporting: " + Input->name + " from: " + Input->path);

    // export chunks one by one
    for(auto& chunk : Input->chunks){
        // Find an empty thread
        while(true){
            bool found = false;
            // Loop through all threads
            for(int i = 0; i < NumOfThreads; i++){
                // We can lock a thread only of it has finished
                if(Threads[i].mut.tryLock()){
                    // We found an empty thread, bind information and run it
                    Progress++;
                    //progress(processedChunks, fileChunksTotal);
                    LOG_INFO("Processing chunk: " + ffw::valToString(Progress) + " out of: " + ffw::valToString(ProgressTotal));
                    PROGRESS(Progress, ProgressTotal);
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

    LOG_DEBUG("Waiting for threads...");
    // Join all threads
    for(int i = 0; i < NumOfThreads; i++){
        Threads[i].thread.join();
    }

    for(auto& item : Input->attachments){
        recursiveChunkExport(&item, InputOutputTemp, Threads, NumOfThreads, Progress, ProgressTotal);
    }
}

void constructRotation(sm2obj::entityInfoStruct* Parent, ffw::mat4* Matrix){
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
        LOG_WARNING("Error loading chunk file index: " + ffw::valToString(chunk->fileIndex));
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

                buildBlock(posRel, chunk->pos, chunk->posFile, chunkData, &threadInfo->chunkBufferA);
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
    ffw::vec3f dockOffset = threadInfo->entityPtr->dockModule - ffw::vec3f(8.0f, 8.0f, 8.0f);
    translation -= dockOffset;

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
    saveRawBlocks(threadInfo->tempFolder, &threadInfo->chunkBufferA, chunk->fileIndex);

    LOG_DEBUG("Chunk index: " + ffw::valToString(chunk->fileIndex) + " exported!");

    // Unlock this thread
    threadInfo->mut.unlock();
    return NULL;
}

///=============================================================================
void generateEntityQueue(sm2obj::entityInfoStruct* Input, std::vector<sm2obj::entityInfoStruct*>* Output){
    Output->push_back(Input);

    for(auto& item : Input->attachments){
        generateEntityQueue(&item, Output);
    }
}

///=============================================================================
bool mergeVertices(sm2obj::entityInfoStruct* Input, const std::string& InputOutputTemp, ffw::file* Output, bool SplitTextures, bool ExportUvMaps){
    Output->writeLine("o " + Input->name);

    for(auto& chunk : Input->chunks){
        ffw::file vertices;

        // Open chunk temp file which contains vertices
        if(!vertices.open(InputOutputTemp + "\\chunk-temp-" + ffw::valToString(chunk.fileIndex) + ".vertices", false, false, false)){
            LOG_ERROR("Error failed to open vertex temp data! Index: " + ffw::valToString(chunk.fileIndex));
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

    // Shading off
    Output->writeLine("s off");

    // Do the same for indices
    for(auto& chunk : Input->chunks){
        ffw::file indices;

        // Open chunk temp file which contains indices
        if(!indices.open(InputOutputTemp + "\\chunk-temp-" + ffw::valToString(chunk.fileIndex) + ".indices", false, false, false)){
            LOG_ERROR("Error failed to open indice temp data! Index: " + ffw::valToString(chunk.fileIndex));
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

/*#include "blockConfig.h"
#include "chunkHeader.h"
#include "chunkLoader.h"
#include "chunkTempLoader.h"
#include "config.h"
#include "blockConstructor.h"
#include "blockExtractor.h"
#include "polygonFiltering.h"
#include "textureExport.h"
#include "materialExport.h"
#include "blockVerticeData.h"

#define TERMINATE(X)\
if(exportExitFunc != NULL)exportExitFunc(X); return (void*)X;

static ffw::vec3i boundingBoxMin;
static ffw::vec3i boundingBoxMax;
static int fileChunksTotal = 0;
static int processedChunks = 0;
static std::string executablePath;

// Information about chunks
struct chunkInfoStruct {
    // Relative position
    ffw::vec3i pos;
    // Relative position of the file from which chunk was loaded
    ffw::vec3i posFile;
    // Index of the chunk
    int index;
    // Index of the file
    int indexFile;
};

// Information about thread
struct threadInfoStruct {
    // Main thread class
    ffw::thread thread;
    // Lock mutex
    ffw::mutex mut;
    // Chunk information that is beeing processed by thread
    chunkInfoStruct* chunkPtr;
    // Buffers to save chunk data
    chunkBufferStruct chunkBufferA;
    chunkBufferStruct chunkBufferB;
};

static threadInfoStruct* threads;
static std::vector<chunkInfoStruct> chunkInfo;

///=============================================================================
void progress(int Value, int Range){
    if(exportProgressFunc != NULL)exportProgressFunc(Value, Range);
}

///=============================================================================
void* processChunk(void* ThreadInfoPtr){
    // Get pointer to the thread info struct
    threadInfoStruct* threadInfo = static_cast<threadInfoStruct*>(ThreadInfoPtr);
    // Lock this thread
    threadInfo->mut.lock();
    // Get chunk pointer
    chunkInfoStruct* chunk = threadInfo->chunkPtr;

    // Load chunk from file
    uint32_t chunkData[16][16][16];
    if(!loadTempChunk(executablePath, chunk->index, chunk->indexFile, &chunkData[0][0][0])){
        ffw::logger().error() << "Error loading chunk index: " << chunk->index << " file: " << chunk->indexFile;
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

                buildBlock(posRel, chunk->pos, chunk->posFile, chunkData, &threadInfo->chunkBufferA);
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

    // Now the data is in buffer A
    // Save it to temp file
    saveRawBlocks(executablePath, &threadInfo->chunkBufferA, chunk->index, chunk->indexFile);

    ffw::logger().debug() << "Chunk: " << chunk->index << " file: " << chunk->indexFile << " exported!";

    // Unlock this thread
    threadInfo->mut.unlock();
    return NULL;
}

///=============================================================================
void* runExporter(void* DATA){
    chunkInfo.clear();
    fileChunksTotal = 0;

    // Initialize logger
    ffw::logger::initLogger();

    ffw::logger().print() << "Starting exporter...";

    // Get executable path
    executablePath = ffw::getExecutablePath();

    // Check if there is a job to do
    if(!textureExport && filePath.size() == 0){
        ffw::logger().error() << "Nothing to do...";
        TERMINATE(false);
    }

    // Check if path to StarMade data folder is not empty
    if(starMadeDataFolder.size() == 0){
        ffw::logger().error() << "Wrong StarMade data folder! Have you missed something?";
        TERMINATE(false);
    }

    // Check if target file is not empty
    if(filePath.size() == 0){
        ffw::logger().error() << "Wrong file name! Have you missed something?";
        TERMINATE(false);
    }

    // Check if output file name is not empty
    if(fileName.size() == 0){
        ffw::logger().error() << "Wrong file name! Have you missed something?";
        TERMINATE(false);
    }

    // Check if file exists
    if(!ffw::checkIfFileExists(filePath)){
        ffw::logger().error() << "Invalid path to blueprint! Maybe the program does not have permissions...";
        TERMINATE(false);
    }

    // Separate path to folder, name, and to extension
    std::string blueprintFolder;
    std::string blueprintName;
    std::string blueprintExtension;
    ffw::getFilePathProperties(filePath, &blueprintFolder, &blueprintName, &blueprintExtension);

    // Get frist part of the blueprint file name
    // this: "Isanth Type-Zero Mb.0.0.0" becames this: "Isanth Type-Zero Mb"
    std::string blueprintNameShort;
    size_t dot = blueprintName.find('.');
    if(dot == std::string::npos){
        ffw::logger().error() << "Selected file has invalid name...";
        TERMINATE(false);
    } else {
        blueprintNameShort = blueprintName.substr(0, dot);
    }

    // Check for all files inside blueprint folder
    // We need to include all files
    std::vector<std::string> allFiles;
    allFiles.push_back(blueprintName + ".smd2");

    // Open target directory
    ffw::listDirectory dir;
    if(!dir.open(blueprintFolder)){
        ffw::logger().error() << "Can not look into the blueprint folder! Maybe the program does not have permissions...";
        TERMINATE(false);
    }

    // Open output OBJ file
    ffw::file objOutput;
    if(!objOutput.open(fileOutputFolder + "\\" + fileName + ".obj", false, true, false)){
        ffw::logger().error() << "Error failed to open OBJ for writing!";
        TERMINATE(false);
    }

    // Include all files that match blueprint name
    for(const auto& file : dir.getFiles()){
        if(file == allFiles[0])continue;
        if(file.find(blueprintNameShort) == 0){
            ffw::logger().debug() << "Adding blueprint file: " << file;
            allFiles.push_back(file);
        }
    }

    // If no output folder is defined then the default path is C:/
    if(fileOutputFolder.size() == 0)fileOutputFolder = "C:";

    // Check file extension
    if(blueprintExtension != "smd2"){
        ffw::logger().error() << "Wrong blueprint file! Expected a file with *.smd2 extension";
        TERMINATE(false);
    }

    // Begin material export
    if(materialExport){
        if(textureSplit && !beginMaterialExport()){
            TERMINATE(false);
        } else if(!textureSplit && !createMaterialAtlas()){
            TERMINATE(false);
        }
        resetMaterials();
        ffw::logger().print() << "Exporting materials is enabled!";
    }

    // Print some debug information
    ffw::logger().print() << "Starting with " << threadsCount << " threads!";
    ffw::logger().print() << "Target blueprint: " << blueprintFolder;

    // Create target directories
    ffw::createDirectory(executablePath + "\\temp");
    ffw::createDirectory(fileOutputFolder);

    // Load block config
    if(!loadBlockTypes(starMadeDataFolder + "\\config\\BlockTypes.properties")){
        ffw::logger().error() << "Failed to load block types from \"data\\BlockTypes.properties\" Check if file exists!";
        TERMINATE(false);
    } else {
        ffw::logger().print() << "Block types loaded!";
    }

    if(!loadBlockConfig(starMadeDataFolder + "\\config\\BlockConfig.xml")){
        ffw::logger().error() << "Failed to load block config from \"data\\BlockConfig.xml\" Check if file exists!";
        TERMINATE(false);
    } else {
        ffw::logger().print() << "Block config loaded!";
    }

    // Run texture export
    if(textureExport && textureSplit){
        ffw::logger().print() << "Exporting textures...";
        ffw::createDirectory(fileOutputFolder + "\\textures");
        if(!exportTextures(starMadeDataFolder + "\\textures\\block\\Default\\256")){
            TERMINATE(false);
        }
    } else if(textureExport){
        ffw::logger().print() << "Exporting atlases...";
        ffw::createDirectory(fileOutputFolder + "\\atlases");
        if(!exportAtlases(starMadeDataFolder + "\\textures\\block\\Default\\256")){
            TERMINATE(false);
        }
    }

    ffw::logger().print() << "Exporting blueprint...";

    // Load all files
    int fileIndex = 0;
    for(const auto& file : allFiles){
        ffw::file fileInput;

        ffw::logger().print() << "Reading file: " << file;

        // Get file position from file name
        size_t pos = file.find('.');
        if(pos == std::string::npos){
            ffw::logger().error() << "Error while retrieving file position from file name! Expected dot with coordinates!";
            TERMINATE(false);
        }

        // Get position as tokens
        std::vector<std::string> tokens = ffw::getTokens(file.substr(pos+1, file.size()-pos-6), '.');
        if(tokens.size() != 3){
            ffw::logger().error() << "Error while retrieving file position from file name! Wrong coordinates!";
            TERMINATE(false);
        }

        // Convert position to integers
        ffw::vec3i filePos;
        try {
            filePos.x = ffw::stringToVal<int>(tokens[0]);
            filePos.y = ffw::stringToVal<int>(tokens[0]);
            filePos.z = ffw::stringToVal<int>(tokens[0]);
            filePos *= 256;
        } catch (std::exception& e){
            ffw::logger().error() << "Error while retrieving file position from file name! Wrong coordinates!";
        }

        // Print file position
        ffw::logger().debug() << "File position: " << filePos;

        // Open a file
        if(!fileInput.open(blueprintFolder + "\\" + file, true, false, false)){
            ffw::logger().error() << "Failed to open file: " << file;
            TERMINATE(false);
        }

        // Check if file is big enough to contain header
        size_t fileSize = fileInput.getSize();
        if(fileSize < size_t(4+32768+16384)){
            ffw::logger().error() << "File is invalid! File is too small. Expected at least 49156 bytes.";
            TERMINATE(false);
        }

        // Load header
        int chunkIndex[CHUNK_SIZE];
        int totalChunks = 0;
        if(!loadChunkHeader(&fileInput, &chunkIndex[0], &totalChunks)){
            //ffw::logger().error() << "Failed to load chunk header!";
            TERMINATE(false);
        }

        // Remember the file offset
        size_t fileOffset = fileInput.getPos();

        ffw::logger().debug() << "Total chunks: " << totalChunks;
        fileChunksTotal += totalChunks;

        // Sort indexes
        // We need to load chunks ordered
        std::sort(std::begin(chunkIndex), std::end(chunkIndex));

        // Load all chunks
        uint32_t chunkData[16][16][16];
        ffw::vec3i chunkPos;
        for(int i = 0; i < CHUNK_SIZE; i++){
            if(chunkIndex[i] < 0)continue;
            ffw::logger().debug() << "Loading chunk index: " << chunkIndex[i];

            // Load chunk
            fileInput.gotoPos(fileOffset + chunkIndex[i]*5120);
            if(!loadChunk(&fileInput, fileOffset, chunkIndex[i], chunkData, &chunkPos)){
                continue;
            }

            // Calculate bounding box
            if(chunkPos.x < boundingBoxMin.x)boundingBoxMin.x = chunkPos.x;
            if(chunkPos.x+16 > boundingBoxMax.x)boundingBoxMax.x = chunkPos.x+16;

            if(chunkPos.y < boundingBoxMin.y)boundingBoxMin.y = chunkPos.y;
            if(chunkPos.y+16 > boundingBoxMax.y)boundingBoxMax.y = chunkPos.y+16;

            if(chunkPos.z < boundingBoxMin.z)boundingBoxMin.z = chunkPos.z;
            if(chunkPos.z+16 > boundingBoxMax.z)boundingBoxMax.z = chunkPos.z+16;

            // Save decompressed raw chunk data to temp folder
            if(!saveTempChunk(executablePath, chunkIndex[i], fileIndex, &chunkData[0][0][0])){
                ffw::logger().warning() << "Error while saving chunk to temp!";
                continue;
            }

            // All chunk to list
            chunkInfo.push_back(chunkInfoStruct{chunkPos, filePos, chunkIndex[i], fileIndex});
        }

        fileIndex++;
    }

    ffw::logger().print() << "Bounding box -X: " << boundingBoxMin.x << " +X: " << boundingBoxMax.x;
    ffw::logger().print() << "Bounding box -Y: " << boundingBoxMin.y << " +Y: " << boundingBoxMax.y;
    ffw::logger().print() << "Bounding box -Z: " << boundingBoxMin.z << " +Z: " << boundingBoxMax.z;

    // Create threads
    threads = new threadInfoStruct[threadsCount];
    for(int i = 0; i < threadsCount; i++){
        threads[i].thread.bindFunction(&processChunk);
    }

    // Start exporting...
    ffw::logger().print() << "Starting threads...";

    // export chunks one by one
    processedChunks = 0;
    for(auto& chunk : chunkInfo){
        // Find an empty thread
        while(true){
            bool found = false;
            // Loop through all threads
            for(int i = 0; i < threadsCount; i++){
                // We can lock a thread only of it has finished
                if(threads[i].mut.tryLock()){
                    // We found an empty thread, bind information and run it
                    processedChunks++;
                    progress(processedChunks, fileChunksTotal);
                    ffw::logger().print() << "Processing: " << processedChunks << " out of: " << fileChunksTotal;
                    // Unlock mutex
                    threads[i].mut.unlock();
                    // Always join even if thread has stopped
                    threads[i].thread.join();
                    // Bind chunk
                    threads[i].chunkPtr = &chunk;
                    // Start
                    threads[i].thread.start(&threads[i]);
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

    ffw::logger().print() << "Waiting for threads...";
    // Join all threads
    for(int i = 0; i < threadsCount; i++){
        threads[i].thread.join();
    }

    // Reset indice offset
    resetIndiceOffset();

    // Generate vertices for all chunks
    processedChunks = 0;
    chunkBufferStruct chunkRawBuffer;
    for(auto& chunk : chunkInfo){
        processedChunks++;
        ffw::logger().print() << "Generating vertices: " << processedChunks << " out of: " << fileChunksTotal;
        // Load a temp block to memory
        loadRawBlocks(executablePath, &chunkRawBuffer, chunk.index, chunk.indexFile);
        // Export block block to temp as indices and vertices
        extractBlocks(executablePath, &chunkRawBuffer, chunk.index, chunk.indexFile);
    }

    // End material export, we do not need it anymore
    if(textureSplit && materialExport)endMaterialExport();

    ffw::logger().print() << "Merging vertices into single OBJ...";

    // Merge files to one OBJ file
    objOutput.writeLine("# StarMade Blueprint Exporter v1.0");
    if(materialExport)objOutput.writeLine("mtllib " + fileName + ".mtl");
    objOutput.writeLine("o " + fileName);

    // Export chunks one by one
    for(const auto& chunk : chunkInfo){
        ffw::file vertices;

        // Open chunk temp file which contains vertices
        if(!vertices.open(executablePath + "\\temp\\" + ffw::valToString(chunk.indexFile) + "_" + ffw::valToString(chunk.index) + ".vertices.data", false, false, false)){
            ffw::logger().error() << "Error failed to open faces temp data! Index: " << chunk.index << " file: " << chunk.indexFile;
            TERMINATE(false);
        }

        // Read whole file and put contents in output OBJ
        std::string temp;
        while(!vertices.eof()){
            vertices.readLine(&temp);
            if(temp.size() == 0)continue;
            objOutput.writeLine(temp);
        }
    }

    // Export UVs
    if(uvsExport && textureSplit){
        for(int i = 0; i < 4; i++){
            objOutput.writeLine("vt " + ffw::valToString(globalTextureUvs[i].x, 6) + " " + ffw::valToString(globalTextureUvs[i].y, 6));
        }
    } else if(uvsExport){
        for(const auto& tile : getExtractedTiles()){
            int atlasId = tile / 256;
            int posY = tile / 16;
            int posX = tile - posY*16;
            posY -= atlasId*16;
            ffw::vec2f tilePos(posX / 16.0f, posY / 16.0f);
            tilePos.y = 1.0f - tilePos.y - 0.0625f;

            for(int i = 0; i < 4; i++){
                ffw::vec2f uvs = globalTextureUvs[i];
                uvs.y = 1.0f - uvs.y;
                ffw::vec2f texPos = uvs * ffw::vec2f(0.052734375f, 0.052734375f) + tilePos + 0.0048828125f;
                objOutput.writeLine("vt " + ffw::valToString(texPos.x, 10) + " " + ffw::valToString(texPos.y, 10));
            }
        }
    }

    // Shading off
    objOutput.writeLine("s off");

    // Do the same for indices
    for(const auto& chunk : chunkInfo){
        ffw::file faces;

        // Open chunk temp file which contains indices
        if(!faces.open(executablePath + "\\temp\\" + ffw::valToString(chunk.indexFile) + "_" + ffw::valToString(chunk.index) + ".faces.data", false, false, false)){
            ffw::logger().error() << "Error failed to open faces temp data! Index: " << chunk.index << " file: " << chunk.indexFile;
            TERMINATE(false);
        }

        // Read whole file and put contents in output OBJ
        std::string temp;
        while(!faces.eof()){
            faces.readLine(&temp);
            if(temp.size() == 0)continue;
            objOutput.writeLine(temp);
        }
    }

    // Delete threads
    delete[] threads;

    // Remove temp folder
    system(std::string("rmdir /Q /S " + executablePath + "\\temp").c_str());

    // Print some debug information
    ffw::logger().print() << "OBJ file saved to: " << fileOutputFolder << "\\" << fileName << ".obj";
    ffw::logger().print() << "Export finished with no critial errors!";

    // Terminate with success
    TERMINATE(true);
}*/
