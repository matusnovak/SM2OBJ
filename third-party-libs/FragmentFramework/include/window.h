/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_RENDER_WINDOW
#define FFW_RENDER_WINDOW

#include <string>
#include <vector>

/*!
    @ingroup Core
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup Core
    */
    class window {
    public:
        window(){
        }
        /*!
            @memberof window
            @ingroup Core
        */
        virtual ~window(){
        }
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void setup() = 0;
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void update() = 0;
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void render() = 0;
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void destroy(){}
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void textInput(unsigned int C){}
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void keyPressed(int Key, int Mode){}
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void mouseMoved(int MouseX, int MouseY){}
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void mouseScroll(int scroll){}
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void mouseButton(int button, int mode){}
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void windowResized(int width, int height){}
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void windowMoved(int windowX, int windowY){}
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void windowShouldClose(){}
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void windowFocus(int focus){}
        /*!
            @memberof window
            @ingroup Core
        */
        virtual void filesDropped(std::vector<std::string> FileList){}
    };
};

#endif
