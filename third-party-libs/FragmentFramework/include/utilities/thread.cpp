/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "thread.h"

// Compile for Visual Studio
#ifdef _MSC_VER
#include <system_error>
///=============================================================================
ffw::thread::thread(){
	threadFunc = NULL;
	dataPtr = NULL;
	sthread = NULL;
}

///=============================================================================
ffw::thread::~thread(){
	if (sthread != NULL){
		delete sthread;
		sthread = NULL;
	}
}

///=============================================================================
bool ffw::thread::start(void* DataPtr){
	if (sthread != NULL){
		delete sthread;
		sthread = NULL;
	}

	dataPtr = DataPtr;
	if(threadFunc != NULL){
		try {
			sthread = new std::thread(threadFunc, dataPtr);
		}
		catch (const std::system_error& e) {
			return false;
		}
	} else if(threadFuncMem != nullptr){
		try {
			sthread = new std::thread(internalThreadFunc, this);
		}
		catch (const std::system_error& e) {
			return false;
		}
	}

	return false;
}

///=============================================================================
bool ffw::thread::join(){
	if(sthread == NULL)return false;
	try {
		sthread->join();
	} catch (const std::system_error& e) {
		return false;
	}
	return true;
}

///=============================================================================
bool ffw::thread::join(void** ReturnValue){
	if (sthread == NULL)return false;
	try {
		sthread->join();
		// Return value is not supported by std::thread :(
		// *ReturnValue = ???;
	} catch (const std::system_error& e) {
		return false;
	}
	return true;
}

///=============================================================================
void* ffw::thread::internalThreadFunc(void* This){
	return static_cast<thread*>(This)->threadFuncMem(static_cast<thread*>(This)->dataPtr);
}

///=============================================================================
void ffw::thread::bindFunction(void* (*Func)(void*)){
	threadFunc = Func;
}

///=============================================================================
void ffw::thread::bindFunction(std::function<void*(void*)> Func){
	threadFuncMem = Func;
}
#endif

// Compile for MinGW
#ifdef __MINGW32__
///=============================================================================
ffw::thread::thread(){
    threadFunc = NULL;
    dataPtr = NULL;
    //threadFuncMem = nullptr;
}

///=============================================================================
ffw::thread::~thread(){
}

///=============================================================================
bool ffw::thread::start(void* DataPtr){
    dataPtr = DataPtr;
    if(threadFunc != NULL){
        return (pthread_create(&pthread, NULL, threadFunc, dataPtr) == 0);

    } else if(threadFuncMem != nullptr){
        return (pthread_create(&pthread, NULL, internalThreadFunc, this) == 0);
    }

    return false;
}

///=============================================================================
bool ffw::thread::join(){
    return (pthread_join(pthread, NULL) == 0);
}

///=============================================================================
bool ffw::thread::join(void** ReturnValue){
    return (pthread_join(pthread, ReturnValue) == 0);
}

///=============================================================================
void* ffw::thread::internalThreadFunc(void* This){
    //((thread *)This)->threadFuncMem(((thread *)This)->dataPtr);
    return static_cast<thread*>(This)->threadFuncMem(static_cast<thread*>(This)->dataPtr);
}

///=============================================================================
void ffw::thread::bindFunction(void* (*Func)(void*)){
    threadFunc = Func;
}

///=============================================================================
void ffw::thread::bindFunction(std::function<void*(void*)> Func){
    threadFuncMem = Func;
}
#endif
