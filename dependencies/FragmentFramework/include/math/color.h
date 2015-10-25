/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_COLOR
#define FFW_COLOR

/*!
 * @ingroup Math
 */
namespace ffw {
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 */
    struct color {
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @brief Red
		 */
        float r;
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @brief Green
		 */
        float g;
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @brief Blue
		 */
        float b;
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @brief Alpha
		 */
        float a;
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 * @brief Constructor
		 */
        color(float R, float G, float B, float A);
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 * @brief Constructor, alpha is initialized to 1.0
		 */
        color(float R, float G, float B);
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 * @brief Constructor, all channels are initialized with same value.
		 * Alpha is set to 1.0
		 */
        color(float Grey);
		/*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 * @brief Default constructor, initializes all channels to 1.0 (white)
		 */
        color();
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 * @brief Sets the color.
		 */
        void set(float R, float G, float B, float A);
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 * @brief Sets the color, alpha is set to 1.0
		 */
        void set(float R, float G, float B);
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 * @brief Sets the channels to same value, alpha is set to 1.0
		 */
        void set(float Grey);
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 */
        color& operator =  (const color &Col);
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 */
        color  operator +  (const color &Col) const;
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 */
        color& operator += (const color &Col);
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 */
        color  operator -  (const color &Col) const;
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 */
        color& operator -= (const color &Col);
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 * @brief Clamps color to 0.0 - 1.0 range
		 */
        color& clamp();
        /*!
		 * @memberof color
		 * @ingroup Math
		 * @inline
		 * @brief Normalizes color
		 */
        color& normalize();
    };
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 * @brief Creates a color from HEX value
	 * @details
	 * For example: `rgb(0x00FFCC)` returns a color composed of 100% green and 80% blue.
	 * @sa rgba
	 */
	color rgb(unsigned long Hex);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 * @brief Creates a color from HEX value with alpha
	 * @details
	 * For example: `rgba(0x00FFCC77)` returns a color composed of 100% green, 80% blue, and 50% alpha.
	 * @sa rgb
	 */
	color rgba(unsigned long Hex);
	/*
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 * @brief Creates a color from HSV values in float format
	 * @param Hue - values between 0.0 and 360.0, however can be outside of the range.
	 * @param Saturation,Saturation - must be between 0.0 and 1.0
	 * @param Alpha - must be between 0.0 and 1.0. By default is set to 1.0
	 * @sa hsv
	 */
	//color FFW_API hsvf(float Hue, float Saturation, float Value, float Alpha = 1.0f);
	/*
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 * @brief Creates a color from HSL values in float format
	 * @param Hue - values between 0.0 and 360.0, however can be outside of the range.
	 * @param Saturation,Luminance - must be between 0.0 and 1.0
	 * @param Alpha - must be between 0.0 and 1.0. By default is set to 1.0
	 * @sa hsl
	 */
	//color FFW_API hslf(float Hue, float Saturation, float Luminance, float Alpha = 1.0f);
	/*
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 * @brief Creates a color from HSL values in byte format
	 * @param Hue - values between 0 and 255 where 255 is 360 degrees.
	 * @param Saturation,Saturation - must be between 0 and 255
	 * @param Alpha - must be between 0 and 255. By default is set to 255
	 * @sa hsvf
	 */
	//color FFW_API hsv(unsigned char Hue, unsigned char Saturation, unsigned char Value, unsigned char Alpha = 255);
	/*
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 * @brief Creates a color from HSL values in byte format
	 * @param Hue - values between 0 and 255 where 255 is 360 degrees.
	 * @param Saturation,Luminance - must be between 0 and 255
	 * @param Alpha - must be between 0 and 255. By default is set to 255
	 * @sa hslf
	 */
	//color FFW_API hsl(unsigned char Hue, unsigned char Saturation, unsigned char Luminance, unsigned char Alpha = 255);
};

#include "color.inl"

#endif
