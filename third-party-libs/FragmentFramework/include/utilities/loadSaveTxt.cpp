/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "loadSaveTxt.h"
#include "file.h"
#include "../math/math.h"
#include "../math/stringMath.h"

///=============================================================================
bool ffw::loadTXT(const std::string& Path, std::string* Data){
    return loadTXT(utf8ToWstr(Path), Data);
}

///=============================================================================
bool ffw::loadTXT(const std::wstring& Path, std::string* Data){
    if(Data == NULL)return false;

    ffw::file input;
    if(!input.open(Path, false, false, false))return false;

    Data->clear();
    while(!input.eof()){
        std::string temp;
        input.readLine(&temp);
        (*Data) += temp + "\n";
    }
    return true;

    /*size_t size = input.getSize();
    Data->resize(size, ' ');
    input.read(&(*Data)[0], size);
    return true;*/

    /*std::ifstream file;
    file.open(Path.c_str(), std::ifstream::in);
    if(!file){
        return false;
    }

    Data->clear();
    std::string temp;
    while(std::getline(file, temp)){
        (*Data) += temp + "\n";
    }

    file.close();
    return true;*/
}

///=============================================================================
bool ffw::saveTXT(const std::string& Path, const std::string& Data){
    return saveTXT(utf8ToWstr(Path), Data);
}

///=============================================================================
bool ffw::saveTXT(const std::wstring& Path, const std::string& Data){
    ffw::file output;
    if(!output.open(Path, false, true, true))return false;

    output.write((void*)&Data[0], Data.size());
    return true;

    /*std::ofstream file;
    file.open(Path.c_str(), std::ofstream::out | std::ofstream::trunc);
    if(!file){
        return false;
    }

    file << Data;

    file.close();
    return true;*/
}

///=============================================================================
bool ffw::loadTXT(const std::string& Path, std::vector<std::string>* Data){
    return loadTXT(utf8ToWstr(Path), Data);
}

///=============================================================================
bool ffw::loadTXT(const std::wstring& Path, std::vector<std::string>* Data){
    if(Data == NULL)return false;

    ffw::file input;
    if(!input.open(Path, false, false, false))return false;

    size_t lines = input.countLines();
    Data->resize(lines);
    for(size_t i = 0; i < lines; i++){
        input.readLine(&(*Data)[i]);
    }

    return true;


    /*if(Data == NULL)return false;

    std::ifstream file;
    file.open(Path.c_str(), std::ifstream::in);
    if(!file){
        return false;
    }

    Data->clear();
    std::string temp;
    while(std::getline(file, temp)){
        Data->push_back(temp);
    }

    file.close();
    return true;*/
}

///=============================================================================
bool ffw::saveTXT(const std::string& Path, const std::vector<std::string>& Data){
    return saveTXT(utf8ToWstr(Path), Data);
}

///=============================================================================
bool ffw::saveTXT(const std::wstring& Path, const std::vector<std::string>& Data){
    ffw::file output;
    if(!output.open(Path, false, true, true))return false;

    for(const auto& line : Data){
        output.writeLine(line);
    }
    return true;

    /*std::ofstream file;
    file.open(Path.c_str(), std::ofstream::out | std::ofstream::trunc);
    if(!file){
        return false;
    }

    for(size_t i = 0; i < Data.size(); i++){
        file << Data[i] + "\n";
    }
    file.close();
    return true;*/
}

/*///=============================================================================
bool ffw::loadTXTutf8(const std::wstring& Path, std::wstring* Data){
    if(Data == NULL)return false;

    FILE* file = _wfopen(&Path[0], L"rtS, ccs=UTF-8");

    if(file == NULL){
        //logger().error() << "[File loader] " << Path << " failed to open!";
        return false;
    }

    struct _stat fileinfo;
    _wstat(&Path[0], &fileinfo);
    size_t size = fileinfo.st_size;

    if(size > 0){
        Data->resize(size);
        size_t wchars_read = fread(&(Data->front()), sizeof(wchar_t), size, file);
        Data->resize(wchars_read);
        Data->shrink_to_fit();
    }

    fclose(file);
    return true;
}

///=============================================================================
bool ffw::saveTXTutf8(const std::wstring& Path, const std::wstring& Data){
    FILE* file = _wfopen(&Path[0], L"wtS, ccs=UTF-8");

    if(file == NULL){
        return false;
    }

    fwrite(&Data[0], sizeof(wchar_t), Data.size(), file);

    fclose(file);
    return true;
}*/
