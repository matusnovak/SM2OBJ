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
	bool exportEmissiveAtlas(const std::vector<blockInfoStruct>& BlockInfo, int Size, int Atlas, const std::string& OutputPath);
	//bool exportTextures(const exportBlueprintArgs& Args);
    bool exportDiffuseAtlas(const std::string& Path, int Size, const std::string& OutputPath);
	bool exportNormalAtlas(const std::string& Path, int Size, const std::string& OutputPath);
	bool exportAlphaAtlas(const std::string& Path, int Size, const std::string& OutputPath);
	bool exportBumpAtlas(const std::string& Path, int Size, const std::string& OutputPath);
	bool exportTileDiffuse(const std::vector<blockInfoStruct>& BlockInfo, const std::string& InputFolder, int Size, const std::string& OutputFolder, const std::string& TextureExtension);
	bool exportTileAlpha(const std::vector<blockInfoStruct>& BlockInfo, const std::string& InputFolder, int Size, const std::string& OutputFolder, const std::string& TextureExtension);
	bool exportTileNormals(const std::vector<blockInfoStruct>& BlockInfo, const std::string& InputFolder, int Size, const std::string& OutputFolder, const std::string& TextureExtension);
	bool exportTileBump(const std::vector<blockInfoStruct>& BlockInfo, const std::string& InputFolder, int Size, const std::string& OutputFolder, const std::string& TextureExtension);
};

#endif



