/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#include <ffw.h>
#include <algorithm>

#include "blockConfig.h"
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
}
