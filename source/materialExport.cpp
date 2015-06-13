/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#include "materialExport.h"
#include "config.h"

static ffw::file material;

///=============================================================================
bool createMaterialAtlas(){
    if(!material.open(fileOutputFolder + "\\" + fileName + ".mtl", false, true, true)){
        ffw::logger().error() << "Failed to open file for exporting material! Program might not have permissions!";
        return false;
    }
    material.writeLine("# StarMade Blueprint Exporter\n");

    for(int i = 0; i < 3; i++){
        material.writeLine("newmtl Mat_Atlas_" + ffw::valToString(i));
        material.writeLine("Ka 0.000 0.000 0.000"); // Ambient color
        material.writeLine("Kd 1.000 1.000 1.000"); // Diffuse color
        if(useSpecularHighlight){
            material.writeLine("Ks 0.800 0.800 0.800"); // Specular level
            material.writeLine("Ns 20.000"); // Glossiness
        } else {
            material.writeLine("Ks 0.000 0.000 0.000"); // Specular level
            material.writeLine("Ns 0.000"); // Glossiness
        }
        material.writeLine("illum 2"); // Specular on/off (1 = disabled, 2 = enabled)
        material.writeLine("Ni 1.000000");
        // Transparency (dissolved)
        material.writeLine("d 1.000000");
        // Textures
        if(exportDiffuse)material.writeLine("map_Kd Atlas_" +   ffw::valToString(i) + "_diff." + imageExtension);
        if(exportBump)   material.writeLine("map_bump Atlas_" + ffw::valToString(i) + "_bump." + imageExtension);
        if(exportAlpha)  material.writeLine("map_d Atlas_" +    ffw::valToString(i) + "_alpha." + imageExtension);
        material.writeLine("\n");
    }

    material.close();
    return true;
}

///=============================================================================
bool beginMaterialExport(){
    if(!material.open(fileOutputFolder + "\\" + fileName + ".mtl", false, true, true)){
        ffw::logger().error() << "Failed to open file for exporting material! Program might not have permissions!";
        return false;
    }
    material.writeLine("# StarMade Blueprint Exporter\n");
    return true;
}

///=============================================================================
void addMaterial(const blockInfoStruct* Block, int TextureIndex){
    material.writeLine("newmtl Mat_" + Block->name + "_" + ffw::valToString(TextureIndex));
    material.writeLine("Ka 0.000 0.000 0.000"); // Ambient color
    material.writeLine("Kd 1.000 1.000 1.000"); // Diffuse color
    if(useSpecularHighlight){
        material.writeLine("Ks 0.800 0.800 0.800"); // Specular level
        material.writeLine("Ns 20.000"); // Glossiness
    } else {
        material.writeLine("Ks 0.000 0.000 0.000"); // Specular level
        material.writeLine("Ns 0.000"); // Glossiness
    }
    material.writeLine("illum 2"); // Specular on/off (1 = disabled, 2 = enabled)
    if(Block->emissive)
        // Emissive color
        material.writeLine("ke " + ffw::valToString(Block->light.r, 6) + " " + ffw::valToString(Block->light.g, 6)
                           + " " + ffw::valToString(Block->light.b, 6) + " " + ffw::valToString(Block->light.a, 6));

    material.writeLine("Ni 1.000000");
    // Transparency (dissolved)
    material.writeLine("d 1.000000");
    // Textures
    if(exportDiffuse)material.writeLine("map_Kd Tex_" +   ffw::valToString(TextureIndex) + "_diff." + imageExtension);
    if(exportBump)   material.writeLine("map_bump Tex_" + ffw::valToString(TextureIndex) + "_bump." + imageExtension);
    if(exportAlpha)  material.writeLine("map_d Tex_" +    ffw::valToString(TextureIndex) + "_alpha." + imageExtension);
    material.writeLine("\n");
}

///=============================================================================
void endMaterialExport(){
    material.close();
}
