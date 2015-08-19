/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_DEFAULTS
#define SM2OBJ_DEFAULTS

#include <ffw.h>

namespace sm2obj {
    class defaults: public ffw::serialization {
    public:
        defaults();
        ~defaults();
        bool load(const std::string& Path, std::vector<std::string>* Missing);
        bool save(const std::string& Path);

        std::string inputBlueprintFolder;
        std::string inputDataFolder;
        std::string outputFileFolder;
        int uvMapsOptions;
        bool exportMaterials;
        bool useDiffuseTextures;
        bool useAlphaTextures;
        bool useNormalTextures;
        bool useEmissiveTextures;
        bool specularHighlight;
        std::string numOfThreads;
        std::string outputTextureFolder;
        int textureOutputFormat;
        int textureExportType;
        int textureTileSize;
        int textureNormals;
        bool exportAttachments;
    };
};
#endif
