/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#include "config.h"

chunkBufferStruct chunkBufferA;
chunkBufferStruct chunkBufferB;
bool (*imageSaver)(const std::string& Path, unsigned char* Pixels, int Width, int Height, ffw::imageType Type);
std::string imageExtension;
bool textureExport = true;
bool materialExport = true;
bool uvsExport = true;
bool useSpecularHighlight = false;
int threadsCount = 1;
std::string filePath;
bool exportDiffuse= true;
bool exportBump= true;
bool exportAlpha= true;
void (*exportProgressFunc)(int A, int B) = NULL;
void (*exportExitFunc)(bool Success) = NULL;
std::string fileOutputFolder;
std::string fileName;
std::string starMadeDataFolder;
