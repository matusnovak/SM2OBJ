/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#ifndef SMD2_EXPORTER_BLOCK_EXTRACTOR
#define SMD2_EXPORTER_BLOCK_EXTRACTOR

#include <ffw.h>
#include "config.h"

void resetIndiceOffset();
void resetMaterials();
const std::vector<int>& getExtractedTiles();
bool saveRawBlocks(const std::string& ExecutablePath, chunkBufferStruct* Input, int ChunkIndex, int FileIndex);
bool loadRawBlocks(const std::string& ExecutablePath, chunkBufferStruct* Input, int ChunkIndex, int FileIndex);
bool extractBlocks(const std::string& ExecutablePath, chunkBufferStruct* Input, int ChunkIndex, int FileIndex);

#endif



