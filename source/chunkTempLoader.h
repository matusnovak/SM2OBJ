/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_CHUNK_TEMP_LOADER
#define SM2OBJ_CHUNK_TEMP_LOADER

#include <ffw.h>

namespace sm2obj{
    bool saveTempChunk(const std::string& Path, int FileIndex, uint32_t* Buffer);
    bool loadTempChunk(const std::string& Path, int FileIndex, uint32_t* Buffer);
}

#endif

