/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#ifndef SMD2_EXPORTER_CHUNK_HEADER
#define SMD2_EXPORTER_CHUNK_HEADER

#include <ffw.h>

bool loadChunkHeader(ffw::file* File, int* ChunkIndex, int* TotalChunks);

#endif



