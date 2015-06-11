/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#ifndef SMD2_EXPORTER_CHUNK_TEMP_LOADER
#define SMD2_EXPORTER_CHUNK_TEMP_LOADER

#include <ffw.h>

bool saveTempChunk(const std::string& ExecutablePath, int Index, int FileIndex, uint32_t* Buffer);
bool loadTempChunk(const std::string& ExecutablePath, int Index, int FileIndex, uint32_t* Buffer);

#endif

