/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_BLOCK_EXTRACTOR
#define SM2OBJ_BLOCK_EXTRACTOR

#include <ffw.h>
#include "config.h"

namespace sm2obj{
    //void resetIndiceOffset();
    //void resetMaterials();
    //const std::vector<int>& getExtractedTiles();
    bool saveRawBlocks(const std::string& TempFolder, chunkBufferStruct* Input, int FileIndex);
    bool loadRawBlocks(const std::string& TempFolder, chunkBufferStruct* Input, int FileIndex);
    bool extractBlocks(const std::string& TempFolder, chunkBufferStruct* Input, int FileIndex, bool ExportMaterials, bool SplitTextures, bool ExportUvMaps, uint64_t* IndicesOffset, uint64_t* TexPosOffset);
}

#endif



