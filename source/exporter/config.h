/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_CONFIG
#define SM2OBJ_CONFIG

#include <ffw.h>

#define SM2OBJ_CHUNK_SIZE 16*16*16
#define SM2OBJ_CHUNK_MAX_VERTICES 8
#define SM2OBJ_CHUNK_MAX_INDICES 8

namespace sm2obj{
    struct exportBlueprintArgs {
		std::string inputConfigFolder;
		std::string inputFolder;
        std::string outputFolder;
		std::string outputName;
		std::string textureExtension;
        bool exportUV;
		bool useAtlas;
		bool exportMaterials;
        bool exportDiffuse;
		bool exportAlpha;
		bool exportNormals;
		bool exportEmissive;
        bool specularHighlight;
		int numOfThreads;
		int width;
		bool normalToBump;
		bool exportAttachments;
		bool (*imageSaver)(const std::string&, unsigned char*, int, int, ffw::imageType);
		void (*callbackLogError)(const std::string& Message);
        void (*callbackLogInfo)(const std::string& Message);
        void (*callbackLogDebug)(const std::string& Message);
        void (*callbackLogWarning)(const std::string& Message);
        void (*callbackProgress)(int Progress, int Total);
        void (*callbackTerminate)(bool Success);
	};

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
		sm2obj::chunkInfoStruct* chunkPtr;
		// Buffers to save chunk data
		sm2obj::chunkBufferStruct chunkBufferA;
		sm2obj::chunkBufferStruct chunkBufferB;
		// Pointer to the entity
		sm2obj::entityInfoStruct* entityPtr;

		sm2obj::exportBlueprintArgs Args;
	};

	extern chunkBufferStruct chunkBufferA;
    extern chunkBufferStruct chunkBufferB;
    extern bool stopExport;

    void bruteforceExit();
};

#endif
