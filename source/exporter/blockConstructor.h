/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_BLOCK_CONSTRUCTOR
#define SM2OBJ_BLOCK_CONSTRUCTOR

#include <ffw.h>
#include "config.h"

namespace sm2obj{
    bool buildBlock(const exportBlueprintArgs& Args, ffw::vec3i Pos, ffw::vec3i PosRel, ffw::vec3i PosFile, uint32_t ChunkData[][16][16], chunkBufferStruct* Output);
}

#endif


