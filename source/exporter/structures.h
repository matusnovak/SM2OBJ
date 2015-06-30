/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SMD2OBJ_STRUCTURES
#define SMD2OBJ_STRUCTURES

namespace sm2obj{
    struct chunkBufferStruct {
        ffw::vec3f vertices  [SM2OBJ_CHUNK_SIZE * SM2OBJ_CHUNK_MAX_VERTICES];
        ffw::vec4i indices   [SM2OBJ_CHUNK_SIZE * SM2OBJ_CHUNK_MAX_INDICES];
        ffw::vec4i indicesUvs[SM2OBJ_CHUNK_SIZE * SM2OBJ_CHUNK_MAX_INDICES];
        uint16_t indicesMat  [SM2OBJ_CHUNK_SIZE * SM2OBJ_CHUNK_MAX_INDICES][3];
        uint32_t indicesCount;
        uint32_t verticesCount;
        uint32_t indicesOffset;
        std::vector<ffw::vec2i> extractedMaterialsList;
    };

    // Information about chunks
    struct chunkInfoStruct {
        // Relative position
        ffw::vec3i pos;
        // Relative position of the file from which chunk was loaded
        ffw::vec3i posFile;
        // Index of the file
        int fileIndex;
    };

    // Information about entity
    struct entityInfoStruct {
        // Name
        std::string name;
        // Relative path
        std::string path;
        // Position of docking in parent space
        ffw::vec3f pos;
        // Orientation of docking
        ffw::quaternion orientation;
        // Position of dock module in local space
        ffw::vec3f dockModule;
        // Dock offset in local space
        ffw::vec3f dockOffset;
        // Attached ships and turrets
        std::vector<entityInfoStruct> attachments;
        // Chunk information
        std::vector<chunkInfoStruct> chunks;
        // Extracted tiles
        std::vector<int> extractedTiles;
        // Extracted tiles
        std::vector<ffw::vec2i> extractedMaterials;
        // Parent pointer
        entityInfoStruct* parent;
    };

    // Information about thread
    struct threadInfoStruct {
        // Path to raw chunks
        std::string tempFolder;
        // Main thread class
        ffw::thread thread;
        // Lock mutex
        ffw::mutex mut;
        // Chunk information that is beeing processed by thread
        chunkInfoStruct* chunkPtr;
        // Buffers to save chunk data
        chunkBufferStruct chunkBufferA;
        chunkBufferStruct chunkBufferB;
        // Pointer to the entity
        entityInfoStruct* entityPtr;
    };
};

#endif
