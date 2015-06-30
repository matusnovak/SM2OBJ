/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_CONFIG
#define SM2OBJ_CONFIG

#include <ffw.h>
#include "constants.h"
#include "structures.h"

namespace sm2obj{
    extern chunkBufferStruct chunkBufferA;
    extern chunkBufferStruct chunkBufferB;

    namespace config {
        // Pointer to image saving function
        // Use one of these:
        // imageSaver = &ffw::saveBMP;
        // imageSaver = &ffw::savePNG;
        // imageSaver = &ffw::saveTGA;
        // imageSaver = &ffw::saveTIFF;
        extern std::string imageExtension;

        typedef bool (*imageSaver)(const std::string& Path, unsigned char* Pixels, int Width, int Height, ffw::imageType Type);
        typedef void (*exportLogError)(const std::string& Message);
        typedef void (*exportLogInfo)(const std::string& Message);
        typedef void (*exportLogDebug)(const std::string& Message);
        typedef void (*exportLogWarning)(const std::string& Message);
        typedef void (*exportProgress)(int Progress, int Total);
        typedef void (*exportExit)(bool Success);

        extern imageSaver imageSaverFunc;
        extern exportLogError exportLogErrorFunc;
        extern exportLogInfo exportLogInfoFunc;
        extern exportLogDebug exportLogDebugFunc;
        extern exportProgress exportProgressFunc;
        extern exportLogWarning exportLogWarningFunc;
        extern exportExit exportExitFunc;
    };
};

#endif
