/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#include "polygonFiltering.h"
#include "blockConfig.h"

///=============================================================================
bool removeDuplicatedFaces(chunkBufferStruct* Input, chunkBufferStruct* Output){
    int processedFaces = 0;

    for(uint32_t i = 0; i < Input->indicesCount; i++){

        if(Input->indices[i].w < 0){

            ffw::vec3f v0(Input->vertices[Input->indices[i].x]);
            ffw::vec3f v1(Input->vertices[Input->indices[i].y]);
            ffw::vec3f v2(Input->vertices[Input->indices[i].z]);

            ffw::vec3f c = (v0 + v1 + v2) / 3.0f;

            bool test = true;
            bool targetTransparency = false;
            // Check if any other polygon occupies same space
            for(uint32_t t = 0; t < Input->indicesCount; t++){
                if(t == i)continue;

                ffw::vec3f vt0(Input->vertices[Input->indices[t].x]);
                ffw::vec3f vt1(Input->vertices[Input->indices[t].y]);
                ffw::vec3f vt2(Input->vertices[Input->indices[t].z]);

                ffw::vec3f ct = (vt0 + vt1 + vt2) / 3.0f;

                if(ffw::vec3f(c - ct).length() < 0.2){
                    targetTransparency = Input->indicesMat[t][2];
                    test = false;
                    break;
                }
            }

            // If tested polygon is not transparent and the target polygon is, add a polygon
            if(!test && !Input->indicesMat[i][2] && targetTransparency){
                test = true;
            }

            // The tested polygon does not occupies same space with any other polygon
            // Add it to output
            if(test){
                Output->vertices[Output->verticesCount + 0] = v0;
                Output->vertices[Output->verticesCount + 1] = v1;
                Output->vertices[Output->verticesCount + 2] = v2;
                Output->verticesCount += 3;

                Output->indices[Output->indicesCount] = ffw::vec4i( processedFaces+0, processedFaces+1, processedFaces+2, -1);
                Output->indicesUvs[Output->indicesCount] = Input->indicesUvs[i];
                Output->indicesMat[Output->indicesCount][0] = Input->indicesMat[i][0];
                Output->indicesMat[Output->indicesCount][1] = Input->indicesMat[i][1];
                processedFaces += 3;
                //resultIndiceMat[resultIndicesCount] = indiceMatIn[i];

                Output->indicesCount += 1;
            }
        } else {
            ffw::vec3f v0(Input->vertices[Input->indices[i].x]);
            ffw::vec3f v1(Input->vertices[Input->indices[i].y]);
            ffw::vec3f v2(Input->vertices[Input->indices[i].z]);
            ffw::vec3f v3(Input->vertices[Input->indices[i].w]);

            ffw::vec3f c = (v0 + v1 + v2 + v3) / 4.0f;

            bool test = true;
            bool targetTransparency = false;
            for(uint32_t t = 0; t < Input->indicesCount; t++){
                if(t == i)continue;

                if(Input->indices[t].w == -1)continue;

                ffw::vec3f vt0(Input->vertices[Input->indices[t].x]);
                ffw::vec3f vt1(Input->vertices[Input->indices[t].y]);
                ffw::vec3f vt2(Input->vertices[Input->indices[t].z]);
                ffw::vec3f vt3(Input->vertices[Input->indices[t].w]);

                ffw::vec3f ct = (vt0 + vt1 + vt2 + vt3) / 4.0f;

                if(ffw::vec3f(c - ct).length() < 0.2){
                    targetTransparency = Input->indicesMat[t][2];
                    test = false;
                    break;
                }
            }

            // If tested polygon is not transparent and the target polygon is, add a polygon
            if(!test && !Input->indicesMat[i][2] && targetTransparency){
                test = true;
            }


            if(test){
                Output->vertices[Output->verticesCount + 0] = v0;
                Output->vertices[Output->verticesCount + 1] = v1;
                Output->vertices[Output->verticesCount + 2] = v2;
                Output->vertices[Output->verticesCount + 3] = v3;
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
bool removeDuplicatedVertices(chunkBufferStruct* Input, chunkBufferStruct* Output){
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
                //Output->indices[Output->indicesCount] = index;
                //Output->indicesCount++;
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
        Output->indicesUvs[Output->indicesCount] = Input->indicesUvs[i];
        Output->indicesCount++;
    }
    return true;
}
