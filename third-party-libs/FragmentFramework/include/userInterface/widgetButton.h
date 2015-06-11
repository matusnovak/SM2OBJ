/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET_BUTTON
#define FFW_UI_WIDGET_BUTTON

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
	class FFW_API uiWidgetButton : public uiWidget {
    public:
        /*!
            @memberof uiWidgetButton
            @ingroup User-Interface
        */
        uiWidgetButton(const std::string& ID, float PosX, float PosY, float Width, float Height, const std::wstring& Text);
        ~uiWidgetButton();

        void update() override;
        void hover(bool Hover) override;
        void mousePressed(int Button, int PosX, int PosY) override;
        void mouseReleased(int Button) override;

    private:
        float* bufferNormal;
        float* bufferHover;
        float* bufferActive;
        int textSize;
        std::wstring text;
    };
};

#endif




