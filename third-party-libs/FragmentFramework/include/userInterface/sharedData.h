/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_SHARED_DATA
#define FFW_UI_SHARED_DATA

#include "../math/math.h"
#include "../graphics/graphicsTexture2D.h"
#include "../graphics/graphicsShader.h"
#include "../graphics/graphicsTrueType.h"

/*!
    @ingroup User-Interface
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup User-Interface
    */
    struct uiColors {
        /*!
            @memberof uiColors
            @ingroup User-Interface
        */
        ffw::color buttonIconColorNormal;
        /*!
            @memberof uiColors
            @ingroup User-Interface
        */
        ffw::color buttonIconColorHover;
        /*!
            @memberof uiColors
            @ingroup User-Interface
        */
        ffw::color buttonIconColorActive;
        /*!
            @memberof uiColors
            @ingroup User-Interface
        */
        ffw::color buttonTextColorNormal;
        /*!
            @memberof uiColors
            @ingroup User-Interface
        */
        ffw::color buttonTextColorHover;
        /*!
            @memberof uiColors
            @ingroup User-Interface
        */
        ffw::color buttonTextColorActive;
        /*!
            @memberof uiColors
            @ingroup User-Interface
        */
        ffw::color textInputTextColorNormal;
        /*!
            @memberof uiColors
            @ingroup User-Interface
        */
        ffw::color textInputTextColorFocus;
        /*!
            @memberof uiColors
            @ingroup User-Interface
        */
        ffw::color tilebarFontColor;
        /*!
            @memberof uiColors
            @ingroup User-Interface
        */
        ffw::color listItemColor;
    };

    class uiSharedData {
    public:
        uiSharedData();
        uiColors colors;
        ffw::trueType* font;

		void setIconSize(int Size);
		void addIcon(const std::string& Name, int PosX, int PosY);
		void addImage(const std::string& Name, int PosX, int PosY, int Width, int Height);
        const ffw::vec4f& getIcon(const std::string& Name);
        const ffw::vec4f& getImage(const std::string& Name);

        ffw::vec2f imagesAtlasSize;
        ffw::vec2f iconsAtlasSize;
    private:
        std::map<std::string, ffw::vec4f> icons;
        std::map<std::string, ffw::vec4f> images;
        float iconSize;
        ffw::vec4f nullIcon;
        ffw::vec4f nullImage;
    };
};

#endif




