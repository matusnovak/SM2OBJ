/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_RENDER_CONTEXT
#define FFW_RENDER_CONTEXT

#include "dll.h"
#include "window.h"
#include "gl/renderUtilities.h"
#include "gl/monitors.h"
#include "utilities/timer.h"

//#include <windows.h>
//#include <iostream>
//#include <iomanip>
//#include <stdio.h>
//#include <time.h>
//#include <pthread.h>
//#include <tchar.h>
//#include <assert.h>

/*!
    @ingroup Core
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup Core
    */
    bool FFW_API initGraphics();
    /*!
        @memberof ffw
        @ingroup Core
    */
	void FFW_API terminateGraphics();
    /*!
        @memberof ffw
        @ingroup Core
        @sa renderUtilities
        @inherit renderUtilities
    */
	class FFW_API renderContext : public renderUtilities {
    public:
        renderContext();
        ~renderContext();
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool init();
        /*!
            @memberof renderContext
            @ingroup Core
        */
        void destroy();
        /*!
            @memberof renderContext
            @ingroup Core
        */
        void run();
        /*!
            @memberof renderContext
            @ingroup Core
        */
        void stop();
        /*!
            @memberof renderContext
            @ingroup Core
        */
        uint64_t getLastFrameTime();
        /*!
            @memberof renderContext
            @ingroup Core
        */
        void setSwapInterval(int Interval);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool showMouseCursor(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool hideMouseCursor(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool setMouseCursorPos(window* Window, int PosX, int PosY);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool hideWindow(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool showWindow(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool iconifyWindow(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool restoreWindow(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool setWindowPos(window* Window, int PosX, int PosY);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool setWindowSize(window* Window, int Width, int Height);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        vec2i getWindowSize(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        vec2i getWindowPos(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool setWindowCursorCustomImage(window* Window, unsigned char* Pixels, int Width, int Height, int PosX, int PosY);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool setWindowCursorCustom(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool setWindowCursorArrow(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool setWindowCursorIbeam(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool setWindowCursorCrosshair(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool setWindowCursorHand(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool setWindowCursorHResize(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool setWindowCursorVresize(window* Window);
        /*!
            @memberof renderContext
            @ingroup Core
        */
        bool addWindow(window* Window, bool Resizable, bool Decorated, bool Iconify, bool Floating, bool Focused, int PosX, int PosY, int Width, int Height, std::string Title, monitor* Monitor);
    private:
        static void keyPressedCB            (GLFWwindow* windowContext, int key, int scancode, int action, int mods);
        static void textInputCB             (GLFWwindow* windowContext, unsigned int key);
        static void mouseMovedCB            (GLFWwindow* windowContext, double xpos, double ypos);
        static void mouseButtonPressedCB    (GLFWwindow* windowContext, int button,int action, int mods);
        static void mouseScrolledCB         (GLFWwindow* windowContext, double xoffset, double yoffset);
        static void windowShouldCloseCB     (GLFWwindow* windowContext);
        static void windowMovedCB           (GLFWwindow* windowContext, int xpos, int ypos);
        static void windowFocusCB           (GLFWwindow* windowContext, int focus);
        static void filesFroppedCB          (GLFWwindow* windowContext, int count, const char** files);

        //renderer activeRenderer;
        GLFWwindow* defaultWindowContext;

        struct wrapper{
            window* windowPtr;
            GLFWwindow* windowContext;
            int windowWidth;
            int windowHeight;
            bool visible;
            GLFWcursor* windowCursor;
            GLFWcursor* windowCursorArrow;
            GLFWcursor* windowCursorIbeam;
            GLFWcursor* windowCursorCrosshair;
            GLFWcursor* windowCursorHand;
            GLFWcursor* windowCursorHresize;
            GLFWcursor* windowCursorVresize;
            int cursorX;
            int cursorY;
        };

        PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
        PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT = NULL;

        std::vector<wrapper> windows;

        bool initialized;
        bool runRenderer;
        uint64_t lastFrameTime;
    };
};
#endif
