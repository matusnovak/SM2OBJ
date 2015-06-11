/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "loadSaveJson.h"
#include "loadSaveTxt.h"
#include "../math/stringMath.h"
#include "../math/math.h"
#include "file.h"

#define THROW(exceptionClass, message) throw exceptionClass(__FILE__, __LINE__, (message) )

///=============================================================================
static size_t findCollon(const std::string& Str, size_t Start, size_t End){
    bool insideString = false;
    for(size_t i = Start; i < End; i++){

        if(Str[i] == '\"'){
            if( ((i == Start) || (i == Start+1 && Str[i-1] != '\\')) ||
                ((i > Start+1) && ((Str[i-1] == '\\' && Str[i-2] == '\\') || (Str[i-1] != '\\'))) ){
                if(!insideString)insideString = true;
                else if(insideString)insideString = false;
            }
        }

        if(!insideString && Str[i] == ':'){
            return i;
        }
    }
    return 0;
}

///=============================================================================
static std::string unicodeToUtf8(const std::string& Str, size_t Start){
    uint16_t value = 0;
    for(int i = 0; i < 4; i++){
        if(Str[Start+i] >= 'A' && Str[Start+i] <= 'F')value += (Str[Start+i] - 'A' + 10) * (uint16_t)pow(16, 3-i);
        else if(Str[Start+i] >= 'a' && Str[Start+i] <= 'f')value += (Str[Start+i] - 'a' + 10 )* (uint16_t)pow(16, 3-i);
        else if(Str[Start+i] >= '0' && Str[Start+i] <= '9')value += (Str[Start+i] - '0') * (uint16_t)pow(16, 3-i);
        else value += (uint16_t)pow(16, 3-i);
    }
    std::wstring wstr = L" ";
    wstr[0] = value;
    return ffw::wstrToUtf8(wstr);
}

///=============================================================================
static std::string toUnicode(uint16_t Chr){
    std::string out = "xxxx";
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
                Str.replace(i, 1, "\\b");
                i++;
                //continue;
            } else if(Str[i] == 9){
                Str.replace(i, 1, "\\t");
                i++;
                //continue;
            } else if(Str[i] == 10){
                Str.replace(i, 1, "\\n");
                i++;
                //continue;
            } else if(Str[i] == 12){
                Str.replace(i, 1, "\\f");
                i++;
                //continue;
            } else if(Str[i] == 13){
                Str.replace(i, 1, "\\c");
                i++;
                //continue;
            } else {
                Str.replace(i, 1, "\\u" + toUnicode((unsigned char)(Str[i])));
                i += 5;
                //std::cout << "i: " << i << std::endl;
                //continue;
            }
        } else if(uint16_t((uint8_t)Str[i]) > 127 && EscapeUnicode){
            size_t p = 0;
            while(uint16_t((uint8_t)Str[i+p]) > 127 && i+p < Str.size()){
                p++;
            }

            std::wstring mbstr = ffw::utf8ToWstr(Str.substr(i, p));
            //std::cout << "replacing: " << mstr[0] << std::endl;
            std::string unicodeStr;
            for(const auto& chr : mbstr){
                unicodeStr += "\\u" + toUnicode((uint16_t)chr);
            }
            Str.replace(i, p, unicodeStr);
            i+= unicodeStr.size();
            //continue;

        } else if(Str[i] == '\"'){
            Str.replace(i, 1, "\\\"");
            i++;
            //continue;
        } else if(Str[i] == '\\'){
            Str.replace(i, 1, "\\\\");
            i++;
            //continue;
        } else if(Str[i] == '/'){
            Str.replace(i, 1, "\\/");
            i++;
            //continue;
        }
        //i++;
        if(i >= Str.size()-1)break;
    }
    return Str;
}

///=============================================================================
static std::string parseStringSimple(const std::string& Str){
    std::string out = Str;

    for(size_t i = 0; ; i++){
        if(out[i] == '\\' && i < out.size()-1){
            if(out[i+1] == '\"'){
                out.replace(i, 2, "\"");

            } else if(out[i+1] == '/'){
                out.replace(i, 2, "/");

            } else if(out[i+1] == '\\'){
                out.replace(i, 2, "\\");

            } else if(out[i+1] == 'b'){
                out.replace(i, 2, " ");
                out[i] = 8;

            } else if(out[i+1] == 'f'){
                out.replace(i, 2, " ");
                out[i] = 12;

            } else if(out[i+1] == 'n'){
                out.replace(i, 2, " ");
                out[i] = 10;

            } else if(out[i+1] == 'r'){
                out.replace(i, 2, " ");
                out[i] = 13;

            } else if(out[i+1] == 'u' && i < out.size()-5){
                out.replace(i, 5, unicodeToUtf8(out, i+2));
                i++;
            }
        }
        if(i >= out.size()-1)break;
    }

    return out;
}

///=============================================================================
static bool parseString(const std::string& Str, size_t Start, size_t End, std::string* Out){
    size_t start = false;
    size_t end = false;

    for(size_t i = Start; i < End; i++){
        if(Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9)continue;
        if(Str[i] == '\"'){
            start = i;
            break;
        } else {
            return false;
        }
    }

    for(size_t i = End-1; i > Start; i--){
        if(Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9)continue;
        if(Str[i] == '\"'){
            end = i;
            break;
        } else {
            return false;
        }
    }

    if(start -end -1 == 0)return false;

    Out->assign(Str, start+1, end-start-1);

    for(size_t i = 0; ; i++){
        if((*Out)[i] == '\\' && i < Out->size()-1){
            if((*Out)[i+1] == '\"'){
                Out->replace(i, 2, "\"");

            } else if((*Out)[i+1] == '/'){
                Out->replace(i, 2, "/");

            } else if((*Out)[i+1] == '\\'){
                Out->replace(i, 2, "\\");

            } else if((*Out)[i+1] == 'b'){
                Out->replace(i, 2, " ");
                (*Out)[i] = 8;

            } else if((*Out)[i+1] == 'f'){
                Out->replace(i, 2, " ");
                (*Out)[i] = 12;

            } else if((*Out)[i+1] == 'n'){
                Out->replace(i, 2, " ");
                (*Out)[i] = 10;

            } else if((*Out)[i+1] == 'r'){
                Out->replace(i, 2, " ");
                (*Out)[i] = 13;

            } else if((*Out)[i+1] == 'u' && i < Out->size()-5){
                Out->replace(i, 5, unicodeToUtf8(*Out, i+2));
                i++;
            }
        }
        if(i >= Out->size()-1)break;
    }

    return true;
}

///=============================================================================
static bool getKey(const std::string& Str, size_t Start, size_t End, std::string* Key){
    size_t start = false;
    size_t end = false;
    for(size_t i = Start; i < End; i++){
        if(Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9)continue;
        if(Str[i] == '\"'){
            start = i;
            break;
        } else {
            return false;
        }
    }

    for(size_t i = End-1; i > Start; i--){
        if(Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9)continue;
        if(Str[i] == '\"'){
            end = i;
            break;
        } else {
            return false;
        }
    }

    Key->assign(Str, start+1, end-start-1);
    return true;
}

///=============================================================================
static bool checkIfInt(const std::string& Str, size_t Start, size_t End){
    for(size_t i = Start; i < End; i++){
        if(Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9)continue;
        if(!((Str[i] >= '0' && Str[i]  <= '9') || Str[i] == '-')){
            return false;
        }
    }
    return true;
}

///=============================================================================
static bool checkIfFloat(const std::string& Str, size_t Start, size_t End){
    for(size_t i = Start; i < End; i++){
        if(Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9)continue;
        if(!((Str[i] >= '0' && Str[i]  <= '9') || Str[i] == '-' || Str[i] == '+' || Str[i] == '.' || Str[i] == 'e' || Str[i] == 'E')){
            return false;
        }
    }
    return true;
}

///=============================================================================
static bool checkIfBool(const std::string& Str, size_t Start, size_t End, bool* Bool){
    bool start = false;
    bool found = false;
    for(size_t i = Start; i < End; i++){
        if(!start && (Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9))continue;
        start = true;
        if(Str[i] == 't' || Str[i] == 'T'){
            if(i+3 > End)return false;
            if((Str[i+1] == 'r' && Str[i+2] == 'u' && Str[i+3] == 'e') || (Str[i+1] == 'R' && Str[i+2] == 'U' && Str[i+3] == 'E')){
                found = true;
                *Bool = true;
                i += 3;
                continue;
            }
        } else if(Str[i] == 'f' || Str[i] == 'F'){
            if(i+4 > End)return false;
            if((Str[i+1] == 'a' && Str[i+2] == 'l' && Str[i+3] == 's' && Str[i+4] == 'e') || (Str[i+1] == 'A' && Str[i+2] == 'L' && Str[i+3] == 'S' && Str[i+4] == 'E')){
                found = true;
                *Bool = false;
                i += 4;
                continue;
            }
        }
        if(found && !(Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9))return false;
    }
    return found;
}

///=============================================================================
static bool checkIfString(const std::string& Str, size_t Start, size_t End){
    bool start = false;
    bool end = false;
    for(size_t i = Start; i < End; i++){
        if(!start && (Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9))continue;
        start = true;
        if(Str[i] != '\"'){
            return false;
        } else break;
    }

    for(size_t i = End-1; i > Start; i--){
        if(!end && (Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9))continue;
        end = true;
        if(Str[i] != '\"'){
            return false;
        } else break;
    }

    return true;
}

///=============================================================================
static bool checkIfObject(const std::string& Str, size_t Start, size_t End){
    bool start = false;
    bool end = false;
    for(size_t i = Start; i < End; i++){
        if(!start && (Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9))continue;
        start = true;
        if(Str[i] != '{'){
            return false;
        } else break;
    }

    for(size_t i = End-1; i > Start; i--){
        if(!end && (Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9))continue;
        end = true;
        if(Str[i] != '}'){
            return false;
        } else break;
    }

    return true;
}

///=============================================================================
static bool checkIfArray(const std::string& Str, size_t Start, size_t End){
    bool start = false;
    bool end = false;
    for(size_t i = Start; i < End; i++){
        if(!start && (Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9))continue;
        start = true;
        if(Str[i] != '['){
            return false;
        } else break;
    }

    for(size_t i = End-1; i > Start; i--){
        if(!end && (Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9))continue;
        end = true;
        if(Str[i] != ']'){
            return false;
        } else break;
    }

    return true;
}

///=============================================================================
static bool checkIfNull(const std::string& Str, size_t Start, size_t End){
    bool start = false;
    bool found = false;
    for(size_t i = Start; i < End; i++){
        if(!start && (Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9))continue;
        start = true;
        if(Str[i] == 'n' || Str[i] == 'N'){
            if(i+3 > End)return false;
            if((Str[i+1] == 'u' && Str[i+2] == 'l' && Str[i+3] == 'l') || (Str[i+1] == 'U' && Str[i+2] == 'L' && Str[i+3] == 'L')){
                found = true;
                i += 3;
                continue;
            }
        }
        if(found && !(Str[i] == 10 || Str[i] == 13 || Str[i] == 32 || Str[i] == 9))return false;
    }
    return found;
}

///=============================================================================
static void parse(const std::string& Str, size_t Start, size_t End, ffw::var* Output){
    if(Start+1 == End)return;
    bool isArray = false;
    if(Str[Start] == '['){
        isArray = true;
    }

    std::vector<size_t> commas;
    int brackets = 0;
    bool insideString = false;

    for(size_t i = Start+1; i < End; i++){
        if     (Str[i] == '{')brackets++;
        else if(Str[i] == '}')brackets--;
        else if(Str[i] == '[')brackets++;
        else if(Str[i] == ']')brackets--;

        /*if((i > Start+1 && Str[i] == '\"' && Str[i-1] != '\\') || (i == Start+1 && Str[i] == '\"')){
            if(!insideString)insideString = true;
            else if(insideString)insideString = false;
        }*/

        if(Str[i] == '\"'){

            if( ((i == Start) || (i == Start+1 && Str[i-1] != '\\')) ||
                ((i > Start+1) && ((Str[i-1] == '\\' && Str[i-2] == '\\') || (Str[i-1] != '\\'))) ){
                if(!insideString)insideString = true;
                else if(insideString)insideString = false;
            }
        }

        if(!insideString && brackets == 0 && Str[i] == ','){
            commas.push_back(i);
        }
    }

    if(isArray){
        *Output = ffw::varArray();
    } else {
        *Output = ffw::varObject();
    }

    size_t i = 0;
    while(true){
        size_t pos = 0;
        size_t length = 0;

        if(commas.size() == 0){
            pos = Start+1;
            length = End - pos;
        } else {
            if(i == 0){
                pos = Start+1;
                length = commas[i] - pos;
            } else if(i > 0 && i < commas.size()){
                pos = commas[i-1]+1;
                length = commas[i] - (commas[i-1]+1);
            } else {
                pos = commas[i-1]+1;
                length = End - (commas[i-1]+1);
            }
            i++;
        }

        if(isArray){
            bool boolean;
            if(checkIfInt(Str, pos, pos+length)){
                Output->getAsArray().push_back(ffw::stringToVal<int>(Str.substr(pos, pos-length)));

            } else if(checkIfFloat(Str, pos, pos+length)){
                Output->getAsArray().push_back(ffw::stringToVal<float>(Str.substr(pos, pos-length)));

            } else if(checkIfBool(Str, pos, pos+length, &boolean)){
                Output->getAsArray().push_back(boolean);

            } else if(checkIfString(Str, pos, pos+length)){
                std::string newStr;
                parseString(Str, pos, pos+length, &newStr);
                Output->getAsArray().push_back(newStr);

            } else if(checkIfNull(Str, pos, pos+length)){
                Output->getAsArray().push_back(nullptr);

            } else if(checkIfArray(Str, pos, pos+length)){
                size_t newBegin = pos;
                size_t newEnd = pos+length;
                for(size_t i = newBegin; i < newEnd; i++){
                    if(Str[i] == '['){newBegin = i;break;}
                }
                for(size_t i = newEnd; i > newBegin; i--){
                    if(Str[i] == ']'){newEnd = i;break;}
                }
                Output->getAsArray().push_back(ffw::var());
                parse(Str, newBegin, newEnd, &Output->getAsArray().at(Output->getAsArray().size()-1));

            } else if(checkIfObject(Str, pos, pos+length)){
                size_t newBegin = pos;
                size_t newEnd = pos+length;
                for(size_t i = newBegin; i < newEnd; i++){
                    if(Str[i] == '{'){newBegin = i;break;}
                }
                for(size_t i = newEnd; i > newBegin; i--){
                    if(Str[i] == '}'){newEnd = i;break;}
                }
                Output->getAsArray().push_back(ffw::var());
                parse(Str, newBegin, newEnd, &Output->getAsArray().at(Output->getAsArray().size()-1));

            } else {
                return;
            }

        } else {
            size_t collon = findCollon(Str, pos, pos+length);
            if(collon == 0){
                return;
            }

            std::string key;
            if(!getKey(Str, pos, collon, &key)){
                return;
            }
            key = parseStringSimple(key);

            bool boolean;

            if(checkIfInt(Str, collon+1, pos+length)){
                Output->getAsObject().insert(std::pair<std::string, ffw::var>(key, ffw::stringToVal<int>(Str.substr(collon+1, (pos+length)-collon-1))));

            } else if(checkIfFloat(Str, collon+1, pos+length)){
                Output->getAsObject().insert(std::pair<std::string, ffw::var>(key, ffw::stringToVal<float>(Str.substr(collon+1, (pos+length)-collon-1))));

            } else if(checkIfBool(Str, collon+1, pos+length, &boolean)){
                Output->getAsObject().insert(std::pair<std::string, ffw::var>(key, boolean));

            } else if(checkIfString(Str, collon+1, pos+length)){
                std::string newStr;
                parseString(Str, collon+1, pos+length, &newStr);
                Output->getAsObject().insert(std::pair<std::string, ffw::var>(key, newStr));

            } else if(checkIfNull(Str, collon+1, pos+length)){
                Output->getAsObject().insert(std::pair<std::string, ffw::var>(key, nullptr));

            } else if(checkIfArray(Str, collon+1, pos+length)){
                size_t newBegin = collon+1;
                size_t newEnd = pos+length;

                for(size_t i = newBegin; i < newEnd; i++){
                    if(Str[i] == '['){newBegin = i;break;}
                }
                for(size_t i = newEnd-1; i > newBegin; i--){
                    if(Str[i] == ']'){newEnd = i;break;}
                }

                Output->getAsObject().insert(std::pair<std::string, ffw::var>(key, ffw::var()));
                parse(Str, newBegin, newEnd, &Output->getAsObject().at(key));

            } else if(checkIfObject(Str, collon+1, pos+length)){
                size_t newBegin = collon+1;
                size_t newEnd = pos+length;

                for(size_t i = newBegin; i < newEnd; i++){
                    if(Str[i] == '{'){newBegin = i;break;}
                }
                for(size_t i = newEnd-1; i > newBegin; i--){
                    if(Str[i] == '}'){newEnd = i;break;}
                }

                Output->getAsObject().insert(std::pair<std::string, ffw::var>(key, ffw::var()));
                parse(Str, newBegin, newEnd, &Output->getAsObject().at(key));

            } else {
                return;
            }
        }

        if(commas.size() == 0)break;
        else if(i == commas.size()+1)break;
    }
}

///=============================================================================
static void encodeJSONFunc(std::string* Output, ffw::var* Var, bool Formated, std::string& Indent, bool EscapeUnicode){
    ffw::var::type varType = Var->getType();

    if(varType == ffw::var::type::vString){
        (*Output) += "\"" + escapeString(Var->getAsString(), EscapeUnicode) + "\"";

    } else if(varType == ffw::var::type::vInt){
        (*Output) += ffw::valToString(Var->getAsInt());

    } else if(varType == ffw::var::type::vFloat){
        (*Output) += ffw::valToString(Var->getAsFloat());

    } else if(varType == ffw::var::type::vBool){
        if(Var->getAsBool())(*Output) += "true";
        else (*Output) += "false";

    } else if(varType == ffw::var::type::vNull){
        (*Output) += "null";

    } else if(varType == ffw::var::type::vArray){
        if(Formated){
            (*Output) += "[\n";
            Indent += "    ";
        } else {
            (*Output) += "[";
        }

        for(size_t i = 0; i < Var->getAsArray().size(); i++){
            if(Formated)(*Output) += Indent;
            encodeJSONFunc(Output, &(Var->getAsArray()[i]), Formated, Indent, EscapeUnicode);
            if(Formated){
                if(i != Var->getAsArray().size()-1)(*Output) += ",\n";
                else (*Output) += "\n";
            } else {
                if(i != Var->getAsArray().size()-1)(*Output) += ",";
            }
        }
        if(Formated){
            Indent = Indent.substr(0, Indent.size()-4);
            (*Output) += Indent + "]";
        } else {
            (*Output) += "]";
        }

    } else if(varType == ffw::var::type::vObject){
        if(Var->getAsObject().begin() == Var->getAsObject().end()){
            (*Output) += "{}";
            return;
        }

        if(Formated){
            (*Output) += "{\n";
            Indent += "    ";
        } else {
            (*Output) += "{";
        }

        auto last = Var->getAsObject().end();
        last--;
        for(auto it = Var->getAsObject().begin(); it != Var->getAsObject().end(); it++){
            if(Formated){
                (*Output) += Indent + "\"" + escapeString(it->first, EscapeUnicode) + "\": ";
            } else {
                (*Output) += "\"" + escapeString(it->first, EscapeUnicode) + "\": ";
            }

            encodeJSONFunc(Output, &(it->second), Formated, Indent, EscapeUnicode);

            if(Formated){
                if(it != last)(*Output) += ",\n";
                else (*Output) += "\n";
            } else {
                if(it != last)(*Output) += ",";
            }
        }

        if(Formated){
            Indent = Indent.substr(0, Indent.size()-4);
            (*Output) += Indent + "}";
        } else {
            (*Output) += "}";
        }
    }
}

///=============================================================================
void ffw::encodeJSON(std::string* Output, ffw::var* Var, bool Formated, bool EscapeUnicode){
    if(Output == NULL)return;
    if(Var == NULL)return;
    std::string indent;
    Output->clear();
    encodeJSONFunc(Output, Var, Formated, indent, EscapeUnicode);
}

///=============================================================================
bool ffw::decodeJSON(const std::string& Str, ffw::var* Output){
    if(Output == NULL)return false;
    if(Str.size() == 0)return false;

    size_t begin = 0;
    size_t end = 0;
    for(size_t i = 0; i < Str.size(); i++){
        if(Str[i] == '{' || Str[i] == '['){
            begin = i;
            break;
        }
    }

    for(long i = Str.size()-1; i > 0; i--){
        if(Str[i] == '}' || Str[i] == ']'){
            end = i;
            break;
        }
    }

    if(begin == 0 && end == 0)return false;

    if(!((Str[begin] == '{' && Str[end] == '}') || (Str[begin] == '[' && Str[end] == ']'))){
        return false;
    }

    parse(Str, begin, end, Output);

    return true;
}

///=============================================================================
bool ffw::loadJSON(const std::string& Path, ffw::var* Output){
    return loadJSON(utf8ToWstr(Path), Output);
}

///=============================================================================
bool ffw::loadJSON(const std::wstring& Path, ffw::var* Output){
    if(Output == NULL)return false;

    std::string buffer;
    if(!loadTXT(Path, &buffer)){
        return false;
    }

    /*ffw::file input;
    if(!input.open(Path, false, false, false)){
        return false;
    }

    size_t length = input.getSize();

    if(length == 0)return false;

    std::string buffer;
    buffer.resize(length, ' ');
    input.read(&buffer[0], length*sizeof(char));
    input.close();*/
    return decodeJSON(buffer, Output);
}

///=============================================================================
bool ffw::saveJSON(const std::string& Path, ffw::var* Input, bool Formated, bool EscapeUnicode){
    return saveJSON(utf8ToWstr(Path), Input, Formated, EscapeUnicode);
}

///=============================================================================
bool ffw::saveJSON(const std::wstring& Path, ffw::var* Input, bool Formated, bool EscapeUnicode){
    if(Input == NULL)return false;

    ffw::file output;
    if(!output.open(Path, false, true, true)){
        return false;
    }

    std::string encoded;
    encodeJSON(&encoded, Input, Formated, EscapeUnicode);

    output.write(&encoded[0], encoded.size());
    output.close();
    return true;
}
