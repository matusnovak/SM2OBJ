/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "loadSaveTiff.h"
#include <tiffio.h>
#include "../math/math.h"
#include "../math/stringMath.h"
#include "file.h"

///=============================================================================
bool ffw::loadTIFF(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, ffw::imageType* Type){
    return loadTIFF(utf8ToWstr(Path), Pixels, Width, Height, Type);
}

///=============================================================================
bool ffw::loadTIFF(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, ffw::imageType* Type){
    TIFF* tif = TIFFOpenW(Path.c_str(), "r");
    if(tif == NULL)return false;

    uint32 imagelength;
    size_t scanline;
    tdata_t buf;
    uint32_t row;
    uint32_t width;
    uint32_t height;
    uint16_t bitsPerPixel;
    uint16_t compression;
    uint16_t dataType;
    imageType type;

    uint16_t photometric;
    uint16_t samplesPerPixel;

    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &imagelength);
    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
    TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bitsPerPixel);
    TIFFGetField(tif, TIFFTAG_COMPRESSION, &compression);
    TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &photometric);
    TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &samplesPerPixel);
    TIFFGetField(tif, TIFFTAG_DATATYPE, &dataType);

    std::cout << "photometric: " << photometric << std::endl;
    std::cout << "samplesPerPixel: " << samplesPerPixel << std::endl;
    std::cout << "dataType: " << dataType << std::endl;

    scanline = TIFFScanlineSize(tif);
    height = imagelength;

    if(bitsPerPixel == 8){
        if(samplesPerPixel == 3 && scanline/3 == width){
            type = imageType::RGB_888;
        } else if(samplesPerPixel == 4 && scanline/4 == width){
            type = imageType::RGB_ALPHA_8888;
        } else if(samplesPerPixel == 2 && scanline/2 == width){
            type = imageType::GRAYSCALE_ALPHA_8;
        } else if(samplesPerPixel == 1 && scanline == width){
            type = imageType::GRAYSCALE_8;
        } else {
            TIFFClose(tif);
            return false;
        }
    } else if(bitsPerPixel == 16){
        if(samplesPerPixel == 3 && scanline/6 == width){
            type = imageType::RGB_161616;
        } else if(samplesPerPixel == 4 && scanline/8 == width){
            type = imageType::RGB_ALPHA_16161616;
        } else if(samplesPerPixel == 2 && scanline/8 == width){
            type = imageType::GRAYSCALE_ALPHA_16;
        } else if(samplesPerPixel == 1 && scanline/2 == width){
            type = imageType::GRAYSCALE_16;
        } else {
            TIFFClose(tif);
            return false;
        }
    } else if(bitsPerPixel == 32){
        if(samplesPerPixel == 3 && scanline/12 == width){
            type = imageType::RGB_323232;
        } else if(samplesPerPixel == 4 && scanline/16 == width){
            type = imageType::RGB_ALPHA_32323232;
        } else if(samplesPerPixel == 2 && scanline/8 == width){
            type = imageType::GRAYSCALE_ALPHA_32;
        } else if(samplesPerPixel == 1 && scanline/4 == width){
            type = imageType::GRAYSCALE_32;
        } else {
            TIFFClose(tif);
            return false;
        }
    } else {
        TIFFClose(tif);
        return false;
    }

    if(Width != NULL)*Width = width;
    if(Height != NULL)*Height = height;
    if(Type != NULL)*Type = type;

    if(Pixels == NULL)return true;

    if     (type == imageType::GRAYSCALE_8)
        *Pixels = new uint8_t[width*height];
    else if(type == imageType::GRAYSCALE_ALPHA_8)
        *Pixels = new uint8_t[width*height*2];
    else if(type == imageType::GRAYSCALE_16)
        *Pixels = new uint8_t[width*height*2];
    else if(type == imageType::GRAYSCALE_ALPHA_16)
        *Pixels = new uint8_t[width*height*4];
    else if(type == imageType::GRAYSCALE_32)
        *Pixels = new uint8_t[width*height*4];
    else if(type == imageType::GRAYSCALE_ALPHA_32)
        *Pixels = new uint8_t[width*height*8];
    else if(type == imageType::RGB_888)
        *Pixels = new uint8_t[width*height*3];
    else if(type == imageType::RGB_ALPHA_8888)
        *Pixels = new uint8_t[width*height*4];
    else if(type == imageType::RGB_161616)
        *Pixels = new uint8_t[width*height*6];
    else if(type == imageType::RGB_ALPHA_16161616)
        *Pixels = new uint8_t[width*height*8];
    else if(type == imageType::RGB_323232)
        *Pixels = new uint8_t[width*height*12];
    else if(type == imageType::RGB_ALPHA_32323232)
        *Pixels = new uint8_t[width*height*16];

    buf = _TIFFmalloc(scanline);
    for (row = 0; row < imagelength; row++){
        TIFFReadScanline(tif, &(*Pixels)[row*scanline], imagelength -row -1);
    }
    _TIFFfree(buf);
    TIFFClose(tif);

    return true;
}

///=============================================================================
bool ffw::saveTIFF(const std::string& Path, unsigned char* Pixels, int Width, int Height, ffw::imageType Type){
    return saveTIFF(utf8ToWstr(Path), Pixels, Width, Height, Type);
}

///=============================================================================
bool ffw::saveTIFF(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, ffw::imageType Type){
    if(Pixels == NULL)return false;
    if(Width == 0 || Height == 0)return false;

    if(!(Type == imageType::GRAYSCALE_8 ||
         Type == imageType::GRAYSCALE_16 ||
         Type == imageType::GRAYSCALE_32 ||
         Type == imageType::GRAYSCALE_ALPHA_8 ||
         Type == imageType::GRAYSCALE_ALPHA_16 ||
         Type == imageType::GRAYSCALE_ALPHA_32 ||
         Type == imageType::RGB_888 ||
         Type == imageType::RGB_161616 ||
         Type == imageType::RGB_323232 ||
         Type == imageType::RGB_ALPHA_8888 ||
         Type == imageType::RGB_ALPHA_16161616 ||
         Type == imageType::RGB_ALPHA_32323232))return false;

    TIFF* tif = TIFFOpenW(Path.c_str(), "w");
    if(tif == NULL)return false;

    uint16_t bitsPerPixel = 0;
    uint16_t samplesPerPixel = 0;
    uint32_t scanline = 0;
    uint16_t photometric = 0;
    uint16_t dataType = 0;

    if(Type == imageType::GRAYSCALE_8){
        bitsPerPixel = 8;
        samplesPerPixel = 1;
        scanline = Width;
        photometric = 1;
        dataType = 0;
    } else if(Type == imageType::GRAYSCALE_16){
        bitsPerPixel = 16;
        samplesPerPixel = 1;
        scanline = Width*2;
        photometric = 1;
        dataType = 0;
    } else if(Type == imageType::GRAYSCALE_32){
        bitsPerPixel = 32;
        samplesPerPixel = 1;
        scanline = Width*4;
        photometric = 1;
        dataType = 3;
    } else if(Type == imageType::GRAYSCALE_ALPHA_8){
        bitsPerPixel = 8;
        samplesPerPixel = 2;
        scanline = Width*2;
        photometric = 1;
        dataType = 0;
    } else if(Type == imageType::GRAYSCALE_ALPHA_16){
        bitsPerPixel = 16;
        samplesPerPixel = 2;
        scanline = Width*4;
        photometric = 1;
        dataType = 0;
    } else if(Type == imageType::GRAYSCALE_ALPHA_32){
        bitsPerPixel = 32;
        samplesPerPixel = 2;
        scanline = Width*8;
        photometric = 1;
        dataType = 3;
    } else if(Type == imageType::RGB_888){
        bitsPerPixel = 8;
        samplesPerPixel = 3;
        scanline = Width*3;
        photometric = 2;
        dataType = 0;
    } else if(Type == imageType::RGB_161616){
        bitsPerPixel = 16;
        samplesPerPixel = 3;
        scanline = Width*6;
        photometric = 2;
        dataType = 0;
    } else if(Type == imageType::RGB_323232){
        bitsPerPixel = 32;
        samplesPerPixel = 3;
        scanline = Width*12;
        photometric = 2;
        dataType = 3;
    } else if(Type == imageType::RGB_ALPHA_8888){
        bitsPerPixel = 8;
        samplesPerPixel = 4;
        scanline = Width*4;
        photometric = 2;
        dataType = 0;
    } else if(Type == imageType::RGB_ALPHA_16161616){
        bitsPerPixel = 16;
        samplesPerPixel = 4;
        scanline = Width*8;
        photometric = 2;
        dataType = 0;
    } else if(Type == imageType::RGB_ALPHA_32323232){
        bitsPerPixel = 32;
        samplesPerPixel = 4;
        scanline = Width*16;
        photometric = 2;
        dataType = 3;
    }

    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, Width);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, Height);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, bitsPerPixel);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, samplesPerPixel);
    TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, photometric);
    TIFFSetField(tif, TIFFTAG_DATATYPE, dataType);

    uint32 rowsperstrip = TIFFDefaultStripSize(tif, -1);

    TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, rowsperstrip);
    TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_PACKBITS);

    // Start CCITTFAX3 setting

    //uint32 group3options = GROUP3OPT_FILLBITS+GROUP3OPT_2DENCODING;
    //TIFFSetField(tif, TIFFTAG_GROUP3OPTIONS, group3options);
    //TIFFSetField(tif, TIFFTAG_FAXMODE, FAXMODE_CLASSF);
    //TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    //TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, -1L);


    // End CCITTFAX3 setting

    //TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

    //TIFFSetField(tif, TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
    //TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

    TIFFSetField(tif, TIFFTAG_RESOLUTIONUNIT, RESUNIT_INCH);
    TIFFSetField(tif, TIFFTAG_XRESOLUTION, 100.0);
    TIFFSetField(tif, TIFFTAG_YRESOLUTION, 100.0);

    //char page_number[20];
    //sprintf(page_number, "Page %d", 1);

    //TIFFSetField(tif, TIFFTAG_SUBFILETYPE, FILETYPE_PAGE);
    //TIFFSetField(tif, TIFFTAG_PAGENUMBER, 1, 1);
    //TIFFSetField(tif, TIFFTAG_PAGENAME, page_number);

    // Write pixels
    for(int row = 0; row < Height; row++){
        if (TIFFWriteScanline(tif, &Pixels[(Height -row -1)*scanline], row, 0) == -1){
            TIFFClose(tif);
            return true;
        }
    }

    // Close the file
    TIFFClose(tif);
    return true;
}
