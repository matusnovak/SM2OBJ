/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#ifndef SMD2_EXPORTER_BLOCK_CONSTRUCTOR
#define SMD2_EXPORTER_BLOCK_CONSTRUCTOR

#include <ffw.h>
#include "config.h"

bool buildBlock(ffw::vec3i Pos, ffw::vec3i PosRel, ffw::vec3i PosFile, uint32_t ChunkData[][16][16], chunkBufferStruct* Output);

#endif


