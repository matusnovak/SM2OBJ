/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_BLOCK_VERTICE_DATA
#define SM2OBJ_BLOCK_VERTICE_DATA

#include <ffw.h>

namespace sm2obj{
    extern ffw::vec2f globalTextureUvs[4];

    extern ffw::vec3f cubeVertices[8];
    extern ffw::vec4i cubeFaces[6];
    extern ffw::vec4i cubeFacesUvs[6];

    extern ffw::vec3f wedgeVertices[6];
    extern ffw::vec4i wedgeFaces[5];
    extern ffw::vec4i wedgeFacesUvs[5];

    extern ffw::vec3f heptaVertices[7];
    extern ffw::vec4i heptaFaces[7];
    extern ffw::vec4i heptaFacesUvs[7];

    extern ffw::vec3f tetraVertices[4];
    extern ffw::vec4i tetraFaces[4];
    extern ffw::vec4i tetraFacesUvs[4];

    extern ffw::vec3f cornerVertices[5];
    extern ffw::vec4i cornerFaces[5];
    extern ffw::vec4i cornerFacesUvs[5];

    extern ffw::vec3f XshapeVertices[8];
    extern ffw::vec4i XshapeFaces[2];
    extern ffw::vec4i XshapeFacesUvs[2];
};

#endif



