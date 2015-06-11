/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "mutex.h"

// Compile for Visual Studio
#ifdef _MSC_VER
#include <system_error>
///=============================================================================
ffw::mutex::mutex(){
	// std::mutex uses it's own constructor
}

///=============================================================================
ffw::mutex::~mutex(){
	// std::mutex uses it's own destructor
}

///=============================================================================
bool ffw::mutex::lock(){
	try {
		mut.lock();
	} catch (const std::system_error& e) {
		return false;
	}
	return true;
}

///=============================================================================
bool ffw::mutex::tryLock(){
	return mut.try_lock();
}

///=============================================================================
bool ffw::mutex::unlock(){
	mut.unlock();
	return true;
}
#endif

// Compile for MinGW
#ifdef __MINGW32__
///=============================================================================
ffw::mutex::mutex(){
    pthread_mutex_init(&mut, NULL);
}

///=============================================================================
ffw::mutex::~mutex(){
    pthread_mutex_destroy(&mut);
}

///=============================================================================
bool ffw::mutex::lock(){
    return (pthread_mutex_lock(&mut) == 0);
}

///=============================================================================
bool ffw::mutex::tryLock(){
    return (pthread_mutex_trylock(&mut) == 0);
}

///=============================================================================
bool ffw::mutex::unlock(){
    return (pthread_mutex_unlock(&mut) == 0);
}
#endif
