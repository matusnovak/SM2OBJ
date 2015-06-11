/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET_ICON
#define FFW_UI_WIDGET_ICON

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
	class FFW_API uiWidgetIcon : public uiWidget {
    public:
        /*!
            @memberof uiWidgetIcon
            @ingroup User-Interface
        */
        uiWidgetIcon(float PosX, float PosY, float Width, float Height, const std::string& IconName, const ffw::color& Color);
        uiWidgetIcon(float PosX, float PosY, float Width, float Height, const ffw::vec4f& IconTile, const ffw::color& Color);
        ~uiWidgetIcon();

        void update() override;

    private:
        std::string iconName;
        ffw::vec4f iconTile;
        ffw::color iconColor;
    };
};

#endif




