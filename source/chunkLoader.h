/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#ifndef SMD2_EXPORTER_CHUNK_LOADER
#define SMD2_EXPORTER_CHUNK_LOADER

#include <ffw.h>

bool loadChunk(ffw::file* File, size_t FileOffset, int ChunkIndex, uint32_t ChunkData[][16][16], ffw::vec3i* Pos);

#endif




