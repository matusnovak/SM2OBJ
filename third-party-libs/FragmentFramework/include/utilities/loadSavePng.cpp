/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "loadSavePng.h"
#include "../math/math.h"
#include "../math/stringMath.h"
#include "file.h"
#include <png.h>
#include <zlib.h>

static void user_error_fn(png_structp png_ptr, png_const_charp error_msg){
}

static void user_warning_fn(png_structp png_ptr, png_const_charp warning_msg){
}

///=============================================================================
bool ffw::loadPNG(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, ffw::imageType* Type){
    return loadPNG(utf8ToWstr(Path), Pixels, Width, Height, Type);
}

///=============================================================================
bool ffw::loadPNG(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, ffw::imageType* Type){
    FILE *inputFile = _wfopen(Path.c_str(), L"rb");
    if(!inputFile)return false;

    uint8_t* header = new uint8_t[8];
    fread(header, 1, 8, inputFile);


    if(png_sig_cmp(header, 0, 8)){
        fclose(inputFile);
        return false;
    }

    png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, user_error_fn, user_warning_fn);

    if(!pngPtr){
        fclose(inputFile);
        return false;
    }

    png_infop infoPtr = png_create_info_struct(pngPtr);
    if(!infoPtr){
        fclose(inputFile);
        return false;
    }

    if(setjmp(png_jmpbuf(pngPtr))){
        fclose(inputFile);
        return false;
    }

    png_init_io(pngPtr, inputFile);
    png_set_sig_bytes(pngPtr, 8);

    png_read_info(pngPtr, infoPtr);

    int  width = png_get_image_width(pngPtr, infoPtr);
    int  height = png_get_image_height(pngPtr, infoPtr);
    png_byte colorType = png_get_color_type(pngPtr, infoPtr);
    png_byte bitDepth = png_get_bit_depth(pngPtr, infoPtr);

    //if(bitDepth == 16)
        //png_set_strip_16(pngPtr);

    if (bitDepth == 16)
        png_set_swap(pngPtr);

    if(colorType == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(pngPtr);

    imageType type;

    if(bitDepth == 1){
        if(colorType == PNG_COLOR_TYPE_GRAY){
            type = imageType::GRAYSCALE_8;
        } else {
            fclose(inputFile);
            return false;
        }
    } else if(bitDepth == 4){
        if(colorType == PNG_COLOR_TYPE_GRAY){
            type = imageType::GRAYSCALE_8;
        } else {
            fclose(inputFile);
            return false;
        }

    } else if(bitDepth == 8){
        if(colorType == PNG_COLOR_TYPE_GRAY){
            type = imageType::GRAYSCALE_8;

        } else if(colorType == PNG_COLOR_TYPE_GRAY_ALPHA){
            type = imageType::GRAYSCALE_ALPHA_8;

        } else if(colorType == PNG_COLOR_TYPE_RGB){
            type = imageType::RGB_888;

        } else if(colorType == PNG_COLOR_TYPE_RGB_ALPHA){
            type = imageType::RGB_ALPHA_8888;

        } else if(colorType == PNG_COLOR_TYPE_PALETTE){
            type = imageType::RGB_888;

        } else {
            fclose(inputFile);
            return false;
        }

    } else if(bitDepth == 16){
        if(colorType == PNG_COLOR_TYPE_GRAY){
            type = imageType::GRAYSCALE_16;

        } else if(colorType == PNG_COLOR_TYPE_GRAY_ALPHA){
            type = imageType::GRAYSCALE_ALPHA_16;

        } else if(colorType == PNG_COLOR_TYPE_RGB){
            type = imageType::RGB_161616;

        } else if(colorType == PNG_COLOR_TYPE_RGB_ALPHA){
            type = imageType::RGB_ALPHA_16161616;

        } else {
            fclose(inputFile);
            return false;
        }

    } else {
        fclose(inputFile);
        return false;
    }

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth
    if(colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8){
        png_set_expand_gray_1_2_4_to_8(pngPtr);
    }

    if(png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)){
        png_set_tRNS_to_alpha(pngPtr);
    }

    // Fill background color if image does not have transparency
    /*if(colorType == PNG_COLOR_TYPE_RGB || colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_PALETTE){
        png_set_filler(pngPtr, 0xFF, PNG_FILLER_AFTER);
    }*/

    /*if(colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA){
        png_set_gray_to_rgb(pngPtr);
    }*/

    if(Width != NULL)*Width = width;
    if(Height != NULL)*Height = height;
    if(Type != NULL)*Type = type;

    if(Pixels == NULL){
        fclose(inputFile);
        return true;
    }

    png_read_update_info(pngPtr, infoPtr);

    // Allocate memory for rows
    png_bytep* rowPointers = new png_bytep[height * sizeof(png_bytep)];
    for(int y = 0; y < height; y++) {
        rowPointers[y] = new png_byte[png_get_rowbytes(pngPtr, infoPtr)];
    }

    // Fill rows with pixels
    png_read_image(pngPtr, rowPointers);

    int stride = 0;

    if       (type == imageType::GRAYSCALE_8){
        *Pixels = new uint8_t[width*height];
        stride = width;

    } else if(type == imageType::GRAYSCALE_ALPHA_8){
        *Pixels = new uint8_t[width*height*2];
        stride = width*2;

    } else if(type == imageType::GRAYSCALE_16){
        *Pixels = new uint8_t[width*height*2];
        stride = width*2;

    } else if(type == imageType::GRAYSCALE_ALPHA_16){
        *Pixels = new uint8_t[width*height*4];
        stride = width*4;

    } else if(type == imageType::RGB_888){
        *Pixels = new uint8_t[width*height*3];
        stride = width*3;

    } else if(type == imageType::RGB_ALPHA_8888){
        *Pixels = new uint8_t[width*height*4];
        stride = width*4;

    } else if(type == imageType::RGB_161616){
        *Pixels = new uint8_t[width*height*6];
        stride = width*6;

    } else if(type == imageType::RGB_ALPHA_16161616){
        *Pixels = new uint8_t[width*height*8];
        stride = width*8;
    }

    for(int y = 0; y < height; y++) {
        memcpy(&((*Pixels)[stride *y]), rowPointers[height -y -1], stride);
    }

    delete[] header;
    for(int y = 0; y < height; y++) {
        delete[] rowPointers[y];
    }
    delete[] rowPointers;

    fclose(inputFile);

    return true;
}

///=============================================================================
bool ffw::savePNG(const std::string& Path, unsigned char* Pixels, int Width, int Height, ffw::imageType Type){
    return savePNG(utf8ToWstr(Path), Pixels, Width, Height, Type);
}

///=============================================================================
bool ffw::savePNG(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, ffw::imageType Type){
    if(Pixels == NULL)return false;
    if(Width == 0 || Height == 0)return false;
    if(!(Type == imageType::GRAYSCALE_8 ||
         Type == imageType::GRAYSCALE_16 ||
         Type == imageType::GRAYSCALE_ALPHA_8 ||
         Type == imageType::GRAYSCALE_ALPHA_16 ||
         Type == imageType::RGB_888 ||
         Type == imageType::RGB_ALPHA_8888 ||
         Type == imageType::RGB_161616 ||
         Type == imageType::RGB_ALPHA_16161616))return false;

    FILE *outputFile = _wfopen(Path.c_str(), L"wb");
    if(!outputFile){
        return false;
    }

    png_structp pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngPtr){
        fclose(outputFile);
        return false;
    }

    png_infop pngInfo = png_create_info_struct(pngPtr);
    if (!pngInfo){
        fclose(outputFile);
        return false;
    }

    if (setjmp(png_jmpbuf(pngPtr))){
        fclose(outputFile);
        return false;
    }

    png_init_io(pngPtr, outputFile);

    int bitDepth = 0;
    png_byte colorType = 0;
    int stride = 0;


    if       (Type == ffw::imageType::GRAYSCALE_8){
        colorType = PNG_COLOR_TYPE_GRAY;
        bitDepth = 8;
        stride = Width;

    } else if(Type == ffw::imageType::GRAYSCALE_16){
        colorType = PNG_COLOR_TYPE_GRAY;
        bitDepth = 16;
        stride = Width*2;

    } else if(Type == ffw::imageType::GRAYSCALE_ALPHA_8){
        colorType = PNG_COLOR_TYPE_GRAY_ALPHA;
        bitDepth = 8;
        stride = Width*2;

    } else if(Type == ffw::imageType::GRAYSCALE_ALPHA_16){
        colorType = PNG_COLOR_TYPE_GRAY_ALPHA;
        bitDepth = 16;
        stride = Width*4;

    } else if(Type == ffw::imageType::RGB_888){
        colorType = PNG_COLOR_TYPE_RGB;
        bitDepth = 8;
        stride = Width*3;

    } else if(Type == ffw::imageType::RGB_ALPHA_8888){
        colorType = PNG_COLOR_TYPE_RGB_ALPHA;
        bitDepth = 8;
        stride = Width*4;

    } else if(Type == ffw::imageType::RGB_161616){
        colorType = PNG_COLOR_TYPE_RGB;
        bitDepth = 16;
        stride = Width*6;

    } else if(Type == ffw::imageType::RGB_ALPHA_16161616){
        colorType = PNG_COLOR_TYPE_RGB_ALPHA;
        bitDepth = 16;
        stride = Width*8;
    }

    png_set_IHDR(
        pngPtr,
        pngInfo,
        Width, Height,
        bitDepth,
        colorType,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );

    png_write_info(pngPtr, pngInfo);

    //png_set_filler(pngPtr, 0, PNG_FILLER_AFTER);

    png_bytep* rowPointers = new png_bytep[Height];
    for(int y = 0; y < Height; y++){
        rowPointers[Height -y -1] = &Pixels[stride*y];
    }

    if(bitDepth == 16)
        png_set_swap(pngPtr);

    png_write_image(pngPtr, rowPointers);
    png_write_end(pngPtr, NULL);

    png_destroy_write_struct(&pngPtr, &pngInfo);

    delete[] rowPointers;

    fclose(outputFile);

    return true;
}
