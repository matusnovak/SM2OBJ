/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "textureExport.h"
#include "blockConfig.h"
#include "config.h"
#include <math.h>

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
static bool saveTexture(const std::string& Path, unsigned char* pixels, int Width, int Height, ffw::imageType Type){
	std::string ext;
	ffw::getFilePathProperties(Path, NULL, NULL, &ext);

	if(ext == "png"){
		return ffw::savePNG(Path, pixels, Width, Height, Type);
	}
	if(ext == "bmp"){
		return ffw::saveBMP(Path, pixels, Width, Height, Type);
	}
	if(ext == "tga"){
		return ffw::saveTGA(Path, pixels, Width, Height, Type);
	}
	if(ext == "tiff"){
		return ffw::saveTIFF(Path, pixels, Width, Height, Type);
	}
	return false;
}

///=============================================================================
static bool loadTexture(const std::string& Path, unsigned char** pixels, int* Width, int* Height, int* Channels){
	ffw::imageType type;
	if(!ffw::loadPNG(Path, pixels, Width, Height, &type))return false;

    if(*Width != *Height){
        ffw::logError() << "Failed to load texture: " << Path <<  " Texture must have same width and height!";
		delete[] pixels;
        return false;
    }

    if(!(*Width == 1024 || *Width == 2048 || *Width == 4096)){
        ffw::logError() << "Failed to load texture: " << Path << " Wrong texture size! Must be either 1024, 2048, or 4096!";
		delete[] pixels;
        return false;
    }

    if(type == ffw::imageType::RGB_888)*Channels = 3;
    else if(type == ffw::imageType::RGB_ALPHA_8888)*Channels = 4;
    else {
        ffw::logError() << "Failed to load texture: " << Path << " Wrong texture format! Must be either 8-bit RGB or 8-bit RGBA!";
		delete[] pixels;
        return false;
    }
	return true;
}

///=============================================================================
bool sm2obj::exportEmissiveAtlas(const std::vector<blockInfoStruct>& BlockInfo, int Size, int Atlas, const std::string& OutputPath){
    int index = Atlas*16*16;
    unsigned char* pixels = new unsigned char[Size*16*Size*16*3];
    int width = Size*16;

    for(int p = 0; p < Size*16*Size*16*3; p++)pixels[p] = 0;

    for(int y = 15; y >= 0; y--){
        for(int x = 0; x < 16; x++){
            const blockInfoStruct* block = findBlockByTexture(BlockInfo, index);
            if(block != NULL && block->emissive){

                for(int h = 0; h < Size; h++){
                    for(int w = 0; w < Size; w++){
                        pixels[width*(y*Size+h)*3 + (x*Size+w)*3 +0] = char(block->light.r * 255);
                        pixels[width*(y*Size+h)*3 + (x*Size+w)*3 +1] = char(block->light.g * 255);
                        pixels[width*(y*Size+h)*3 + (x*Size+w)*3 +2] = char(block->light.b * 255);
                    }
                }

            }
            index++;
        }
    }

	if(!saveTexture(OutputPath, pixels, Size*16, Size*16, ffw::imageType::RGB_888)){
		ffw::logError() << "Failed to save texture: " << OutputPath << " Program might not have permissions or target folder " << OutputPath << " does not exists!";
		return false;
	}

    delete[] pixels;
    return true;
}

///=============================================================================
bool sm2obj::exportDiffuseAtlas(const std::string& Path, int Size, const std::string& OutputPath){
	unsigned char* pixels;
    int width;
    int height;
    int channels;
    
	if(!loadTexture(Path, &pixels, &width, &height, &channels)){
		ffw::logError() << "Failed to load atlas: " << Path;
		return false;
	}

	bool result = saveTexture(OutputPath, pixels, width, height, (channels == 4 ? ffw::imageType::RGB_ALPHA_8888 : ffw::imageType::RGB_888));
	delete[] pixels;
	return result;
}

///=============================================================================
bool sm2obj::exportNormalAtlas(const std::string& Path, int Size, const std::string& OutputPath){
	unsigned char* pixels;
    int width;
    int height;
    int channels;
    
	if(!loadTexture(Path, &pixels, &width, &height, &channels)){
		ffw::logError() << "Failed to load atlas: " << Path;
		return false;
	}

	bool result = saveTexture(OutputPath, pixels, width, height, (channels == 4 ? ffw::imageType::RGB_ALPHA_8888 : ffw::imageType::RGB_888));
	delete[] pixels;
	return result;
}

///=============================================================================
bool sm2obj::exportAlphaAtlas(const std::string& Path, int Size, const std::string& OutputPath){
	unsigned char* pixels;
    int width;
    int height;
    int channels;
    
	if(!loadTexture(Path, &pixels, &width, &height, &channels)){
		ffw::logError() << "Failed to load atlas: " << Path;
		return false;
	}

	unsigned char* pixelsOut = new unsigned char[width*height];
	if(channels == 4){
		extractAlpha(pixels, width, height, pixelsOut);
	} else {
		for(int p = 0; p < width*height*1; p++)pixelsOut[p] = 255;
	}

	bool result = saveTexture(OutputPath, pixelsOut, width, height, ffw::imageType::GRAYSCALE_8);
	delete[] pixels;
	delete[] pixelsOut;
	return result;
}

///=============================================================================
bool sm2obj::exportBumpAtlas(const std::string& Path, int Size, const std::string& OutputPath){
	unsigned char* pixels;
    int width;
    int height;
    int channels;
    
	if(!loadTexture(Path, &pixels, &width, &height, &channels)){
		ffw::logError() << "Failed to load atlas: " << Path;
		return false;
	}

	unsigned char* pixelsOut = new unsigned char[width*height*1];

	convertNormalToBump(pixels, width, height, pixelsOut);

	bool result = saveTexture(OutputPath, pixelsOut, width, height, ffw::imageType::GRAYSCALE_8);
	delete[] pixels;
	delete[] pixelsOut;
	return result;
}

///=============================================================================
bool sm2obj::exportTileAlpha(const std::vector<blockInfoStruct>& BlockInfo, const std::string& InputFolder, int Size, const std::string& OutputFolder, const std::string& TextureExtension){
	int index = 0;

    int total = 16*16*6;
    int progress = 1;

	std::string textures[3] = {"t000.png", "t001.png", "t002.png"};
    for(const auto& tex : textures){
        unsigned char* pixels;
        int width;
        int height;
        int channels;
		std::string file = InputFolder + "\\" + tex;

        ffw::logDebug() << "Reading file: " << file;

        if(!loadTexture(file, &pixels, &width, &height, &channels)){
            ffw::logError() << "Failed to load atlas: " << file;
			return false;
        }

        int bleeding = int((width / 16)*0.15625f);

        int splitSize = (width / 16) - bleeding;
        ffw::logDebug() << "Splitting texture to: " << splitSize << "x" << splitSize << " chunks";

		unsigned char* pixelsOut = new unsigned char[splitSize*splitSize*channels];
		unsigned char* pixelsOutAlpha = new unsigned char[splitSize*splitSize*1];
			
		for(int y = 0; y < height; y += (width / 16)){
			bool out = false;
			for(int x = 0; x < width; x += (width / 16)){
				const blockInfoStruct* block = findBlockByTexture(BlockInfo, index);
				if(block == NULL){
					index++;
					continue;
				}
				
				std::string outputFile = OutputFolder + "\\Tex_" + ffw::valToString(index) + "_alpha." + TextureExtension;
					
				subsection(pixels, width, height, x + bleeding/2, y + bleeding/2, channels, pixelsOut, splitSize, splitSize);

				if(channels == 4){
					extractAlpha(pixelsOut, splitSize, splitSize, pixelsOutAlpha);
				} else {
					for(int p = 0; p < splitSize*splitSize; p++)pixelsOutAlpha[p] = 255;
				}

				if(!saveTexture(outputFile, pixelsOutAlpha, splitSize, splitSize, ffw::imageType::GRAYSCALE_8)){
					ffw::logError() << "Failed to save texture: " << outputFile;
					warningMessageFlag = true;

					out = true;
					break;
				}

				index++;
			}
			if(out)break;
		}

		delete[] pixelsOut;
		delete[] pixelsOutAlpha;
		delete[] pixels;
	}
}

///=============================================================================
bool sm2obj::exportTileNormals(const std::vector<blockInfoStruct>& BlockInfo, const std::string& InputFolder, int Size, const std::string& OutputFolder, const std::string& TextureExtension){
	int index = 0;

    int total = 16*16*6;
    int progress = 1;

	std::string textures[3] = {"t000_NRM.png", "t001_NRM.png", "t002_NRM.png"};
    for(const auto& tex : textures){
        unsigned char* pixels;
        int width;
        int height;
        int channels;
		std::string file = InputFolder + "\\" + tex;

        ffw::logDebug() << "Reading file: " << file;

        if(!loadTexture(file, &pixels, &width, &height, &channels)){
            ffw::logError() << "Failed to load atlas: " << file;
			return false;
        }

        int bleeding = int((width / 16)*0.15625f);

        int splitSize = (width / 16) - bleeding;
        ffw::logDebug() << "Splitting texture to: " << splitSize << "x" << splitSize << " chunks";

		unsigned char* pixelsOut = new unsigned char[splitSize*splitSize*channels];
			
		for(int y = 0; y < height; y += (width / 16)){
			bool out = false;
			for(int x = 0; x < width; x += (width / 16)){
				const blockInfoStruct* block = findBlockByTexture(BlockInfo, index);
				if(block == NULL){
					index++;
					continue;
				}
				
				std::string outputFile = OutputFolder + "\\Tex_" + ffw::valToString(index) + "_norm." + TextureExtension;
					
				subsection(pixels, width, height, x + bleeding/2, y + bleeding/2, channels, pixelsOut, splitSize, splitSize);

				if(!saveTexture(outputFile, pixelsOut, splitSize, splitSize, ffw::imageType::RGB_888)){
					ffw::logError() << "Failed to save texture: " << outputFile;
					warningMessageFlag = true;

					out = true;
					break;
				}

				index++;
			}
			if(out)break;
		}

		delete[] pixelsOut;
		delete[] pixels;
	}
}

///=============================================================================
bool sm2obj::exportTileBump(const std::vector<blockInfoStruct>& BlockInfo, const std::string& InputFolder, int Size, const std::string& OutputFolder, const std::string& TextureExtension){
	int index = 0;

    int total = 16*16*6;
    int progress = 1;

	std::string textures[3] = {"t000_NRM.png", "t001_NRM.png", "t002_NRM.png"};
    for(const auto& tex : textures){
        unsigned char* pixels;
        int width;
        int height;
        int channels;
		std::string file = InputFolder + "\\" + tex;

        ffw::logDebug() << "Reading file: " << file;

        if(!loadTexture(file, &pixels, &width, &height, &channels)){
            ffw::logError() << "Failed to load atlas: " << file;
			return false;
        }

        int bleeding = int((width / 16)*0.15625f);

        int splitSize = (width / 16) - bleeding;
        ffw::logDebug() << "Splitting texture to: " << splitSize << "x" << splitSize << " chunks";

		unsigned char* pixelsOut = new unsigned char[splitSize*splitSize*channels];
		unsigned char* pixelsOutBump = new unsigned char[splitSize*splitSize*1];
			
		for(int y = 0; y < height; y += (width / 16)){
			bool out = false;
			for(int x = 0; x < width; x += (width / 16)){
				const blockInfoStruct* block = findBlockByTexture(BlockInfo, index);
				if(block == NULL){
					index++;
					continue;
				}
				
				std::string outputFile = OutputFolder + "\\Tex_" + ffw::valToString(index) + "_bump." + TextureExtension;
					
				subsection(pixels, width, height, x + bleeding/2, y + bleeding/2, channels, pixelsOut, splitSize, splitSize);
				convertNormalToBump(pixelsOut, splitSize, splitSize, pixelsOutBump);

				if(!saveTexture(outputFile, pixelsOutBump, splitSize, splitSize, ffw::imageType::GRAYSCALE_8)){
					ffw::logError() << "Failed to save texture: " << outputFile;
					warningMessageFlag = true;

					out = true;
					break;
				}

				index++;
			}
			if(out)break;
		}

		delete[] pixelsOut;
		delete[] pixelsOutBump;
		delete[] pixels;
	}
}

///=============================================================================
bool sm2obj::exportTileDiffuse(const std::vector<blockInfoStruct>& BlockInfo, const std::string& InputFolder, int Size, const std::string& OutputFolder, const std::string& TextureExtension){
	int index = 0;

    int total = 16*16*6;
    int progress = 1;

	std::string textures[3] = {"t000.png", "t001.png", "t002.png"};
    for(const auto& tex : textures){
        unsigned char* pixels;
        int width;
        int height;
        int channels;
		std::string file = InputFolder + "\\" + tex;

        ffw::logDebug() << "Reading file: " << file;

        if(!loadTexture(file, &pixels, &width, &height, &channels)){
            ffw::logError() << "Failed to load atlas: " << file;
			return false;
        }

        int bleeding = int((width / 16)*0.15625f);

        int splitSize = (width / 16) - bleeding;
        ffw::logDebug() << "Splitting texture to: " << splitSize << "x" << splitSize << " chunks";

		unsigned char* pixelsOut = new unsigned char[splitSize*splitSize*channels];
			
		for(int y = 0; y < height; y += (width / 16)){
			bool out = false;
			for(int x = 0; x < width; x += (width / 16)){
				const blockInfoStruct* block = findBlockByTexture(BlockInfo, index);
				if(block == NULL){
					index++;
					continue;
				}
				
				std::string outputFile = OutputFolder + "\\Tex_" + ffw::valToString(index) + "_diff." + TextureExtension;
					
				subsection(pixels, width, height, x + bleeding/2, y + bleeding/2, channels, pixelsOut, splitSize, splitSize);

				if(!saveTexture(outputFile, pixelsOut, splitSize, splitSize, (channels == 4 ? ffw::imageType::RGB_ALPHA_8888 : ffw::imageType::RGB_888))){
					ffw::logError() << "Failed to save texture: " << outputFile;
					warningMessageFlag = true;

					out = true;
					break;
				}

				index++;
			}
			if(out)break;
		}

		delete[] pixelsOut;
		delete[] pixels;

        /*unsigned char* outputDiffusePixels = new unsigned char[splitSize*splitSize*channels];
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
        delete[] pixels;*/

    }
    return true;
}

/*
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
		ffw::logInfo() << "Texture: " << tex;

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
*/