/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_TEXTURE_EXPORT
#define SM2OBJ_TEXTURE_EXPORT

#include <ffw.h>
#include "config.h"

namespace sm2obj{
    bool exportEmissiveAtlas(const std::string& InputConfigFolder, const std::string& OutputFolder, int TileWidth);
    bool exportTextures(const std::string& InputFolder, const std::string& OutputFolder, bool ConvertNormals);
    bool exportAtlases(const std::string& InputFolder, const std::string& OutputFolder, bool ConvertNormals);
};

#endif



