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
    //bool createMaterialAtlas(ffw::file* Output);
    //bool beginMaterialExport();
	bool createMaterialAtlas(ffw::file* Output, bool SpecularHighlight, bool Diffuse, bool Alpha, bool Normals, bool Emissive, const std::string& TextureExtension);
    //void createMaterialTile(ffw::file* Output, const blockInfoStruct* block, int TextureIndex);
	void createMaterialTile(ffw::file* Output, const blockInfoStruct* Block, int TextureIndex, bool SpecularHighlight, bool Diffuse, bool Alpha, bool Normals, bool Emissive, const std::string& TextureExtension);
    //void endMaterialExport();
}

#endif




