/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET_BOX
#define FFW_UI_WIDGET_BOX

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
	class FFW_API uiWidgetBox : public uiWidget {
    public:
        /*!
            @memberof uiWidgetBox
            @ingroup User-Interface
        */
        uiWidgetBox(float PosX, float PosY, float Width, float Height);
        ~uiWidgetBox();
        /*!
            @memberof uiWidgetBox
            @ingroup User-Interface
        */
        void update() override;
    };
};

#endif



