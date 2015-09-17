/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "defaults.h"

sm2obj::defaults::defaults(){
    serializeItem(&inputBlueprintFolder, "input-blueprint-folder");
    serializeItem(&inputDataFolder, "input-data-folder");
    serializeItem(&outputFileFolder, "output-file-folder");
    serializeItem(&uvMapsOptions, "uv-maps-options");
    serializeItem(&exportMaterials, "exportMaterials");
    serializeItem(&useDiffuseTextures, "use-diffuse-textures");
    serializeItem(&useAlphaTextures, "use-alpha-textures");
    serializeItem(&useNormalTextures, "use-normal-textures");
    serializeItem(&useEmissiveTextures, "use-emissive-textures");
    serializeItem(&specularHighlight, "specular-highlight");
    serializeItem(&numOfThreads, "num-of-threads");
    serializeItem(&outputTextureFolder, "output-texture-folder");
    serializeItem(&textureOutputFormat, "texture-output-format");
    serializeItem(&textureExportType, "texture-export-type");
    serializeItem(&textureTileSize, "texture-tile-size");
    serializeItem(&textureNormals, "texture-normals");
    serializeItem(&exportAttachments, "export-attachments");
}

sm2obj::defaults::~defaults(){
}

bool sm2obj::defaults::load(const std::string& Path, std::vector<std::string>* Missing){
    //return deserializeAsJson(Path, Missing);
	ffw::var data;
	if(!ffw::loadJSON(Path, &data))return false;
	return deserialize(&data, Missing);
}

bool sm2obj::defaults::save(const std::string& Path){
    //return serializeAsJson(Path, true);
	ffw::var data;
	std::string dataStr;
	if(!serialize(&data, true))return false;
	ffw::encodeJSON(&dataStr, &data, true, true);
	return ffw::saveTXT(Path, dataStr);
}

