/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_MANAGER
#define FFW_UI_MANAGER

#include "window.h"

#include "../dll.h"
#include "../math/stringMath.h"
#include "../math/math.h"
#include "../graphics/graphicsTexture2D.h"
#include "../graphics/graphicsShader.h"
#include "../graphics/graphicsTrueType.h"
#include "../utilities/timer.h"

#include <GL/glfw3.h>
#include <GL/gl.h>

/*!
    @ingroup User-Interface
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup User-Interface
    */
	class FFW_API uiManager {
    public:
        uiManager();
        ~uiManager();
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        bool init();
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        void destroy();
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        void deleteAllWindows();
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        bool loadTileTexture(const std::string& Path);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        bool loadIconsTexture(const std::string& Path);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        ffw::texture2D* createIconsTexture(int Size);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        int loadIconsData(const std::string& Path, int Size);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        bool loadImagesTexture(const std::string& Path);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        ffw::texture2D* createImagesTexture(int Size);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        int loadImagesData(const std::string& Path);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        bool addImageData(const std::string& Name, int PosX, int PosY, int Width, int Height);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        bool loadFont(const std::string& Path, int Points, int Dpi);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        void draw();
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        void update();
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        void setViewport(int PosX, int PosY, int Width, int Height);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        void injectMousePos(int MouseX, int MouseY);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        void injectMouseButtonPressed(int Button);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        void injectMouseButtonReleased(int Button);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        void injectKeyPressed(int Key, int Mode);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        void injectTextInput(int C);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        uiWindow* addWindow(int PosX, int PosY, int Width, int Height, const std::wstring& Title, bool Tilebar, bool Closeable, bool Background);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        uiColors* getColors();
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        void setTilebarTextColor(const ffw::color& Color);
        /*!
            @memberof uiManager
            @ingroup User-Interface
        */
        void poolEventsAll();

    private:
        void checkWindowOrder();
        void checkHoverIndex();

        ffw::texture2D tileTexture;
        ffw::texture2D iconTexture;
        ffw::texture2D imageTexture;
        ffw::shader tileShader;
        uiSharedData sharedData;
        ffw::trueType font;
        std::vector<uiWindow*> windowsVec;
        std::vector<int> windowsIndex;
        ffw::mat4 MVP;
        bool initialized;

        ffw::vec2i injectedMousePos;
        bool updateInjectedMousePos;
        int injectedMouseButtonPressed;
        int injectedMouseButtonReleased;
        bool updateInjectedMouseButtonPressed;
        bool updateInjectedMouseButtonReleased;
        int injectedKeyPressed;
        int injectedKeyPressedMode;
        bool updateInjectedKeyPressed;
        int injectedTextInput;
        bool updateInjectedTextInput;

        bool windowMoving;
        ffw::vec2i windowMovingPosOld;
        int windowMovingIndex;
        int windowHoverIndex;
        int windowHoverIndexOld;
        int windowActiveIndex;

        int shaderViewLoc;
        int shaderSamplerTilesLoc;
        int shaderSamplerFontLoc;
        int shaderSamplerIconLoc;
        int shaderSamplerImageLoc;
        int shaderPositionLoc;
        int shaderTexCoordsLoc;
        int shaderColorLoc;
        int shaderOffsetLoc;
        int viewportWidth;
        int viewportHeight;

        PFNGLACTIVETEXTUREPROC glActiveTexture;
    };
};

#endif
