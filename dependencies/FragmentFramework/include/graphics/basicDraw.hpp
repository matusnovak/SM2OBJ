/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_BASIC_DRAW
#define FFW_BASIC_DRAW

#include "../config.h"
#include "../render/renderContext.hpp"
#include "texture2D.hpp"
#include "font.hpp"

/*!
    @ingroup Graphics
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Graphics
    */
    void FFW_API drawRectangle(const ffw::renderContext* Context, int PosX, int PosY, int Width, int Height);
    /*!
        @memberof ffw
        @ingroup Graphics
    */
    void FFW_API drawTriangle(const ffw::renderContext* Context, int P0x, int P0y, int P1x, int P1y, int P2x, int P2y);
    /*!
        @memberof ffw
        @ingroup Graphics
    */
    void FFW_API drawTexture(const ffw::renderContext* Context, int PosX, int PosY, int Width, int Height, const ffw::texture2D* Texture);
    /*!
        @memberof ffw
        @ingroup Graphics
    */
    void FFW_API drawTexture(const ffw::renderContext* Context, int PosX, int PosY, int Width, int Height, const ffw::texture2D* Texture, bool MirrorX, bool MirrorY);
    /*!
        @memberof ffw
        @ingroup Graphics
    */
    void FFW_API drawTextureSubsection(const ffw::renderContext* Context, int PosX, int PosY, int Width, int Height, const ffw::texture2D* Texture, float SubX, float SubY, float SubW, float SubH);
    /*!
        @memberof ffw
        @ingroup Graphics
    */
    void FFW_API drawTextureSubsection(const ffw::renderContext* Context, int PosX, int PosY, int Width, int Height, const ffw::texture2D* Texture, float SubX, float SubY, float SubW, float SubH, bool MirrorX, bool MirrorY);
    /*!
        @memberof ffw
        @ingroup Graphics
    */
    void FFW_API drawArc(const ffw::renderContext* Context, int PosX, int PosY, int InnerRadius, int OuterRadius, int StartAngle, int EndAngle, int Steps);
    /*!
        @memberof ffw
        @ingroup Graphics
    */
    void FFW_API drawCircle(const ffw::renderContext* Context, int PosX, int PosY, int Radius, int Steps);
	/*!
        @memberof ffw
        @ingroup Graphics
    */
    void FFW_API drawLine(const ffw::renderContext* Context, int StartX, int StartY, int EndX, int EndY);
	/*!
        @memberof ffw
        @ingroup Graphics
    */
    void FFW_API drawLineThick(const ffw::renderContext* Context, int StartX, int StartY, int EndX, int EndY, int Thickness);
	/*!
        @memberof ffw
        @ingroup Graphics
    */
	void FFW_API drawString(const ffw::renderContext* Context, int PosX, int PosY, const font* Font, const std::string& Str);
	/*!
        @memberof ffw
        @ingroup Graphics
    */
	void FFW_API drawString(const ffw::renderContext* Context, int PosX, int PosY, const font* Font, const std::wstring& Str);
	/*!
        @memberof ffw
        @ingroup Graphics
    */
	void FFW_API drawBezier(const ffw::renderContext* Context, int StartX, int StartY, int CP0X, int CP0Y, int CP1X, int CP1Y, int EndX, int EndY, int Steps);
	/*!
        @memberof ffw
        @ingroup Graphics
    */
	void FFW_API drawBezierThick(const ffw::renderContext* Context, int StartX, int StartY, int CP0X, int CP0Y, int CP1X, int CP1Y, int EndX, int EndY, int Thickness, int Steps);
	/*!
        @memberof ffw
        @ingroup Graphics
    */
	void FFW_API enableBlendFunc(const ffw::renderContext* Context, unsigned int source, unsigned int destination);
	/*!
        @memberof ffw
        @ingroup Graphics
    */
	void FFW_API enableBlendFuncSeparate(const ffw::renderContext* Context, unsigned int srcRgb, unsigned int destRgb, unsigned int srcAlpha, unsigned int destAlpha);
	/*!
        @memberof ffw
        @ingroup Graphics
    */
	void FFW_API disableBlendFunc(const ffw::renderContext* Context);
	/*!
        @memberof ffw
        @ingroup Graphics
    */
	void FFW_API activeTexture(const ffw::renderContext* Context, unsigned int Texture);
	/*!
        @memberof ffw
        @ingroup Graphics
    */
	void FFW_API setDrawBuffers(const ffw::renderContext* Context, int Num, const unsigned int* Buffs);
};
#endif
