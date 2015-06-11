/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET_PROGRESSBAR
#define FFW_UI_WIDGET_PROGRESSBAR

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
	class FFW_API uiWidgetProgressbar : public uiWidget {
    public:
        /*!
            @memberof uiWidgetProgressbar
            @ingroup User-Interface
        */
        uiWidgetProgressbar(const std::string& ID, float PosX, float PosY, float Width, float Value);
        ~uiWidgetProgressbar();

        void update() override;
        /*!
            @memberof uiWidgetProgressbar
            @ingroup User-Interface
        */
        void setValue(float Value);
        /*!
            @memberof uiWidgetProgressbar
            @ingroup User-Interface
        */
        float getValue() const;

    private:
        void updateProgress();
        float value;
    };
};

#endif







