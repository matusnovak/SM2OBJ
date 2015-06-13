/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#ifndef SMD2_EXPORTER_CONFIG
#define SMD2_EXPORTER_CONFIG

#include <ffw.h>

#define CHUNK_SIZE 16*16*16
#define CHUNK_MAX_VERTICES 8
#define CHUNK_MAX_INDICES 8

struct chunkBufferStruct {
    ffw::vec3f vertices[CHUNK_SIZE * CHUNK_MAX_VERTICES];
    uint32_t verticesCount;
    ffw::vec4i indices[CHUNK_SIZE * CHUNK_MAX_INDICES];
    ffw::vec4i indicesUvs[CHUNK_SIZE * CHUNK_MAX_INDICES];
    uint16_t indicesMat[CHUNK_SIZE * CHUNK_MAX_INDICES][3];
    uint32_t indicesCount;
    uint32_t indicesOffset;
};

extern chunkBufferStruct chunkBufferA;
extern chunkBufferStruct chunkBufferB;
// Pointer to image saving function
// Use one of these:
// imageSaver = &ffw::saveBMP;
// imageSaver = &ffw::savePNG;
// imageSaver = &ffw::saveTGA;
// imageSaver = &ffw::saveTIFF;
extern bool (*imageSaver)(const std::string& Path, unsigned char* Pixels, int Width, int Height, ffw::imageType Type);
// Pointer to image saving function
// Use one of these:
// imageExtension = "bmp";
// imageExtension = "png";
// imageExtension = "tga";
// imageExtension = "tiff";
extern std::string imageExtension;
// Should textures be exported?
extern bool textureExport;
// Should textures be split?
extern bool textureSplit;
// Should materials be exported?
extern bool materialExport;
// Should UVs be exported?
extern bool uvsExport;
// Specular highlights on / off
extern bool useSpecularHighlight;
// Number of threads 0 - 16
extern int threadsCount;
// Path to blueprint file, for example:
// C:\\StarMade\\blueprints\\Isanth Type-Zero Mb\\DATA\\Isanth Type-Zero Mb.0.0.0.smd2
extern std::string filePath;
// Output folder
extern std::string fileOutputFolder;
// Output filename (without extension)
extern std::string fileName;
// Path to StarMade data folder, for example:
// C:\\StarMade\\data
extern std::string starMadeDataFolder;
// Should materials use diffuse texture?
extern bool exportDiffuse;
// Should materials use bump texture?
extern bool exportBump;
// Should materials use alpha texture?
extern bool exportAlpha;
// Callback when chunks are beeing exported
// A - current chunk
// B - total chunks
extern void (*exportProgressFunc)(int A, int B);
// Callback when export exists with Success or without
extern void (*exportExitFunc)(bool Success);

#endif
