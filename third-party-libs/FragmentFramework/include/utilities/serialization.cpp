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
template <class T>
static void serializeVec2(ffw::var* Data, const ffw::serialization::item& Item){
    ffw::varArray dataArray;

    dataArray.push_back(static_cast<ffw::vec2<T>*>(Item.ptr)->x);
    dataArray.push_back(static_cast<ffw::vec2<T>*>(Item.ptr)->y);

    Data->getAsObject().insert(std::make_pair(Item.name, dataArray));
}

///=============================================================================
template <class T>
static void serializeVec3(ffw::var* Data, const ffw::serialization::item& Item){
    ffw::varArray dataArray;

    dataArray.push_back(static_cast<ffw::vec3<T>*>(Item.ptr)->x);
    dataArray.push_back(static_cast<ffw::vec3<T>*>(Item.ptr)->y);
    dataArray.push_back(static_cast<ffw::vec3<T>*>(Item.ptr)->z);

    Data->getAsObject().insert(std::make_pair(Item.name, dataArray));
}

///=============================================================================
template <class T>
static void serializeVec4(ffw::var* Data, const ffw::serialization::item& Item){
    ffw::varArray dataArray;

    dataArray.push_back(static_cast<ffw::vec4<T>*>(Item.ptr)->x);
    dataArray.push_back(static_cast<ffw::vec4<T>*>(Item.ptr)->y);
    dataArray.push_back(static_cast<ffw::vec4<T>*>(Item.ptr)->z);
    dataArray.push_back(static_cast<ffw::vec4<T>*>(Item.ptr)->w);

    Data->getAsObject().insert(std::make_pair(Item.name, dataArray));
}

///=============================================================================
bool ffw::serialization::serializeAsJson(const std::string& Path, bool Formated){
    return serializeAsJson(utf8ToWstr(Path), Formated);
}

///=============================================================================
bool ffw::serialization::serializeAsJson(const std::wstring& Path, bool Formated){
    ffw::var data = ffw::varObject();
    // Test first
    if(!saveTXT(Path, "..."))return false;

    serializeAsVar(&data, Formated);
    return saveJSON(Path, &data, Formated, true);
}

///=============================================================================
bool ffw::serialization::serializeAsVar(ffw::var* Data, bool Formated){
    for(const auto& item : varList){

        if       (item.code == typeid(int).hash_code()){
            Data->getAsObject().insert(std::make_pair(item.name, *static_cast<int*>(item.ptr)));

        } else if(item.code == typeid(float).hash_code()){
            Data->getAsObject().insert(std::make_pair(item.name, *static_cast<float*>(item.ptr)));

        } else if(item.code == typeid(bool).hash_code()){
            Data->getAsObject().insert(std::make_pair(item.name, *static_cast<bool*>(item.ptr)));

        } else if(item.code == typeid(std::string).hash_code()){
            Data->getAsObject().insert(std::make_pair(item.name, *static_cast<std::string*>(item.ptr)));

        } else if(item.code == typeid(std::vector<int>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *static_cast<std::vector<int>*>(item.ptr)){
                dataArray.push_back(element);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<float>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *static_cast<std::vector<float>*>(item.ptr)){
                dataArray.push_back(element);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<bool>).hash_code()){
            ffw::varArray dataArray;

            for(const bool& element : *static_cast<std::vector<bool>*>(item.ptr)){
                dataArray.push_back(element);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<std::string>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *static_cast<std::vector<std::string>*>(item.ptr)){
                dataArray.push_back(element);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(ffw::vec2f).hash_code()){
            serializeVec2<float>(Data, item);

        } else if(item.code == typeid(ffw::vec3f).hash_code()){
            serializeVec3<float>(Data, item);

        } else if(item.code == typeid(ffw::vec4f).hash_code()){
            serializeVec4<float>(Data, item);

        } else if(item.code == typeid(ffw::vec2i).hash_code()){
            serializeVec2<int>(Data, item);

        } else if(item.code == typeid(ffw::vec3i).hash_code()){
            serializeVec3<int>(Data, item);

        } else if(item.code == typeid(ffw::vec4i).hash_code()){
            serializeVec4<int>(Data, item);

        } else if(item.code == typeid(ffw::color).hash_code()){
            ffw::varArray dataArray;

            dataArray.push_back(static_cast<ffw::color*>(item.ptr)->r);
            dataArray.push_back(static_cast<ffw::color*>(item.ptr)->g);
            dataArray.push_back(static_cast<ffw::color*>(item.ptr)->b);
            dataArray.push_back(static_cast<ffw::color*>(item.ptr)->a);

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(ffw::quaternion).hash_code()){
            ffw::varArray dataArray;

            dataArray.push_back(static_cast<ffw::quaternion*>(item.ptr)->x);
            dataArray.push_back(static_cast<ffw::quaternion*>(item.ptr)->y);
            dataArray.push_back(static_cast<ffw::quaternion*>(item.ptr)->z);
            dataArray.push_back(static_cast<ffw::quaternion*>(item.ptr)->w);

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<ffw::vec2f>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *static_cast<std::vector<ffw::vec2f>*>(item.ptr)){
                dataArray.push_back(ffw::varArray());
                auto& subDataArray = dataArray[dataArray.size()-1].getAsArray();
                subDataArray.push_back(element.x);
                subDataArray.push_back(element.y);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<ffw::vec3f>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *static_cast<std::vector<ffw::vec3f>*>(item.ptr)){
                dataArray.push_back(ffw::varArray());
                auto& subDataArray = dataArray[dataArray.size()-1].getAsArray();
                subDataArray.push_back(element.x);
                subDataArray.push_back(element.y);
                subDataArray.push_back(element.z);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<ffw::vec4f>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *static_cast<std::vector<ffw::vec4f>*>(item.ptr)){
                dataArray.push_back(ffw::varArray());
                auto& subDataArray = dataArray[dataArray.size()-1].getAsArray();
                subDataArray.push_back(element.x);
                subDataArray.push_back(element.y);
                subDataArray.push_back(element.z);
                subDataArray.push_back(element.w);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<ffw::vec2i>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *static_cast<std::vector<ffw::vec2i>*>(item.ptr)){
                dataArray.push_back(ffw::varArray());
                auto& subDataArray = dataArray[dataArray.size()-1].getAsArray();
                subDataArray.push_back(element.x);
                subDataArray.push_back(element.y);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<ffw::vec3i>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *static_cast<std::vector<ffw::vec3i>*>(item.ptr)){
                dataArray.push_back(ffw::varArray());
                auto& subDataArray = dataArray[dataArray.size()-1].getAsArray();
                subDataArray.push_back(element.x);
                subDataArray.push_back(element.y);
                subDataArray.push_back(element.z);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<ffw::vec4i>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *static_cast<std::vector<ffw::vec4i>*>(item.ptr)){
                dataArray.push_back(ffw::varArray());
                auto& subDataArray = dataArray[dataArray.size()-1].getAsArray();
                subDataArray.push_back(element.x);
                subDataArray.push_back(element.y);
                subDataArray.push_back(element.z);
                subDataArray.push_back(element.w);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<ffw::color>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *static_cast<std::vector<ffw::color>*>(item.ptr)){
                dataArray.push_back(ffw::varArray());
                auto& subDataArray = dataArray[dataArray.size()-1].getAsArray();
                subDataArray.push_back(element.r);
                subDataArray.push_back(element.g);
                subDataArray.push_back(element.b);
                subDataArray.push_back(element.a);
            }

            Data->getAsObject().insert(std::make_pair(item.name, dataArray));

        } else if(item.code == typeid(std::vector<ffw::quaternion>).hash_code()){
            ffw::varArray dataArray;

            for(const auto& element : *static_cast<std::vector<ffw::quaternion>*>(item.ptr)){
                dataArray.push_back(ffw::varArray());
                auto& subDataArray = dataArray[dataArray.size()-1].getAsArray();
                subDataArray.push_back(element.x);
                subDataArray.push_back(element.y);
                subDataArray.push_back(element.z);
                subDataArray.push_back(element.w);
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
                *static_cast<int*>(item.ptr) = found->second.getAsInt();

            } else if(item.code == typeid(float).hash_code()){
                *static_cast<float*>(item.ptr) = found->second.getAsFloat();

            } else if(item.code == typeid(bool).hash_code()){
                *static_cast<bool*>(item.ptr) = found->second.getAsBool();

            } else if(item.code == typeid(std::string).hash_code()){
                *static_cast<std::string*>(item.ptr) = found->second.getAsString();

            } else if(item.code == typeid(std::vector<int>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                     static_cast<std::vector<int>*>(item.ptr)->push_back(element.getAsInt());
                }

            } else if(item.code == typeid(std::vector<float>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                     static_cast<std::vector<float>*>(item.ptr)->push_back(element.getAsFloat());
                }

            } else if(item.code == typeid(std::vector<bool>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    static_cast<std::vector<bool>*>(item.ptr)->push_back(element.getAsBool());
                }

            } else if(item.code == typeid(std::vector<std::string>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    static_cast<std::vector<std::string>*>(item.ptr)->push_back(element.getAsString());
                }

            } else if(item.code == typeid(ffw::vec2f).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();
                if(elements.size() != 2){Missing->push_back(item.name); result = false; continue;}

                static_cast<ffw::vec2f*>(item.ptr)->x = elements[0].getAsFloat();
                static_cast<ffw::vec2f*>(item.ptr)->y = elements[1].getAsFloat();

            } else if(item.code == typeid(ffw::vec3f).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();
                if(elements.size() != 3){Missing->push_back(item.name); result = false; continue;}

                static_cast<ffw::vec3f*>(item.ptr)->x = elements[0].getAsFloat();
                static_cast<ffw::vec3f*>(item.ptr)->y = elements[1].getAsFloat();
                static_cast<ffw::vec3f*>(item.ptr)->z = elements[2].getAsFloat();

            } else if(item.code == typeid(ffw::vec4f).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();
                if(elements.size() != 4){Missing->push_back(item.name); result = false; continue;}

                static_cast<ffw::vec4f*>(item.ptr)->x = elements[0].getAsFloat();
                static_cast<ffw::vec4f*>(item.ptr)->y = elements[1].getAsFloat();
                static_cast<ffw::vec4f*>(item.ptr)->z = elements[2].getAsFloat();
                static_cast<ffw::vec4f*>(item.ptr)->w = elements[3].getAsFloat();

            } else if(item.code == typeid(ffw::vec2i).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();
                if(elements.size() != 2){Missing->push_back(item.name); result = false; continue;}

                static_cast<ffw::vec2i*>(item.ptr)->x = elements[0].getAsInt();
                static_cast<ffw::vec2i*>(item.ptr)->y = elements[1].getAsInt();

            } else if(item.code == typeid(ffw::vec3i).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();
                if(elements.size() != 3){Missing->push_back(item.name); result = false; continue;}

                static_cast<ffw::vec3i*>(item.ptr)->x = elements[0].getAsInt();
                static_cast<ffw::vec3i*>(item.ptr)->y = elements[1].getAsInt();
                static_cast<ffw::vec3i*>(item.ptr)->z = elements[2].getAsInt();

            } else if(item.code == typeid(ffw::vec4i).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();
                if(elements.size() != 4){Missing->push_back(item.name); result = false; continue;}

                static_cast<ffw::vec4i*>(item.ptr)->x = elements[0].getAsInt();
                static_cast<ffw::vec4i*>(item.ptr)->y = elements[1].getAsInt();
                static_cast<ffw::vec4i*>(item.ptr)->z = elements[2].getAsInt();
                static_cast<ffw::vec4i*>(item.ptr)->w = elements[3].getAsInt();

            } else if(item.code == typeid(ffw::color).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();
                if(elements.size() != 4){Missing->push_back(item.name); result = false; continue;}

                static_cast<ffw::color*>(item.ptr)->r = elements[0].getAsFloat();
                static_cast<ffw::color*>(item.ptr)->g = elements[1].getAsFloat();
                static_cast<ffw::color*>(item.ptr)->b = elements[2].getAsFloat();
                static_cast<ffw::color*>(item.ptr)->a = elements[3].getAsFloat();

            } else if(item.code == typeid(ffw::quaternion).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();
                if(elements.size() != 4){Missing->push_back(item.name); result = false; continue;}

                static_cast<ffw::quaternion*>(item.ptr)->x = elements[0].getAsFloat();
                static_cast<ffw::quaternion*>(item.ptr)->y = elements[1].getAsFloat();
                static_cast<ffw::quaternion*>(item.ptr)->z = elements[2].getAsFloat();
                static_cast<ffw::quaternion*>(item.ptr)->w = elements[3].getAsFloat();

            } else if(item.code == typeid(std::vector<ffw::vec2f>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    auto& subElements = element.getAsArray();
                    if(subElements.size() != 2)continue;
                    static_cast<std::vector<ffw::vec2f>*>(item.ptr)->push_back(ffw::vec2f(subElements[0].getAsFloat(), subElements[1].getAsFloat()));
                }

            } else if(item.code == typeid(std::vector<ffw::vec3f>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    auto& subElements = element.getAsArray();
                    if(subElements.size() != 3)continue;
                    static_cast<std::vector<ffw::vec3f>*>(item.ptr)->push_back(ffw::vec3f(subElements[0].getAsFloat(), subElements[1].getAsFloat(), subElements[2].getAsFloat()));
                }

            } else if(item.code == typeid(std::vector<ffw::vec4f>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    auto& subElements = element.getAsArray();
                    if(subElements.size() != 4)continue;
                    static_cast<std::vector<ffw::vec4f>*>(item.ptr)->push_back(ffw::vec4f(subElements[0].getAsFloat(), subElements[1].getAsFloat(), subElements[2].getAsFloat(), subElements[3].getAsFloat()));
                }

            } else if(item.code == typeid(std::vector<ffw::vec2i>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    auto& subElements = element.getAsArray();
                    if(subElements.size() != 2)continue;
                    static_cast<std::vector<ffw::vec2i>*>(item.ptr)->push_back(ffw::vec2i(subElements[0].getAsInt(), subElements[1].getAsInt()));
                }

            } else if(item.code == typeid(std::vector<ffw::vec3i>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    auto& subElements = element.getAsArray();
                    if(subElements.size() != 3)continue;
                    static_cast<std::vector<ffw::vec3i>*>(item.ptr)->push_back(ffw::vec3i(subElements[0].getAsInt(), subElements[1].getAsInt(), subElements[2].getAsInt()));
                }

            } else if(item.code == typeid(std::vector<ffw::vec4i>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    auto& subElements = element.getAsArray();
                    if(subElements.size() != 4)continue;
                    static_cast<std::vector<ffw::vec4i>*>(item.ptr)->push_back(ffw::vec4i(subElements[0].getAsInt(), subElements[1].getAsInt(), subElements[2].getAsInt(), subElements[3].getAsInt()));
                }

            } else if(item.code == typeid(std::vector<ffw::color>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    auto& subElements = element.getAsArray();

                    if(subElements.size() != 4)continue;
                    static_cast<std::vector<ffw::color>*>(item.ptr)->push_back(ffw::color(subElements[0].getAsFloat(), subElements[1].getAsFloat(), subElements[2].getAsFloat(), subElements[3].getAsFloat()));
                }


            } else if(item.code == typeid(std::vector<ffw::quaternion>).hash_code()){
                ffw::varArray& elements = found->second.getAsArray();

                for(auto& element : elements){
                    auto& subElements = element.getAsArray();
                    if(subElements.size() != 4)continue;
                    static_cast<std::vector<ffw::quaternion>*>(item.ptr)->push_back(ffw::quaternion(subElements[0].getAsFloat(), subElements[1].getAsFloat(), subElements[2].getAsFloat(), subElements[3].getAsFloat()));
                }

            }

        } else {
            if(Missing != NULL) Missing->push_back(item.name);
            result = false;
        }
    }

    return result;
}
