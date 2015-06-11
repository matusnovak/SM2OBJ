/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET_LINE
#define FFW_UI_WIDGET_LINE

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
	class FFW_API uiWidgetLine : public uiWidget {
    public:
        /*!
            @memberof uiWidgetLine
            @ingroup User-Interface
        */
        uiWidgetLine(float PosX, float PosY, float Width, bool Vertical);
        ~uiWidgetLine();

        void update() override;

    private:
        bool vertical;
    };
};

#endif




