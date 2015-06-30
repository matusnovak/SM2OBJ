/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#define SM2OBJ_CHUNK_SIZE 16*16*16
#define SM2OBJ_CHUNK_MAX_VERTICES 8
#define SM2OBJ_CHUNK_MAX_INDICES 8

#define TERMINATE(X)\
sm2obj::config::exportExitFunc(X); return X;

#define LOG_DEBUG(X)\
sm2obj::config::exportLogDebugFunc(X);

#define LOG_ERROR(X)\
sm2obj::config::exportLogErrorFunc(X);

#define LOG_INFO(X)\
sm2obj::config::exportLogInfoFunc(X);

#define LOG_WARNING(X)\
sm2obj::config::exportLogWarningFunc(X);

#define PROGRESS(X, Y)\
sm2obj::config::exportProgressFunc(X, Y);
