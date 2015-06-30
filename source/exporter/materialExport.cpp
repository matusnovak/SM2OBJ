/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "materialExport.h"
#include "config.h"

//static ffw::file material;

///=============================================================================
bool sm2obj::createMaterialAtlas(ffw::file* Output, bool UseDiffuse, bool UseNormal, bool UseAlpha, bool UseEmissive, bool Specular){
    Output->writeLine("# SM2OBJ\n");

    for(int i = 0; i < 3; i++){
        Output->writeLine("newmtl Mat_Atlas_" + ffw::valToString(i));
        Output->writeLine("Ka 0.000 0.000 0.000"); // Ambient color
        Output->writeLine("Kd 1.000 1.000 1.000"); // Diffuse color
        if(Specular){
            Output->writeLine("Ks 0.800 0.800 0.800"); // Specular level
            Output->writeLine("Ns 20.000"); // Glossiness
        } else {
            Output->writeLine("Ks 0.000 0.000 0.000"); // Specular level
            Output->writeLine("Ns 0.000"); // Glossiness
        }
        Output->writeLine("illum 2"); // Specular on/off (1 = disabled, 2 = enabled)
        Output->writeLine("Ni 1.000000");
        // Transparency (dissolved)
        Output->writeLine("d 1.000000");
        // Textures
        if(UseDiffuse) Output->writeLine("map_Kd Atlas_" +   ffw::valToString(i) + "_diff." + config::imageExtension);
        if(UseNormal)  Output->writeLine("map_bump Atlas_" + ffw::valToString(i) + "_bump." + config::imageExtension);
        if(UseAlpha)   Output->writeLine("map_d Atlas_" +    ffw::valToString(i) + "_alpha." + config::imageExtension);
        if(UseEmissive)Output->writeLine("map_Ke Atlas_" +    ffw::valToString(i) + "_emissive." + config::imageExtension);
        Output->writeLine("\n");
    }

    return true;
}

///=============================================================================
void sm2obj::createMaterialTile(ffw::file* Output, const blockInfoStruct* Block, int TextureIndex, bool UseDiffuse, bool UseNormal, bool UseAlpha, bool UseEmissive, bool Specular){
    Output->writeLine("newmtl Mat_" + Block->name + "_" + ffw::valToString(TextureIndex));
    Output->writeLine("Ka 0.000 0.000 0.000"); // Ambient color
    Output->writeLine("Kd 1.000 1.000 1.000"); // Diffuse color
    if(Specular){
        Output->writeLine("Ks 0.800 0.800 0.800"); // Specular level
        Output->writeLine("Ns 20.000"); // Glossiness
    } else {
        Output->writeLine("Ks 0.000 0.000 0.000"); // Specular level
        Output->writeLine("Ns 0.000"); // Glossiness
    }
    Output->writeLine("illum 2"); // Specular on/off (1 = disabled, 2 = enabled)
    if(UseEmissive && Block->emissive)
        // Emissive color
        Output->writeLine("ke " + ffw::valToString(Block->light.r, 6) + " " + ffw::valToString(Block->light.g, 6)
                           + " " + ffw::valToString(Block->light.b, 6) + " " + ffw::valToString(Block->light.a, 6));

    Output->writeLine("Ni 1.000000");
    // Transparency (dissolved)
    Output->writeLine("d 1.000000");
    // Textures
    if(UseDiffuse)Output->writeLine("map_Kd Tex_" +   ffw::valToString(TextureIndex) + "_diff." + config::imageExtension);
    if(UseNormal) Output->writeLine("map_bump Tex_" + ffw::valToString(TextureIndex) + "_bump." + config::imageExtension);
    if(UseAlpha)  Output->writeLine("map_d Tex_" +    ffw::valToString(TextureIndex) + "_alpha." + config::imageExtension);
    Output->writeLine("\n");
}
