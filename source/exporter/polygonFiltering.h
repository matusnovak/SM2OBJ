/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_POLYGON_FILTERING
#define SM2OBJ_POLYGON_FILTERING

#include <ffw.h>
#include "config.h"

namespace sm2obj{
    bool removeDuplicatedFaces(chunkBufferStruct* Input, chunkBufferStruct* Output);
    bool removeDuplicatedVertices(chunkBufferStruct* Input, chunkBufferStruct* Output);
}

#endif


