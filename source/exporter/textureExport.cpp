/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "textureExport.h"
#include "blockConfig.h"
#include <math.h>

static bool loadBlocks(const sm2obj::exportBlueprintArgs& Args){
    sm2obj::clearBlockConfig();
    // Load block types
    if(!sm2obj::loadBlockTypes(Args, Args.inputConfigFolder + "\\BlockTypes.properties")){
        return false;
    }

    // Load block config
    if(!sm2obj::loadBlockConfig(Args, Args.inputConfigFolder + "\\BlockConfig.xml")){
        return false;
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
bool sm2obj::exportEmissiveAtlas(const exportBlueprintArgs& Args){
    Args.callbackLogDebug("Exporting emissive atlas");

    if(!loadBlocks(Args))return false;

    int index = 0;
    unsigned char* pixels = new unsigned char[Args.width*16*Args.width*16*3];
    int width = Args.width*16;

    for(int i = 0; i < 3; i++){

        for(int p = 0; p < Args.width*16*Args.width*16*3; p++)pixels[p] = 0;

        for(int y = 15; y >= 0; y--){
            for(int x = 0; x < 16; x++){
                const blockInfoStruct* block = findBlockByTexture(index);
                if(block != NULL && block->emissive){

                    for(int h = 0; h < Args.width; h++){
                        for(int w = 0; w < Args.width; w++){
                            pixels[width*(y*Args.width+h)*3 + (x*Args.width+w)*3 +0] = char(block->light.r * 255);
                            pixels[width*(y*Args.width+h)*3 + (x*Args.width+w)*3 +1] = char(block->light.g * 255);
                            pixels[width*(y*Args.width+h)*3 + (x*Args.width+w)*3 +2] = char(block->light.b * 255);
                        }
                    }

                }
                index++;
            }
        }

		std::string outputFile = Args.outputFolder + "\\Atlas_" + ffw::valToString(i) + "_emissive." + Args.textureExtension;
        if(!Args.imageSaver(outputFile, pixels, Args.width*16, Args.width*16, ffw::imageType::RGB_888)){
            Args.callbackLogError("Failed to save texture: " + outputFile + " Program might not have permissions or target folder " + Args.outputFolder + " does not exists!");
            Args.callbackTerminate(false);
            return false;
        }
    }

    delete[] pixels;
    return true;
}

///=============================================================================
bool sm2obj::exportAtlases(const exportBlueprintArgs& Args){
    int index = 0;
    Args.callbackLogDebug("Exporting textures from: " + Args.inputFolder);

    int total = 6;
    int progress = 1;

	std::string textures[6] = {"t000.png", "t001.png", "t002.png", "t000_NRM.png", "t001_NRM.png", "t002_NRM.png"};
    for(int i = 0; i < 6; i++){
        std::string tex = textures[i];
        if(i == 3)index = 0;
        unsigned char* pixels;
        int width;
        int height;
        int channels;
        ffw::imageType type;
		ffw::logger().info() << "Texture: " << tex;

        Args.callbackLogDebug("Reading file: " + Args.inputFolder + "\\" + tex);

        if(!ffw::loadPNG(Args.inputFolder + "\\" + tex, &pixels, &width, &height, &type)){
            Args.callbackLogError("Failed to load texture: " + Args.inputFolder + "\\" + tex);
            Args.callbackTerminate(false);  return false;
        }

        if(width != height){
            Args.callbackLogError("Failed to load texture: " + Args.inputFolder + "\\" + tex + " Texture must have same width and height!");
            Args.callbackTerminate(false);  return false;
        }

        if(!(width == 1024 || width == 2048 || width == 4096)){
            Args.callbackLogError("Failed to load texture: " + Args.inputFolder + "\\" + tex + " Wrong texture size! Must be either 1024, 2048, or 4096!");
            Args.callbackTerminate(false);  return false;
        }

        if(type == ffw::imageType::RGB_888)channels = 3;
        else if(type == ffw::imageType::RGB_ALPHA_8888)channels = 4;
        else {
            Args.callbackLogError("Failed to load texture: " + Args.inputFolder + "\\" + tex + " Wrong texture format! Must be either 8-bit RGB or 8-bit RGBA!");
            Args.callbackTerminate(false);  return false;
        }

        unsigned char* outputAlphaPixels = new unsigned char[width*height*1];
        unsigned char* outputBumpPixels = new unsigned char[width*height*1];

        bool isNormal = false;
        if(tex.find("_NRM") != std::string::npos){
            isNormal = true;
        }

        Args.callbackLogInfo("Processing texture: " + tex);

        Args.callbackProgress(progress, total);

        // Diffuse
        if(!isNormal){
            std::string outputFile = Args.outputFolder + "\\Atlas_" + ffw::valToString(index) + "_diff." + Args.textureExtension;
			if(!Args.imageSaver(outputFile, pixels, width, height, type)){
                Args.callbackLogError("Failed to save texture: " + outputFile + " Program might not have permissions or target folder " + Args.outputFolder + " does not exists!");
                Args.callbackTerminate(false);  return false;
            }
        }

        // Alpha
        if(!isNormal && type == ffw::imageType::RGB_ALPHA_8888){
            extractAlpha(pixels, width, height, outputAlphaPixels);

			std::string outputFile = Args.outputFolder + "\\Atlas_" + ffw::valToString(index) + "_alpha." + Args.textureExtension;
            if(!Args.imageSaver(outputFile, outputAlphaPixels, width, height, ffw::imageType::GRAYSCALE_8)){
                Args.callbackLogError("Failed to save texture: " + outputFile + " Program might not have permissions or target folder " + Args.outputFolder + " does not exists!");
                Args.callbackTerminate(false);  return false;
            }

        // Alpha alternative
        } else if(!isNormal){
            for(int p = 0; p < width*height*1; p++)outputAlphaPixels[p] = 255;

			std::string outputFile = Args.outputFolder + "\\Atlas_" + ffw::valToString(index) + "_alpha." + Args.textureExtension;
            if(!Args.imageSaver(outputFile, outputAlphaPixels, width, height, ffw::imageType::GRAYSCALE_8)){
                Args.callbackLogError("Failed to save texture: " + outputFile + " Program might not have permissions or target folder " + Args.outputFolder + " does not exists!");
                Args.callbackTerminate(false);  return false;
            }
        }

        // Normals
        if(isNormal && !Args.normalToBump){

			std::string outputFile = Args.outputFolder + "\\Atlas_" + ffw::valToString(index) + "_bump." + Args.textureExtension;
			if(!Args.imageSaver(outputFile, pixels, width, height, type)){
                Args.callbackLogError("Failed to save texture: " + outputFile + " Program might not have permissions or target folder " + Args.outputFolder + " does not exists!");
                Args.callbackTerminate(false);  return false;
            }
        }

        // Bump
        if(isNormal && Args.normalToBump){
            convertNormalToBump(pixels, width, height, outputBumpPixels);

			std::string outputFile = Args.outputFolder + "\\Atlas_" + ffw::valToString(index) + "_bump." + Args.textureExtension;
            if(!Args.imageSaver(outputFile, outputBumpPixels, width, height, ffw::imageType::GRAYSCALE_8)){
                Args.callbackLogError("Failed to save texture: " + outputFile + " Program might not have permissions or target folder " + Args.outputFolder + " does not exists!");
                Args.callbackTerminate(false);  return false;
            }
        }

        index++;
        progress++;

        delete[] pixels;
        delete[] outputAlphaPixels;
        delete[] outputBumpPixels;
    }

    Args.callbackTerminate(true);
    return true;
}

///=============================================================================
bool sm2obj::exportTextures(const exportBlueprintArgs& Args){
    int index = 0;

    Args.callbackLogDebug("Exporting textures from: " + Args.inputFolder);

    int total = 16*16*6;
    int progress = 1;

	std::string textures[6] = {"t000.png", "t001.png", "t002.png", "t000_NRM.png", "t001_NRM.png", "t002_NRM.png"};
    for(int i = 0; i < 6; i++){
        std::string tex = textures[i];
        if(i == 3)index = 0;
        unsigned char* pixels;
        int width;
        int height;
        int channels;
        ffw::imageType type;

        Args.callbackLogDebug("Reading file: " + Args.inputFolder + "\\" + tex);

        if(!ffw::loadPNG(Args.inputFolder + "\\" + tex, &pixels, &width, &height, &type)){
            Args.callbackLogError("Failed to load texture: " + Args.inputFolder + "\\" + tex);
            Args.callbackTerminate(false);  return false;
        }

        if(width != height){
            Args.callbackLogError("Failed to load texture: " + Args.inputFolder + "\\" + tex + " Texture must have same width and height!");
            Args.callbackTerminate(false);  return false;
        }

        if(!(width == 1024 || width == 2048 || width == 4096)){
            Args.callbackLogError("Failed to load texture: " + Args.inputFolder + "\\" + tex + " Wrong texture size! Must be either 1024, 2048, or 4096!");
            Args.callbackTerminate(false);  return false;
        }

        if(type == ffw::imageType::RGB_888)channels = 3;
        else if(type == ffw::imageType::RGB_ALPHA_8888)channels = 4;
        else {
            Args.callbackLogError("Failed to load texture: " + Args.inputFolder + "\\" + tex + " Wrong texture format! Must be either 8-bit RGB or 8-bit RGBA!");
            Args.callbackTerminate(false);  return false;
        }

        int bleeding = int((width / 16)*0.15625f);

        int splitSize = (width / 16) - bleeding;
        Args.callbackLogDebug("Splitting texture to: " + ffw::valToString(splitSize) + "x" + ffw::valToString(splitSize) + " chunks");

        unsigned char* outputDiffusePixels = new unsigned char[splitSize*splitSize*channels];
        unsigned char* outputAlphaPixels = new unsigned char[splitSize*splitSize*1];
        unsigned char* outputBumpPixels = new unsigned char[splitSize*splitSize*1];

        bool isNormal = false;
        if(tex.find("_NRM") != std::string::npos){
            isNormal = true;
        }

        Args.callbackLogInfo("Processing texture: " + tex);

        for(int y = 0; y < height; y += (width / 16)){
            for(int x = 0; x < width; x += (width / 16)){
                Args.callbackProgress(progress, total);

                subsection(pixels, width, height, x + bleeding/2, y + bleeding/2, channels, outputDiffusePixels, splitSize, splitSize);

                // Diffuse
                if(!isNormal){
                    std::string outputFile = Args.outputFolder + "\\Tex_" + ffw::valToString(index) + "_diff." + Args.textureExtension;
					if(!Args.imageSaver(outputFile, outputDiffusePixels, splitSize, splitSize, type)){
                        Args.callbackLogError("Failed to save texture: " + outputFile + " Program might not have permissions or target folder " + Args.outputFolder + " does not exists!");
                        Args.callbackTerminate(false);  return false;
                    }
                }

                // Alpha
                if(!isNormal && type == ffw::imageType::RGB_ALPHA_8888){
                    extractAlpha(outputDiffusePixels, splitSize, splitSize, outputAlphaPixels);

					std::string outputFile = Args.outputFolder + "\\Tex_" + ffw::valToString(index) + "_alpha." + Args.textureExtension;
                    if(!Args.imageSaver(outputFile, outputAlphaPixels, splitSize, splitSize, ffw::imageType::GRAYSCALE_8)){
                        Args.callbackLogError("Failed to save texture: " + outputFile + " Program might not have permissions or target folder " + Args.outputFolder + " does not exists!");
                        Args.callbackTerminate(false);  return false;
                    }
                }

                // Alpha alternative
                if(!isNormal && type == ffw::imageType::RGB_ALPHA_8888){
                    for(int p = 0; p < splitSize*splitSize*1; p++)outputAlphaPixels[p] = 255;

					std::string outputFile = Args.outputFolder + "\\Tex_" + ffw::valToString(index) + "_alpha." + Args.textureExtension;
                    if(!Args.imageSaver(outputFile, outputAlphaPixels, splitSize, splitSize, ffw::imageType::GRAYSCALE_8)){
                        Args.callbackLogError("Failed to save texture: " + outputFile + " Program might not have permissions or target folder " + Args.outputFolder + " does not exists!");
                        Args.callbackTerminate(false);  return false;
                    }
                }

                // Normals
                if(isNormal && !Args.normalToBump){

					std::string outputFile = Args.outputFolder + "\\Tex_" + ffw::valToString(index) + "_bump." + Args.textureExtension;
					if(!Args.imageSaver(outputFile, outputDiffusePixels, splitSize, splitSize, type)){
                        Args.callbackLogError("Failed to save texture: " + outputFile + " Program might not have permissions or target folder " + Args.outputFolder + " does not exists!");
                        Args.callbackTerminate(false);  return false;
                    }
                }

                // Bump
                if(isNormal && Args.normalToBump){
                    convertNormalToBump(outputDiffusePixels, splitSize, splitSize, outputBumpPixels);

					std::string outputFile = Args.outputFolder + "\\Tex_" + ffw::valToString(index) + "_bump." + Args.textureExtension;
                    if(!Args.imageSaver(outputFile, outputBumpPixels, splitSize, splitSize, ffw::imageType::GRAYSCALE_8)){
                        Args.callbackLogError("Failed to save texture: " + outputFile + " Program might not have permissions or target folder " + Args.outputFolder + " does not exists!");
                        Args.callbackTerminate(false);  return false;
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
    Args.callbackTerminate(true);
    return true;
}
