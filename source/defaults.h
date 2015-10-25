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

        std::string inputStarMadeFolder;
        std::string outputFolder;
        int uvMapsOptions;
        bool useDiffuseTextures;
        bool useAlphaTextures;
        bool useEmissiveTextures;
		bool useBumpsOrNormals;
        int numOfThreads;
        int textureFormat;
        int textureSize;
        bool exportAttachments;
    };
};
#endif
