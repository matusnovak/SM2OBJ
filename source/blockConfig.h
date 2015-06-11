/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#ifndef SMD2_EXPORTER_BLOCK_CONFIG
#define SMD2_EXPORTER_BLOCK_CONFIG

#include <ffw.h>

// Block info
struct blockInfoStruct {
    // Block name
    std::string name;
    // Block icon (not used)
    int icon;
    // Block texture ID
    // In this order: Front, Back, Top, Bottom, Left, Right
    uint16_t texture[6];
    // Block ID
    uint16_t id;
    // Is block transparent?
    bool transparent;
    // Is block emissive?
    bool emissive;
    // Light color
    ffw::color light;
    // Type of object
    // 0 = undefined
    // 1 = cube
    // 2 = wedge
    // 3 = corner
    // 4 = hepta
    // 5 = tetra
    int object;
};

bool loadBlockTypes(const std::string& Path);
bool loadBlockConfig(const std::string& Path);
const blockInfoStruct* findBlock(int ID);
const blockInfoStruct* findBlockByTexture(int Index);

#endif


