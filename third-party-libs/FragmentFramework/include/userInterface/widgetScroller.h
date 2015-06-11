/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET_SCROLLER
#define FFW_UI_WIDGET_SCROLLER

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
	class FFW_API uiWidgetScroller : public uiWidget {
    public:
        /*!
            @memberof uiWidgetScroller
            @ingroup User-Interface
        */
        uiWidgetScroller(const std::string& ID, float PosX, float PosY, float Width, float Value, bool Vertical);
        ~uiWidgetScroller();

        void update() override;
        void hover(bool Hover) override;
        void mousePressed(int Button, int PosX, int PosY) override;
        void mouseReleased(int Button) override;
        void mousePos(int PosX, int PosY) override;
        /*!
            @memberof uiWidgetScroller
            @ingroup User-Interface
        */
        void setValue(float Value);
        /*!
            @memberof uiWidgetScroller
            @ingroup User-Interface
        */
        float getValue() const;

    private:
        void updateScroller();

        float* knobNormal;
        float* knobHover;
        float* knobActive;
        float value;
        int mouseX;
        int mouseY;
        bool vertical;
        bool drag;
    };
};

#endif

