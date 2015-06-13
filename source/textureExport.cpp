/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#include "textureExport.h"
#include "blockConfig.h"
#include <math.h>

static std::string textures[6] = {"t000.png", "t001.png", "t002.png", "t000_NRM.png", "t001_NRM.png", "t002_NRM.png"};

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
bool exportAtlases(const std::string& FolderPath){
    int index = 0;

    for(int i = 0; i < 6; i++){
        std::string tex = textures[i];
        unsigned char* pixels;
        if(i == 3)index = 0;
        int width;
        int height;
        ffw::imageType type;

        ffw::logger().print() << "Reading file: " << tex;

        if(!ffw::loadPNG(FolderPath + "\\" + tex, &pixels, &width, &height, &type)){
            ffw::logger().error() << "Failed to load texture: " << tex;
            return 0;
        }

        if(width != height){
            ffw::logger().error() << "Failed to load texture: " << tex << " Texture must have same width and height!";
            return 0;
        }

        if(!(width == 1024 || width == 2048 || width == 4096)){
            ffw::logger().error() << "Failed to load texture: " << tex << " Wrong texture size! Must be either 1024, 2048, or 4096!";
            return 0;
        }

        if(!(type == ffw::imageType::RGB_888 || type == ffw::imageType::RGB_ALPHA_8888)){
            ffw::logger().error() << "Failed to load texture: " << tex << " Wrong texture format! Must be either 8-bit RGB or 8-bit RGBA!";
            return 0;
        }

        bool isNormal = false;
        if(tex.find("_NRM") != std::string::npos){
            isNormal = true;
        }

        unsigned char* outputPixelsAlpha = NULL;
        unsigned char* outputNormals = NULL;

        if(!isNormal){
            outputPixelsAlpha = new unsigned char[width*height*1];
        } else {
            outputNormals = new unsigned char[width*height*1];
        }

        if(isNormal){
            // Export bump map from normal map
            convertNormalToBump(pixels, width, height, outputNormals);

            if(!imageSaver(fileOutputFolder + "\\atlases\\Atlas_" + ffw::valToString(index) + "_bump." + imageExtension, outputNormals, width, height, ffw::imageType::GRAYSCALE_8)){
                ffw::logger().error() << "Failed to save output texture: " << index << " Program might not have permissions or target folder " << fileOutputFolder << "\\atlases\\ does not exists!";
                return 0;
            }
        } else {

            // Export diffuse
            if(!imageSaver(fileOutputFolder + "\\atlases\\Atlas_" + ffw::valToString(index) + "_diff." + imageExtension, pixels, width, height, type)){
                ffw::logger().error() << "Failed to save output texture: " << index << " Program might not have permissions or target folder " << fileOutputFolder << "\\atlases\\ does not exists!";
                return 0;
            }
            // Export alpha
            if(!isNormal){
                if(type == ffw::imageType::RGB_ALPHA_8888){
                    extractAlpha(pixels, width, height, outputPixelsAlpha);

                } else {
                    // Texture is not transparent, fill all pixels with white color
                    for(int p = 0; p < width*height; p++)outputPixelsAlpha[p] = 255;
                }

                if(!imageSaver(fileOutputFolder + "\\atlases\\Atlas_" + ffw::valToString(index) + "_alpha." + imageExtension, outputPixelsAlpha, width, height, ffw::imageType::GRAYSCALE_8)){
                    ffw::logger().error() << "Failed to save output texture: " << index << " Program might not have permissions or target folder " << fileOutputFolder << "\\atlases\\ does not exists!";
                    return 0;
                }
            }
        }

        index++;

        if(!isNormal && type == ffw::imageType::RGB_ALPHA_8888)delete[] outputPixelsAlpha;
        if(isNormal)delete[] outputNormals;
    }
    return true;
}

///=============================================================================
bool exportTextures(const std::string& FolderPath){
    int index = 0;

    ffw::logger().print() << "Exporting textures from: " << FolderPath;

    for(int i = 0; i < 6; i++){
        std::string tex = textures[i];
        if(i == 3)index = 0;
        unsigned char* pixels;
        int width;
        int height;
        int channels;
        ffw::imageType type;

        ffw::logger().print() << "Reading file: " << tex;

        if(!ffw::loadPNG(FolderPath + "\\" + tex, &pixels, &width, &height, &type)){
            ffw::logger().error() << "Failed to load texture: " << tex;
            return 0;
        }

        if(width != height){
            ffw::logger().error() << "Failed to load texture: " << tex << " Texture must have same width and height!";
            return 0;
        }

        if(!(width == 1024 || width == 2048 || width == 4096)){
            ffw::logger().error() << "Failed to load texture: " << tex << " Wrong texture size! Must be either 1024, 2048, or 4096!";
            return 0;
        }

        if(type == ffw::imageType::RGB_888)channels = 3;
        else if(type == ffw::imageType::RGB_ALPHA_8888)channels = 4;
        else {
            ffw::logger().error() << "Failed to load texture: " << tex << " Wrong texture format! Must be either 8-bit RGB or 8-bit RGBA!";
            return 0;
        }

        int bleeding = (width / 16)*0.15625f;

        int splitSize = (width / 16) - bleeding;

        ffw::logger().print() << "Splitting texture to: " << splitSize << "x" << splitSize << " chunks!";

        unsigned char* outputPixels = new unsigned char[splitSize*splitSize*channels];
        unsigned char* outputPixelsAlpha = NULL;
        unsigned char* outputNormals = NULL;

        bool isNormal = false;
        if(tex.find("_NRM") != std::string::npos){
            isNormal = true;
        }

        if(!isNormal && type == ffw::imageType::RGB_ALPHA_8888){
            outputPixelsAlpha = new unsigned char[splitSize*splitSize*1];
        }
        if(isNormal){
            outputNormals = new unsigned char[splitSize*splitSize*1];
        }

        for(int y = 0; y < height; y += (width / 16)){
            for(int x = 0; x < width; x += (width / 16)){
                subsection(pixels, width, height, x + bleeding/2, y + bleeding/2, channels, outputPixels, splitSize, splitSize);

                if(isNormal){
                    // Export bump map from normal map
                    convertNormalToBump(outputPixels, splitSize, splitSize, outputNormals);
                    if(!imageSaver(fileOutputFolder + "\\textures\\Tex_" + ffw::valToString(index) + "_bump." + imageExtension, outputNormals, splitSize, splitSize, ffw::imageType::GRAYSCALE_8)){
                        ffw::logger().error() << "Failed to save output texture: " << index << " Program might not have permissions or target folder " << fileOutputFolder << "\\textures\\ does not exists!";
                        return 0;
                    }
                } else {

                    // Export diffuse
                    if(!imageSaver(fileOutputFolder + "\\textures\\Tex_" + ffw::valToString(index) + "_diff." + imageExtension, outputPixels, splitSize, splitSize, type)){
                        ffw::logger().error() << "Failed to save output texture: " << index << " Program might not have permissions or target folder " << fileOutputFolder << "\\textures\\ does not exists!";
                        return 0;
                    }

                    // Export alpha
                    if(!isNormal && type == ffw::imageType::RGB_ALPHA_8888){
                        extractAlpha(outputPixels, splitSize, splitSize, outputPixelsAlpha);

                        if(!imageSaver(fileOutputFolder + "\\textures\\Tex_" + ffw::valToString(index) + "_alpha." + imageExtension, outputPixelsAlpha, splitSize, splitSize, ffw::imageType::GRAYSCALE_8)){
                            ffw::logger().error() << "Failed to save output texture: " << index << " Program might not have permissions or target folder " << fileOutputFolder << "\\textures\\ does not exists!";
                            return 0;
                        }
                    }
                }

                index++;
            }
        }

        if(!isNormal && type == ffw::imageType::RGB_ALPHA_8888)delete[] outputPixelsAlpha;
        if(isNormal)delete[] outputNormals;
        delete[] outputPixels;
    }
    return true;
}
