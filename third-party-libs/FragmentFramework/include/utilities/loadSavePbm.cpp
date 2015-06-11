/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "loadSavePbm.h"
#include "../math/math.h"
#include "../math/stringMath.h"
#include "file.h"

///=============================================================================
bool ffw::loadPBM(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, ffw::imageType* Type){
    return loadPBM(utf8ToWstr(Path), Pixels, Width, Height, Type);
}

///=============================================================================
bool ffw::loadPBM(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, ffw::imageType* Type){
    file input;
    if(!input.open(Path, true, false, false)){
        return false;
    }

    // Check if file is big enough to contain header
    size_t size = input.getSize();

    std::string header[4];

    input.readLine(&header[0]);
    input.readLine(&header[1]);
    input.readLine(&header[2]);
    input.readLine(&header[3]);

    if(header[0].size() == 0 || header[1].size() == 0 || header[2].size() == 0 || header[3].size() == 0)return false;

    uint32_t width = stringToVal<unsigned long>(header[1]);
    uint32_t height = stringToVal<unsigned long>(header[2]);
    imageType type;

    uint32_t offset = input.getPos();
    uint32_t dataLength = 0;
    uint32_t scanline = 0;

    if(header[0] == "P6" && header[3] == "255"){
        type = imageType::RGB_888;
        dataLength = width*height*3;
        scanline = width*3;
        if(offset + dataLength > size)return false;
    } else if(header[0] == "P6" && header[3] == "65535"){
        type = imageType::RGB_161616;
        dataLength = width*height*6;
        scanline = width*6;
        if(offset + dataLength > size)return false;
    } else if(header[0] == "PF" && header[3] == "-1.0000"){
        type = imageType::RGB_323232;
        dataLength = width*height*12;
        scanline = width*12;
        if(offset + dataLength > size)return false;
    } else if(header[0] == "P5" && header[3] == "255"){
        type = imageType::GRAYSCALE_8;
        dataLength = width*height;
        scanline = width;
        if(offset + dataLength > size)return false;
    } else if(header[0] == "P5" && header[3] == "65535"){
        type = imageType::GRAYSCALE_16;
        dataLength = width*height*2;
        scanline = width*2;
        if(offset + dataLength > size)return false;
    } else if(header[0] == "Pf" && header[3] == "-1.0000"){
        type = imageType::GRAYSCALE_32;
        dataLength = width*height*4;
        scanline = width*4;
        if(offset + dataLength > size)return false;
    } else {
        return false;
    }

    if(Width != NULL)*Width = width;
    if(Height != NULL)*Height = height;
    if(Type != NULL)*Type = type;

    if(Pixels == NULL)return true;

    if(type == imageType::GRAYSCALE_8){
        *Pixels = new uint8_t[width*height];
    } else if(type == imageType::GRAYSCALE_16){
        *Pixels = new uint8_t[width*height*2];
    } else if(type == imageType::GRAYSCALE_32){
        *Pixels = new uint8_t[width*height*4];
    } else if(type == imageType::RGB_888){
        *Pixels = new uint8_t[width*height*3];
    } else if(type == imageType::RGB_161616){
        *Pixels = new uint8_t[width*height*6];
    } else if(type == imageType::RGB_323232){
        *Pixels = new uint8_t[width*height*12];
    }

    for(uint32_t row = 0; row < height; row++){
        input.gotoPos(offset + (height -row -1)*scanline);
        input.read(&(*Pixels)[row*scanline], scanline);
    }

    if(type == imageType::GRAYSCALE_16){
        for(uint32_t i = 0; i < width*height*2; i += 2){
            uint8_t temp = (*Pixels)[i];
            (*Pixels)[i] = (*Pixels)[i+1];
            (*Pixels)[i+1] = temp;
        }
    } else if(type == imageType::RGB_161616){
        for(uint32_t i = 0; i < width*height*6; i += 6){
            uint8_t tempR = (*Pixels)[i];
            (*Pixels)[i] = (*Pixels)[i+1];
            (*Pixels)[i+1] = tempR;

            uint8_t tempG = (*Pixels)[i+2];
            (*Pixels)[i+2] = (*Pixels)[i+3];
            (*Pixels)[i+3] = tempG;

            uint8_t tempB = (*Pixels)[i+4];
            (*Pixels)[i+4] = (*Pixels)[i+5];
            (*Pixels)[i+5] = tempB;
        }
    }

    return true;
}

///=============================================================================
bool ffw::savePBM(const std::string& Path, unsigned char* Pixels, int Width, int Height, ffw::imageType Type){
    return savePBM(utf8ToWstr(Path), Pixels, Width, Height, Type);
}

///=============================================================================
bool ffw::savePBM(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, ffw::imageType Type){
    if(Pixels == NULL)return false;
    if(Width == 0 || Height == 0)return false;

    if(!(Type == imageType::GRAYSCALE_8 ||
         Type == imageType::GRAYSCALE_16 ||
         Type == imageType::GRAYSCALE_32 ||
         Type == imageType::RGB_888 ||
         Type == imageType::RGB_161616 ||
         Type == imageType::RGB_323232))return false;

    file output;
    if(!output.open(Path, true,true, true)){
        return false;
    }

    std::string header[4];
    uint32_t scanline = 0;

    if(Type == imageType::GRAYSCALE_8){
        header[0] = "P5";
        header[3] = "255";
        scanline = Width;
    } else if(Type == imageType::GRAYSCALE_16){
        header[0] = "P5";
        header[3] = "65535";
        scanline = Width*2;
    } else if(Type == imageType::GRAYSCALE_32){
        header[0] = "Pf";
        header[3] = "-1.0000";
        scanline = Width*4;
    } else if(Type == imageType::RGB_888){
        header[0] = "P6";
        header[3] = "255";
        scanline = Width*3;
    } else if(Type == imageType::RGB_161616){
        header[0] = "P6";
        header[3] = "65535";
        scanline = Width*6;
    } else if(Type == imageType::RGB_323232){
        header[0] = "PF";
        header[3] = "-1.0000";
        scanline = Width*12;
    }

    header[1] = valToString(Width);
    header[2] = valToString(Height);

    output.writeLine(header[0]);
    output.writeLine(header[1]);
    output.writeLine(header[2]);
    output.writeLine(header[3]);

    uint32_t offset = output.getPos();

    // Fill whole file
    for(int row = 0; row < Height; row++){
        output.write(Pixels, scanline);
    }

    uint8_t* rowPtr = NULL;

    if(Type == imageType::GRAYSCALE_16){
        rowPtr = new uint8_t[Width*2];
    } else if(Type == imageType::RGB_161616){
        rowPtr = new uint8_t[Width*6];
    }

    // Save rows in reverse order
    for(int row = 0; row < Height; row++){
        output.gotoPos(offset + (Height -row -1)*scanline);

        if(Type == imageType::GRAYSCALE_16){
            uint8_t* tempPtr = &Pixels[row*scanline];
            for(int i = 0; i < Width*2; i += 2){
                rowPtr[i+0] = tempPtr[i+1];
                rowPtr[i+1] = tempPtr[i+0];
            }
        } else if(Type == imageType::RGB_161616){
            uint8_t* tempPtr = &Pixels[row*scanline];
            for(int i = 0; i < Width*6; i += 6){
                rowPtr[i+0] = tempPtr[i+1];
                rowPtr[i+1] = tempPtr[i+0];

                rowPtr[i+2] = tempPtr[i+3];
                rowPtr[i+3] = tempPtr[i+2];

                rowPtr[i+4] = tempPtr[i+5];
                rowPtr[i+5] = tempPtr[i+4];
            }
        } else {
            rowPtr = &Pixels[row*scanline];
        }

        output.write(rowPtr, scanline);
    }

    if(Type == imageType::GRAYSCALE_16 || Type == imageType::RGB_161616){
        delete[] rowPtr;
    }

    return true;
}

