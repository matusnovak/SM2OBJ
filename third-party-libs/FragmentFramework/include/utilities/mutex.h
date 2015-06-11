/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_MUTEX
#define FFW_MUTEX

#include "../dll.h"

// Compile for Visual Studio
#ifdef _MSC_VER
#include <mutex>

namespace ffw{
	class FFW_API mutex {
	public:
		mutex();
		~mutex();
		bool lock();
		bool tryLock();
		bool unlock();

	private:
		std::mutex mut;
	};
};

#endif

// Compile for MinGW
#ifdef __MINGW32__
#include <pthread.h>

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	class FFW_API mutex {
    public:
        mutex();
        ~mutex();
        /*!
            @memberof mutex
            @ingroup Utilities
        */
        bool lock();
        /*!
            @memberof mutex
            @ingroup Utilities
        */
        bool tryLock();
        /*!
            @memberof mutex
            @ingroup Utilities
        */
        bool unlock();

    private:
        pthread_mutex_t mut;
    };
};
#endif

#endif
