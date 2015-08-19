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
	bool exportEmissiveAtlas(const exportBlueprintArgs& Args);
    bool exportTextures(const exportBlueprintArgs& Args);
    bool exportAtlases(const exportBlueprintArgs& Args);
};

#endif



