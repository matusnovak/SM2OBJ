/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TIMER
#define FFW_TIMER

#include "../common.h"

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	class FFW_API timer{
    public:
        /*!
            @memberof timer
            @ingroup Utilities
        */
        timer();
        /*!
            @memberof timer
            @ingroup Utilities
        */
        void begin();
        /*!
            @memberof timer
            @ingroup Utilities
        */
        void end();
        /*!
            @memberof timer
            @ingroup Utilities
        */
        double getTime();
        /*!
            @memberof timer
            @ingroup Utilities
        */
        unsigned long long getTimeMilli();
        /*!
            @memberof timer
            @ingroup Utilities
        */
        unsigned long long getTimeMicro();

    private:
        std::chrono::steady_clock::time_point t1;
        std::chrono::steady_clock::time_point t2;
    };
};
#endif
