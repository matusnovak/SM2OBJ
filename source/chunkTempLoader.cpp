/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "chunkTempLoader.h"
#include "config.h"

///=============================================================================
bool sm2obj::saveTempChunk(const std::string& Folder, int FileIndex, uint32_t* Buffer){
    ffw::file input;
    if(!input.open(Folder + "\\chunk-temp-"+ ffw::valToString(FileIndex) + ".raw", std::ios::out | std::ios::binary | std::ios::trunc))return false;
    if(!input.write(Buffer, SM2OBJ_CHUNK_SIZE*sizeof(uint32_t)))return false;
    input.close();
    return true;
}

///=============================================================================
bool sm2obj::loadTempChunk(const std::string& Folder, int FileIndex, uint32_t* Buffer){
    ffw::file input;
    if(!input.open(Folder + "\\chunk-temp-"+ ffw::valToString(FileIndex) + ".raw", std::ios::in | std::ios::binary))return false;
    if(input.getSize() < SM2OBJ_CHUNK_SIZE*sizeof(uint32_t))return false;
    if(!input.read(Buffer, SM2OBJ_CHUNK_SIZE*sizeof(uint32_t)))return false;
    input.close();
    return true;
}
