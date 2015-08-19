/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_THREAD
#define FFW_THREAD

#include "../config.h"

// Compile for Visual Studio
#if defined(_USING_MSVC)
#include <thread>
#elif defined(_USING_MINGW)
#include <pthread.h>
#endif
#include <functional>

namespace ffw{
	class FFW_API thread{
	public:
		thread();
		virtual ~thread();
		bool start(void* DataPtr);
		bool join();
		bool join(void** ReturnValue);
		void bindFunction(void* (*Func)(void*));
		void bindFunction(std::function<void*(void*)> Func);

	private:
		static void *internalThreadFunc(void* This);
		void* (*threadFunc)(void*);
		std::function<void*(void*)> threadFuncMem;
		#if defined(_USING_MSVC)
		std::thread* sthread;
		#elif defined(_USING_MINGW)
        pthread_t pthread;
		#endif
        void* dataPtr;
	};
};

#endif
