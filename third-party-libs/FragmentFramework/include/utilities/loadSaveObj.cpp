/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "loadSaveObj.h"
#include "../math/math.h"
#include "../math/stringMath.h"
#include <iostream>
#include <fstream>

///=============================================================================
bool ffw::loadOBJ(const std::string& Path, float** Vertices, unsigned int* NumVertices){
    return loadOBJ(utf8ToWstr(Path), Vertices, NumVertices);
}

///=============================================================================
bool ffw::loadOBJ(const std::wstring& Path, float** Vertices, unsigned int* NumVertices){

    std::ifstream file;
    file.open(wstrToAnsi(Path), std::ifstream::in);
    if(!file){
        //logger().error() << "[File loader] " << path << " failed to open!";
        return false;
    }

    std::string temp;
    std::vector<int> objectBegin;
    std::vector<int> objectEnd;
    std::vector<int> vNum;
    std::vector<int> vnNum;
    std::vector<int> vtNum;
    std::vector<int> fNum;
    std::vector<int> vertNum;
    std::vector<bool> texCoordsExists;
    std::vector<bool> normalsExists;
    int objectCount = -1;
    int begin = -1;
    bool endOfObject = false;
    int line = 0;
    while(std::getline(file, temp)){
        // If line is a vertice
        if        (temp[0] == 'v' && temp[1] == ' '){
            if(endOfObject){
                // Found new object
                objectBegin.push_back( begin );
                objectEnd.push_back( line-1 );
                begin = -1;
                endOfObject = false;
            }
            if(begin < 0){
                begin = line;
                objectCount++;
                vNum.push_back(0);
                vnNum.push_back(0);
                vtNum.push_back(0);
                fNum.push_back(0);
                vertNum.push_back(0);
                texCoordsExists.push_back(false);
                normalsExists.push_back(false);
            }
            vNum[objectCount]++;

        // If line is a normal
        } else if (temp[0] == 'v' && temp[1] == 'n'){
            vnNum[objectCount]++;
            if(!normalsExists[objectCount])normalsExists[objectCount] = true;

        // If line is a texture coord
        } else if (temp[0] == 'v' && temp[1] == 't'){
            vtNum[objectCount]++;
            if(!texCoordsExists[objectCount])texCoordsExists[objectCount] = true;

        // If line is a face (triangle or quad)
        } else if (temp[0] == 'f' && temp[1] == ' '){
            fNum[objectCount]++;
            std::vector<std::string> tokens = ffw::getTokens(temp, ' ');
            if(tokens.size() == 4)vertNum[objectCount] += 3;
            else if(tokens.size() == 5)vertNum[objectCount] += 6;
            else {
                //logger().error() << "[File loader] " << path << " is corrupted!";
                return false;
            }
            endOfObject = true;
        }
        line++;
    }
    objectBegin.push_back( begin );
    objectEnd.push_back( line-1 );

    /*if(objectCount+1 <= 0){
        logger().error() << "[File loader] " << path << " has no objects!";
        return false;
    }*/

    /*logger().debug() << "[File loader] " << path << " contains: " << objectCount+1 << " objects ->";
    for(int i = 0; i < objectCount+1; i++){
        logger().debug() << "Object ID: " << i << " verices: " << vNum[i] << " normals: " << vnNum[i] << " tex coords: " << vtNum[i] << " faces: " << fNum[i] << " total vertices: " << vertNum[i];
    }*/

    // Temporary buffers
    //float*  vert        [objectCount+1];
    //float*  norm        [objectCount+1];
    //float*  texCoords   [objectCount+1];
    //int*    faces       [objectCount+1];

	float** vert = new float*[objectCount + 1];
	float** norm = new float*[objectCount + 1];
	float** texCoords = new float*[objectCount + 1];
	int** faces = new int*[objectCount + 1];

    // Fill buffers for each object
    for(int i = 0; i < objectCount+1; i++){
        file.clear();
        file.seekg(0, file.beg);
        line = 0;

        /*if(!normalsExists[i]){
            logger().warning() << "[File loader] " << path << " object: " << i << " has no normals!";
        }
        if(!texCoordsExists[i]){
            logger().warning() << "[File loader] " << path << " object: " << i << " has no texure coordinates!";
        }*/

        // Create buffers
        vert[i] = new float[vNum[i]*3];
        if(normalsExists[i])
            norm[i] = new float[vnNum[i]*3];
        if(texCoordsExists[i])
            texCoords[i] = new float[vtNum[i]*2];
        faces[i] = new int[vertNum[i]*3];

        // Counters
        int vNumCount = 0;
        int vnNumCount = 0;
        int vtNumCount = 0;
        int fNumCount = 0;

        while(std::getline(file, temp)){
            // Skip to the begining of the object
            if(line < objectBegin[i]){
                line++;
                continue;
            }
            // Get line tokens
            std::vector<std::string> tokens =ffw:: getTokens(temp, ' ');

            // Line is a vertex
            if(tokens.size() == 4 && tokens[0] == "v"){
                vert[i][(vNumCount*3) +0] = ffw::stringToVal<float>(tokens[1]);
                vert[i][(vNumCount*3) +1] = ffw::stringToVal<float>(tokens[2]);
                vert[i][(vNumCount*3) +2] = ffw::stringToVal<float>(tokens[3]);
                vNumCount++;
            }
            // Line is a normal
            if(tokens.size() == 4 && tokens[0] == "vn" && normalsExists[i]){
                norm[i][(vnNumCount*3) +0] = ffw::stringToVal<float>(tokens[1]);
                norm[i][(vnNumCount*3) +1] = ffw::stringToVal<float>(tokens[2]);
                norm[i][(vnNumCount*3) +2] = ffw::stringToVal<float>(tokens[3]);
                vnNumCount++;
            }
            // Line is a texture coord
            if(tokens.size() >= 3 && tokens[0] == "vt" && texCoordsExists[i]){
                texCoords[i][(vtNumCount*2) +0] = ffw::stringToVal<float>(tokens[1]);
                texCoords[i][(vtNumCount*2) +1] = ffw::stringToVal<float>(tokens[2]);
                vtNumCount++;
            }
            // Line is a face
            if(tokens.size() >= 4 && tokens[0] == "f"){
                // Face is a triangle
                if(tokens.size() == 4){
                    std::vector<std::string> v0 = ffw::getTokens(tokens[1], '/');
                    std::vector<std::string> v1 = ffw::getTokens(tokens[2], '/');
                    std::vector<std::string> v2 = ffw::getTokens(tokens[3], '/');
                    // Check if we get all tokens
                    if(v0.size() != v1.size() || v0.size() != v2.size()){
                        //logger().error() << "[File loader] " << path << " is corrupted at line: " << line;
                        for(int p = 0; p < objectCount+1; p++){
                            delete[] vert[p];
                            if(normalsExists[p])   delete[] norm[p];
                            if(texCoordsExists[p]) delete[] texCoords[p];
                            delete[] faces[p];
                        }
						delete[] vert;
						delete[] norm;
						delete[] texCoords;
						delete[] faces;
                        return false;
                    }

                    // No texure coordinates or normals
                    if(v0.size() == 1){
                        faces[i][(fNumCount)+0] = ffw::stringToVal<int>(v2[0]);
                        faces[i][(fNumCount)+3] = ffw::stringToVal<int>(v1[0]);
                        faces[i][(fNumCount)+6] = ffw::stringToVal<int>(v0[0]);

                    // Texutre coordinates only
                    } else if(v0.size() == 2 && tokens[1].find("//") == std::string::npos){
                        faces[i][(fNumCount)+0] = ffw::stringToVal<int>(v2[0]);    faces[i][(fNumCount)+1] = ffw::stringToVal<int>(v2[1]);    faces[i][(fNumCount)+2] = -1;
                        faces[i][(fNumCount)+3] = ffw::stringToVal<int>(v1[0]);    faces[i][(fNumCount)+4] = ffw::stringToVal<int>(v1[1]);    faces[i][(fNumCount)+5] = -1;
                        faces[i][(fNumCount)+6] = ffw::stringToVal<int>(v0[0]);    faces[i][(fNumCount)+7] = ffw::stringToVal<int>(v0[1]);    faces[i][(fNumCount)+8] = -1;

                    // Normals only
                    } else if(v0.size() == 2 && tokens[1].find("//") != std::string::npos){
                        faces[i][(fNumCount)+0] = ffw::stringToVal<int>(v2[0]);    faces[i][(fNumCount)+1] = -1;    faces[i][(fNumCount)+2] = ffw::stringToVal<int>(v2[1]);
                        faces[i][(fNumCount)+3] = ffw::stringToVal<int>(v1[0]);    faces[i][(fNumCount)+4] = -1;    faces[i][(fNumCount)+5] = ffw::stringToVal<int>(v1[1]);
                        faces[i][(fNumCount)+6] = ffw::stringToVal<int>(v0[0]);    faces[i][(fNumCount)+7] = -1;    faces[i][(fNumCount)+8] = ffw::stringToVal<int>(v0[1]);
                    // Both
                    } else {
                        faces[i][(fNumCount)+0] = ffw::stringToVal<int>(v2[0]);    faces[i][(fNumCount)+1] = ffw::stringToVal<int>(v2[1]);    faces[i][(fNumCount)+2] = ffw::stringToVal<int>(v2[2]);
                        faces[i][(fNumCount)+3] = ffw::stringToVal<int>(v1[0]);    faces[i][(fNumCount)+4] = ffw::stringToVal<int>(v1[1]);    faces[i][(fNumCount)+5] = ffw::stringToVal<int>(v1[2]);
                        faces[i][(fNumCount)+6] = ffw::stringToVal<int>(v0[0]);    faces[i][(fNumCount)+7] = ffw::stringToVal<int>(v0[1]);    faces[i][(fNumCount)+8] = ffw::stringToVal<int>(v0[2]);
                    }
                    // We have a triangle of 3 vertices, each containing 3 indices
                    fNumCount += 9;
                // Face is a quad
                } else if(tokens.size() == 5){
                    // Check if we get all tokens
                    std::vector<std::string> v0 = ffw::getTokens(tokens[1], '/');
                    std::vector<std::string> v1 = ffw::getTokens(tokens[2], '/');
                    std::vector<std::string> v2 = ffw::getTokens(tokens[3], '/');
                    std::vector<std::string> v3 = ffw::getTokens(tokens[4], '/');
                    // Check if we get all tokens
                    if(v0.size() != v1.size() || v0.size() != v2.size() || v0.size() != v3.size()){
                        //logger().error() << "[File loader] " << path << " is corrupted at line: " << line;
                        for(int p = 0; p < objectCount+1; p++){
                            delete[] vert[p];
                            if(normalsExists[p])   delete[] norm[p];
                            if(texCoordsExists[p]) delete[] texCoords[p];
                            delete[] faces[p];
                        }
						delete[] vert;
						delete[] norm;
						delete[] texCoords;
						delete[] faces;
                        return false;
                    }

                    // No texure coordinates or normals
                    if(v0.size() == 1){
                        faces[i][(fNumCount*9)+0] = ffw::stringToVal<int>(v2[0]);
                        faces[i][(fNumCount*9)+3] = ffw::stringToVal<int>(v1[0]);
                        faces[i][(fNumCount*9)+6] = ffw::stringToVal<int>(v0[0]);

                        faces[i][(fNumCount*9)+0+9] = ffw::stringToVal<int>(v3[0]);
                        faces[i][(fNumCount*9)+3+9] = ffw::stringToVal<int>(v2[0]);
                        faces[i][(fNumCount*9)+6+9] = ffw::stringToVal<int>(v0[0]);

                    // Texutre coordinates only
                    } else if(v0.size() == 2 && tokens[1].find("//") == std::string::npos){
                        faces[i][(fNumCount)+0] = ffw::stringToVal<int>(v2[0]);    faces[i][(fNumCount)+1] = -1;    faces[i][(fNumCount)+2] = ffw::stringToVal<int>(v2[1]);
                        faces[i][(fNumCount)+3] = ffw::stringToVal<int>(v1[0]);    faces[i][(fNumCount)+4] = -1;    faces[i][(fNumCount)+5] = ffw::stringToVal<int>(v1[1]);
                        faces[i][(fNumCount)+6] = ffw::stringToVal<int>(v0[0]);    faces[i][(fNumCount)+7] = -1;    faces[i][(fNumCount)+8] = ffw::stringToVal<int>(v0[1]);

                        faces[i][(fNumCount)+0+9] = ffw::stringToVal<int>(v3[0]);  faces[i][(fNumCount)+1+9] = -1;  faces[i][(fNumCount)+2+9] = ffw::stringToVal<int>(v3[1]);
                        faces[i][(fNumCount)+3+9] = ffw::stringToVal<int>(v2[0]);  faces[i][(fNumCount)+4+9] = -1;  faces[i][(fNumCount)+5+9] = ffw::stringToVal<int>(v2[1]);
                        faces[i][(fNumCount)+6+9] = ffw::stringToVal<int>(v0[0]);  faces[i][(fNumCount)+7+9] = -1;  faces[i][(fNumCount)+8+9] = ffw::stringToVal<int>(v0[1]);

                    // Normals only
                    } else if(v0.size() == 2 && tokens[1].find("//") != std::string::npos){
                        faces[i][(fNumCount)+0] = ffw::stringToVal<int>(v2[0]);    faces[i][(fNumCount)+1] = ffw::stringToVal<int>(v2[1]);    faces[i][(fNumCount)+2] = -1;
                        faces[i][(fNumCount)+3] = ffw::stringToVal<int>(v1[0]);    faces[i][(fNumCount)+4] = ffw::stringToVal<int>(v1[1]);    faces[i][(fNumCount)+5] = -1;
                        faces[i][(fNumCount)+6] = ffw::stringToVal<int>(v0[0]);    faces[i][(fNumCount)+7] = ffw::stringToVal<int>(v0[1]);    faces[i][(fNumCount)+8] = -1;

                        faces[i][(fNumCount)+0+9] = ffw::stringToVal<int>(v3[0]);  faces[i][(fNumCount)+1+9] = ffw::stringToVal<int>(v3[1]);  faces[i][(fNumCount)+2+9] = -1;
                        faces[i][(fNumCount)+3+9] = ffw::stringToVal<int>(v2[0]);  faces[i][(fNumCount)+4+9] = ffw::stringToVal<int>(v2[1]);  faces[i][(fNumCount)+5+9] = -1;
                        faces[i][(fNumCount)+6+9] = ffw::stringToVal<int>(v0[0]);  faces[i][(fNumCount)+7+9] = ffw::stringToVal<int>(v0[1]);  faces[i][(fNumCount)+8+9] = -1;
                    // Both
                    } else {
                        faces[i][(fNumCount)+0] = ffw::stringToVal<int>(v2[0]);    faces[i][(fNumCount)+1] = ffw::stringToVal<int>(v2[1]);    faces[i][(fNumCount)+2] = ffw::stringToVal<int>(v2[2]);
                        faces[i][(fNumCount)+3] = ffw::stringToVal<int>(v1[0]);    faces[i][(fNumCount)+4] = ffw::stringToVal<int>(v1[1]);    faces[i][(fNumCount)+5] = ffw::stringToVal<int>(v1[2]);
                        faces[i][(fNumCount)+6] = ffw::stringToVal<int>(v0[0]);    faces[i][(fNumCount)+7] = ffw::stringToVal<int>(v0[1]);    faces[i][(fNumCount)+8] = ffw::stringToVal<int>(v0[2]);

                        faces[i][(fNumCount)+0+9] = ffw::stringToVal<int>(v3[0]);  faces[i][(fNumCount)+1+9] = ffw::stringToVal<int>(v3[1]);  faces[i][(fNumCount)+2+9] = ffw::stringToVal<int>(v3[2]);
                        faces[i][(fNumCount)+3+9] = ffw::stringToVal<int>(v2[0]);  faces[i][(fNumCount)+4+9] = ffw::stringToVal<int>(v2[1]);  faces[i][(fNumCount)+5+9] = ffw::stringToVal<int>(v2[2]);
                        faces[i][(fNumCount)+6+9] = ffw::stringToVal<int>(v0[0]);  faces[i][(fNumCount)+7+9] = ffw::stringToVal<int>(v0[1]);  faces[i][(fNumCount)+8+9] = ffw::stringToVal<int>(v0[2]);
                    }
                    // We have a 2 triangles of 3 vertices, each containing 3 indices
                    fNumCount += 18;
                }
            }

            line++;
            if(line > objectEnd[i])break;
        }

    }

    // Get vertex count of all objects
    (*NumVertices) = 0;
    for(int i = 0; i < objectCount+1; i++){
        (*NumVertices) += vertNum[i];
    }

    // 8 floats per one vertex
    // X, Y, Z, Xn, Yn, Zn, U, V
    *Vertices = new float[(*NumVertices)*8];

    // Fill buffer for each object
    for(int i = 0; i < objectCount+1; i++){
        int offset = 0;
        // For each triangle
        for(int f = 0; f < vertNum[i]; f += 3){
            // Calculate normals
            ffw::vec3f normal;
            //normalsExists[i] = false;
            if(!normalsExists[i]){
                int v0Index = faces[i][(f*3)+(0)+0]-1;
                int v1Index = faces[i][(f*3)+(3)+0]-1;
                int v2Index = faces[i][(f*3)+(6)+0]-1;

                while(v0Index >= vNum[i]) v0Index -= vNum[i];
                while(v1Index >= vNum[i]) v1Index -= vNum[i];
                while(v2Index >= vNum[i]) v2Index -= vNum[i];

                ffw::vec3f v0;
                ffw::vec3f v1;
                ffw::vec3f v2;

                v0.x = vert[i][(v0Index*3)+0];
                v0.y = vert[i][(v0Index*3)+1];
                v0.z = vert[i][(v0Index*3)+2];

                v1.x = vert[i][(v1Index*3)+0];
                v1.y = vert[i][(v1Index*3)+1];
                v1.z = vert[i][(v1Index*3)+2];

                v2.x = vert[i][(v2Index*3)+0];
                v2.y = vert[i][(v2Index*3)+1];
                v2.z = vert[i][(v2Index*3)+2];

                ffw::vec3f dir0 = v0 - v1;
                ffw::vec3f dir1 = v0 - v2;
                normal = ffw::cross(dir0, dir1);
                normal.normalize();
            }

            // For each vertex
            for(unsigned int v = 0; v < 3; v++){
                int vIndex = faces[i][(f*3)+(v*3)+0]-1;
                int nIndex = faces[i][(f*3)+(v*3)+2]-1;
                int tIndex = faces[i][(f*3)+(v*3)+1]-1;

                while(vIndex >= vNum[i]) vIndex -= vNum[i];
                (*Vertices)[offset + (f*8)+(v*8)+0] = vert[i][(vIndex*3)+0];
                (*Vertices)[offset + (f*8)+(v*8)+1] = vert[i][(vIndex*3)+1];
                (*Vertices)[offset + (f*8)+(v*8)+2] = vert[i][(vIndex*3)+2];

                if(!normalsExists[i]){
                    (*Vertices)[offset + (f*8)+(v*8)+3] = normal.x;
                    (*Vertices)[offset + (f*8)+(v*8)+4] = normal.y;
                    (*Vertices)[offset + (f*8)+(v*8)+5] = normal.z;
                } else {
                    while(nIndex >= vnNum[i]) nIndex -= vnNum[i];
                    (*Vertices)[offset + (f*8)+(v*8)+3] = norm[i][(nIndex*3)+0];
                    (*Vertices)[offset + (f*8)+(v*8)+4] = norm[i][(nIndex*3)+1];
                    (*Vertices)[offset + (f*8)+(v*8)+5] = norm[i][(nIndex*3)+2];
                }

                if(!texCoordsExists[i]){
                    (*Vertices)[offset + (f*8)+(v*8)+6] = 0.0f;
                    (*Vertices)[offset + (f*8)+(v*8)+7] = 0.0f;
                } else {
                    while(tIndex >= vtNum[i]) tIndex -= vtNum[i];
                    (*Vertices)[offset + (f*8)+(v*8)+6] = texCoords[i][(tIndex*2)+0];
                    (*Vertices)[offset + (f*8)+(v*8)+7] = texCoords[i][(tIndex*2)+1];
                }
            }
        }
        offset += vertNum[i];
    }

    // Delete buffers
    for(int i = 0; i < objectCount+1; i++){
        delete[] vert[i];
        if(normalsExists[i])   delete[] norm[i];
        if(texCoordsExists[i]) delete[] texCoords[i];
        delete[] faces[i];
    }

	delete[] vert;
	delete[] norm;
	delete[] texCoords;
	delete[] faces;

    file.close();
    return true;
}
