/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "defaults.h"

sm2obj::defaults::defaults(){
    serialize(&inputBlueprintFolder, "input-blueprint-folder");
    serialize(&inputDataFolder, "input-data-folder");
    serialize(&outputFileFolder, "output-file-folder");
    serialize(&uvMapsOptions, "uv-maps-options");
    serialize(&exportMaterials, "exportMaterials");
    serialize(&useDiffuseTextures, "use-diffuse-textures");
    serialize(&useAlphaTextures, "use-alpha-textures");
    serialize(&useNormalTextures, "use-normal-textures");
    serialize(&useEmissiveTextures, "use-emissive-textures");
    serialize(&specularHighlight, "specular-highlight");
    serialize(&numOfThreads, "num-of-threads");
    serialize(&outputTextureFolder, "output-texture-folder");
    serialize(&textureOutputFormat, "texture-output-format");
    serialize(&textureExportType, "texture-export-type");
    serialize(&textureTileSize, "texture-tile-size");
    serialize(&textureNormals, "texture-normals");
    serialize(&exportAttachments, "export-attachments");
}

sm2obj::defaults::~defaults(){
}

bool sm2obj::defaults::load(const std::string& Path){
    return deserializeAsJson(Path, NULL);
}

bool sm2obj::defaults::save(const std::string& Path){
    return serializeAsJson(Path, true);
}
