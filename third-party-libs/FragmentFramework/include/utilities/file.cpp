/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "file.h"
#include "../math/math.h"
#include "../math/stringMath.h"
#include <iostream>
#include <fstream>
#include <algorithm>

///=============================================================================
ffw::file::file(){
}

///=============================================================================
ffw::file::~file(){
    if(fileStream.is_open())fileStream.close();
}

///=============================================================================
bool ffw::file::open(const std::string& Path, bool IsBinary, bool Write, bool DeleteContents){
    return open(utf8ToWstr(Path), IsBinary, Write, DeleteContents);
}

///=============================================================================
bool ffw::file::open(const std::wstring& Path, bool IsBinary, bool Write, bool DeleteContents){
    std::ios_base::openmode mode;
    // Ugly mode selection
    if(IsBinary){
        if(Write){
            if(DeleteContents)  mode = std::ios::out | std::ios::binary | std::ios::trunc;
            else                mode = std::ios::out | std::ios::binary;
        } else {
            if(DeleteContents)  mode = std::ios::in | std::ios::binary | std::ios::trunc;
            else                mode = std::ios::in | std::ios::binary;
        }
    } else {
        if(Write){
            if(DeleteContents)  mode = std::ios::out | std::ios::trunc;
            else                mode = std::ios::out;
        } else {
            if(DeleteContents)  mode = std::ios::in | std::ios::trunc;
            else                mode = std::ios::in;
        }
    }
    fileStream.open(wstrToAnsi(Path), mode);

    if(!fileStream){
        return false;
    }

    //if(!Write)gotoBeginning();

    return true;
}

///=============================================================================
bool ffw::file::isOpen(){
    return fileStream.is_open();
    //return fileOpen;
}

///=============================================================================
bool ffw::file::read(void* Data, size_t Size){
    if(!fileStream.is_open())return false;
    fileStream.read(reinterpret_cast<char*>(Data), Size);
    //return !fileStream.fail();
    return true;
}

///=============================================================================
bool ffw::file::write(void* Data, size_t Size){
    if(!fileStream.is_open())return false;
    fileStream.write(reinterpret_cast<const char*>(Data), Size);
    return !fileStream.fail();
}

///=============================================================================
bool ffw::file::readLine(std::string* Str){
    if(!fileStream.is_open())return false;
    std::getline(fileStream, *Str);
	//return !fileStream.fail();
	return true;
}

///=============================================================================
bool ffw::file::writeLine(const std::string& Str){
    if(!fileStream.is_open())return false;
    if(!(fileStream << Str))return false;
	fileStream.put('\n');
	return !fileStream.fail();
}

///=============================================================================
bool ffw::file::readChar(char* Chr){
    if(!fileStream.is_open())return false;
    fileStream.get(*Chr);
	//return !fileStream.fail();
	return true;
}

///=============================================================================
bool ffw::file::writeChar(char Chr){
    if(!fileStream.is_open())return false;
    fileStream.put(Chr);
	return !fileStream.fail();
}

///=============================================================================
bool ffw::file::gotoPos(unsigned int Pos){
    if(!fileStream.is_open())return false;
	fileStream.seekg(Pos);
	return !fileStream.fail();
}

///=============================================================================
bool ffw::file::gotoPosOffset(unsigned int Pos){
    if(!fileStream.is_open())return false;
    std::streampos currentPos = fileStream.tellg();
    currentPos += Pos;
	fileStream.seekg(currentPos);
	return !fileStream.fail();
}

///=============================================================================
bool ffw::file::gotoLine(unsigned int Num){
    if(!fileStream.is_open())return false;
    if(!gotoBeginning())return false;

    unsigned int i = 0;
    while(i != Num){
        fileStream.ignore(256, '\n');
		if(fileStream.fail())return false;
        i++;
    }
    std::streampos pos = fileStream.tellg();
    pos -= 1;
    fileStream.seekg(pos);
    return true;
}

///=============================================================================
bool ffw::file::gotoEnd(){
    if(!fileStream.is_open())return false;
    fileStream.seekg(0, std::ios::end);
    return true;
}

///=============================================================================
bool ffw::file::gotoBeginning(){
    if(!fileStream.is_open())return false;
    fileStream.seekg(0, std::ios::beg);
    return true;
}

///=============================================================================
size_t ffw::file::getPos(){
    if(!fileStream.is_open())return 0;
	return (size_t)fileStream.tellg();
}

///=============================================================================
size_t ffw::file::countLines(){
    if(!fileStream.is_open())return 0;
	size_t pos = (size_t)fileStream.tellg();
    fileStream.seekg(0, std::ios::beg);
	size_t lines = (size_t)std::count(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>(), '\n');
    fileStream.seekg(pos);
    if(getSize() > 0 && lines == 0)lines = 1;
    return lines;
}

///=============================================================================
void ffw::file::close(){
    fileStream.close();
}

///=============================================================================
size_t ffw::file::getSize(){
    if(!fileStream.is_open())return 0;
	size_t pos = (size_t)fileStream.tellg();
    fileStream.seekg(0, std::ios::end);
	size_t size = (size_t)fileStream.tellg();
    fileStream.seekg(pos);
    return size;
}

///=============================================================================
bool ffw::file::eof(){
    return fileStream.eof();
}
