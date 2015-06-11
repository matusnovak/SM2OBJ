/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "timer.h"

///=============================================================================
ffw::timer::timer(){
    /*beginTime.QuadPart = 0;
    endTime.QuadPart = 0;
    QueryPerformanceFrequency(&frequency);*/
}

///=============================================================================
void ffw::timer::begin(){
    /*QueryPerformanceCounter(&beginTime);*/
    t1 = std::chrono::steady_clock::now();
}

///=============================================================================
void ffw::timer::end(){
    /*QueryPerformanceCounter(&endTime);*/
    t2 = std::chrono::steady_clock::now();
}

///=============================================================================
double ffw::timer::getTime(){
    /*LARGE_INTEGER time;
    time.QuadPart = endTime.QuadPart - beginTime.QuadPart;
    return ((double)time.QuadPart /(double)frequency.QuadPart);*/
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    return time_span.count();
}
///=============================================================================
uint64_t ffw::timer::getTimeMilli(){
    //chrono::duration <double, milli> (diff).count()
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
}

///=============================================================================
uint64_t ffw::timer::getTimeMicro(){
    //chrono::duration <double, milli> (diff).count()
    return std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
}

///=============================================================================
