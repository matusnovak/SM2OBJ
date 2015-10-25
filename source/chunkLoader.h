/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_CHUNK_LOADER
#define SM2OBJ_CHUNK_LOADER

#include <ffw.h>
#include "config.h"

namespace sm2obj{
    bool loadChunk(ffw::file* File, size_t FileOffset, int ChunkIndex, uint32_t ChunkData[][16][16], ffw::vec3i* Pos);
}

#endif




