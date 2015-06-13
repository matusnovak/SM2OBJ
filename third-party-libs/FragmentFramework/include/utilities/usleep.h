/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_USLEEP
#define FFW_USLEEP

#include "../dll.h"
#include <stdint.h>

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	void FFW_API usleep(int64_t Micros);
};
#endif