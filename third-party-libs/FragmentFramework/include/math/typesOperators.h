/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TYPE_OPERATORS
#define FFW_TYPE_OPERATORS

/*!
	@ingroup Math
*/
namespace ffw{
    /*!
		@memberof ffw
		@ingroup Math
		@inline
	*/
    template <class T> std::ostream& operator << (std::ostream& os, const vec2<T>& V);
    /*!
		@memberof ffw
		@ingroup Math
		@inline
	*/
    template <class T> std::ostream& operator << (std::ostream& os, const vec3<T>& V);
    /*!
		@memberof ffw
		@ingroup Math
		@inline
	*/
    template <class T> std::ostream& operator << (std::ostream& os, const vec4<T>& V);
    /*!
		@memberof ffw
		@ingroup Math
		@inline
	*/
	std::ostream& operator << (std::ostream& os, const quaternion& Q);
    /*!
		@memberof ffw
		@ingroup Math
		@inline
	*/
	template <class T> vec4<T> operator * (mat4& M, const ffw::vec4<T> &V);
};

#include "typesOperators.inl"

#endif
