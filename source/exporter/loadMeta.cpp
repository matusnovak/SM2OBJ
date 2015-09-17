/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "loadMeta.h"

///=============================================================================
std::string pathToName(std::string Str){
	for(auto& c : Str)if(c == '/' || c == '\\')c = '_';
	return Str;
}

///=============================================================================
std::string pathWithoutName(const std::string& Str, const std::string& Name){
	if(Name.size() > Str.size())return Str;
	return Str.substr(Name.size(), Str.size() - Name.size());
}

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

	std::cout << "pos: " << pos << std::endl;

    // Go back 6 bytes
    size_t origin = pos;
    input.gotoPos(origin - 6);

    uint32_t totalEntries;
    input.read(&totalEntries, sizeof(uint32_t));
    totalEntries = ffw::byteSwap32(totalEntries);

	pos -= 2;

	for(uint32_t i = 0; i < totalEntries; i++){
		std::string name;

		input.gotoPos(pos);
		std::cout << "reading name from: " << pos << std::endl;

		// Read attachment name
		uint16_t strLength;
        input.read(&strLength, sizeof(uint16_t));
        strLength = ffw::byteSwap16(strLength);
        name.resize(strLength);
        input.read(&name[0], strLength);

		Output->attachments.push_back({pathToName(name), "\\" + pathWithoutName(name, Name), ffw::vec3f(8.0f, 8.0f, 8.0f), ffw::quatf(), ffw::vec3f(), ffw::vec3f(), std::vector<entityInfoStruct>(), std::vector<chunkInfoStruct>(), std::vector<int>(), std::vector<ffw::vec2i>(), Output});

		//std::cout << "attachment name length: " << strLength << std::endl;
		//std::cout << "attachment name: " << name << std::endl;

		if(i + 1 != totalEntries){
			pos = findName(&input, Name);

			if(pos == 0){
				Args.callbackLogError("Failed to read next attachment path from meta: " + Path);
				break;
			}

			//std::cout << "NEXT FOUND POS: " << pos -2 << std::endl;
			pos -= 2;
		}
	}

    /*for(uint32_t i = 0; i < totalEntries; i++){
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

		std::cout << "name0: " << name0 << std::endl;
		std::cout << "name1: " << name1 << std::endl;

        size_t slash = name0.find('/');
        if(slash != std::string::npos){
            name0 = name0.substr(slash+1, name0.size()-slash-1);
        } else {
            Args.callbackLogError("Failed to read next attachment path from meta: " + Path);
            continue;
        }

        ffw::quatf quat;
        ffw::vec3i dockOffset;

        if(orientation[4] == 0x0E && orientation[6] == 0x01){
            dockOffset = ffw::vec3i(0, 1, 0);
        }

        if(orientation[4] == 0x0C && orientation[6] == 0x01){
            quat *= ffw::quatf().rotate(180.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 1, 0);
        }

        if(orientation[4] == 0x0F && orientation[6] == 0x01){
            quat *= ffw::quatf().rotate(90.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 1, 0);
        }

        if(orientation[4] == 0x0D && orientation[6] == 0x01){
            quat *= ffw::quatf().rotate(270.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 1, 0);
        }

        if(orientation[4] == 0x00 && orientation[6] == 0x00){
            quat *= ffw::quatf().rotate(270.0f, 0.0f, 0.0f, 1.0f);
            dockOffset = ffw::vec3i(-1, 0, 0);
        }

        if(orientation[4] == 0x03 && orientation[6] == 0x00){
            quat *= ffw::quatf().rotate(270.0f, 0.0f, 0.0f, 1.0f);
            quat *= ffw::quatf().rotate(90.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(-1, 0, 0);
        }

        if(orientation[4] == 0x02 && orientation[6] == 0x00){
            quat *= ffw::quatf().rotate(270.0f, 0.0f, 0.0f, 1.0f);
            quat *= ffw::quatf().rotate(180.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(-1, 0, 0);
        }

        if(orientation[4] == 0x01 && orientation[6] == 0x00){
            quat *= ffw::quatf().rotate(270.0f, 0.0f, 0.0f, 1.0f);
            quat *= ffw::quatf().rotate(270.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(-1, 0, 0);
        }

        if(orientation[4] == 0x04 && orientation[6] == 0x00){
            quat *= ffw::quatf().rotate(90.0f, 0.0f, 0.0f, 1.0f);
            dockOffset = ffw::vec3i(1, 0, 0);
        }

        if(orientation[4] == 0x07 && orientation[6] == 0x00){
            quat *= ffw::quatf().rotate(90.0f, 0.0f, 0.0f, 1.0f);
            quat *= ffw::quatf().rotate(270.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(1, 0, 0);
        }

        if(orientation[4] == 0x06 && orientation[6] == 0x00){
            quat *= ffw::quatf().rotate(90.0f, 0.0f, 0.0f, 1.0f);
            quat *= ffw::quatf().rotate(180.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(1, 0, 0);
        }

        if(orientation[4] == 0x05 && orientation[6] == 0x00){
            quat *= ffw::quatf().rotate(90.0f, 0.0f, 0.0f, 1.0f);
            quat *= ffw::quatf().rotate(90.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(1, 0, 0);
        }

        if(orientation[4] == 0x0B && orientation[6] == 0x01){
            quat *=  ffw::quatf().rotate(180.0f, 0.0f, 0.0f, 1.0f);
            quat *=  ffw::quatf().rotate(270.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, -1, 0);
        }

        if(orientation[4] == 0x08 && orientation[6] == 0x01){
            quat *=  ffw::quatf().rotate(180.0f, 0.0f, 0.0f, 1.0f);
            quat *=  ffw::quatf().rotate(180.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, -1, 0);
        }

        if(orientation[4] == 0x09 && orientation[6] == 0x01){
            quat *=  ffw::quatf().rotate(180.0f, 0.0f, 0.0f, 1.0f);
            quat *=  ffw::quatf().rotate(90.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, -1, 0);
        }

        if(orientation[4] == 0x0A && orientation[6] == 0x01){
            quat *= ffw::quatf().rotate(180.0f, 0.0f, 0.0f, 1.0f);
            dockOffset = ffw::vec3i(0, -1, 0);
        }

        if(orientation[4] == 0x00 && orientation[6] == 0x01){
            quat *= ffw::quatf().rotate(270.0f, 1.0f, 0.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, 1);
        }

        if(orientation[4] == 0x01 && orientation[6] == 0x01){
            quat *= ffw::quatf().rotate(270.0f, 1.0f, 0.0f, 0.0f);
            quat *= ffw::quatf().rotate(270.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, 1);
        }

        if(orientation[4] == 0x03 && orientation[6] == 0x01){
            quat *= ffw::quatf().rotate(270.0f, 1.0f, 0.0f, 0.0f);
            quat *= ffw::quatf().rotate(90.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, 1);
        }

        if(orientation[4] == 0x02 && orientation[6] == 0x01){
            quat *= ffw::quatf().rotate(270.0f, 1.0f, 0.0f, 0.0f);
            quat *= ffw::quatf().rotate(180.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, 1);
        }

        if(orientation[4] == 0x04 && orientation[6] == 0x01){
            quat *= ffw::quatf().rotate(90.0f, 1.0f, 0.0f, 0.0f);
            quat *= ffw::quatf().rotate(180.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, -1);
        }

        if(orientation[4] == 0x05 && orientation[6] == 0x01){
            quat *= ffw::quatf().rotate(90.0f, 1.0f, 0.0f, 0.0f);
            quat *= ffw::quatf().rotate(270.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, -1);
        }

        if(orientation[4] == 0x07 && orientation[6] == 0x01){
            quat *= ffw::quatf().rotate(90.0f, 1.0f, 0.0f, 0.0f);
            quat *= ffw::quatf().rotate(90.0f, 0.0f, 1.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, -1);
        }

        if(orientation[4] == 0x06 && orientation[6] == 0x01){
            quat *= ffw::quatf().rotate(90.0f, 1.0f, 0.0f, 0.0f);
            dockOffset = ffw::vec3i(0, 0, -1);
        }

        Output->attachments.push_back({name2, "\\" + name0, (ffw::vec3f)pos, quat, (ffw::vec3f)dockModule, (ffw::vec3f)dockOffset, std::vector<entityInfoStruct>(), std::vector<chunkInfoStruct>(), std::vector<int>(), std::vector<ffw::vec2i>(), Output});
    }*/

    return true;
}
