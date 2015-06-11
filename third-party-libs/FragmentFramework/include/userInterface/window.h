/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WINDOW
#define FFW_UI_WINDOW

#include "../dll.h"
#include "canvas.h"
#include "widgetImage.h"
#include "callback.h"

#include "../math/stringMath.h"
#include "../math/math.h"
#include "sharedData.h"

/*!
    @ingroup User-Interface
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup User-Interface
    */
	class FFW_API uiWindow {
    public:
        uiWindow(bool Tilebar, bool Closeable, bool Background);
        ~uiWindow();

        struct canvasWrapper {
            uiCanvas* ptr;
            bool hasHover;
        };

        bool init();
        void create();
        void destroy();
        void updateBuffers();
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        void setTitle(const std::wstring& Title);
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
		uiCanvas* addCanvas(int PosX, int PosY, int Width, int Height);
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        const std::vector<canvasWrapper>& getCanvases();
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        uiCanvas* getBackgroundCanvas();
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        void injectMousePos(int MouseX, int MouseY);
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        void injectMouseButtonPressed(int Button);
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        void injectMouseButtonReleased(int Button);
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        void injectKeyPressed(int Key, int Mode);
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        void injectTextInput(int C);
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        void resetUserInput();
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        void setSize(int Width, int Height);
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        void setPos(int PosX, int PosY);
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        const ffw::vec2i& getSize() const;
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        const ffw::vec2i& getPos() const;
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        void setMoveable(bool Moveable);
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        bool isMoveable() const;
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        void setVisible(bool Visibility);
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        bool isVisible() const;
        void setDataPtr(uiSharedData* SharedData);
        void poolEvents();
        void poolEventsPrivate();
        /*!
            @memberof uiWindow
            @ingroup User-Interface
        */
        template <class T> void addListener(void (T::*Func)(const uiEvent&), T* Instance){
            callback<T>* clb = new callback<T>(Func, Instance);
            listeners.push_back(clb);
        }

    private:
        void windowBackgroundEvent(const uiEvent& Event);
        uiWidget* addWidgetBcg(uiWidget* Widget);

        std::vector<canvasWrapper> canvases;
        std::vector<callbackInterface*> listeners;
        std::vector<callbackInterface*> listenersPrivate;
        uiCanvas backgroundCanvas;
        uiSharedData* sharedData;
        std::wstring title;
        ffw::vec2i size;
        ffw::vec2i pos;
        bool visible;
        bool moveable;
        bool tilebar;
        bool hideable;
        bool createBackground;
        bool createTilebar;
        bool createCloseButton;
        uiWidget* buttonClose;
    };
};

#endif
