/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_TILE_DATA
#define FFW_UI_TILE_DATA

#include <iostream>

#include "../math/math.h"

namespace tileData {
    extern ffw::vec2f textureSize;

    extern int boxDefaultTiles[9];
    extern ffw::vec4f boxDefaultTop;
    extern ffw::vec4f boxDefaultBottom;
    extern ffw::vec4f boxDefaultLeft;
    extern ffw::vec4f boxDefaultRight;
    extern ffw::vec4f boxDefaultMiddle;
    extern ffw::vec4f boxDefaultTopLeft;
    extern ffw::vec4f boxDefaultTopRight;
    extern ffw::vec4f boxDefaultBottomLeft;
    extern ffw::vec4f boxDefaultBottomRight;

    extern int boxListTiles[9];
    extern ffw::vec4f boxListTop;
    extern ffw::vec4f boxListBottom;
    extern ffw::vec4f boxListLeft;
    extern ffw::vec4f boxListRight;
    extern ffw::vec4f boxListMiddle;
    extern ffw::vec4f boxListTopLeft;
    extern ffw::vec4f boxListTopRight;
    extern ffw::vec4f boxListBottomLeft;
    extern ffw::vec4f boxListBottomRight;
    extern int boxListSelectedTile;
    extern ffw::vec4f boxListSelected;

    extern int buttonNormalTiles[3];
    extern ffw::vec4f buttonNormalLeft;
    extern ffw::vec4f buttonNormalMiddle;
    extern ffw::vec4f buttonNormalRight;

    extern int buttonHoverTiles[3];
    extern ffw::vec4f buttonHoverLeft;
    extern ffw::vec4f buttonHoverMiddle;
    extern ffw::vec4f buttonHoverRight;

    extern int buttonActiveTiles[3];
    extern ffw::vec4f buttonActiveLeft;
    extern ffw::vec4f buttonActiveMiddle;
    extern ffw::vec4f buttonActiveRight;

    extern int lineHorizontalTiles[3];
    extern ffw::vec4f lineHorizontalLeft;
    extern ffw::vec4f lineHorizontalMiddle;
    extern ffw::vec4f lineHorizontalRight;

    extern int lineVerticalTiles[3];
    extern ffw::vec4f lineVerticalLeft;
    extern ffw::vec4f lineVerticalMiddle;
    extern ffw::vec4f lineVerticalRight;

    extern int iconTiles[3];
    extern ffw::vec4f iconNormal;
    extern ffw::vec4f iconHover;
    extern ffw::vec4f iconActive;

    extern int switchHorizontalTiles[2];
    extern ffw::vec4f switchHorizontalOff;
    extern ffw::vec4f switchHorizontalOn;

    extern int switchVerticalTiles[2];
    extern ffw::vec4f switchVerticalOff;
    extern ffw::vec4f switchVerticalOn;

    extern int checkboxOffTiles[3];
    extern ffw::vec4f checkboxOffNormal;
    extern ffw::vec4f checkboxOffHover;
    extern ffw::vec4f checkboxOffActive;

    extern int checkboxOnTiles[3];
    extern ffw::vec4f checkboxOnNormal;
    extern ffw::vec4f checkboxOnHover;
    extern ffw::vec4f checkboxOnActive;

    extern int progressbarFrontTiles[3];
    extern ffw::vec4f progressbarFrontLeft;
    extern ffw::vec4f progressbarFrontMiddle;
    extern ffw::vec4f progressbarFrontRight;

    extern int progressbarBackTiles[3];
    extern ffw::vec4f progressbarBackLeft;
    extern ffw::vec4f progressbarBackMiddle;
    extern ffw::vec4f progressbarBackRight;

    extern int sliderHorizontalFrontTiles[3];
    extern ffw::vec4f sliderHorizontalFrontLeft;
    extern ffw::vec4f sliderHorizontalFrontMiddle;
    extern ffw::vec4f sliderHorizontalFrontRight;

    extern int sliderHorizontalBackTiles[3];
    extern ffw::vec4f sliderHorizontalBackLeft;
    extern ffw::vec4f sliderHorizontalBackMiddle;
    extern ffw::vec4f sliderHorizontalBackRight;

    extern int sliderVerticalFrontTiles[3];
    extern ffw::vec4f sliderVerticalFrontLeft;
    extern ffw::vec4f sliderVerticalFrontMiddle;
    extern ffw::vec4f sliderVerticalFrontRight;

    extern int sliderVerticalBackTiles[3];
    extern ffw::vec4f sliderVerticalBackLeft;
    extern ffw::vec4f sliderVerticalBackMiddle;
    extern ffw::vec4f sliderVerticalBackRight;

    extern int sliderKnobTiles[3];
    extern ffw::vec4f sliderKnobNormal;
    extern ffw::vec4f sliderKnobHover;
    extern ffw::vec4f sliderKnobActive;

    extern int scrollerHorizontalTiles[3];
    extern ffw::vec4f scrollerHorizontalLeft;
    extern ffw::vec4f scrollerHorizontalMiddle;
    extern ffw::vec4f scrollerHorizontalRight;

    extern int scrollerVerticalTiles[3];
    extern ffw::vec4f scrollerVerticalLeft;
    extern ffw::vec4f scrollerVerticalMiddle;
    extern ffw::vec4f scrollerVerticalRight;

    extern int scrollerHorizontalKnobTiles[3];
    extern ffw::vec4f scrollerHorizontalKnobNormal;
    extern ffw::vec4f scrollerHorizontalKnobHover;
    extern ffw::vec4f scrollerHorizontalKnobActive;

    extern int scrollerVerticalKnobTiles[3];
    extern ffw::vec4f scrollerVerticalKnobNormal;
    extern ffw::vec4f scrollerVerticalKnobHover;
    extern ffw::vec4f scrollerVerticalKnobActive;

    extern int textInputNormalTiles[3];
    extern ffw::vec4f textInputNormalLeft;
    extern ffw::vec4f textInputNormalMiddle;
    extern ffw::vec4f textInputNormalRight;

    extern int textInputFocusTiles[3];
    extern ffw::vec4f textInputFocusLeft;
    extern ffw::vec4f textInputFocusMiddle;
    extern ffw::vec4f textInputFocusRight;

    extern ffw::vec4f iconArrowDown;
    extern ffw::vec4f iconArrowLeft;
    extern ffw::vec4f iconArrowRight;
    extern ffw::vec4f iconArrowUp;
    extern ffw::vec4f iconArrows;
    extern ffw::vec4f iconPlus;
    extern ffw::vec4f iconMinus;
    extern ffw::vec4f iconTriangle;
    extern ffw::vec4f iconCheck;
    extern ffw::vec4f iconCross;
    extern ffw::vec4f iconCircle;
};

#endif


