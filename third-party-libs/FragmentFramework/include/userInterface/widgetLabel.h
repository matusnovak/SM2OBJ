/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET_LABEL
#define FFW_UI_WIDGET_LABEL

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
	class FFW_API uiWidgetLabel : public uiWidget {
    public:
        /*!
            @memberof uiWidgetLabel
            @ingroup User-Interface
        */
        uiWidgetLabel(float PosX, float PosY, const std::wstring& Text, int Aligment, const ffw::color& Color);
        uiWidgetLabel(float PosX, float PosY, const std::wstring& Text, int Aligment, const ffw::color& Color, int Wrap);
        ~uiWidgetLabel();

        void update() override;

    private:
        std::wstring text;
        int aligment;
        int wrap;
        ffw::color textColor;
    };
};

#endif





