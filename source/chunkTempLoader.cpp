/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#include "chunkTempLoader.h"
#include "config.h"

///=============================================================================
bool saveTempChunk(const std::string& ExecutablePath, int Index, int FileIndex, uint32_t* Buffer){
    ffw::file input;
    if(!input.open(ExecutablePath + "\\temp\\"+ ffw::valToString(FileIndex) + "_" + ffw::valToString(Index) + ".data", true, true, true))return false;
    if(!input.write(Buffer, CHUNK_SIZE*sizeof(uint32_t)))return false;
    input.close();
    return true;
}

///=============================================================================
bool loadTempChunk(const std::string& ExecutablePath, int Index, int FileIndex, uint32_t* Buffer){
    ffw::file input;
    if(!input.open(ExecutablePath + "\\temp\\"+ ffw::valToString(FileIndex) + "_" + ffw::valToString(Index) + ".data", true, false, false))return false;
    if(input.getSize() < CHUNK_SIZE*sizeof(uint32_t))return false;
    if(!input.read(Buffer, CHUNK_SIZE*sizeof(uint32_t)))return false;
    input.close();
    return true;
}
