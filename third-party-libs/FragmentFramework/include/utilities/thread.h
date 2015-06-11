/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_THREAD
#define FFW_THREAD

#include "../dll.h"

// Compile for Visual Studio
#ifdef _MSC_VER
#include <thread>
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
		std::thread* sthread;
		void* dataPtr;
	};
};

#endif

// Compile for MinGW
#ifdef __MINGW32__
#include <pthread.h>
#include <functional>

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	class FFW_API thread{
    public:
        thread();
        virtual ~thread();
        /*!
            @memberof thread
            @ingroup Utilities
        */
        bool start(void* DataPtr);
        /*!
            @memberof thread
            @ingroup Utilities
        */
        bool join();
        /*!
            @memberof thread
            @ingroup Utilities
        */
        bool join(void** ReturnValue);
        /*!
            @memberof thread
            @ingroup Utilities
        */
        void bindFunction(void* (*Func)(void*));
        /*!
            @memberof thread
            @ingroup Utilities
        */
        void bindFunction(std::function<void*(void*)> Func);

    private:
        static void *internalThreadFunc(void* This);
        void* (*threadFunc)(void*);
        std::function<void*(void*)> threadFuncMem;
        pthread_t pthread;
        void* dataPtr;
    };
};
#endif

#endif
