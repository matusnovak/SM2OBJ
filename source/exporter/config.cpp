/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "config.h"

sm2obj::chunkBufferStruct sm2obj::chunkBufferA;
sm2obj::chunkBufferStruct sm2obj::chunkBufferB;

std::string sm2obj::config::imageExtension;
sm2obj::config::imageSaver sm2obj::config::imageSaverFunc;
sm2obj::config::exportLogError sm2obj::config::exportLogErrorFunc;
sm2obj::config::exportLogInfo sm2obj::config::exportLogInfoFunc;
sm2obj::config::exportLogDebug sm2obj::config::exportLogDebugFunc;
sm2obj::config::exportProgress sm2obj::config::exportProgressFunc;
sm2obj::config::exportLogWarning sm2obj::config::exportLogWarningFunc;
sm2obj::config::exportExit sm2obj::config::exportExitFunc;

