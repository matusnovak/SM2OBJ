/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "loadSaveXml.h"

#include <tinyxml2.h>

static void convertXML(tinyxml2::XMLElement* XML, ffw::var* Output);
static void insertToObject(tinyxml2::XMLElement* root, ffw::var* Output);
static void insertToArray(tinyxml2::XMLElement* root, ffw::var* Output);

///=============================================================================
static bool checkIfInt(const std::string& Str){
    for(const auto& chr : Str){
        if(chr == 10 || chr == 13 || chr == 32 || chr == 9)continue;
        if(!((chr >= '0' && chr  <= '9') || chr == '-')){
            return false;
        }
    }
    return true;
}

///=============================================================================
static bool checkIfFloat(const std::string& Str){
    for(const auto& chr : Str){
        if(chr == 10 || chr == 13 || chr == 32 || chr == 9)continue;
        if(!((chr >= '0' && chr  <= '9') || chr == '-' || chr == '+' || chr == '.' || chr == 'e' || chr == 'E')){
            return false;
        }
    }
    return true;
}

///=============================================================================
static bool checkIfBool(const std::string& Str, bool* Bool){
    if(Str.size() == 4 && (Str.find("true") == 0 || Str.find("TRUE") == 0)){
        *Bool = true;
        return true;
    } else if (Str.size() == 5 && (Str.find("false") == 0 || Str.find("FALSE") == 0)){
        *Bool = false;
        return true;
    }
    return false;
}

///=============================================================================
static ffw::var parseVariable(const std::string& Str){
    ffw::var variable;
    bool test;
    if(checkIfInt(Str)){
        variable = ffw::stringToVal<int>(Str);
        return variable;
    } else if(checkIfFloat(Str)){
        variable = ffw::stringToVal<float>(Str);
        return variable;
    } else if(checkIfBool(Str, &test)){
        variable = test;
        return variable;
    }
    variable = Str;
    return variable;
}

///=============================================================================
static void insertToObject(tinyxml2::XMLElement* root, ffw::var* Output){
    if(root->FirstChild() != NULL){
        // Parent does have children
        if(root->GetText() != NULL){
            // Children is a simple text
            const tinyxml2::XMLAttribute* attributePtr = root->FirstAttribute();
            if(attributePtr == NULL){
                Output->getAsObject().insert(std::make_pair(root->Name(), parseVariable(root->GetText())));
            } else {
                auto result = Output->getAsObject().insert(std::make_pair(root->Name(), ffw::varObject()));
                while(attributePtr != NULL){
                    result.first->second.getAsObject().insert(std::pair<std::string, ffw::var>("@" + std::string(attributePtr->Name()), parseVariable(attributePtr->Value())));
                    attributePtr = attributePtr->Next();
                }
                result.first->second.getAsObject().insert(std::pair<std::string, ffw::var>("content", parseVariable(root->GetText())));
            }

        } else {
            // Children has more elements
            const tinyxml2::XMLAttribute* attributePtr = root->FirstAttribute();
            if(attributePtr == NULL){
                auto result = Output->getAsObject().insert(std::make_pair(root->Name(), ffw::varObject()));
                convertXML(root->FirstChildElement(), &(result.first->second));

            } else {
                auto result = Output->getAsObject().insert(std::make_pair(root->Name(), ffw::varObject()));
                while(attributePtr != NULL){
                    result.first->second.getAsObject().insert(std::pair<std::string, ffw::var>("@" + std::string(attributePtr->Name()), parseVariable(attributePtr->Value())));
                    attributePtr = attributePtr->Next();
                }
                result = result.first->second.getAsObject().insert(std::make_pair("content", ffw::varObject()));
                convertXML(root->FirstChildElement(), &(result.first->second));
            }
        }
    } else {
        // Parent does not have children
        const tinyxml2::XMLAttribute* attributePtr = root->FirstAttribute();
        if(attributePtr == NULL){
            Output->getAsObject().insert(std::make_pair(root->Name(), ""));
        } else {
            auto result = Output->getAsObject().insert(std::make_pair(root->Name(), ffw::varObject()));
            while(attributePtr != NULL){
                result.first->second.getAsObject().insert(std::pair<std::string, ffw::var>("@" + std::string(attributePtr->Name()), parseVariable(attributePtr->Value())));
                attributePtr = attributePtr->Next();
            }
        }
    }
}

///=============================================================================
static void insertToArray(tinyxml2::XMLElement* root, ffw::var* Output){
    if(root->FirstChild() != NULL){
        // Parent does have children
        if(root->GetText() != NULL){
            // Children is a simple text
            const tinyxml2::XMLAttribute* attributePtr = root->FirstAttribute();
            if(attributePtr == NULL){
                Output->getAsArray().push_back(parseVariable(root->GetText()));
            } else {
                Output->getAsArray().push_back(ffw::varObject());
                auto result = &(Output->getAsArray().at(Output->getAsArray().size()-1));
                while(attributePtr != NULL){
                    result->getAsObject().insert(std::pair<std::string, ffw::var>("@" + std::string(attributePtr->Name()), parseVariable(attributePtr->Value())));
                    attributePtr = attributePtr->Next();
                }
                result->getAsObject().insert(std::pair<std::string, ffw::var>("content", parseVariable(root->GetText())));
            }
        } else {
            // Children has more elements
            const tinyxml2::XMLAttribute* attributePtr = root->FirstAttribute();
            if(attributePtr == NULL){
                Output->getAsArray().push_back(ffw::varObject());
                convertXML(root->FirstChildElement(), &(Output->getAsArray().at(Output->getAsArray().size()-1)));

            } else {
                Output->getAsArray().push_back(ffw::varObject());
                auto result = &(Output->getAsArray().at(Output->getAsArray().size()-1));
                while(attributePtr != NULL){
                    result->getAsObject().insert(std::pair<std::string, ffw::var>("@" + std::string(attributePtr->Name()), parseVariable(attributePtr->Value())));
                    attributePtr = attributePtr->Next();
                }
                auto resultPair = result->getAsObject().insert(std::make_pair("content", ffw::varObject()));
                convertXML(root->FirstChildElement(), &(resultPair.first->second));
            }
        }
    } else {
        // Parent does not have children
        const tinyxml2::XMLAttribute* attributePtr = root->FirstAttribute();
        if(attributePtr == NULL){
            Output->getAsArray().push_back(parseVariable(root->Name()));
        } else {
            Output->getAsArray().push_back(ffw::varObject());
            auto result = &(Output->getAsArray().at(Output->getAsArray().size()-1));
            while(attributePtr != NULL){
                result->getAsObject().insert(std::pair<std::string, ffw::var>("@" + std::string(attributePtr->Name()), parseVariable(attributePtr->Value())));
                attributePtr = attributePtr->Next();
            }
        }
    }
}

///=============================================================================
static void convertXML(tinyxml2::XMLElement* XML, ffw::var* Output){
    tinyxml2::XMLElement* root = XML;
    while(root != NULL){
        // Check if var is a object
        if(Output->getType() == ffw::var::type::vObject){
            // Check if element exists in array
            auto found = Output->getAsObject().find(root->Name());
            if(found != Output->getAsObject().end()){

                if(found->second.getType() != ffw::var::type::vArray){
                    // Element already exists! Convert to array...
                    ffw::var temp = found->second;
                    found->second = ffw::varArray();
                    found->second.getAsArray().push_back(temp);
                    //found->second.getAsArray().push_back(ffw::varArray());
                    insertToArray(root, &(found->second));
                } else {
                    // Element found but is not an array
                    insertToArray(root, &(found->second));
                }
            } else {
                // Element does not exists!
                insertToObject(root, Output);
            }
        } else {
            // Var is array
            insertToArray(root, Output);
        }

        root = root->NextSiblingElement();
    }
}

///=============================================================================
static std::string toUnicode(uint16_t Chr){
    std::string out = "xxxx;";
    char a = Chr / 4096;
    char b = (Chr -(a*4096)) / 256;
    char c = (Chr -(a*4096) -(b*256)) / 16;
    char d = Chr -(a*4096) -(b*256) -(c*16);
    if(a >= 10) a = 'A'+(a-10);
    else a = '0' + a;
    if(b >= 10) b = 'A'+(b-10);
    else b = '0' + b;
    if(c >= 10) c = 'A'+(c-10);
    else c = '0' + c;
    if(d >= 10) d = 'A'+(d-10);
    else d = '0' + d;
    out[0] = a;
    out[1] = b;
    out[2] = c;
    out[3] = d;
    return out;
}

///=============================================================================
static std::string escapeString(std::string Str, bool EscapeUnicode){
    if(Str.size() == 0)return "";
    for(size_t i = 0; ; i++){
        if((unsigned char)Str[i] < 32){
            if(Str[i] == 8){
                Str.replace(i, 1, "&#x0008;");
                i += 7;
            } else if(Str[i] == 9){
                Str.replace(i, 1, "&#x0009;");
                i += 7;
            } else if(Str[i] == 10){
                Str.replace(i, 1, "&#x000A;");
                i += 7;
            } else if(Str[i] == 12){
                Str.replace(i, 1, "&#x000C;");
                i += 7;
            } else if(Str[i] == 13){
                Str.replace(i, 1, "&#x000D;");
                i += 7;
            } else {
                Str.replace(i, 1, "&#x" + toUnicode((unsigned char)(Str[i])));
                i += 7;
            }
        } else if(uint16_t((uint8_t)Str[i]) > 127 && EscapeUnicode){
            /*size_t p = 0;
            while(uint16_t((uint8_t)Str[i+p]) > 127 && i+p < Str.size()){
                p++;
            }
            std::wstring mstr = ffw::utf8ToWstr(Str.substr(i, p));
            Str.replace(i, p, "&#x" + toUnicode((unsigned short)(mstr[0])));
            i += 7;*/

            size_t p = 0;
            while(uint16_t((uint8_t)Str[i+p]) > 127 && i+p < Str.size()){
                p++;
            }

            std::wstring mbstr = ffw::utf8ToWstr(Str.substr(i, p));
            //std::cout << "replacing: " << mstr[0] << std::endl;
            std::string unicodeStr;
            for(const auto& chr : mbstr){
                unicodeStr += "&#x" + toUnicode((uint16_t)chr);
            }
            Str.replace(i, p, unicodeStr);
            i+= unicodeStr.size();

        } else if(Str[i] == '\"'){
            Str.replace(i, 1, "&quot;");
            i += 5;
        } else if(Str[i] == '\"'){
            Str.replace(i, 1, "&apos;");
            i += 5;
        } else if(Str[i] == '&'){
            Str.replace(i, 1, "&amp;");
            i += 4;
        } else if(Str[i] == '<'){
            Str.replace(i, 1, "&lt;");
            i += 3;
        } else if(Str[i] == '>'){
            Str.replace(i, 1, "&gt;");
            i += 3;
        }
        if(i >= Str.size()-1)break;
    }
    return Str;
}

///=============================================================================
static bool checkIfAttributesEmpty(ffw::var* Input){
    if(Input->getType() != ffw::var::type::vObject){
        return false;
    }

    for(auto it = Input->getAsObject().begin(); it != Input->getAsObject().end(); it++){
        if(it->first[0] == '@')continue;
        else return false;
    }

    return true;
}

///=============================================================================
static bool checkIfAttributesContent(ffw::var* Input){
    if(Input->getType() != ffw::var::type::vObject){
        return false;
    }

    for(auto it = Input->getAsObject().begin(); it != Input->getAsObject().end(); it++){
        if(it->first[0] == '@')continue;
        else if(it->first == "content")continue;
        else return false;
    }

    return true;
}

///=============================================================================
static void encodeXMLFunc(std::string* Output, ffw::var* Var, bool Formated, std::string& Indent, bool EscapeUnicode, const std::string& ArrayTag){
    ffw::var::type varType = Var->getType();

    if(varType == ffw::var::type::vString){
        (*Output) += escapeString(Var->getAsString(), EscapeUnicode);

    } else if(varType == ffw::var::type::vInt){
        (*Output) += ffw::valToString(Var->getAsInt());

    } else if(varType == ffw::var::type::vFloat){
        (*Output) += ffw::valToString(Var->getAsFloat());

    } else if(varType == ffw::var::type::vBool){
        if(Var->getAsBool())(*Output) += "true";
        else (*Output) += "false";

    } else if(varType == ffw::var::type::vNull){
        (*Output) += "null";

    } else if(varType == ffw::var::type::vObject){
        //(*Output) += Indent

        for(auto it = Var->getAsObject().begin(); it != Var->getAsObject().end(); it++){
            if(checkIfAttributesEmpty(&(it->second))){
                std::string attr;
                if(Formated)
                    attr += Indent + "<" + escapeString(it->first, EscapeUnicode) + " ";
                else
                    attr += "<" + escapeString(it->first, EscapeUnicode) + " ";
                for(auto itit = it->second.getAsObject().begin(); itit != it->second.getAsObject().end(); itit++){
                    attr += itit->first.substr(1, itit->first.size()-1) + "=\"";
                    if     (itit->second.getType() == ffw::var::type::vString)attr += escapeString(itit->second.getAsString(), EscapeUnicode) + "\"";
                    else if(itit->second.getType() == ffw::var::type::vInt)attr += ffw::valToString(itit->second.getAsInt()) + "\"";
                    else if(itit->second.getType() == ffw::var::type::vFloat)attr += ffw::valToString(itit->second.getAsFloat()) + "\"";
                    else if(itit->second.getType() == ffw::var::type::vBool){
                         if(itit->second.getAsBool())attr += "true\"";
                         else attr += "false\"";
                    }
                    else if(itit->second.getType() == ffw::var::type::vNull)attr += "null\"";
                    else attr += "\"";
                }
                if(Formated)
                    (*Output) += attr + " />\n";
                else
                    (*Output) += attr + " />";

            } else if(checkIfAttributesContent(&(it->second))){
                std::string attr;
                if(Formated)
                    attr += Indent + "<" + escapeString(it->first, EscapeUnicode) + " ";
                else
                    attr += "<" + escapeString(it->first, EscapeUnicode) + " ";
                for(auto itit = it->second.getAsObject().begin(); itit != it->second.getAsObject().end(); itit++){
                    if(itit->first[0] != '@')continue;
                    attr += itit->first.substr(1, itit->first.size()-1) + "=\"";
                    if     (itit->second.getType() == ffw::var::type::vString)attr += escapeString(itit->second.getAsString(), EscapeUnicode) + "\"";
                    else if(itit->second.getType() == ffw::var::type::vInt)attr += ffw::valToString(itit->second.getAsInt()) + "\"";
                    else if(itit->second.getType() == ffw::var::type::vFloat)attr += ffw::valToString(itit->second.getAsFloat()) + "\"";
                    else if(itit->second.getType() == ffw::var::type::vBool){
                         if(itit->second.getAsBool())attr += "true\"";
                         else attr += "false\"";
                    }
                    else if(itit->second.getType() == ffw::var::type::vNull)attr += "null\"";
                    else attr += "\"";
                }

                bool isContentObject = false;
                bool isContentArray = false;

                if     (it->second.getAsObject()["content"].getType() == ffw::var::type::vObject)isContentObject = true;
                else if(it->second.getAsObject()["content"].getType() == ffw::var::type::vArray)isContentArray = true;

                if(isContentObject || isContentArray){
                    (*Output) += attr + ">\n";
                    Indent += "    ";
                }else{
                    (*Output) += attr + ">";
                }

                encodeXMLFunc(Output, &(it->second.getAsObject()["content"]), Formated, Indent, EscapeUnicode, "element");

                if(Formated){
                    if(isContentObject || isContentArray){
                        Indent = Indent.substr(0, Indent.size()-4);
                        (*Output) += Indent + "</" + escapeString(it->first, EscapeUnicode) + ">\n";
                    } else {
                        (*Output) += "</" + escapeString(it->first, EscapeUnicode) + ">\n";
                    }
                } else {
                    (*Output) += "</" + escapeString(it->first, EscapeUnicode) + ">";
                }

            } else {
                bool inside = false;
                bool isArray = false;
                if(it->second.getType() == ffw::var::type::vArray)isArray = true;

                if(Formated &&
                        ((it->second.getType() == ffw::var::type::vObject && it->second.getAsObject().begin() != it->second.getAsObject().end())
                      || (it->second.getType() == ffw::var::type::vArray && it->second.getAsArray().size() > 0)) ){

                    if(!isArray)(*Output) += Indent + "<" + escapeString(it->first, EscapeUnicode) + ">\n";
                    if(!isArray)Indent += "    ";
                    inside = true;
                } else if(Formated){
                    if(!isArray)(*Output) += Indent + "<" + escapeString(it->first, EscapeUnicode) + ">";
                } else {
                    if(!isArray)(*Output) += "<" + escapeString(it->first, EscapeUnicode) + ">";
                }

                encodeXMLFunc(Output, &(it->second), Formated, Indent, EscapeUnicode, escapeString(it->first, EscapeUnicode));

                if(Formated){
                    if(inside){
                        if(!isArray)Indent = Indent.substr(0, Indent.size()-4);
                        if(!isArray)(*Output) += Indent + "</" + escapeString(it->first, EscapeUnicode) + ">\n";
                    } else {
                        if(!isArray)(*Output) += "</" + escapeString(it->first, EscapeUnicode) + ">\n";
                    }
                } else {
                    if(!isArray)(*Output) += "</" + escapeString(it->first, EscapeUnicode) + ">";
                }
            }
        }
    } else if(varType == ffw::var::type::vArray){

        for(size_t i = 0; i < Var->getAsArray().size(); i++){
            bool inside = false;
            std::string arrayTagCopy = ArrayTag;
            if(Var->getAsArray().at(i).getType() == ffw::var::type::vArray){
                arrayTagCopy = "element";
            }

            if(Formated &&
                    ((Var->getAsArray().at(i).getType() == ffw::var::type::vObject && Var->getAsArray().at(i).getAsObject().begin() != Var->getAsArray().at(i).getAsObject().end())
                  || (Var->getAsArray().at(i).getType() == ffw::var::type::vArray && Var->getAsArray().at(i).getAsArray().size() > 0)) ){
                (*Output) += Indent + "<" + arrayTagCopy + ">\n";
                Indent += "    ";
                inside = true;
            } else if(Formated){
                (*Output) += Indent + "<" + arrayTagCopy + ">";
            } else {
                (*Output) += "<" + arrayTagCopy + ">";
            }

            encodeXMLFunc(Output, &(Var->getAsArray().at(i)), Formated, Indent, EscapeUnicode, "element");
            if(Formated){
                if(inside){
                    Indent = Indent.substr(0, Indent.size()-4);
                    (*Output) += Indent + "</" + arrayTagCopy + ">\n";
                } else {
                    (*Output) += "</" + arrayTagCopy + ">\n";
                }
            } else {
                (*Output) += "</" + arrayTagCopy + ">";
            }
        }
    }
}

///=============================================================================
bool ffw::decodeXML(const std::string& Str, ffw::var* Output){
    if(Output == NULL)return false;
    if(Str.size() == 0)return false;

    tinyxml2::XMLDocument doc;
    doc.Parse(Str.c_str());
    if(doc.Error())return false;
    *Output = ffw::varObject();
    convertXML(doc.RootElement(), Output);
    return true;
}

///=============================================================================
void ffw::encodeXML(std::string* Output, ffw::var* Var, bool Formated, bool EscapeUnicode){
    if(Output == NULL)return;
    if(Var == NULL)return;

    std::string indent;
    Output->clear();
    if(EscapeUnicode)
        (*Output) += "<?xml version=\"1.0\"? encoding=\"UTF-8\"?>";
    else
        (*Output) += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    if(Formated)(*Output) += "\n";
    encodeXMLFunc(Output, Var, Formated, indent, EscapeUnicode, "");
}

///=============================================================================
bool ffw::loadXML(const std::wstring& Path, ffw::var* Output){
    return loadXML(wstrToAnsi(Path), Output);
}

///=============================================================================
bool ffw::loadXML(const std::string& Path, ffw::var* Output){
    if(Output == NULL)return false;

    tinyxml2::XMLDocument doc;
    doc.LoadFile(Path.c_str());
    if(doc.Error())return false;
    *Output = ffw::varObject();
    convertXML(doc.RootElement(), Output);
    return true;
}

///=============================================================================
bool ffw::saveXML(const std::string& Path, ffw::var* Input, bool Formated, bool EscapeUnicode){
    return saveXML(utf8ToWstr(Path), Input, Formated, EscapeUnicode);
}

///=============================================================================
bool ffw::saveXML(const std::wstring& Path, ffw::var* Input, bool Formated, bool EscapeUnicode){
    if(Input == NULL)return false;

    ffw::file output;
    if(!output.open(Path, false, true, true)){
        return false;
    }

    std::string encoded;
    encodeXML(&encoded, Input, Formated, EscapeUnicode);

    output.write(&encoded[0], encoded.size());
    output.close();
    return true;
}
