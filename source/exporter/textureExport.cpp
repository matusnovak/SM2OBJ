/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "textureExport.h"
#include "blockConfig.h"
#include <math.h>

static std::string textures[6] = {"t000.png", "t001.png", "t002.png", "t000_NRM.png", "t001_NRM.png", "t002_NRM.png"};

static bool loadBlocks(const std::string& InputConfigFolder){
    sm2obj::clearBlockConfig();
    // Load block types
    if(!sm2obj::loadBlockTypes(InputConfigFolder + "\\BlockTypes.properties")){
        TERMINATE(false);
    }

    // Load block config
    if(!sm2obj::loadBlockConfig(InputConfigFolder + "\\BlockConfig.xml")){
        TERMINATE(false);
    }
    return true;
}

///=============================================================================
static void extractAlpha(unsigned char* InputPixels, int InputWidth, int InputHeight, unsigned char* OutputPixels){
    for(int y = 0; y < InputHeight; y++){
        for(int x = 0; x < InputWidth; x++){
            OutputPixels[InputWidth*y +x] = InputPixels[InputWidth*y*4 + x*4 +3];
        }
    }
}

///=============================================================================
static void subsection(unsigned char* InputPixels, int InputWidth, int InputHeight, int OutputPosX, int OutputPosY, int InputChannels, unsigned char* OutputPixels, int OutputWidth, int OutputHeight){
    for(int y = 0, p = 0; y < InputHeight; y++){
        if(y >= OutputPosY && y < OutputPosY+OutputHeight){
            memcpy(&OutputPixels[OutputWidth*p*InputChannels], &InputPixels[InputWidth*(InputHeight - y -1)*InputChannels + OutputPosX*InputChannels], OutputWidth*InputChannels);
            p++;
        }
    }
}

///=============================================================================
static void convertNormalToBump(unsigned char* InputPixels, int InputWidth, int InputHeight, unsigned char* OutputPixels){
    ffw::vec3f n(0.0f, 0.0f, 1.0f);
    for(int y = 0; y < InputHeight; y++){
        for(int x = 0; x < InputWidth; x++){
            //OutputPixels[InputWidth*y +x] = InputPixels[InputWidth*y*3 + x*3 +0];
            ffw::vec3f norm(InputPixels[InputWidth*y*3 + x*3 +0] / 255.0f, InputPixels[InputWidth*y*3 + x*3 +1] / 255.0f, InputPixels[InputWidth*y*3 + x*3 +2] / 255.0f);

            float dot = ffw::dot(n, norm);
            dot = powf(dot, 20.0f);
            OutputPixels[InputWidth*y +x] = uint8_t(dot*255.0f);
        }
    }
}

///=============================================================================
bool sm2obj::exportEmissiveAtlas(const std::string& InputConfigFolder, const std::string& OutputFolder, int TileWidth){
    LOG_DEBUG("Exporting emissive atlas");

    if(!loadBlocks(InputConfigFolder))return false;

    int index = 0;
    unsigned char* pixels = new unsigned char[TileWidth*16*TileWidth*16*3];
    int width = TileWidth*16;

    for(int i = 0; i < 3; i++){

        for(int p = 0; p < TileWidth*16*TileWidth*16*3; p++)pixels[p] = 0;

        for(int y = 15; y >= 0; y--){
            for(int x = 0; x < 16; x++){
                const blockInfoStruct* block = findBlockByTexture(index);
                if(block != NULL && block->emissive){

                    for(int h = 0; h < TileWidth; h++){
                        for(int w = 0; w < TileWidth; w++){
                            pixels[width*(y*TileWidth+h)*3 + (x*TileWidth+w)*3 +0] = block->light.r * 255;
                            pixels[width*(y*TileWidth+h)*3 + (x*TileWidth+w)*3 +1] = block->light.g * 255;
                            pixels[width*(y*TileWidth+h)*3 + (x*TileWidth+w)*3 +2] = block->light.b * 255;
                        }
                    }

                }
                index++;
            }
        }

        if(!config::imageSaverFunc(OutputFolder + "\\Atlas_" + ffw::valToString(i) + "_emissive." + config::imageExtension, pixels, TileWidth*16, TileWidth*16, ffw::imageType::RGB_888)){
            LOG_ERROR("Failed to save texture: " + OutputFolder + "\\Atlas_" + ffw::valToString(i) + "_emissive." + config::imageExtension + " Program might not have permissions or target folder " + OutputFolder + " does not exists!");
            TERMINATE(false);
        }
    }

    delete[] pixels;
    return true;
}

///=============================================================================
bool sm2obj::exportAtlases(const std::string& InputFolder, const std::string& OutputFolder, bool ConvertNormals){
    int index = 0;

    LOG_DEBUG("Exporting textures from: " + InputFolder);

    int total = 6;
    int progress = 1;

    for(int i = 0; i < 6; i++){
        std::string tex = textures[i];
        if(i == 3)index = 0;
        unsigned char* pixels;
        int width;
        int height;
        int channels;
        ffw::imageType type;

        LOG_DEBUG("Reading file: " + InputFolder + "\\" + tex);

        if(!ffw::loadPNG(InputFolder + "\\" + tex, &pixels, &width, &height, &type)){
            LOG_ERROR("Failed to load texture: " + InputFolder + "\\" + tex);
            TERMINATE(false);
        }

        if(width != height){
            LOG_ERROR("Failed to load texture: " + InputFolder + "\\" + tex + " Texture must have same width and height!");
            TERMINATE(false);
        }

        if(!(width == 1024 || width == 2048 || width == 4096)){
            LOG_ERROR("Failed to load texture: " + InputFolder + "\\" + tex + " Wrong texture size! Must be either 1024, 2048, or 4096!");
            TERMINATE(false);
        }

        if(type == ffw::imageType::RGB_888)channels = 3;
        else if(type == ffw::imageType::RGB_ALPHA_8888)channels = 4;
        else {
            LOG_ERROR("Failed to load texture: " + InputFolder + "\\" + tex + " Wrong texture format! Must be either 8-bit RGB or 8-bit RGBA!");
            TERMINATE(false);
        }

        unsigned char* outputAlphaPixels = new unsigned char[width*height*1];
        unsigned char* outputBumpPixels = new unsigned char[width*height*1];

        bool isNormal = false;
        if(tex.find("_NRM") != std::string::npos){
            isNormal = true;
        }

        LOG_INFO("Processing texture: " + tex);

        PROGRESS(progress, total);

        // Diffuse
        if(!isNormal){
            if(!config::imageSaverFunc(OutputFolder + "\\Atlas_" + ffw::valToString(index) + "_diff." + config::imageExtension, pixels, width, height, type)){
                LOG_ERROR("Failed to save texture: " + OutputFolder + "\\Atlas_" + ffw::valToString(index) + "_diff." + config::imageExtension + " Program might not have permissions or target folder " + OutputFolder + " does not exists!");
                TERMINATE(false);
            }
        }

        // Alpha
        if(!isNormal && type == ffw::imageType::RGB_ALPHA_8888){
            extractAlpha(pixels, width, height, outputAlphaPixels);

            if(!config::imageSaverFunc(OutputFolder + "\\Atlas_" + ffw::valToString(index) + "_alpha." + config::imageExtension, outputAlphaPixels, width, height, ffw::imageType::GRAYSCALE_8)){
                LOG_ERROR("Failed to save texture: " + OutputFolder + "\\Atlas_" + ffw::valToString(index) + "_alpha." + config::imageExtension + " Program might not have permissions or target folder " + OutputFolder + " does not exists!");
                TERMINATE(false);
            }

        // Alpha alternative
        } else if(!isNormal){
            for(int p = 0; p < width*height*1; p++)outputAlphaPixels[p] = 255;

            if(!config::imageSaverFunc(OutputFolder + "\\Atlas_" + ffw::valToString(index) + "_alpha." + config::imageExtension, outputAlphaPixels, width, height, ffw::imageType::GRAYSCALE_8)){
                LOG_ERROR("Failed to save texture: " + OutputFolder + "\\Atlas_" + ffw::valToString(index) + "_alpha." + config::imageExtension + " Program might not have permissions or target folder " + OutputFolder + " does not exists!");
                TERMINATE(false);
            }
        }

        // Normals
        if(isNormal && !ConvertNormals){
            if(!config::imageSaverFunc(OutputFolder + "\\Atlas_" + ffw::valToString(index) + "_bump." + config::imageExtension, pixels, width, height, type)){
                LOG_ERROR("Failed to save texture: " + OutputFolder + "\\Atlas_" + ffw::valToString(index) + "_bump." + config::imageExtension + " Program might not have permissions or target folder " + OutputFolder + " does not exists!");
                TERMINATE(false);
            }
        }

        // Bump
        if(isNormal && ConvertNormals){
            convertNormalToBump(pixels, width, height, outputBumpPixels);

            if(!config::imageSaverFunc(OutputFolder + "\\Atlas_" + ffw::valToString(index) + "_bump." + config::imageExtension, outputBumpPixels, width, height, ffw::imageType::GRAYSCALE_8)){
                LOG_ERROR("Failed to save texture: " + OutputFolder + "\\Atlas_" + ffw::valToString(index) + "_bump." + config::imageExtension + " Program might not have permissions or target folder " + OutputFolder + " does not exists!");
                TERMINATE(false);
            }
        }

        index++;
        progress++;

        delete[] pixels;
        delete[] outputAlphaPixels;
        delete[] outputBumpPixels;
    }

    TERMINATE(true);
    return true;
}

///=============================================================================
bool sm2obj::exportTextures(const std::string& InputFolder, const std::string& OutputFolder, bool ConvertNormals){
    int index = 0;

    LOG_DEBUG("Exporting textures from: " + InputFolder);

    int total = 16*16*6;
    int progress = 1;

    for(int i = 0; i < 6; i++){
        std::string tex = textures[i];
        if(i == 3)index = 0;
        unsigned char* pixels;
        int width;
        int height;
        int channels;
        ffw::imageType type;

        LOG_DEBUG("Reading file: " + InputFolder + "\\" + tex);

        if(!ffw::loadPNG(InputFolder + "\\" + tex, &pixels, &width, &height, &type)){
            LOG_ERROR("Failed to load texture: " + InputFolder + "\\" + tex);
            TERMINATE(false);
        }

        if(width != height){
            LOG_ERROR("Failed to load texture: " + InputFolder + "\\" + tex + " Texture must have same width and height!");
            TERMINATE(false);
        }

        if(!(width == 1024 || width == 2048 || width == 4096)){
            LOG_ERROR("Failed to load texture: " + InputFolder + "\\" + tex + " Wrong texture size! Must be either 1024, 2048, or 4096!");
            TERMINATE(false);
        }

        if(type == ffw::imageType::RGB_888)channels = 3;
        else if(type == ffw::imageType::RGB_ALPHA_8888)channels = 4;
        else {
            LOG_ERROR("Failed to load texture: " + InputFolder + "\\" + tex + " Wrong texture format! Must be either 8-bit RGB or 8-bit RGBA!");
            TERMINATE(false);
        }

        int bleeding = (width / 16)*0.15625f;

        int splitSize = (width / 16) - bleeding;
        LOG_DEBUG("Splitting texture to: " + ffw::valToString(splitSize) + "x" + ffw::valToString(splitSize) + " chunks");

        unsigned char* outputDiffusePixels = new unsigned char[splitSize*splitSize*channels];
        unsigned char* outputAlphaPixels = new unsigned char[splitSize*splitSize*1];
        unsigned char* outputBumpPixels = new unsigned char[splitSize*splitSize*1];

        bool isNormal = false;
        if(tex.find("_NRM") != std::string::npos){
            isNormal = true;
        }

        LOG_INFO("Processing texture: " + tex);

        for(int y = 0; y < height; y += (width / 16)){
            for(int x = 0; x < width; x += (width / 16)){
                PROGRESS(progress, total);

                subsection(pixels, width, height, x + bleeding/2, y + bleeding/2, channels, outputDiffusePixels, splitSize, splitSize);

                // Diffuse
                if(!isNormal){
                    if(!config::imageSaverFunc(OutputFolder + "\\Tex_" + ffw::valToString(index) + "_diff." + config::imageExtension, outputDiffusePixels, splitSize, splitSize, type)){
                        LOG_ERROR("Failed to save texture: " + OutputFolder + "\\Tex_" + ffw::valToString(index) + "_diff." + config::imageExtension + " Program might not have permissions or target folder " + OutputFolder + " does not exists!");
                        TERMINATE(false);
                    }
                }

                // Alpha
                if(!isNormal && type == ffw::imageType::RGB_ALPHA_8888){
                    extractAlpha(outputDiffusePixels, splitSize, splitSize, outputAlphaPixels);

                    if(!config::imageSaverFunc(OutputFolder + "\\Tex_" + ffw::valToString(index) + "_alpha." + config::imageExtension, outputAlphaPixels, splitSize, splitSize, ffw::imageType::GRAYSCALE_8)){
                        LOG_ERROR("Failed to save texture: " + OutputFolder + "\\Tex_" + ffw::valToString(index) + "_alpha." + config::imageExtension + " Program might not have permissions or target folder " + OutputFolder + " does not exists!");
                        TERMINATE(false);
                    }
                }

                // Alpha alternative
                if(!isNormal && type == ffw::imageType::RGB_ALPHA_8888){
                    for(int p = 0; p < splitSize*splitSize*1; p++)outputAlphaPixels[p] = 255;

                    if(!config::imageSaverFunc(OutputFolder + "\\Tex_" + ffw::valToString(index) + "_alpha." + config::imageExtension, outputAlphaPixels, splitSize, splitSize, ffw::imageType::GRAYSCALE_8)){
                        LOG_ERROR("Failed to save texture: " + OutputFolder + "\\Tex_" + ffw::valToString(index) + "_alpha." + config::imageExtension + " Program might not have permissions or target folder " + OutputFolder + " does not exists!");
                        TERMINATE(false);
                    }
                }

                // Normals
                if(isNormal && !ConvertNormals){
                    if(!config::imageSaverFunc(OutputFolder + "\\Tex_" + ffw::valToString(index) + "_bump." + config::imageExtension, outputDiffusePixels, splitSize, splitSize, type)){
                        LOG_ERROR("Failed to save texture: " + OutputFolder + "\\Tex_" + ffw::valToString(index) + "_bump." + config::imageExtension + " Program might not have permissions or target folder " + OutputFolder + " does not exists!");
                        TERMINATE(false);
                    }
                }

                // Bump
                if(isNormal && ConvertNormals){
                    convertNormalToBump(outputDiffusePixels, splitSize, splitSize, outputBumpPixels);

                    if(!config::imageSaverFunc(OutputFolder + "\\Tex_" + ffw::valToString(index) + "_bump." + config::imageExtension, outputBumpPixels, splitSize, splitSize, ffw::imageType::GRAYSCALE_8)){
                        LOG_ERROR("Failed to save texture: " + OutputFolder + "\\Tex_" + ffw::valToString(index) + "_bump." + config::imageExtension + " Program might not have permissions or target folder " + OutputFolder + " does not exists!");
                        TERMINATE(false);
                    }
                }

                index++;
                progress++;
            }
        }

        delete[] outputDiffusePixels;
        delete[] outputAlphaPixels;
        delete[] outputBumpPixels;
        delete[] pixels;
    }
    TERMINATE(true);
    return true;
}
