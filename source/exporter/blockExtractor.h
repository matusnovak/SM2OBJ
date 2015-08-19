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
    bool saveRawBlocks(const exportBlueprintArgs& Args, const std::string& TempFolder, chunkBufferStruct* Input, int FileIndex);
    bool loadRawBlocks(const exportBlueprintArgs& Args, const std::string& TempFolder, chunkBufferStruct* Input, int FileIndex);
    bool extractBlocks(const exportBlueprintArgs& Args, const std::string& TempFolder, chunkBufferStruct* Input, int FileIndex, uint64_t* IndicesOffset, uint64_t* TexPosOffset);
}

#endif



