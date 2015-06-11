/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET_BUTTON_ICON
#define FFW_UI_WIDGET_BUTTON_ICON

#include "widget.h"

/*!
    @ingroup User-Interface
*/
namespace ffw {
     /*!
        @memberof ffw
        @ingroup User-Interface
        @inherit uiWidget
        @sa uiWidget
    */
	class FFW_API uiWidgetButtonIcon : public uiWidget {
    public:
        /*!
            @memberof uiWidgetButtonIcon
            @ingroup User-Interface
        */
        uiWidgetButtonIcon(const std::string& ID, float PosX, float PosY, float Width, float Height, const std::string& IconName, int Padding);
        uiWidgetButtonIcon(const std::string& ID, float PosX, float PosY, float Width, float Height, const ffw::vec4f& IconTile, int Padding);
        ~uiWidgetButtonIcon();

        void update() override;
        void hover(bool Hover) override;
        void mousePressed(int Button, int PosX, int PosY) override;
        void mouseReleased(int Button) override;

    private:
        float* bufferNormal;
        float* bufferHover;
        float* bufferActive;
        std::string iconName;
        ffw::vec4f iconTile;
        int padding;
    };
};

#endif





