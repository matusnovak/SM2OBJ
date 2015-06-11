/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "usleep.h"
#include <windows.h>

///=============================================================================
void ffw::usleep(int64_t Micros) {
    HANDLE timer;
    LARGE_INTEGER delayInterval;

    // Convert to 100 nanosecond interval, negative value indicates relative time
    delayInterval.QuadPart = -(10*Micros);

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &delayInterval, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}
///=============================================================================
