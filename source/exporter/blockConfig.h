/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SMD2OBJ_BLOCK_CONFIG
#define SMD2OBJ_BLOCK_CONFIG

#include <ffw.h>

namespace sm2obj{
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
        // -1 = undefined
        //  0 = cube
        //  1 = wedge
        //  2 = corner
        //  3 = X-shape
        //  4 = tetra
        //  5 = hepta
        int object;
    };

    void clearBlockConfig();
    bool loadBlockTypes(const std::string& Path);
    bool loadBlockConfig(const std::string& Path);
    const blockInfoStruct* findBlock(int ID);
    const blockInfoStruct* findBlockByTexture(int Index);
};

#endif


