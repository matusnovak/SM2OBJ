/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET_IMAGE_DYNAMIC
#define FFW_UI_WIDGET_IMAGE_DYNAMIC

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
	class FFW_API uiWidgetImageDynamic : public uiWidget {
    public:
        /*!
            @memberof uiWidgetImageDynamic
            @ingroup User-Interface
        */
        uiWidgetImageDynamic(const std::string& ID, float PosX, float PosY, float Width, float Height, const std::string& ImageName, const ffw::color& TintColor);
        ~uiWidgetImageDynamic();

        void update() override;

        void mousePressed(int Button, int PosX, int PosY) override;
        void mouseReleased(int Button) override;

    private:
        std::string imageName;
        ffw::color tintColor;
    };
};

#endif






