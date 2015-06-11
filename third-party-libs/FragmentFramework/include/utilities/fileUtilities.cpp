/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "fileUtilities.h"

///=============================================================================
bool ffw::checkIfFileExists(const std::wstring& Path){
    FILE* file = _wfopen(Path.c_str(), L"r");
    if(file == NULL)return false;
    fclose(file);
    return true;
}

///=============================================================================
bool ffw::checkIfFileExists(const std::string& Path){
    FILE* file = fopen(Path.c_str(), "r");
    if(file == NULL)return false;
    fclose(file);
    return true;
}

///=============================================================================
void ffw::getFilePathProperties(const std::string& Path, std::string *Directory, std::string *FileName, std::string *FileExtension){
    size_t slashPos = Path.find_last_of('\\');
    size_t dotPos = Path.find_last_of('.');
    size_t namePos = 0;

    if(slashPos == std::string::npos)slashPos = Path.find_last_of('/');

    if(slashPos != std::string::npos){
        namePos = slashPos+1;
        if(Directory != NULL)*Directory = Path.substr(0, slashPos+1);
    } else {
        if(Directory != NULL)*Directory = "";
    }

    dotPos = Path.find_last_of('.');

    if(dotPos != std::string::npos){
        if(FileName != NULL)*FileName = Path.substr(namePos, dotPos-namePos);
        if(FileExtension != NULL)*FileExtension = Path.substr(dotPos+1, Path.size()-dotPos-1);
    } else {
        if(FileName != NULL)*FileName = Path.substr(namePos, Path.size()-namePos);
        if(FileExtension != NULL)*FileExtension = "";
    }
}
