/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "blockVerticeData.h"

/*ffw::vec2f globalTextureUvs[4] = {
    ffw::vec2f(1.000000, 0.000000),
    ffw::vec2f(1.000000, 1.000000),
    ffw::vec2f(0.000000, 1.000000),
    ffw::vec2f(0.000000, 0.000000)
};*/

// Mirrored
ffw::vec2f sm2obj::globalTextureUvs[4] = {
    ffw::vec2f(0.000000, 0.000000),
    ffw::vec2f(0.000000, 1.000000),
    ffw::vec2f(1.000000, 1.000000),
    ffw::vec2f(1.000000, 0.000000)
};

ffw::vec3f sm2obj::cubeVertices[8] = {
    ffw::vec3f(1.000000, 1.000000, 0.000000),
    ffw::vec3f(1.000000, -0.000000, -0.000000),
    ffw::vec3f(1.000000, 0.000000, -1.000000),
    ffw::vec3f(1.000000, 1.000000, -1.000000),
    ffw::vec3f(0.000000, 1.000000, 0.000000),
    ffw::vec3f(0.000000, -0.000000, -0.000000),
    ffw::vec3f(0.000000, 1.000000, -1.000000),
    ffw::vec3f(0.000000, 0.000000, -1.000000)
};

ffw::vec4i sm2obj::cubeFaces[6] = {
    ffw::vec4i(4, 3, 8, 7), // Top
    ffw::vec4i(2, 1, 5, 6), // Bottom
    ffw::vec4i(1, 4, 7, 5), // Front
    ffw::vec4i(6, 8, 3, 2), // Back
    ffw::vec4i(1, 2, 3, 4), // Left
    ffw::vec4i(7, 8, 6, 5)  // Right
};

ffw::vec4i sm2obj::cubeFacesUvs[6] = {
    ffw::vec4i(1, 2, 3, 4), // 1 2 3 4
    ffw::vec4i(3, 4, 1, 2), // 4 1 2 3
    ffw::vec4i(3, 4, 1, 2), // 1 2 3 4
    ffw::vec4i(3, 4, 1, 2), // 3 4 1 2
    ffw::vec4i(2, 3, 4, 1), // 2 3 4 1
    ffw::vec4i(4, 1, 2, 3)  // 2 3 4 1 // 2 1 4 3
};



ffw::vec3f sm2obj::wedgeVertices[6] = {
    ffw::vec3f(0.000000, 0.000000, 0.000000),
    ffw::vec3f(1.000000, 0.000000, 0.000000),
    ffw::vec3f(1.000000, 1.000000, 0.000000),
    ffw::vec3f(0.000000, 1.000000, -0.000000),
    ffw::vec3f(0.000000, 0.000000, -1.000000),
    ffw::vec3f(1.000000, 0.000000, -1.000000)
};

ffw::vec4i sm2obj::wedgeFaces[5] = {
    ffw::vec4i(1, 2, 3, 4),
    ffw::vec4i(1, 4, 5, -1),
    ffw::vec4i(2, 1, 5, 6),
    ffw::vec4i(5, 4, 3, 6),
    ffw::vec4i(2, 6, 3, -1)
};

ffw::vec4i sm2obj::wedgeFacesUvs[5] = {
    ffw::vec4i(4, 1, 2, 3),  // 4 1 2 3
    ffw::vec4i(1, 2, 4, -1), // 1 2 4
    ffw::vec4i(2, 3, 4, 1),  // 2 3 4 1
    ffw::vec4i(1, 2, 3, 4),  // 1 2 3 4
    ffw::vec4i(4, 1, 3, -1)  // 4 1 3
};



ffw::vec3f sm2obj::heptaVertices[7] = {
    ffw::vec3f(1.000000, 1.000000, 0.000000),
    ffw::vec3f(1.000000, 0.000000, 0.000000),
    ffw::vec3f(1.000000, 0.000000, -1.000000),
    ffw::vec3f(0.000000, 1.000000, 0.000000),
    ffw::vec3f(0.000000, 0.000000, 0.000000),
    ffw::vec3f(0.000000, 1.000000, -1.000000),
    ffw::vec3f(0.000000, 0.000000, -1.000000)
};

ffw::vec4i sm2obj::heptaFaces[7] = {
    ffw::vec4i(1, 2, 3, -1),
    ffw::vec4i(2, 1, 4, 5),
    ffw::vec4i(6, 7, 5, 4),
    ffw::vec4i(3, 7, 6, -1),
    ffw::vec4i(4, 1, 6, -1),
    ffw::vec4i(5, 7, 3, 2),
    ffw::vec4i(6, 1, 3, -1)
};

ffw::vec4i sm2obj::heptaFacesUvs[7] = {
    ffw::vec4i(3, 4, 1, -1), // 3 4 1
    ffw::vec4i(1, 2, 3, 4),  // 1 2 3 4
    ffw::vec4i(1, 4, 3, 2),  // 1 4 3 2
    ffw::vec4i(2, 1, 4, -1), // 2 1 4
    ffw::vec4i(2, 3, 1, -1), // 2 3 1
    ffw::vec4i(3, 4, 1, 2),  // 3 4 1 2
    ffw::vec4i(1, 3, 4, -1)  // 1 3 4
};



ffw::vec3f sm2obj::tetraVertices[4] = {
    ffw::vec3f(-0.000000, 0.000000, 0.000000),
    ffw::vec3f(1.000000, 0.000000, 0.000000),
    ffw::vec3f(-0.000000, 1.000000, 0.000000),
    ffw::vec3f(-0.000000, 0.000000, -1.000000)
};

ffw::vec4i sm2obj::tetraFaces[4] = {
    ffw::vec4i(1, 2, 3, -1),
    ffw::vec4i(4, 1, 3, -1),
    ffw::vec4i(1, 4, 2, -1),
    ffw::vec4i(3, 2, 4, -1)
};

ffw::vec4i sm2obj::tetraFacesUvs[4] = {
    ffw::vec4i(4, 1, 3, -1), // 4 1 3
    ffw::vec4i(4, 1, 2, -1), // 4 1 2
    ffw::vec4i(2, 3, 1, -1), // 2 3 1
    ffw::vec4i(3, 4, 2, -1)  // 3 4 2
};



ffw::vec3f sm2obj::cornerVertices[5] = {
    ffw::vec3f(1.000000, 0.000000, -1.000000),
    ffw::vec3f(0.000000, 0.000000, -1.000000),
    ffw::vec3f(1.000000, 1.000000, 0.000000),
    ffw::vec3f(1.000000, 0.000000, 0.000000),
    ffw::vec3f(0.000000, 0.000000, 0.000000)
};

ffw::vec4i sm2obj::cornerFaces[5] = {
    ffw::vec4i(1, 2, 3, -1),
    ffw::vec4i(4, 1, 3, -1),
    ffw::vec4i(5, 4, 3, -1),
    ffw::vec4i(2, 1, 4, 5),
    ffw::vec4i(2, 5, 3, -1)
};

ffw::vec4i sm2obj::cornerFacesUvs[5] = {
    ffw::vec4i(2, 3, 1, -1), // 2 3 1
    ffw::vec4i(4, 1, 3, -1), // 4 1 3
    ffw::vec4i(4, 1, 2, -1), // 4 1 2
    ffw::vec4i(4, 1, 2, 3),  // 4 1 2 3
    ffw::vec4i(3, 4, 1, -1)  // 3 4 1
};


ffw::vec3f sm2obj::XshapeVertices[8] = {
    ffw::vec3f(0.000000, 0.000000, -1.000000),
    ffw::vec3f(1.000000, 0.000000, 0.000000),
    ffw::vec3f(0.000000, 1.000000, -1.000000),
    ffw::vec3f(1.000000, 1.000000, 0.000000),
    ffw::vec3f(0.000000, 0.000000, -0.000000),
    ffw::vec3f(1.000000, 0.000000, -1.000000),
    ffw::vec3f(0.000000, 1.000000, 0.000000),
    ffw::vec3f(1.000000, 1.000000, -1.000000)
};

ffw::vec4i sm2obj::XshapeFaces[2] = {
    ffw::vec4i(1, 2, 4, 3),
    ffw::vec4i(5, 6, 8, 7)
};

ffw::vec4i sm2obj::XshapeFacesUvs[2] = {
    ffw::vec4i(2, 3, 4, 1),
    ffw::vec4i(2, 3, 4, 1)
};

