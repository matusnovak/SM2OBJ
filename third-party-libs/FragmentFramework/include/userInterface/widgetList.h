/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET_LIST
#define FFW_UI_WIDGET_LIST

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
	class FFW_API uiWidgetList : public uiWidget {
    public:
        /*!
            @memberof uiWidgetList
            @ingroup User-Interface
        */
        uiWidgetList(const std::string& ID, float PosX, float PosY, float Width, float Height, int ItemHeight, int StrLength, const std::vector<std::wstring>& Items);
        ~uiWidgetList();

        void update() override;
        void hover(bool Hover) override;
        void mousePressed(int Button, int PosX, int PosY) override;
        void mouseReleased(int Button) override;
        void mousePos(int PosX, int PosY) override;

        /*!
            @memberof uiWidgetList
            @ingroup User-Interface
        */
        void setValue(const std::vector<std::wstring>& Items);
        /*!
            @memberof uiWidgetList
            @ingroup User-Interface
        */
        int getSelected();
        /*!
            @memberof uiWidgetList
            @ingroup User-Interface
        */
        const std::wstring& getSelectedStr();

    private:
        void updateScroller();
        void updateList();

        float* knobNormal;
        float* knobHover;
        float* knobActive;
        float value;
        int mouseX;
        int mouseY;
        bool drag;
        int selected;
        int start;
        int startOld;
        int selectedOld;
        int itemHeight;
        int itemCount;
        int strLength;
        ffw::vec2f selectionSize;
        std::vector<std::wstring> items;
    };
};

#endif




