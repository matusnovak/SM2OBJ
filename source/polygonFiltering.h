/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#ifndef SMD2_EXPORTER_POLYGON_FILTERING
#define SMD2_EXPORTER_POLYGON_FILTERING

#include <ffw.h>
#include "config.h"

bool removeDuplicatedFaces(chunkBufferStruct* Input, chunkBufferStruct* Output);

bool removeDuplicatedVertices(chunkBufferStruct* Input, chunkBufferStruct* Output);

#endif


