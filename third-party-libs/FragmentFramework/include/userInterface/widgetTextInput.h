/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET_TEXT_INPUT
#define FFW_UI_WIDGET_TEXT_INPUT

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
	class FFW_API uiWidgetTextInput : public uiWidget {
    public:
        /*!
            @memberof uiWidgetTextInput
            @ingroup User-Interface
        */
        uiWidgetTextInput(const std::string& ID, float PosX, float PosY, float Width, const std::wstring& Text, int Length = 100);
        ~uiWidgetTextInput();

        void update() override;
        void focus(bool Focus) override;
        void keyPressed(int Key, int Mode) override;
        void textInput(int C) override;
        /*!
            @memberof uiWidgetTextInput
            @ingroup User-Interface
        */
        void setValue(const std::string& Str);
        /*!
            @memberof uiWidgetTextInput
            @ingroup User-Interface
        */
        void setValue(const std::wstring& Str);
        /*!
            @memberof uiWidgetTextInput
            @ingroup User-Interface
        */
        const std::wstring& getValue() const;

    private:
        void updateTextNormal();
        void updateTextFocus();

        float* bufferNormal;
        float* bufferFocus;
        std::wstring text;
        int maxLength;
        ffw::vec2f stringPos;

        int dotsWidth;
        int underscoreWidth;
        bool textHasChanged;
        bool ctrlPressed;
    };
};

#endif





