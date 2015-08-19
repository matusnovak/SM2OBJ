/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_MUTEX
#define FFW_MUTEX

#include "../config.h"

// Compile for Visual Studio
#if defined(_USING_MSVC)
#include <mutex>
#elif defined(_USING_MINGW)
#include <pthread.h>
#endif

namespace ffw{
	class FFW_API mutex {
	public:
		mutex();
		~mutex();
		bool lock();
		bool tryLock();
		bool unlock();

	private:
		#if defined(_USING_MSVC)
		std::mutex mut;
		#elif defined(_USING_MINGW)
		pthread_mutex_t mut;
		#endif
	};
};

#endif
