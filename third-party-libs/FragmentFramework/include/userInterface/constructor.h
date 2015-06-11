/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_USER_INTERFACE_CONSTRUCTOR
#define FFW_USER_INTERFACE_CONSTRUCTOR

#include <iostream>
#include "../dll.h"
#include "../math/math.h"
#include "../graphics/graphicsTrueType.h"
#include "tileData.h"

namespace ffw {
    namespace uiConstruct {
		void FFW_API box(float* Ptr, const ffw::vec2f& Pos, const ffw::vec2f& Size, const ffw::vec4f& Top, const ffw::vec4f& Bottom, const ffw::vec4f& Left, const ffw::vec4f& Right, const ffw::vec4f& Middle, const ffw::vec4f& TopLeft, const ffw::vec4f& TopRight, const ffw::vec4f& BottomLeft, const ffw::vec4f& BottomRight, int* TileData);
		void FFW_API boxHorizontal(float* Ptr, const ffw::vec2f& Pos, const ffw::vec2f& Size, const ffw::vec4f& TileLeft, const ffw::vec4f& TileMiddle, const ffw::vec4f& TileRight, int* TileData);
		void FFW_API boxVertical(float* Ptr, const ffw::vec2f& Pos, const ffw::vec2f& Size, const ffw::vec4f& TileBottom, const ffw::vec4f& TileMiddle, const ffw::vec4f& TileTop, int* TileData);
		void FFW_API boxSingle(float* Ptr, const ffw::vec2f& Pos, const ffw::vec2f& Size, const ffw::vec4f& Tile, float TileData);
		void FFW_API boxSingle(float* Ptr, const ffw::vec2f& Pos, const ffw::vec2f& Size, const ffw::vec4f& Tile, float TileData, const ffw::color& Color);
		void FFW_API boxSingle(float* Ptr, const ffw::vec2f& Pos, const ffw::vec2f& Size, const ffw::vec4f& Tile, float TileData, const ffw::color& Color, const ffw::vec2f& AtlasSize);
		void FFW_API text(float* Ptr, const ffw::vec2f& Pos, const std::wstring& Str, const ffw::color& Color, ffw::trueType* Font);
		void FFW_API text(float* Ptr, const ffw::vec2f& Pos, const std::wstring& Str, const ffw::color& Color, ffw::trueType* Font, size_t Start, size_t End);
    };
};

#endif



