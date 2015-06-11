/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "serialization.h"
#include "../math/stringMath.h"
#include "loadSaveJson.h"
#include "loadSaveTxt.h"

///=============================================================================
bool ffw::serialization::serializeAsJson(const std::string& Path, bool Formated){
    return serializeAsJson(utf8ToWstr(Path), Formated);
}

///=============================================================================
bool ffw::serialization::serializeAsJson(const std::wstring& Path, bool Formated){
    ffw::var data = ffw::varObject();
    // Test
    if(!saveTXT(Path, ""))return false;

    serializeAsVar(&data, Formated);

    return saveJSON(Path, &data, Formated, true);
}

///=============================================================================
bool ffw::serialization::serializeAsVar(ffw::var* Data, bool Formated){
    for(const auto& item : varList){

        if       (item.code == typeid(int).hash_code()){
            Data->getAsObject().insert(std::make_pair(item.name, *(int*)(item.ptr)));

        } else if(item.code == typeid(float).hash_code()){
            Data->getAsObject().insert(std::make_pair(item.name, *(float*)(item.ptr)));

        } else if(item.code == typeid(bool).hash_code()){
            Data->getAsObject().insert(std::make_pair(item.name, *(bool*)(item.ptr)));

        } else if(item.code == typeid(std::string).hash_code()){
            Data->getAsObject().insert(std::make_pair(item.name, *(std::string*)(item.ptr)));

        } else if(item.code == typeid(std::vector<int>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *(std::vector<int>*)(item.ptr)){
                dataArray.push_back(element);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<float>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *(std::vector<float>*)(item.ptr)){
                dataArray.push_back(element);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<bool>).hash_code()){
            ffw::varArray dataArray;

            for(const bool& element : *(std::vector<bool>*)(item.ptr)){
                dataArray.push_back(element);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<std::string>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *(std::vector<std::string>*)(item.ptr)){
                dataArray.push_back(element);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        }
    }
    return true;
}

///=============================================================================
bool ffw::serialization::deserializeAsJson(const std::string& Path, std::vector<std::string>* Missing){
    return deserializeAsJson(utf8ToWstr(Path), Missing);
}

///=============================================================================
bool ffw::serialization::deserializeAsJson(const std::wstring& Path, std::vector<std::string>* Missing){
    ffw::var data;
    if(!loadJSON(Path, &data)){
        return false;
    }

    return deserializeAsVar(&data, Missing);
}

///=============================================================================
bool ffw::serialization::deserializeAsVar(ffw::var* Data, std::vector<std::string>* Missing){
    if(Data->getType() != var::type::vObject){
        return false;
    }

    bool result = true;
    for(const auto& item : varList){
        const auto& found = Data->getAsObject().find(item.name);

        if(found != Data->getAsObject().end()){

            if       (item.code == typeid(int).hash_code()){
                *(int*)(item.ptr) = found->second.getAsInt();

            } else if(item.code == typeid(float).hash_code()){
                *(float*)(item.ptr) = found->second.getAsFloat();

            } else if(item.code == typeid(bool).hash_code()){
                *(bool*)(item.ptr) = found->second.getAsBool();

            } else if(item.code == typeid(std::string).hash_code()){
                *(std::string*)(item.ptr) = found->second.getAsString();

            } else if(item.code == typeid(std::vector<int>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    ((std::vector<int>*)(item.ptr))->push_back(element.getAsInt());
                }

            } else if(item.code == typeid(std::vector<float>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    ((std::vector<float>*)(item.ptr))->push_back(element.getAsFloat());
                }

            } else if(item.code == typeid(std::vector<bool>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    ((std::vector<bool>*)(item.ptr))->push_back(element.getAsBool());
                }

            } else if(item.code == typeid(std::vector<std::string>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    ((std::vector<std::string>*)(item.ptr))->push_back(element.getAsString());
                }
            }
        } else {
            if(Missing != NULL) Missing->push_back(item.name);
            result = false;
        }
    }

    return result;
}
