/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_COLOR
#define FFW_COLOR

/*!
	@ingroup Math
*/
namespace ffw {
    /*!
		@memberof ffw
		@ingroup Math
	*/
    struct color {
        /*!
			@memberof color
			@ingroup Math
		*/
        float r;
        /*!
			@memberof color
			@ingroup Math
		*/
        float g;
        /*!
			@memberof color
			@ingroup Math
		*/
        float b;
        /*!
			@memberof color
			@ingroup Math
		*/
        float a;
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        color();
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        color(float R, float G, float B, float A);
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        color(float R, float G, float B);
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        color(float Grey);
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        void set(float R, float G, float B, float A);
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        void set(float R, float G, float B);
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        void set(float Grey);
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        void setUbyte(unsigned char R, unsigned char G, unsigned char B, unsigned char A);
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        void setUbyte(unsigned char R, unsigned char G, unsigned char B);
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        void setUbyte(unsigned char Grey);
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        color& operator =  (const color &Col);
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        color  operator +  (const color &Col) const;
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        color& operator += (const color &Col);
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        color  operator -  (const color &Col) const;
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        color& operator -= (const color &Col);
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        color& clamp();
        /*!
			@memberof color
			@ingroup Math
			@inline
		*/
        color& normalize();
    };
};
#endif

#include "color.inl"
