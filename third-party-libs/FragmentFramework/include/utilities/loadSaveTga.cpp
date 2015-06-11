/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "loadSaveTga.h"
#include "../math/math.h"
#include "../math/stringMath.h"
#include "file.h"

static uint8_t tgaFooter[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x52, 0x55, 0x45, 0x56, 0x49, 0x53, 0x49, 0x4F, 0x4E, 0x2D, 0x58, 0x46, 0x49, 0x4c, 0x45, 0x2E, 0x00};

///=============================================================================
bool ffw::loadTGA(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, ffw::imageType* Type){
    return loadTGA(utf8ToWstr(Path), Pixels, Width, Height, Type);
}

///=============================================================================
bool ffw::loadTGA(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, ffw::imageType* Type){
    file input;
    if(!input.open(Path, true, false, false)){
        return false;
    }

    // Check if file is big enough to contain header
    size_t size = input.getSize();
    if(size < 18)return false;

    uint8_t idLength;
    uint8_t colorMapType;
    uint8_t imageType;
    uint16_t colorMapEntry;
    uint16_t colorMapLength;
    uint8_t colorMapSize;
    uint16_t originX;
    uint16_t originY;
    uint16_t width;
    uint16_t height;
    uint8_t bitsPerPixel;
    uint8_t imageDescriptor;
    ffw::imageType type;

    // Read header
    input.read(&idLength,           sizeof(uint8_t));
    input.read(&colorMapType,       sizeof(uint8_t));
    input.read(&imageType,          sizeof(uint8_t));
    input.read(&colorMapEntry,      sizeof(uint16_t));
    input.read(&colorMapLength,     sizeof(uint16_t));
    input.read(&colorMapSize,       sizeof(uint8_t));
    input.read(&originX,            sizeof(uint16_t));
    input.read(&originY,            sizeof(uint16_t));
    input.read(&width,              sizeof(uint16_t));
    input.read(&height,             sizeof(uint16_t));
    input.read(&bitsPerPixel,       sizeof(uint8_t));
    input.read(&imageDescriptor,    sizeof(uint8_t));

    // Read extra id
    if(idLength > 0){
        uint8_t* id = new uint8_t[idLength];
        input.read(&id, idLength*sizeof(uint8_t));
        delete[] id;
    }

    // Check if there is no compression
    if(colorMapType != 0)return false;
    if(!(imageType == 2 || imageType == 3))return false;

    // Get number of channels
    if(imageType == 3){
        type = ffw::imageType::GRAYSCALE_8;

    } else if(imageType == 2 && bitsPerPixel == 16 && imageDescriptor == 1){
        type = ffw::imageType::RGB_ALPHA_5551;

    } else if(imageType == 2 && bitsPerPixel == 24 && imageDescriptor == 0){
        type = ffw::imageType::RGB_888;

    } else if(imageType == 2 && bitsPerPixel == 32 && imageDescriptor == 8){
        type = ffw::imageType::RGB_ALPHA_8888;

    } else {
        return false;
    }

    // Check if file contains all pixels
    if(size < 18 + size_t(width*height*(bitsPerPixel/8))){
        return false;
    }

    if(Width != NULL)*Width = width;
    if(Height != NULL)*Height = height;
    if(Type != NULL)*Type = type;

    if(Pixels == NULL)return true;

    // Black and white, nothing to do
    if(type == ffw::imageType::GRAYSCALE_8){
        *Pixels = new uint8_t[width*height];
        input.read(*Pixels, width*height);

    // RGBA_5155 to RGBA_5551
    } else if(type == ffw::imageType::RGB_ALPHA_5551){
        uint8_t* temp = new uint8_t[width*height*2];
        input.read(temp, width*height*2);
        *Pixels = new uint8_t[width*height*2];
        // 16 bit BGR to 24bit RGB
        //uint16_t* tempPtr = (uint16_t*)temp;
        //for(int i = 0, p = 0; i < width*height; i ++, p += 3){

            /*uint8_t red = (tempPtr[i] & 0x7C00) >> 10;
            red = red << (8-5) | red >> (2*5-8);

            uint8_t green = (tempPtr[i] & 0x03E0) >> 5;
            green = green << (8-5) | green >> (2*5-8);

            uint8_t blue = (tempPtr[i] & 0x001F);
            blue = blue << (8-5) | blue >> (2*5-8);

            (*Pixels)[p+0] = red;
            (*Pixels)[p+1] = green;
            (*Pixels)[p+2] = blue;*/
        for(int i = 0; i < width*height*2; i+=2){
            (*Pixels)[i+0] = temp[i+1];
            (*Pixels)[i+1] = temp[i+0];
        }
        delete[] temp;

    // BGR_888 to RGB_888
    } else if(type == ffw::imageType::RGB_888){
        uint8_t* temp = new uint8_t[width*height*3];
        input.read(temp, width*height*3);
        *Pixels = new uint8_t[width*height*3];
        for(int i = 0; i < width*height*3; i += 3){
            (*Pixels)[i+0] = temp[i+2];
            (*Pixels)[i+1] = temp[i+1];
            (*Pixels)[i+2] = temp[i+0];
        }
        delete[] temp;

    // BGRA_8888 to RGBA_8888
    } else if(type == ffw::imageType::RGB_ALPHA_8888){
        uint8_t* temp = new uint8_t[width*height*4];
        input.read(temp, width*height*4);
        *Pixels = new uint8_t[width*height*4];
        for(int i = 0; i < width*height*4; i += 4){
            (*Pixels)[i+0] = temp[i+2];
            (*Pixels)[i+1] = temp[i+1];
            (*Pixels)[i+2] = temp[i+0];
            (*Pixels)[i+3] = temp[i+3];
        }
        delete[] temp;
    }

    return true;
}

///=============================================================================
bool ffw::saveTGA(const std::string& Path, unsigned char* Pixels, int Width, int Height, imageType Type){
    return saveTGA(utf8ToWstr(Path), Pixels, Width, Height, Type);
}

///=============================================================================
bool ffw::saveTGA(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, imageType Type){
    if(Pixels == NULL)return false;
    if(Width == 0 || Height == 0)return false;

    if(!(Type == imageType::GRAYSCALE_8 ||
         Type == imageType::RGB_ALPHA_5551 ||
         Type == imageType::RGB_888 ||
         Type == imageType::RGB_ALPHA_8888))return false;

    if(Pixels == NULL)return false;

    file output;
    if(!output.open(Path, true,true, true)){
        return false;
    }

    uint8_t idLength = 0;
    uint8_t colorMapType = 0;
    uint8_t imageType = 3;
    uint16_t colorMapEntry = 0;
    uint16_t colorMapLength = 0;
    uint8_t colorMapSize = 0;
    uint16_t originX = 0;
    uint16_t originY = 0;
    uint16_t width = Width;
    uint16_t height = Height;
    uint8_t bitsPerPixel = 32;
    uint8_t imageDescriptor = 0;

    if(Type == ffw::imageType::GRAYSCALE_8){
        imageType = 3;
        bitsPerPixel = 8;
        imageDescriptor = 0;

    } else if(Type == ffw::imageType::RGB_ALPHA_5551){
        imageType = 2;
        bitsPerPixel = 16;
        imageDescriptor = 1;

    } else if(Type == ffw::imageType::RGB_888){
        imageType = 2;
        bitsPerPixel = 24;
        imageDescriptor = 0;

    } else if(Type == ffw::imageType::RGB_ALPHA_8888){
        imageType = 2;
        bitsPerPixel = 32;
        imageDescriptor = 8;
    }

    // Read header
    output.write(&idLength,           sizeof(uint8_t));
    output.write(&colorMapType,       sizeof(uint8_t));
    output.write(&imageType,          sizeof(uint8_t));
    output.write(&colorMapEntry,      sizeof(uint16_t));
    output.write(&colorMapLength,     sizeof(uint16_t));
    output.write(&colorMapSize,       sizeof(uint8_t));
    output.write(&originX,            sizeof(uint16_t));
    output.write(&originY,            sizeof(uint16_t));
    output.write(&width,              sizeof(uint16_t));
    output.write(&height,             sizeof(uint16_t));
    output.write(&bitsPerPixel,       sizeof(uint8_t));
    output.write(&imageDescriptor,    sizeof(uint8_t));

    // GRAYSCALE_8
    if(Type == ffw::imageType::GRAYSCALE_8){
        //temp = Pixels;
        output.write(Pixels, width*height);

    // RGBA_5551 to BGRA_5515
    } else if(Type == ffw::imageType::RGB_ALPHA_5551){
        uint8_t* temp = new uint8_t[width*height*2];
        for(int i = 0; i < width*height*2; i += 2){
            temp[i+0] = Pixels[i+1];
            temp[i+1] = Pixels[i+0];
        }
        output.write(temp, width*height*2);
        delete[] temp;

    // RGB_888 to BGR_888
    } else if(Type == ffw::imageType::RGB_888){
        uint8_t* temp = new uint8_t[width*height*3];
        for(int i = 0; i < width*height*3; i += 3){
            temp[i+0] = Pixels[i+2];
            temp[i+1] = Pixels[i+1];
            temp[i+2] = Pixels[i+0];
        }
        output.write(temp, width*height*3);
        delete[] temp;

    // RGBA_8888 to BGRA_8888
    } else if(Type == ffw::imageType::RGB_ALPHA_8888){
        uint8_t* temp = new uint8_t[width*height*4];
        for(int i = 0; i < width*height*4; i += 4){
            temp[i+0] = Pixels[i+2];
            temp[i+1] = Pixels[i+1];
            temp[i+2] = Pixels[i+0];
            temp[i+3] = Pixels[i+3];
        }
        output.write(temp, width*height*4);
        delete[] temp;

    }

    output.write(&tgaFooter[0], sizeof(tgaFooter));

    return true;
}
