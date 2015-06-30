/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SMD2_EXPORT_BLUEPRINT
#define SMD2_EXPORT_BLUEPRINT

#include "config.h"

namespace sm2obj{
    bool exportBlueprint(const std::string& InputConfigFolder, const std::string& InputFolder,
                         const std::string& OutputFolder, const std::string& OutputName,
                         bool ExportUV, bool UseAtlas, bool ExportMaterials,
                         bool ExportDiffuse, bool ExportAlpha, bool ExportNormals, bool ExportEmissive,
                         bool SpecularHighlight, int NumOfThreads, bool ExportAttachments);
};

#endif
