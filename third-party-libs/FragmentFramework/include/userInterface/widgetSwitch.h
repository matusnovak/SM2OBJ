/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET_SWITCH
#define FFW_UI_WIDGET_SWITCH

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
	class FFW_API uiWidgetSwitch : public uiWidget {
    public:
        /*!
            @memberof uiWidgetSwitch
            @ingroup User-Interface
        */
        uiWidgetSwitch(const std::string& ID, float PosX, float PosY, bool Vertical, bool Value);
        ~uiWidgetSwitch();

        void update() override;
        void mousePressed(int Button, int PosX, int PosY) override;
        /*!
            @memberof uiWidgetSwitch
            @ingroup User-Interface
        */
        void setValue(bool Value);
        /*!
            @memberof uiWidgetSwitch
            @ingroup User-Interface
        */
        bool getValue() const;

    private:
        float* bufferOn;
        float* bufferOff;
        bool value;
        bool vertical;
    };
};

#endif






