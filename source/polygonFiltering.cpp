/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "polygonFiltering.h"
#include "blockConfig.h"

///=============================================================================
bool sm2obj::removeDuplicatedFaces(chunkBufferStruct* Input, chunkBufferStruct* Output){
    int processedFaces = 0;

    for(uint32_t i = 0; i < Input->indicesCount; i++){

        if(Input->indices[i].w < 0){

            ffw::vec3f c = (Input->vertices[Input->indices[i].x] + Input->vertices[Input->indices[i].y] + Input->vertices[Input->indices[i].z]) / 3.0f;

            bool test = true;
            bool targetTransparency = false;
            int8_t targetObjectType = -1;
            // Check if any other polygon occupies same space
            for(uint32_t t = 0; t < Input->indicesCount; t++){
                if(t == i)continue;

                ffw::vec3f ct = (Input->vertices[Input->indices[t].x] + Input->vertices[Input->indices[t].y] + Input->vertices[Input->indices[t].z]) / 3.0f;

                if(ffw::vec3f(c - ct).length() < 0.2){
                    targetTransparency = Input->indicesMat[t][2] & 0x00FF;
                    targetObjectType = (Input->indicesMat[t][2] & 0xFF00) >> 8;
                    test = false;
                    break;
                }
            }

            // If tested polygon is not transparent and the target polygon is, add a polygon
            if(!test && !Input->indicesMat[i][2] && targetTransparency){
                test = true;
            }

            // Exclude this for objects like grass, light rods and so on...
            if(!test && targetObjectType == 3){
                test = true;
            }

            // The tested polygon does not occupies same space with any other polygon
            // Add it to output
            if(test){
                Output->vertices[Output->verticesCount + 0] = Input->vertices[Input->indices[i].x];
                Output->vertices[Output->verticesCount + 1] = Input->vertices[Input->indices[i].y];
                Output->vertices[Output->verticesCount + 2] = Input->vertices[Input->indices[i].z];
                Output->verticesCount += 3;

                Output->indices[Output->indicesCount] = ffw::vec4i( processedFaces+0, processedFaces+1, processedFaces+2, -1);
                Output->indicesUvs[Output->indicesCount] = Input->indicesUvs[i];
                Output->indicesMat[Output->indicesCount][0] = Input->indicesMat[i][0];
                Output->indicesMat[Output->indicesCount][1] = Input->indicesMat[i][1];
                processedFaces += 3;

                Output->indicesCount += 1;
            }
        } else {

            ffw::vec3f c = (Input->vertices[Input->indices[i].x] + Input->vertices[Input->indices[i].y] + Input->vertices[Input->indices[i].z] + Input->vertices[Input->indices[i].w]) / 4.0f;

            bool test = true;
            bool targetTransparency = false;
            int8_t targetObjectType = -1;
            for(uint32_t t = 0; t < Input->indicesCount; t++){
                if(t == i)continue;

                if(Input->indices[t].w == -1)continue;

                ffw::vec3f ct = (Input->vertices[Input->indices[t].x] + Input->vertices[Input->indices[t].y] + Input->vertices[Input->indices[t].z] + Input->vertices[Input->indices[t].w]) / 4.0f;

                if(ffw::vec3f(c - ct).length() < 0.2){
                    targetTransparency = Input->indicesMat[t][2] & 0x00FF;
                    targetObjectType = (Input->indicesMat[t][2] & 0xFF00) >> 8;
                    test = false;
                    break;
                }
            }

            // If tested polygon is not transparent and the target polygon is, add a polygon
            if(!test && !Input->indicesMat[i][2] && targetTransparency){
                test = true;
            }

            // Exclude this for objects like grass, light rods and so on...
            if(!test && targetObjectType == 3){
                test = true;
            }

            if(test){
                Output->vertices[Output->verticesCount + 0] = Input->vertices[Input->indices[i].x];
                Output->vertices[Output->verticesCount + 1] = Input->vertices[Input->indices[i].y];
                Output->vertices[Output->verticesCount + 2] = Input->vertices[Input->indices[i].z];
                Output->vertices[Output->verticesCount + 3] = Input->vertices[Input->indices[i].w];
                Output->verticesCount += 4;

                Output->indices[Output->indicesCount] = ffw::vec4i( processedFaces+0, processedFaces+1, processedFaces+2, processedFaces+3);
                Output->indicesUvs[Output->indicesCount] = Input->indicesUvs[i];
                Output->indicesMat[Output->indicesCount][0] = Input->indicesMat[i][0];
                Output->indicesMat[Output->indicesCount][1] = Input->indicesMat[i][1];
                processedFaces += 4;
                //resultIndiceMat[Output->indicesCount] = indiceMatIn[i];

                Output->indicesCount += 1;
            }
        }
    }
    return true;
}

///=============================================================================
bool sm2obj::removeDuplicatedVertices(chunkBufferStruct* Input, chunkBufferStruct* Output){
    for(uint32_t i = 0; i < Input->indicesCount; i++){
        ffw::vec4i result;
        for(int v = 0; v < 4; v++){
            int index;
            if(v == 0)index = Input->indices[i].x;
            if(v == 1)index = Input->indices[i].y;
            if(v == 2)index = Input->indices[i].z;
            if(v == 3)index = Input->indices[i].w;

            if(index == -1){
                result.w = -1;
                continue;
            }

            ffw::vec3f vertex = Input->vertices[index];

            int32_t test = -1;
            for(uint32_t t = 0; t < Output->verticesCount; t++){
                if(Output->vertices[t] == vertex){
                    test = t;
                    break;
                }
            }

            if(test == -1){
                Output->vertices[Output->verticesCount] = vertex;
                if(v == 0)result.x = Output->verticesCount;
                if(v == 1)result.y = Output->verticesCount;
                if(v == 2)result.z = Output->verticesCount;
                if(v == 3)result.w = Output->verticesCount;
                Output->verticesCount++;
            } else {
                if(v == 0)result.x = test;
                if(v == 1)result.y = test;
                if(v == 2)result.z = test;
                if(v == 3)result.w = test;
            }
        }

        Output->indices[Output->indicesCount] = result;
        Output->indicesMat[Output->indicesCount][0] = Input->indicesMat[i][0];
        Output->indicesMat[Output->indicesCount][1] = Input->indicesMat[i][1];
        Output->indicesMat[Output->indicesCount][2] = Input->indicesMat[i][2];
        Output->indicesUvs[Output->indicesCount] = Input->indicesUvs[i];
        Output->indicesCount++;
    }
    return true;
}
