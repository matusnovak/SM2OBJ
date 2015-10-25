/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SMD2OBJ_BLOCK_CONFIG
#define SMD2OBJ_BLOCK_CONFIG

#include <ffw.h>
#include "config.h"

namespace sm2obj{
    bool loadBlockTypes(std::vector<blockTypeStruct>& BlockTypes, const std::string& Path);
    bool loadBlockConfig(std::vector<blockTypeStruct>& BlockTypes, std::vector<blockInfoStruct>& BlockInfo, const std::string& Path);
    const blockInfoStruct* findBlock(const std::vector<blockInfoStruct>& BlockInfo, int ID);
    const blockInfoStruct* findBlockByTexture(const std::vector<blockInfoStruct>& BlockInfo, int Index);
};

#endif


