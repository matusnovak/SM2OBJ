/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_MATH
#define FFW_MATH

#include <GL/glfw3.h>
#include <string>
#include <math.h>
#include "constants.h"
#include <initializer_list>
#include <stdint.h>

/*!
	@defgroup Math
	@brief Functions and structures for mathematics
*/

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
#include "quaternion.h"
#include "color.h"
#include "var.h"
#include "range.h"
#include "memPool.h"

/*!
	@ingroup Math
*/
namespace ffw {
    extern uint32_t randX;
    extern uint32_t randY;
    extern uint32_t randZ;
    extern uint32_t randW;
    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec2<float> vec2f;
    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec2<int> vec2i;
    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec2<double> vec2d;
    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec3<float> vec3f;
    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec3<int> vec3i;
    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec3<double> vec3d;
    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec4<float> vec4f;
    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec4<int> vec4i;
    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec4<double> vec4d;
};

#include "baseFunctions.h"
#include "typesOperators.h"

#endif