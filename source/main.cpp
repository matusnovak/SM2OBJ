/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "window.h"

static sm2obj::window mainWindow;

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow){
    ffw::logger::initLogger(ffw::getExecutablePath());
    return mainWindow.create(hThisInstance, nCmdShow);
}
