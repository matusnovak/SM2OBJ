/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "blockConfig.h"
#include "config.h"

struct blockTypeStruct {
    std::string name;
    int id;
};

static std::vector<sm2obj::blockInfoStruct> blocksInfo;
static std::vector<blockTypeStruct> blocksType;

///=============================================================================
static void fixName(std::string* Str){
    for(auto& chr : *Str)if(chr == ' ')chr = '_';
}

///=============================================================================
static std::string fixSpaces(const std::string& Str){
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
bool sm2obj::loadBlockTypes(const std::string& Path){
    // Open file for input
    ffw::file input;
    if(!input.open(Path, false, false, false)){
        LOG_ERROR("Failed to read block types from: " + Path);
        return false;
    }

    LOG_INFO("Reading block type properties...");

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
                LOG_WARNING("Error reading type ID at line: " + ffw::valToString(lineNumber));
                continue;
            }

            if(tokens[0].size() == 0){
                LOG_WARNING("Error reading type name at line: " + ffw::valToString(lineNumber));
                continue;
            }

            blocksType.push_back({tokens[0], id});
        }
    }

    LOG_DEBUG("Loaded: " + ffw::valToString(blocksType.size()) + " block types!");
    return true;
}

///=============================================================================
static int findBlockType(const std::string& Type){
    for(const auto& block : blocksType){
        if(block.name == Type)return block.id;
    }
    return -1;
}

///=============================================================================
const sm2obj::blockInfoStruct* sm2obj::findBlock(int ID){
    for(const auto& block : blocksInfo){
        if(block.id == ID)return &block;
    }
    return NULL;
}

///=============================================================================
const sm2obj::blockInfoStruct* sm2obj::findBlockByTexture(int Index){
    for(const auto& block : blocksInfo){
        for(int i = 0; i < 6; i++){
            if(block.texture[i] == Index)return &block;
        }
    }
    return NULL;
}

///=============================================================================
void sm2obj::clearBlockConfig(){
    blocksInfo.clear();
    blocksType.clear();
}

///=============================================================================
bool sm2obj::loadBlockConfig(const std::string& Path){
    // Open file for input
    ffw::file input;
    if(!input.open(Path, false, false, false)){
        LOG_ERROR("Failed to read block config from: " + Path);
        return false;
    }

    LOG_INFO("Reading block config...");

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
                LOG_WARNING("Wrong number of tokens at line: " + ffw::valToString(lineNumber) + " expecting 5!");
                continue;
            }

            blocksInfo.push_back(blockInfoStruct());
            auto& newBlock = blocksInfo[blocksInfo.size()-1];

            size_t pos = tokens[1].find('"', 1);
            if(pos != std::string::npos){
                try {
                    newBlock.icon = ffw::stringToVal<int>(tokens[1].substr(1, pos-1));
                } catch (std::exception& e){
                    LOG_WARNING("Error reading icon data at line: " + ffw::valToString(lineNumber));
                    blocksInfo.pop_back();
                    continue;
                }
            }

            pos = tokens[2].find('"', 1);
            if(pos != std::string::npos){
                newBlock.name = tokens[2].substr(1, pos-1);
                if(newBlock.name.size() == 0){
                    LOG_WARNING("Error reading name data at line: " + ffw::valToString(lineNumber));
                    blocksInfo.pop_back();
                    continue;
                }
                fixName(&newBlock.name);
            }

            pos = tokens[3].find('"', 1);
            if(pos != std::string::npos){
                std::vector<std::string> texTokens = ffw::getTokens(tokens[3].substr(1, pos-1), ',');
                if(texTokens.size() != 6){
                    LOG_WARNING("Error reading texture data at line: " + ffw::valToString(lineNumber));
                    blocksInfo.pop_back();
                    continue;
                }

                try {
                    for(int i = 0; i < 6; i++){
                        newBlock.texture[i] = ffw::stringToVal<int>(texTokens[i]);
                    }

                } catch (std::exception& e){
                    LOG_WARNING("Error reading texture data at line: " + ffw::valToString(lineNumber));
                    blocksInfo.pop_back();
                    continue;
                }
            }

            pos = tokens[4].find('"', 1);
            if(pos != std::string::npos){
                std::string type = tokens[4].substr(1, pos-1);
                if(type.size() == 0){
                    LOG_WARNING("Error reading type data at line: " + ffw::valToString(lineNumber));
                    blocksInfo.pop_back();
                    continue;
                }

                int id = findBlockType(type);
                if(id == -1){
                    LOG_WARNING("Could not find ID for type: " + type);
                    continue;
                }

                newBlock.id = id;
                newBlock.object = -1;
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
                bool success = false;
                if(tokens.size() == 4){
                    try {
                        blocksInfo[blocksInfo.size()-1].light.r = ffw::stringToVal<float>(tokens[0]);
                        blocksInfo[blocksInfo.size()-1].light.g = ffw::stringToVal<float>(tokens[1]);
                        blocksInfo[blocksInfo.size()-1].light.b = ffw::stringToVal<float>(tokens[2]);
                        blocksInfo[blocksInfo.size()-1].light.a = ffw::stringToVal<float>(tokens[3]);
                        success = true;

                    } catch (std::exception& e){
                        // Nothing to do
                    }
                }
                if(!success)LOG_WARNING("Error reading light source color data at line: " + ffw::valToString(lineNumber));
            }

        } else if(blocksInfo.size() > 0 && (first = line.find("<BlockStyle>")) != std::string::npos){
            size_t last = line.find("</BlockStyle>");
            bool success = false;
            if(last != std::string::npos){
                try {
                    blocksInfo[blocksInfo.size()-1].object = ffw::stringToVal<int>(line.substr(first+12, last-first-12));
                    success = true;

                } catch (std::exception& e){
                    // Nothing to do
                }
            }
            if(!success)LOG_WARNING("Error reading block style as int at line: " + ffw::valToString(lineNumber));
        }
    }

    LOG_DEBUG("Loaded: " + ffw::valToString(blocksInfo.size()) + " blocks!");
    return true;
}

