/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET_CHECKBOX
#define FFW_UI_WIDGET_CHECKBOX

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
	class FFW_API uiWidgetCheckbox : public uiWidget {
    public:
        /*!
            @memberof uiWidgetCheckbox
            @ingroup User-Interface
        */
        uiWidgetCheckbox(const std::string& ID, float PosX, float PosY, float Size, bool Value);
        ~uiWidgetCheckbox();

        void update() override;
        void hover(bool Hover) override;
        void mousePressed(int Button, int PosX, int PosY) override;
        void mouseReleased(int Button) override;
        /*!
            @memberof uiWidgetCheckbox
            @ingroup User-Interface
        */
        void setValue(bool Value);
        /*!
            @memberof uiWidgetCheckbox
            @ingroup User-Interface
        */
        bool getValue() const;

    private:
        float* bufferOnNormal;
        float* bufferOnHover;
        float* bufferOnActive;
        float* bufferOffNormal;
        float* bufferOffHover;
        float* bufferOffActive;
        bool value;
    };
};

#endif







