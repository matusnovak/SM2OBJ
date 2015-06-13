/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#include "blockExtractor.h"
#include "blockConfig.h"
#include "materialExport.h"

static uint64_t chunkFaceTotal = 0;
static std::vector<ffw::vec2i> extractedMaterials;
static std::vector<int> extractedTiles;

///=============================================================================
void resetIndiceOffset(){
    chunkFaceTotal = 0;
}

///=============================================================================
void resetMaterials(){
    extractedMaterials.clear();
    extractedTiles.clear();
}

///=============================================================================
const std::vector<int>& getExtractedTiles(){
    return extractedTiles;
}

///=============================================================================
bool loadRawBlocks(const std::string& ExecutablePath, chunkBufferStruct* Input, int ChunkIndex, int FileIndex){
    ffw::file input;

    if(!input.open(ExecutablePath + "\\temp\\" + ffw::valToString(FileIndex) + "_" + ffw::valToString(ChunkIndex) + ".raw.data", true, false, false)){
        ffw::logger().error() << "Error loading raw chunk data! Chunk index: " << ChunkIndex << " file index: " << FileIndex;
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
bool saveRawBlocks(const std::string& ExecutablePath, chunkBufferStruct* Input, int ChunkIndex, int FileIndex){
    ffw::file output;

    if(!output.open(ExecutablePath + "\\temp\\" + ffw::valToString(FileIndex) + "_" + ffw::valToString(ChunkIndex) + ".raw.data", true, true, true)){
        ffw::logger().error() << "Error saving raw chunk data! Chunk index: " << ChunkIndex << " file index: " << FileIndex;
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
bool extractBlocks(const std::string& ExecutablePath, chunkBufferStruct* Input, int ChunkIndex, int FileIndex){
    ffw::file vertices;
    ffw::file faces;

    if(!vertices.open(ExecutablePath + "\\temp\\" + ffw::valToString(FileIndex) + "_" + ffw::valToString(ChunkIndex) + ".vertices.data", false, true, true)){
        ffw::logger().error() << "Error saving vertices chunk data! Chunk index: " << ChunkIndex << " file index: " << FileIndex;
        return false;
    }

    if(!faces.open(ExecutablePath + "\\temp\\" + ffw::valToString(FileIndex) + "_" + ffw::valToString(ChunkIndex) + ".faces.data", false, true, true)){
        ffw::logger().error() << "Error saving polygons chunk data! Chunk index: " << ChunkIndex << " file index: " << FileIndex;
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
        if(textureSplit && materialExport && (lastId != Input->indicesMat[i][0] || lastTex != Input->indicesMat[i][1])){
            lastId = Input->indicesMat[i][0];
            lastTex = Input->indicesMat[i][1];
            block = findBlock(lastId);

            if(block != NULL){
                faces.writeLine("usemtl Mat_" + block->name + "_" + ffw::valToString(lastTex));

                bool found = false;
                for(const auto& item : extractedMaterials){
                    if(item.x == lastId && item.y == lastTex){found = true; break;}
                }
                if(!found){
                    addMaterial(block, lastTex);
                    extractedMaterials.push_back(ffw::vec2i(lastId, lastTex));
                }

            } else {
                faces.writeLine("usemtl Mat_Unknown_" + ffw::valToString(Input->indicesMat[i][0]) + "_" + ffw::valToString(lastTex));
            }
        }


        if(!textureSplit && materialExport && lastTex != Input->indicesMat[i][1]){
            lastTex = Input->indicesMat[i][1];

            if(lastAtlas != Input->indicesMat[i][1] / 256){
                lastAtlas = Input->indicesMat[i][1] / 256;
                faces.writeLine("usemtl Mat_Atlas_" + ffw::valToString(lastAtlas));
            }

            bool found = false;
            for(size_t f = 0; f < extractedTiles.size(); f++){
                if(extractedTiles[f] == Input->indicesMat[i][1]){found = true; currentTextureOffset = f; break;}
            }
            if(!found){
                currentTextureOffset = extractedTiles.size();
                extractedTiles.push_back(Input->indicesMat[i][1]);
            }
        }

        if(uvsExport){

            if(Input->indices[i].w == -1){
                faces.writeLine("f " + ffw::valToString(Input->indices[i].x + chunkFaceTotal +1) + "/" + ffw::valToString(Input->indicesUvs[i].x + currentTextureOffset*4) + " "
                                     + ffw::valToString(Input->indices[i].y + chunkFaceTotal +1) + "/" + ffw::valToString(Input->indicesUvs[i].y + currentTextureOffset*4) + " "
                                     + ffw::valToString(Input->indices[i].z + chunkFaceTotal +1) + "/" + ffw::valToString(Input->indicesUvs[i].z + currentTextureOffset*4));
            } else {
                faces.writeLine("f " + ffw::valToString(Input->indices[i].x + chunkFaceTotal +1) + "/" + ffw::valToString(Input->indicesUvs[i].x + currentTextureOffset*4) + " "
                                     + ffw::valToString(Input->indices[i].y + chunkFaceTotal +1) + "/" + ffw::valToString(Input->indicesUvs[i].y + currentTextureOffset*4) + " "
                                     + ffw::valToString(Input->indices[i].z + chunkFaceTotal +1) + "/" + ffw::valToString(Input->indicesUvs[i].z + currentTextureOffset*4) + " "
                                     + ffw::valToString(Input->indices[i].w + chunkFaceTotal +1) + "/" + ffw::valToString(Input->indicesUvs[i].w + currentTextureOffset*4));
            }

        } else {
            if(Input->indices[i].w == -1){
                faces.writeLine("f " + ffw::valToString(Input->indices[i].x + chunkFaceTotal +1) + " "
                                     + ffw::valToString(Input->indices[i].y + chunkFaceTotal +1) + " "
                                     + ffw::valToString(Input->indices[i].z + chunkFaceTotal +1));
            } else {
                faces.writeLine("f " + ffw::valToString(Input->indices[i].x + chunkFaceTotal +1) + " "
                                     + ffw::valToString(Input->indices[i].y + chunkFaceTotal +1) + " "
                                     + ffw::valToString(Input->indices[i].z + chunkFaceTotal +1) + " "
                                     + ffw::valToString(Input->indices[i].w + chunkFaceTotal +1));
            }
        }
    }

    chunkFaceTotal += Input->verticesCount;

    faces.close();

    return true;
}
