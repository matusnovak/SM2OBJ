/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "loadMeta.h"

///=============================================================================
static size_t findName(ffw::file* Input, const std::string& Name){
    char c;
    std::string test;
    test.resize(Name.size());

    size_t pos = 0;
    while(!Input->eof()){
        pos = Input->getPos();
        Input->read(&c, 1);
        if(c == Name[0]){
            if(Input->getSize() - Input->getPos() < Name.size())return 0;

            Input->read(&test[1], test.size()-1);
            test[0] = c;

            if(test == Name){
                return pos;
            } else {
                Input->gotoPos(pos+1);
            }
        }
    }
    return 0;
}

///=============================================================================
bool sm2obj::loadMeta(const exportBlueprintArgs& Args, entityInfoStruct* Output, const std::string& Path, const std::string& Name){
    ffw::file input;
    if(!input.open(Path, true, false, false)){
        Args.callbackLogError("Failed to open meta file from: " + Path);
        return false;
    }

    Args.callbackLogDebug("Reading: " + Path);

    size_t pos = findName(&input, Name);

    if(pos == 0){
        Args.callbackLogDebug("Could not load attachments for blueprint: " + Name + " Blueprint might be outdated or there are no attachments!");
        return true;
    }

    // Go back 6 bytes
    size_t origin = pos-6;
    input.gotoPos(origin);

    uint32_t totalEntries;
    input.read(&totalEntries, sizeof(uint32_t));
    totalEntries = ffw::byteSwap32(totalEntries);

    for(uint32_t i = 0; i < totalEntries; i++){
        std::string name0;
        std::string name1;
        std::string name2;
        char bytes0[13];
        char additionalInformation[227];

        uint16_t strLength;
        input.read(&strLength, sizeof(uint16_t));
        strLength = ffw::byteSwap16(strLength);
        name0.resize(strLength);
        input.read(&name0[0], strLength);

        input.read(&bytes0[0], sizeof(bytes0));

        input.read(&strLength, sizeof(uint16_t));
        strLength = ffw::byteSwap16(strLength);
        name1.resize(strLength);
        input.read(&name1[0], strLength);

        char unknownByte;
        ffw::vec3i pos;
        char orientation[12];
        input.read(&unknownByte, sizeof(unknownByte));
        input.read(&pos.x, sizeof(pos.x));
        input.read(&pos.y, sizeof(pos.y));
        input.read(&pos.z, sizeof(pos.z));
        pos.x = ffw::byteSwap32(pos.x);
        pos.y = ffw::byteSwap32(pos.y);
        pos.z = ffw::byteSwap32(pos.z);

        input.read(&orientation, sizeof(orientation));

        input.read(&strLength, sizeof(uint16_t));
        strLength = ffw::byteSwap16(strLength);
        name2.resize(strLength);
        input.read(&name2[0], strLength);

        ffw::vec3i dockModule;
        input.read(&unknownByte, sizeof(unknownByte));
        input.read(&dockModule.x, sizeof(dockModule.x));
        input.read(&dockModule.y, sizeof(dockModule.y));
        input.read(&dockModule.z, sizeof(dockModule.z));
        dockModule.x = ffw::byteSwap32(dockModule.x);
        dockModule.y = ffw::byteSwap32(dockModule.y);
        dockModule.z = ffw::byteSwap32(dockModule.z);

        input.read(&additionalInformation[0], sizeof(additionalInformation));

        size_t slash = name0.find('/');
        if(slash != std::string::npos){
            name0 = name0.substr(slash+1, name0.size()-slash-1);
        } else {
            Args.callbackLogError("Failed to read next attachment path from meta: " + Path);
            continue;
        }

        ffw::quaternion quat;
        ffw::vec3i dockOffset;

        if(orientation[4] == 0x0E && orientation[6] == 0x01){
            dockOffset = ffw::vec3i(0, 1, 0);
        }

        if(orientation[4] == 0x0C && orientation[6] == 0x01){
            quat *= ffw::quaternion().rotate(180.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 1, 0);
        }

        if(orientation[4] == 0x0F && orientation[6] == 0x01){
            quat *= ffw::quaternion().rotate(90.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 1, 0);
        }

        if(orientation[4] == 0x0D && orientation[6] == 0x01){
            quat *= ffw::quaternion().rotate(270.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 1, 0);
        }

        if(orientation[4] == 0x00 && orientation[6] == 0x00){
            quat *= ffw::quaternion().rotate(270.0f, 0.0f, 0.0f, 1.0f);
            dockOffset = ffw::vec3i(-1, 0, 0);
        }

        if(orientation[4] == 0x03 && orientation[6] == 0x00){
            quat *= ffw::quaternion().rotate(270.0f, 0.0f, 0.0f, 1.0f);
            quat *= ffw::quaternion().rotate(90.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(-1, 0, 0);
        }

        if(orientation[4] == 0x02 && orientation[6] == 0x00){
            quat *= ffw::quaternion().rotate(270.0f, 0.0f, 0.0f, 1.0f);
            quat *= ffw::quaternion().rotate(180.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(-1, 0, 0);
        }

        if(orientation[4] == 0x01 && orientation[6] == 0x00){
            quat *= ffw::quaternion().rotate(270.0f, 0.0f, 0.0f, 1.0f);
            quat *= ffw::quaternion().rotate(270.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(-1, 0, 0);
        }

        if(orientation[4] == 0x04 && orientation[6] == 0x00){
            quat *= ffw::quaternion().rotate(90.0f, 0.0f, 0.0f, 1.0f);
            dockOffset = ffw::vec3i(1, 0, 0);
        }

        if(orientation[4] == 0x07 && orientation[6] == 0x00){
            quat *= ffw::quaternion().rotate(90.0f, 0.0f, 0.0f, 1.0f);
            quat *= ffw::quaternion().rotate(270.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(1, 0, 0);
        }

        if(orientation[4] == 0x06 && orientation[6] == 0x00){
            quat *= ffw::quaternion().rotate(90.0f, 0.0f, 0.0f, 1.0f);
            quat *= ffw::quaternion().rotate(180.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(1, 0, 0);
        }

        if(orientation[4] == 0x05 && orientation[6] == 0x00){
            quat *= ffw::quaternion().rotate(90.0f, 0.0f, 0.0f, 1.0f);
            quat *= ffw::quaternion().rotate(90.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(1, 0, 0);
        }

        if(orientation[4] == 0x0B && orientation[6] == 0x01){
            quat *=  ffw::quaternion().rotate(180.0f, 0.0f, 0.0f, 1.0f);
            quat *=  ffw::quaternion().rotate(270.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, -1, 0);
        }

        if(orientation[4] == 0x08 && orientation[6] == 0x01){
            quat *=  ffw::quaternion().rotate(180.0f, 0.0f, 0.0f, 1.0f);
            quat *=  ffw::quaternion().rotate(180.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, -1, 0);
        }

        if(orientation[4] == 0x09 && orientation[6] == 0x01){
            quat *=  ffw::quaternion().rotate(180.0f, 0.0f, 0.0f, 1.0f);
            quat *=  ffw::quaternion().rotate(90.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, -1, 0);
        }

        if(orientation[4] == 0x0A && orientation[6] == 0x01){
            quat *= ffw::quaternion().rotate(180.0f, 0.0f, 0.0f, 1.0f);
            dockOffset = ffw::vec3i(0, -1, 0);
        }

        if(orientation[4] == 0x00 && orientation[6] == 0x01){
            quat *= ffw::quaternion().rotate(270.0f, 1.0f, 0.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, 1);
        }

        if(orientation[4] == 0x01 && orientation[6] == 0x01){
            quat *= ffw::quaternion().rotate(270.0f, 1.0f, 0.0f, 0.0f);
            quat *= ffw::quaternion().rotate(270.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, 1);
        }

        if(orientation[4] == 0x03 && orientation[6] == 0x01){
            quat *= ffw::quaternion().rotate(270.0f, 1.0f, 0.0f, 0.0f);
            quat *= ffw::quaternion().rotate(90.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, 1);
        }

        if(orientation[4] == 0x02 && orientation[6] == 0x01){
            quat *= ffw::quaternion().rotate(270.0f, 1.0f, 0.0f, 0.0f);
            quat *= ffw::quaternion().rotate(180.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, 1);
        }

        if(orientation[4] == 0x04 && orientation[6] == 0x01){
            quat *= ffw::quaternion().rotate(90.0f, 1.0f, 0.0f, 0.0f);
            quat *= ffw::quaternion().rotate(180.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, -1);
        }

        if(orientation[4] == 0x05 && orientation[6] == 0x01){
            quat *= ffw::quaternion().rotate(90.0f, 1.0f, 0.0f, 0.0f);
            quat *= ffw::quaternion().rotate(270.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, -1);
        }

        if(orientation[4] == 0x07 && orientation[6] == 0x01){
            quat *= ffw::quaternion().rotate(90.0f, 1.0f, 0.0f, 0.0f);
            quat *= ffw::quaternion().rotate(90.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, -1);
        }

        if(orientation[4] == 0x06 && orientation[6] == 0x01){
            quat *= ffw::quaternion().rotate(90.0f, 1.0f, 0.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, -1);
        }

        Output->attachments.push_back({name2, "\\" + name0, (ffw::vec3f)pos, quat, (ffw::vec3f)dockModule, (ffw::vec3f)dockOffset, std::vector<entityInfoStruct>(), std::vector<chunkInfoStruct>(), std::vector<int>(), std::vector<ffw::vec2i>(), Output});
    }

    return true;
}
