/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#include "blockConstructor.h"
#include "blockConfig.h"
#include "blockVerticeData.h"

static void addObjectCube(chunkBufferStruct* Output, const ffw::vec3f& Pos, int Rot, const blockInfoStruct* Block);
static void addObjectWedge(chunkBufferStruct* Output, const ffw::vec3f& Pos, int Rot, const blockInfoStruct* Block);
static void addObjectHepta(chunkBufferStruct* Output, const ffw::vec3f& Pos, int Rot, const blockInfoStruct* Block);
static void addObjectXshape(chunkBufferStruct* Output, const ffw::vec3f& Pos, int Rot, const blockInfoStruct* Block);
static void addObjectTetra(chunkBufferStruct* Output, const ffw::vec3f& Pos, int Rot, const blockInfoStruct* Block);
static void addObjectCorner(chunkBufferStruct* Output, const ffw::vec3f& Pos, int RotA, int RotB, const blockInfoStruct* Block);

///=============================================================================
static void getBlock(uint32_t Buffer[][16][16], int* BlockID, int* RotA, int* RotB, int PosX, int PosY, int PosZ){
    // Block information is arranged in this order:
    // first byte is block extra rotation
    // second byte is block main rotation
    // Lasst two bytes is block ID
    uint32_t& value = Buffer[PosZ][PosY][PosX];
    *BlockID = (value & 0x0000FFFF);
    *RotA = (value & 0x00FF0000) >> 16;
    if((value & 0xFF000000) > 0){
        *RotB = 1;
    } else {
        *RotB = 0;
    }
}

///=============================================================================
bool buildBlock(ffw::vec3i Pos, ffw::vec3i PosRel, ffw::vec3i PosFile, uint32_t ChunkData[][16][16], chunkBufferStruct* Output){
    int id;
    int rotA;
    int rotB;

    // Decode block from input
    getBlock(ChunkData, &id, &rotA, &rotB, Pos.x, Pos.y, Pos.z);

    // Get absolute block position
    ffw::vec3f PosF(float(Pos.x + PosRel.x/* + PosFile.x*/), float(Pos.y + PosRel.y/* + PosFile.y*/), float(Pos.z + PosRel.z/* + PosFile.x*/));

    // Find block
    const blockInfoStruct* block = findBlock(id);
    if(block == NULL){
        // Can not find block ID
    } else {
        // -1 = undefined
        //  0 = cube
        //  1 = wedge
        //  2 = corner
        //  3 = X-shape
        //  4 = tetra
        //  5 = hepta

        switch (block->object){
            case 0: addObjectCube(Output, PosF, rotA, block); break;
            case 1: addObjectWedge(Output, PosF, rotA, block); break;
            case 2: addObjectCorner(Output, PosF, rotA, rotB, block); break;
            case 3: addObjectXshape(Output, PosF, rotA, block); break;
            case 4: addObjectTetra(Output, PosF, rotA, block); break;
            case 5: addObjectHepta(Output, PosF, rotA, block); break;
            default: break;
        };
    }

    return true;
}

///=============================================================================
void addObjectCube(chunkBufferStruct* Output, const ffw::vec3f& Pos, int Rot, const blockInfoStruct* Block){
    // Add vertices
    for(uint32_t i = 0, p = Output->verticesCount; i < 8; i++, p++){
        // Get vector of the vertice
        ffw::vec3f v = cubeVertices[i] + ffw::vec3f(-0.5f, -0.5f, +0.5f);

        // Rotate it
        if(Rot == 0){
            v.rotateX(90);
        } else if(Rot == 1){
            v.rotateX(-90);
        } else if(Rot == 2){
            // Nothing to do
        } else if(Rot == 3){
            v.rotateX(180);
        } else if(Rot == 4){
            v.rotateX(90);
            v.rotateY(270);
        } else if(Rot == 5){
            v.rotateX(90);
            v.rotateY(90);
        }

        // Add vertice to output
        Output->vertices[p] = v + Pos;
    }

    Output->verticesCount += 8;

    // Add indices
    for(uint32_t i = 0, p = Output->indicesCount; i < 6; i++, p++){
        // Add indices (starting from 0) to output plus the offset
        Output->indices[p] = cubeFaces[i]-1 + Output->indicesOffset;
        Output->indicesUvs[p] = cubeFacesUvs[i];
        Output->indicesMat[p][0] = Block->id;
        Output->indicesMat[p][2] = Block->transparent;
    }

    // Add material IDs
    Output->indicesMat[Output->indicesCount + 0][1] = Block->texture[3];
    Output->indicesMat[Output->indicesCount + 1][1] = Block->texture[2];
    Output->indicesMat[Output->indicesCount + 2][1] = Block->texture[0];
    Output->indicesMat[Output->indicesCount + 3][1] = Block->texture[1];
    Output->indicesMat[Output->indicesCount + 4][1] = Block->texture[4];
    Output->indicesMat[Output->indicesCount + 5][1] = Block->texture[5];

    Output->indicesOffset += 8;
    Output->indicesCount += 6;
}

///=============================================================================
void addObjectXshape(chunkBufferStruct* Output, const ffw::vec3f& Pos, int Rot, const blockInfoStruct* Block){
    // Add vertices
    for(uint32_t i = 0, p = Output->verticesCount; i < 8; i++, p++){
        // Get vector of the vertice
        ffw::vec3f v = XshapeVertices[i] + ffw::vec3f(-0.5f, -0.5f, +0.5f);

        // Rotate it
        if(Rot == 0){
            v.rotateX(90);
        } else if(Rot == 1){
            v.rotateX(-90);
        } else if(Rot == 2){
            // Nothing to do
        } else if(Rot == 3){
            v.rotateX(180);
        } else if(Rot == 4){
            v.rotateX(90);
            v.rotateY(270);
        } else if(Rot == 5){
            v.rotateX(90);
            v.rotateY(90);
        }

        // Add vertice to output
        Output->vertices[p] = v + Pos;
    }

    Output->verticesCount += 8;

    // Add indices
    for(uint32_t i = 0, p = Output->indicesCount; i < 2; i++, p++){
        // Add indices (starting from 0) to output plus the offset
        Output->indices[p] = XshapeFaces[i]-1 + Output->indicesOffset;
        Output->indicesUvs[p] = XshapeFacesUvs[i];
        Output->indicesMat[p][0] = Block->id;
        Output->indicesMat[p][2] = uint16_t(Block->transparent) | (uint16_t(Block->object) << 8);
        Output->indicesMat[p][1] = Block->texture[0];
    }

    Output->indicesOffset += 8;
    Output->indicesCount += 2;
}

///=============================================================================
void addObjectWedge(chunkBufferStruct* Output, const ffw::vec3f& Pos, int Rot, const blockInfoStruct* Block){
    for(uint32_t i = 0, p = Output->verticesCount; i < 6; i++, p++){
        ffw::vec3f v = wedgeVertices[i] + ffw::vec3f(-0.5f, -0.5f, +0.5f);

        if(Rot == 1){
            v.rotateY(90);
        } else if(Rot == 2){
            v.rotateY(180);
        } else if(Rot == 3){
            v.rotateY(270);

        } else if(Rot == 4){
            v.rotateX(-90);
        } else if(Rot == 5){
            v.rotateX(-90);
            v.rotateY(270);
        } else if(Rot == 6){
            v.rotateX(-90);
            v.rotateY(180);
        } else if(Rot == 7){
            v.rotateX(-90);
            v.rotateY(90);

        } else if(Rot == 8){
            v.rotateZ(-90);
        } else if(Rot == 9){
            v.rotateZ(-90);
            v.rotateY(270);
        } else if(Rot == 10){
            v.rotateZ(-90);
            v.rotateY(90);
        } else if(Rot == 11){
            v.rotateZ(-90);
            v.rotateY(180);
        }

        Output->vertices[p] = v + Pos;
    }

    Output->verticesCount += 6;

    for(uint32_t i = 0, p = Output->indicesCount; i < 5; i++, p++){
        Output->indices[p] = wedgeFaces[i]-1 + Output->indicesOffset;
        Output->indicesUvs[p] = wedgeFacesUvs[i];

        if(wedgeFaces[i].w == -1)Output->indices[p].w = -1;
        Output->indicesMat[p][0] = Block->id;
        Output->indicesMat[p][1] = Block->texture[0];
        Output->indicesMat[p][2] = Block->transparent;
        //chunkFacesMat[p] = ID;
    }

    Output->indicesOffset += 6;
    Output->indicesCount += 5;
}

///=============================================================================
void addObjectHepta(chunkBufferStruct* Output, const ffw::vec3f& Pos, int Rot, const blockInfoStruct* Block){
    for(uint32_t i = 0, p = Output->verticesCount; i < 7; i++, p++){
        ffw::vec3f v = heptaVertices[i] + ffw::vec3f(-0.5f, -0.5f, +0.5f);

        if(Rot == 1){
            v.rotateY(-90);
        } else if(Rot == 2){
            v.rotateY(180);
        } else if(Rot == 3){
            v.rotateY(-270);

        } else if(Rot == 4){
            v.rotateX(-90);
        } else if(Rot == 5){
            v.rotateX(-90);
            v.rotateY(270);
        } else if(Rot == 6){
            v.rotateX(-90);
            v.rotateY(180);
        } else if(Rot == 7){
            v.rotateX(-90);
            v.rotateY(90);

        } else if(Rot == 8){
            v.rotateZ(-90);
        } else if(Rot == 9){
            v.rotateZ(-90);
            v.rotateY(270);
        } else if(Rot == 10){
            v.rotateZ(-90);
            v.rotateY(90);
        } else if(Rot == 11){
            v.rotateZ(-90);
            v.rotateY(180);
        }

        Output->vertices[p] = v + Pos;
    }

    Output->verticesCount += 7;

    for(uint32_t i = 0, p = Output->indicesCount; i < 7; i++, p++){
        Output->indices[p] = heptaFaces[i]-1 + Output->indicesOffset;
        Output->indicesUvs[p] = heptaFacesUvs[i];

        if(heptaFaces[i].w == -1)Output->indices[p].w = -1;
        Output->indicesMat[p][0] = Block->id;
        Output->indicesMat[p][1] = Block->texture[0];
        Output->indicesMat[p][2] = Block->transparent;
    }

    Output->indicesOffset += 7;
    Output->indicesCount += 7;
}

///=============================================================================
void addObjectTetra(chunkBufferStruct* Output, const ffw::vec3f& Pos, int Rot, const blockInfoStruct* Block){
    for(uint32_t i = 0, p = Output->verticesCount; i < 4; i++, p++){
        ffw::vec3f v = tetraVertices[i] + ffw::vec3f(-0.5f, -0.5f, +0.5f);

        if(Rot == 1){
            v.rotateY(-90);
        } else if(Rot == 2){
            v.rotateY(180);
        } else if(Rot == 3){
            v.rotateY(90);

        } else if(Rot == 4){
            v.rotateX(-90);
        } else if(Rot == 5){
            v.rotateX(-90);
            v.rotateY(270);
        } else if(Rot == 6){
            v.rotateX(-90);
            v.rotateY(180);
        } else if(Rot == 7){
            v.rotateX(-90);
            v.rotateY(90);

        }

        Output->vertices[p] = v + Pos;
    }

    Output->verticesCount += 4;

    for(uint32_t i = 0, p = Output->indicesCount; i < 4; i++, p++){
        Output->indices[p] = tetraFaces[i]-1 + Output->indicesOffset;
        Output->indicesUvs[p] = tetraFacesUvs[i];

        if(tetraFaces[i].w == -1)Output->indices[p].w = -1;
        //chunkFacesMat[p] = ID;
        Output->indicesMat[p][0] = Block->id;
        Output->indicesMat[p][1] = Block->texture[0];
        Output->indicesMat[p][2] = Block->transparent;
    }

    Output->indicesOffset += 4;
    Output->indicesCount += 4;
}

///=============================================================================
void addObjectCorner(chunkBufferStruct* Output, const ffw::vec3f& Pos, int RotA, int RotB, const blockInfoStruct* Block){
    for(uint32_t i = 0, p = Output->verticesCount; i < 5; i++, p++){
        ffw::vec3f v = cornerVertices[i] + ffw::vec3f(-0.5f, -0.5f, +0.5f);

        if(RotB == 0 && RotA == 3){

        } else if(RotB == 0 && RotA == 4){
            v.rotateX(180);
            v.rotateY(180);
        } else if(RotB == 0 && RotA == 5){
            v.rotateX(180);
            v.rotateY(90);
        } else if(RotB == 0 && RotA == 6){
            v.rotateX(180);
        } else if(RotB == 0 && RotA == 7){
            v.rotateX(180);
            v.rotateY(-90);
        } else if(RotB == 0 && RotA == 8){
            v.rotateX(90);
            v.rotateZ(180);
        } else if(RotB == 0 && RotA == 9){
            v.rotateX(90);
            v.rotateZ(90);
        } else if(RotB == 0 && RotA == 10){
            v.rotateX(90);
        } else if(RotB == 0 && RotA == 11){
            v.rotateX(90);
            v.rotateZ(270);
        } else if(RotB == 0 && RotA == 12){
            v.rotateX(-90);
            v.rotateZ(180);
        } else if(RotB == 0 && RotA == 13){
            v.rotateX(-90);
            v.rotateZ(90);
        } else if(RotB == 0 && RotA == 14){
            v.rotateX(-90);
        } else if(RotB == 0 && RotA == 15){
            v.rotateX(-90);
            v.rotateZ(270);
        } else if(RotB == 1 && RotA == 0){
            v.rotateZ(-90);
            v.rotateX(90);
        } else if(RotB == 1 && RotA == 1){
            v.rotateZ(-90);
            v.rotateX(180);
        } else if(RotB == 1 && RotA == 2){
            v.rotateZ(-90);
            v.rotateX(270);
        } else if(RotB == 1 && RotA == 3){
            v.rotateZ(-90);
        } else if(RotB == 1 && RotA == 4){
            v.rotateZ(90);
            v.rotateX(180);
        } else if(RotB == 1 && RotA == 5){
            v.rotateZ(90);
            v.rotateX(270);
        } else if(RotB == 1 && RotA == 6){
            v.rotateZ(90);
        } else if(RotB == 1 && RotA == 7){
            v.rotateZ(90);
            v.rotateX(90);
        } else if(RotB == 0 && RotA == 0){
            v.rotateY(270);
        } else if(RotB == 0 && RotA == 1){
            v.rotateY(180);
        } else if(RotB == 0 && RotA == 2){
            v.rotateY(90);
        } else {
            return;
        }

        Output->vertices[p] = v + Pos;
    }

    Output->verticesCount += 5;

    for(uint32_t i = 0, p = Output->indicesCount; i < 5; i++, p++){
        Output->indices[p] = cornerFaces[i]-1 + Output->indicesOffset;
        Output->indicesUvs[p] = cornerFacesUvs[i];

        if(cornerFaces[i].w == -1)Output->indices[p].w = -1;
        //chunkFacesMat[p] = ID;
        Output->indicesMat[p][0] = Block->id;
        Output->indicesMat[p][1] = Block->texture[0];
        Output->indicesMat[p][2] = Block->transparent;
    }

    Output->indicesOffset += 5;
    Output->indicesCount += 5;
}
