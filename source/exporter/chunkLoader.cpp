/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "chunkLoader.h"
#include "config.h"

#include <zlib.h>

// Load chunk and decompress data
///=============================================================================
bool sm2obj::loadChunk(const exportBlueprintArgs& Args, ffw::file* File, size_t FileOffset, int ChunkIndex, uint32_t ChunkData[][16][16], ffw::vec3i* Pos){
    uint64_t timeStamp;
    int32_t relativePosition[3];
    uint8_t chunkType;
    uint32_t compressedDataLength;
    uint8_t compressedData[5095];
    unsigned char rawChunkData[16][16][16][3];

	std::cout << "chunk size: " << File->getSize() << std::endl;

    if( ! (File->read(&timeStamp, sizeof(uint64_t)) &&
           File->read(&relativePosition, sizeof(int32_t)*3) &&
           File->read(&chunkType, sizeof(uint8_t)) &&
           File->read(&compressedDataLength, sizeof(uint32_t)) &&
           File->read(&compressedData, 5095)) ){
        Args.callbackLogError("Chunk error while reading chunk header!");
        return false;
    }

    timeStamp = ffw::byteSwap64(timeStamp);
    relativePosition[0] = ffw::byteSwap32(relativePosition[0]);
    relativePosition[1] = ffw::byteSwap32(relativePosition[1]);
    relativePosition[2] = ffw::byteSwap32(relativePosition[2]);
    compressedDataLength = ffw::byteSwap32(compressedDataLength);

    if(relativePosition[0] > 9999 || relativePosition[0] < -9999 ||
       relativePosition[1] > 9999 || relativePosition[1] < -9999 ||
       relativePosition[2] > 9999 || relativePosition[2] < -9999){
        Args.callbackLogWarning("Chunk error while reading chunk header! Wrong relative position!");
        return false;
    }

    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    int ret = inflateInit(&strm);
    if(ret != Z_OK){
        Args.callbackLogWarning("Chunk failed to load! Z-Lib init error!");
        inflateEnd(&strm);
        return false;
    }

    strm.avail_in = compressedDataLength;
    strm.next_in = compressedData;

    strm.avail_out = 16*16*16*3;
    strm.next_out = &rawChunkData[0][0][0][0];

    ret = inflate(&strm, Z_NO_FLUSH);

    int have = (16*16*16*3) - strm.avail_out;

    if(have != 12288){
        Args.callbackLogWarning("Can not decompress data! Chunk might be corrupted!");
        return false;
    }

    Pos->x = relativePosition[0];
    Pos->y = relativePosition[1];
    Pos->z = relativePosition[2];

    inflateEnd(&strm);

    for(int z = 0; z < 16; z++){
        for(int y = 0; y < 16; y++){
            for(int x = 0; x < 16; x++){

                unsigned int A = rawChunkData[z][y][x][0];
                unsigned int B = rawChunkData[z][y][x][1];
                unsigned int C = rawChunkData[z][y][x][2];

                if((A > 0 || B > 0) && C > 0){

                    uint16_t id = uint16_t(0x07 & B) * 256 + uint16_t(C);
                    uint16_t rot = uint8_t(0xF0 & A) >> 4;

                    char rot2 = (0x08 & A);
                    if(rot2){
                        rot = 0xFF00 + rot;
                    }

                    ChunkData[z][y][x] = uint16_t(rot)*256*256 + id;
                } else {
                    ChunkData[z][y][x] = 0;
                }
            }
        }
    }
    return true;
}
