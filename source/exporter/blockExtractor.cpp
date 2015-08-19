/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "blockExtractor.h"
#include "blockConfig.h"
#include "materialExport.h"

//static uint64_t chunkFaceTotal = 0;
//static std::vector<ffw::vec2i> extractedMaterials;
//static std::vector<int> extractedTiles;

///=============================================================================
bool sm2obj::loadRawBlocks(const exportBlueprintArgs& Args, const std::string& TempFolder, chunkBufferStruct* Input, int FileIndex){
    ffw::file input;

    if(!input.open(TempFolder + "\\chunk-temp-processed-" + ffw::valToString(FileIndex) + ".raw", true, false, false)){
        Args.callbackLogError("Failed to load processed raw chunk data! Chunk index: " + ffw::valToString(FileIndex));
        return false;
    }

    input.read(&Input->verticesCount, sizeof(uint32_t));
    input.read(&Input->indicesCount, sizeof(uint32_t));

    for(uint32_t i = 0; i < Input->verticesCount; i++){
        input.read(&Input->vertices[i].x, sizeof(float));
        input.read(&Input->vertices[i].y, sizeof(float));
        input.read(&Input->vertices[i].z, sizeof(float));
    }

    for(uint32_t i = 0; i < Input->indicesCount; i++){
        input.read(&Input->indices[i].x, sizeof(int));
        input.read(&Input->indices[i].y, sizeof(int));
        input.read(&Input->indices[i].z, sizeof(int));
        input.read(&Input->indices[i].w, sizeof(int));
    }

    for(uint32_t i = 0; i < Input->indicesCount; i++){
        input.read(&Input->indicesUvs[i].x, sizeof(int));
        input.read(&Input->indicesUvs[i].y, sizeof(int));
        input.read(&Input->indicesUvs[i].z, sizeof(int));
        input.read(&Input->indicesUvs[i].w, sizeof(int));
    }

    for(uint32_t i = 0; i < Input->indicesCount; i++){
        input.read(&Input->indicesMat[i][0], sizeof(uint16_t));
        input.read(&Input->indicesMat[i][1], sizeof(uint16_t));
        input.read(&Input->indicesMat[i][2], sizeof(uint16_t));
    }

    return true;
}

///=============================================================================
bool sm2obj::saveRawBlocks(const exportBlueprintArgs& Args, const std::string& TempFolder, chunkBufferStruct* Input, int FileIndex){
    ffw::file output;

    if(!output.open(TempFolder + "\\chunk-temp-processed-" + ffw::valToString(FileIndex) + ".raw", true, true, true)){
        Args.callbackLogError("Failed to svae processed raw chunk data! Chunk index: " + ffw::valToString(FileIndex));
        return false;
    }

    output.write(&Input->verticesCount, sizeof(uint32_t));
    output.write(&Input->indicesCount, sizeof(uint32_t));

    for(uint32_t i = 0; i < Input->verticesCount; i++){
        output.write(&Input->vertices[i].x, sizeof(float));
        output.write(&Input->vertices[i].y, sizeof(float));
        output.write(&Input->vertices[i].z, sizeof(float));
    }

    for(uint32_t i = 0; i < Input->indicesCount; i++){
        output.write(&Input->indices[i].x, sizeof(int));
        output.write(&Input->indices[i].y, sizeof(int));
        output.write(&Input->indices[i].z, sizeof(int));
        output.write(&Input->indices[i].w, sizeof(int));
    }

    for(uint32_t i = 0; i < Input->indicesCount; i++){
        output.write(&Input->indicesUvs[i].x, sizeof(int));
        output.write(&Input->indicesUvs[i].y, sizeof(int));
        output.write(&Input->indicesUvs[i].z, sizeof(int));
        output.write(&Input->indicesUvs[i].w, sizeof(int));
    }

    for(uint32_t i = 0; i < Input->indicesCount; i++){
        output.write(&Input->indicesMat[i][0], sizeof(uint16_t));
        output.write(&Input->indicesMat[i][1], sizeof(uint16_t));
        output.write(&Input->indicesMat[i][2], sizeof(uint16_t));
    }

    return true;
}

///=============================================================================
bool sm2obj::extractBlocks(const exportBlueprintArgs& Args, const std::string& TempFolder, chunkBufferStruct* Input, int FileIndex, uint64_t* IndicesOffset, uint64_t* TexPosOffset){
    ffw::file vertices;
    ffw::file indices;

    if(!vertices.open(TempFolder + "\\chunk-temp-" + ffw::valToString(FileIndex) + ".vertices", false, true, true)){
        Args.callbackLogError("Failed to svae chunk vertices! Chunk index: " + ffw::valToString(FileIndex));
        return false;
    }

    if(!indices.open(TempFolder + "\\chunk-temp-" + ffw::valToString(FileIndex) + ".indices", false, true, true)){
        Args.callbackLogError("Failed to svae chunk indices! Chunk index: " + ffw::valToString(FileIndex));
        return false;
    }

    for(uint32_t i = 0; i < Input->verticesCount; i++){
        vertices.writeLine("v " + ffw::valToString(Input->vertices[i].x, 6) + " "
                                + ffw::valToString(Input->vertices[i].y, 6) + " "
                                + ffw::valToString(Input->vertices[i].z, 6));
    }

    vertices.close();

    int lastId = -1;
    int lastTex = -1;
    int lastAtlas = -1;
    int currentTextureOffset = 0;
    const blockInfoStruct* block = NULL;
    for(uint32_t i = 0; i < Input->indicesCount; i++){
        if(!Args.useAtlas && Args.exportMaterials && (lastId != Input->indicesMat[i][0] || lastTex != Input->indicesMat[i][1])){
            lastId = Input->indicesMat[i][0];
            lastTex = Input->indicesMat[i][1];
            block = findBlock(lastId);

            if(block != NULL){
                indices.writeLine("usemtl Mat_" + block->name + "_" + ffw::valToString(lastTex));

                bool found = false;
                for(const auto& item : Input->extractedMaterialsList){
                    if(item.x == lastId && item.y == lastTex){found = true; break;}
                }
                if(!found){
                    //addMaterial(block, lastTex);
                    Input->extractedMaterialsList.push_back(ffw::vec2i(lastId, lastTex));
                }

            } else {
                indices.writeLine("usemtl Mat_Unknown_" + ffw::valToString(Input->indicesMat[i][0]) + "_" + ffw::valToString(lastTex));
            }
        }


        if(Args.useAtlas && Args.exportMaterials && lastTex != Input->indicesMat[i][1]){
            lastTex = Input->indicesMat[i][1];

            if(lastAtlas != Input->indicesMat[i][1] / 256){
                lastAtlas = Input->indicesMat[i][1] / 256;
                indices.writeLine("usemtl Mat_Atlas_" + ffw::valToString(lastAtlas));
            }

            bool found = false;
            for(size_t f = 0; f < Input->extractedMaterialsList.size(); f++){
                if(Input->extractedMaterialsList[f].x == Input->indicesMat[i][1]){found = true; currentTextureOffset = f; break;}
            }
            if(!found){
                currentTextureOffset = Input->extractedMaterialsList.size();
                Input->extractedMaterialsList.push_back(ffw::vec2i(Input->indicesMat[i][1], -1));
            }
        }

        if(Args.exportUV){

            if(Input->indices[i].w == -1){
                indices.writeLine("f " + ffw::valToString(Input->indices[i].x + (*IndicesOffset) +1) + "/" + ffw::valToString(Input->indicesUvs[i].x + (*TexPosOffset) + currentTextureOffset*4) + " "
                                     + ffw::valToString(Input->indices[i].y + (*IndicesOffset) +1) + "/" + ffw::valToString(Input->indicesUvs[i].y + (*TexPosOffset) + currentTextureOffset*4) + " "
                                     + ffw::valToString(Input->indices[i].z + (*IndicesOffset) +1) + "/" + ffw::valToString(Input->indicesUvs[i].z + (*TexPosOffset) + currentTextureOffset*4));
            } else {
                indices.writeLine("f " + ffw::valToString(Input->indices[i].x + (*IndicesOffset) +1) + "/" + ffw::valToString(Input->indicesUvs[i].x + (*TexPosOffset) + currentTextureOffset*4) + " "
                                     + ffw::valToString(Input->indices[i].y + (*IndicesOffset) +1) + "/" + ffw::valToString(Input->indicesUvs[i].y + (*TexPosOffset) + currentTextureOffset*4) + " "
                                     + ffw::valToString(Input->indices[i].z + (*IndicesOffset) +1) + "/" + ffw::valToString(Input->indicesUvs[i].z + (*TexPosOffset) + currentTextureOffset*4) + " "
                                     + ffw::valToString(Input->indices[i].w + (*IndicesOffset) +1) + "/" + ffw::valToString(Input->indicesUvs[i].w + (*TexPosOffset) + currentTextureOffset*4));
            }

        } else {
            if(Input->indices[i].w == -1){
                indices.writeLine("f " + ffw::valToString(Input->indices[i].x + (*IndicesOffset) +1) + " "
                                     + ffw::valToString(Input->indices[i].y + (*IndicesOffset) +1) + " "
                                     + ffw::valToString(Input->indices[i].z + (*IndicesOffset) +1));
            } else {
                indices.writeLine("f " + ffw::valToString(Input->indices[i].x + (*IndicesOffset) +1) + " "
                                     + ffw::valToString(Input->indices[i].y + (*IndicesOffset) +1) + " "
                                     + ffw::valToString(Input->indices[i].z + (*IndicesOffset) +1) + " "
                                     + ffw::valToString(Input->indices[i].w + (*IndicesOffset) +1));
            }
        }
    }

    *IndicesOffset += Input->verticesCount;

    //if(SplitTextures)*TexPosOffset += 4;
    //else *TexPosOffset += currentTextureOffset;

    indices.close();

    return true;
}
