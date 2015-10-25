/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_CHUNK_HEADER
#define SM2OBJ_CHUNK_HEADER

#include <ffw.h>

namespace sm2obj{
    bool loadChunkHeader(ffw::file* File, int* ChunkIndex, int* TotalChunks);
}

#endif



