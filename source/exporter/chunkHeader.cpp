/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "chunkHeader.h"

struct chunkIndexS {
    int32_t chunkID;
    uint32_t chunkLen;
};

///=============================================================================
bool sm2obj::loadChunkHeader(ffw::file* File, int* ChunkIndex, int* TotalChunks){
    uint32_t unknownInt;

    chunkIndexS chunkIndex[16][16][16];
    uint64_t timeStampIndex[16][16][16];

    if(!File->read(&unknownInt, sizeof(uint32_t))){
        ffw::logger().error() << "Read error at first byte in header!";
        return false;
    }

    if(!File->read(chunkIndex, sizeof(chunkIndexS)*16*16*16)){
        ffw::logger().error() << "Read error at chunk index in header!";
        return false;
    }

    if(!File->read(timeStampIndex, sizeof(uint64_t)*16*16*16)){
        ffw::logger().error() << "Read error at time stamp in header!";
        return false;
    }

    uint8_t wtfByte;
    File->read(&wtfByte, 1);

    for(int z = 0; z < 16; z++){
        for(int y = 0; y < 16; y++){
            for(int x = 0; x < 16; x++){
                auto& currentIndex = chunkIndex[x][y][z];

                // Swap bytes due to endianness
                currentIndex.chunkID = __builtin_bswap32(currentIndex.chunkID);
                currentIndex.chunkLen = __builtin_bswap32(currentIndex.chunkLen);

                auto& currentStamp = timeStampIndex[z][y][x];
                currentStamp = __builtin_bswap64(currentStamp);

                if(currentIndex.chunkID >= 0){
                    (*TotalChunks)++;
                    ChunkIndex[z*16*16 + y*16 + x] = currentIndex.chunkID;
                } else {
                    ChunkIndex[z*16*16 + y*16 + x] = -1;
                }

            }
        }
    }
    return true;
}
