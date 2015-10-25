/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "defaults.h"

sm2obj::defaults::defaults(){
    serializeItem(&inputStarMadeFolder, "starmade-folder");
    serializeItem(&outputFolder, "output-folder");
    serializeItem(&uvMapsOptions, "uv-maps");
    serializeItem(&useDiffuseTextures, "use-diffuse");
    serializeItem(&useAlphaTextures, "use-alpha");
    serializeItem(&useBumpsOrNormals, "bumps-or-normals");
    serializeItem(&useEmissiveTextures, "use-emissive");
    serializeItem(&numOfThreads, "num-of-threads");
    serializeItem(&textureFormat, "texture-format");
    serializeItem(&textureSize, "texture-size");
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

