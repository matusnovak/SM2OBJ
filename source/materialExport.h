/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#ifndef SMD2_EXPORTER_MATERIAL_EXPORT
#define SMD2_EXPORTER_MATERIAL_EXPORT

#include <ffw.h>
#include "config.h"
#include "blockConfig.h"

bool createMaterialAtlas();
bool beginMaterialExport();
void addMaterial(const blockInfoStruct* block, int TextureIndex);
void endMaterialExport();


#endif




