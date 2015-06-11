/*
    Distributed under the MIT License.
    Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*/

#include "blockConfig.h"

struct blockTypeStruct {
    std::string name;
    int id;
};

std::vector<blockInfoStruct> blocksInfo;
std::vector<blockTypeStruct> blocksType;

///=============================================================================
std::string fixName(std::string Str){
    for(auto& chr : Str)if(chr == ' ')chr = '_';
    return Str;
}

///=============================================================================
std::string fixSpaces(const std::string& Str){
    if(Str.size() == 1)return Str;

    size_t first = 0;
    size_t last = Str.size()-1;
    bool found = false;
    for(size_t i = 0; i < Str.size(); i++){
        if(!found && Str[i] == ' ')continue;
        if(!found){
            found = true;
            first = i;
        }
        if(found && Str[i] == ' '){
            last = i-1;
        }
    }

    if(last == first)return "";
    return Str.substr(first, last-first+1);
}

///=============================================================================
bool loadBlockTypes(const std::string& Path){
    // Open file for input
    ffw::file input;
    if(!input.open(Path, false, false, false)){
        return false;
    }

    ffw::logger().debug() << "Reading block type properties from: " << Path;

    int lineNumber = 0;
    while(!input.eof()){
        lineNumber++;
        std::string line;
        input.readLine(&line);

        if(line.size() == 0)continue;

        std::vector<std::string> tokens = ffw::getTokens(line, '=');
        if(tokens.size() == 2){
            tokens[0] = fixSpaces(tokens[0]);
            tokens[1] = fixSpaces(tokens[1]);

            int id;
            try {
                id = ffw::stringToVal<int>(tokens[1]);

            } catch (std::exception& e){
                ffw::logger().warning() << "Error reading type ID at line: " << lineNumber;
                continue;
            }

            if(tokens[0].size() == 0){
                ffw::logger().warning() << "Error reading type name at line: " << lineNumber;
                continue;
            }

            // Fix name by replacing spaces with underscore
            blocksType.push_back({fixName(tokens[0]), id});
        }
    }

    ffw::logger().debug() << "Loaded: " << blocksType.size() << " block types!";
    return true;
}

///=============================================================================
int findBlockType(const std::string& Type){
    for(const auto& block : blocksType){
        if(block.name == Type)return block.id;
    }
    return -1;
}

///=============================================================================
const blockInfoStruct* findBlock(int ID){
    for(const auto& block : blocksInfo){
        if(block.id == ID)return &block;
    }
    return NULL;
}

///=============================================================================
const blockInfoStruct* findBlockByTexture(int Index){
    for(const auto& block : blocksInfo){
        for(int i = 0; i < 6; i++){
            if(block.texture[i] == Index)return &block;
        }
    }
    return NULL;
}

///=============================================================================
bool loadBlockConfig(const std::string& Path){
    // Open file for input
    ffw::file input;
    if(!input.open(Path, false, false, false)){
        return false;
    }

    ffw::logger().debug() << "Reading block config from: " << Path;

    // Loop through all lines
    int lineNumber = 0;
    while(!input.eof()){
        lineNumber++;
        std::string line;
        input.readLine(&line);

        if(line.size() == 0)continue;
        size_t first = 0;
        if(line.find("<Block icon=") != std::string::npos){
            std::vector<std::string> tokens = ffw::getTokens(line, '=');
            if(tokens.size() != 5){
                ffw::logger().warning() << "Wrong number of tokens at line: " << lineNumber << " expecting 5!";
                continue;
            }

            blocksInfo.push_back(blockInfoStruct());
            auto& newBlock = blocksInfo[blocksInfo.size()-1];

            size_t pos = tokens[1].find('"', 1);
            if(pos != std::string::npos){
                try {
                    newBlock.icon = ffw::stringToVal<int>(tokens[1].substr(1, pos-1));
                } catch (std::exception& e){
                    ffw::logger().warning() << "Error reading icon data at line: " << lineNumber;
                    blocksInfo.pop_back();
                    continue;
                }
            }

            pos = tokens[2].find('"', 1);
            if(pos != std::string::npos){
                newBlock.name = tokens[2].substr(1, pos-1);
                if(newBlock.name.size() == 0){
                    ffw::logger().warning() << "Error reading name data at line: " << lineNumber;
                    blocksInfo.pop_back();
                    continue;
                }
            }

            pos = tokens[3].find('"', 1);
            if(pos != std::string::npos){
                std::vector<std::string> texTokens = ffw::getTokens(tokens[3].substr(1, pos-1), ',');
                if(texTokens.size() != 6){
                    ffw::logger().warning() << "Error reading texture data at line: " << lineNumber;
                    blocksInfo.pop_back();
                    continue;
                }

                try {
                    for(int i = 0; i < 6; i++){
                        newBlock.texture[i] = ffw::stringToVal<int>(texTokens[i]);
                    }

                } catch (std::exception& e){
                    ffw::logger().warning() << "Error reading texture data at line: " << lineNumber;
                    blocksInfo.pop_back();
                    continue;
                }
            }

            pos = tokens[4].find('"', 1);
            if(pos != std::string::npos){
                std::string type = tokens[4].substr(1, pos-1);
                if(type.size() == 0){
                    ffw::logger().warning() << "Error reading type data at line: " << lineNumber;
                    blocksInfo.pop_back();
                    continue;
                }

                int id = findBlockType(type);
                if(id == -1){
                    ffw::logger().warning() << "Could not find ID for type: " << type;
                    continue;
                }

                newBlock.id = id;
            }

            if(newBlock.name.find("Wedge") != std::string::npos){
                newBlock.object = 2;

            } else if(newBlock.name.find("Corner") != std::string::npos){
                newBlock.object = 3;

            } else if(newBlock.name.find("Hepta") != std::string::npos){
                newBlock.object = 4;

            } else if(newBlock.name.find("Tetra") != std::string::npos){
                newBlock.object = 5;

            } else {
                newBlock.object = 1;
            }

        } else if(blocksInfo.size() > 0 && line.find("<Transparency>false</Transparency>") != std::string::npos){
            blocksInfo[blocksInfo.size()-1].transparent = false;
        } else if(blocksInfo.size() > 0 && line.find("<Transparency>true</Transparency>") != std::string::npos){
            blocksInfo[blocksInfo.size()-1].transparent = true;
        } else if(blocksInfo.size() > 0 && line.find("<LightSource>false</LightSource>") != std::string::npos){
            blocksInfo[blocksInfo.size()-1].emissive = false;
        } else if(blocksInfo.size() > 0 && line.find("<LightSource>true</LightSource>") != std::string::npos){
            blocksInfo[blocksInfo.size()-1].emissive = true;
        } else if(blocksInfo.size() > 0 && (first = line.find("<LightSourceColor>")) != std::string::npos){
            size_t last = line.find("</LightSourceColor>");
            if(last != std::string::npos){
                std::vector<std::string> tokens = ffw::getTokens(line.substr(first+18, last-first-18), ',');
                if(tokens.size() == 4){
                    try {
                        blocksInfo[blocksInfo.size()-1].light.r = ffw::stringToVal<float>(tokens[0]);
                        blocksInfo[blocksInfo.size()-1].light.g = ffw::stringToVal<float>(tokens[1]);
                        blocksInfo[blocksInfo.size()-1].light.b = ffw::stringToVal<float>(tokens[2]);
                        blocksInfo[blocksInfo.size()-1].light.a = ffw::stringToVal<float>(tokens[3]);

                    } catch (std::exception& e){

                        ffw::logger().warning() << "Error reading light source color as floats at line: " << lineNumber;
                        continue;
                    }
                } else {
                    ffw::logger().warning() << "Error reading light source color data at line: " << lineNumber;
                    continue;
                }
            }
        }
    }

    ffw::logger().debug() << "Loaded: " << blocksType.size() << " blocks!";
    return true;
}

