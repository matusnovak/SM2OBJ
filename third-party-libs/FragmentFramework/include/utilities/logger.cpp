/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "logger.h"
#include <Windows.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/timeb.h>
#include "../systemUtils/win32SysUtils.h"

static int verbosity = 0;
static std::string path = ".";
static HANDLE hConsole;
static bool initialized = false;
static bool consoleInit = false;
static bool consoleOut = true;

///=============================================================================
void ffw::logger::initLogger(std::string Path){
    clearLog();
    path = Path + "\\log.txt";
    initialized = true;
}

///=============================================================================
void ffw::logger::initLogger(){
    clearLog();
    path = getExecutablePath() + "\\log.txt";
    initialized = true;
}

///=============================================================================
std::ostringstream& ffw::logger::print() {
    type = 2;
    os << getTime() + "[NOTICE]  ";
    return os;
}

///=============================================================================
std::ostringstream& ffw::logger::verbose() {
    type = 0;
    os << getTime() + "[VERBOSE] ";
    return os;
}

///=============================================================================
std::ostringstream& ffw::logger::debug() {
    type = 1;
    os << getTime() + "[DEBUG]   ";
    return os;
}

///=============================================================================
std::ostringstream& ffw::logger::notice() {
    type = 2;
    os << getTime() + "[NOTICE]  ";
    return os;
}

///=============================================================================
std::ostringstream& ffw::logger::info() {
    type = 3;
    os << getTime() + "[INFO]    ";
    return os;
}

///=============================================================================
std::ostringstream& ffw::logger::warning() {
    type = 4;
    os << getTime() + "[WARNING] ";
    return os;
}

///=============================================================================
std::ostringstream& ffw::logger::error() {
    type = 5;
    os << getTime() + "[ERROR]   ";
    return os;
}

///=============================================================================
void ffw::logger::clearLog(){
    std::ofstream file;
    file.open("log.txt", std::ofstream::out | std::ofstream::trunc);
    file << "";
    file.close();
}

///=============================================================================
void ffw::logger::setVerbosity(int Level){
    verbosity = Level;
    if(verbosity > 5)verbosity = 5;
}

///=============================================================================
ffw::logger::~logger() {
    os << "\n";

    if(consoleOut){
        if(!consoleInit){
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            consoleInit = true;
        }
        if(type >= verbosity){
            if     (type == 0)  	SetConsoleTextAttribute(hConsole, 8);
            else if(type == 1) 		SetConsoleTextAttribute(hConsole, 7);
            else if(type == 2) 		SetConsoleTextAttribute(hConsole, 15);
            else if(type == 3)		SetConsoleTextAttribute(hConsole, 11);
            else if(type == 4)   	SetConsoleTextAttribute(hConsole, 14);
            else if(type == 5) 		SetConsoleTextAttribute(hConsole, 12);
            std::cout << os.str();
            SetConsoleTextAttribute(hConsole, 7);
        }
    }

    if(initialized){
        addLine();
    }
	os.clear();
}

///=============================================================================
void ffw::logger::addLine() {
    std::ofstream file;
    file.open(path, std::ofstream::out | std::ofstream::app);
    file << os.str();
    file.close();
}

///=============================================================================
void ffw::logger::setConsoleOutput(bool Enabled){
    consoleOut = Enabled;
}

///=============================================================================
std::string ffw::logger::getTime() {
    time_t rawtime;
    struct tm * timeInfo;

    time (&rawtime);
    timeInfo = localtime(&rawtime);
    int timeDay = timeInfo->tm_mday;
    int timeMonth = timeInfo->tm_mon +1;
    int timeYear = timeInfo->tm_year +1900;
    int timeHours = timeInfo->tm_hour;
    int timeMinutes = timeInfo->tm_min;
    int timeSeconds = timeInfo->tm_sec;

    std::ostringstream timeMessage;

    if(timeDay < 10)        timeMessage << "0" << timeDay << "-";
    else                    timeMessage << timeDay << "-";

    if(timeMonth < 10)      timeMessage << "0" << timeMonth << "-";
    else                    timeMessage << timeMonth << "-";

                            timeMessage << timeYear << " [";

    if(timeHours < 10)      timeMessage << "0" << timeHours << ":";
    else                    timeMessage << timeHours << ":";

    if(timeMinutes < 10)    timeMessage << "0" << timeMinutes << ":";
    else                    timeMessage << timeMinutes << ":";

    if(timeSeconds < 10)    timeMessage << "0" << timeSeconds << "] ";
    else                    timeMessage << timeSeconds << "] ";

    return timeMessage.str();
}
///=============================================================================
