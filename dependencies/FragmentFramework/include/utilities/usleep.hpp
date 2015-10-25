/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_USLEEP
#define FFW_USLEEP

#include "../common.h"

/*!
 * @ingroup Utilities
 */
namespace ffw{
    /*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Sleeps in micro seconds
     */
	void FFW_API usleep(unsigned long long Micros);
};
#endif
