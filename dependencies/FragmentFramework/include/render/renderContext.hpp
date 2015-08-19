/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_RENDER_CONTEXT
#define FFW_RENDER_CONTEXT

namespace ffw {
    class renderContext;
};

#include "../config.h"
#include "../gl/monitors.hpp"
#include "../gl/extensions.hpp"
#include "../graphics/basicShaders.hpp"

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
    */
    class FFW_API renderContext {
    public:
        renderContext();
        virtual ~renderContext();
        /*!
            @memberof renderContext
            @ingroup Core
        */
        virtual void setViewport(int PosX, int PosY, int Width, int Height) = 0;
        /*!
            @memberof renderContext
            @ingroup Core
        */
        virtual const ffw::mat4& getViewMatrix() const = 0;
        /*!
            @memberof renderContext
            @ingroup Core
        */
        virtual void getViewport(int *PosX, int *PosY, int *Width, int *Height) const = 0;
        /*!
            @memberof renderContext
            @ingroup Core
        */
        virtual void* getGlextFunc(const std::string& FunctionName) const = 0;
        /*!
            @memberof renderContext
            @ingroup Core
        */
        virtual bool isGlextFuncPresent(const std::string& FunctionName) const = 0;
        /*!
            @memberof renderContext
            @ingroup Core
        */
        virtual void setSwapInterval(int Interval) = 0;
        /*!
            @memberof renderContext
            @ingroup Core
        */
        virtual const glExtensions& getGlExtensions() const = 0;
        /*!
            @memberof renderContext
            @ingroup Core
        */
        virtual const basicShaders& getBasicShaders() const = 0 ;
    };
}

#endif
