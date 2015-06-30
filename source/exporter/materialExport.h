/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_MATERIAL_EXPORT
#define SM2OBJ_MATERIAL_EXPORT

#include <ffw.h>
#include "config.h"
#include "blockConfig.h"

namespace sm2obj{
    bool createMaterialAtlas(ffw::file* Output, bool UseDiffuse, bool UseNormal, bool UseAlpha, bool UseEmissive, bool Specular);
    //bool beginMaterialExport();
    void createMaterialTile(ffw::file* Output, const blockInfoStruct* block, int TextureIndex, bool UseDiffuse, bool UseNormal, bool UseAlpha, bool UseEmissive, bool Specular);
    //void endMaterialExport();
}

#endif




