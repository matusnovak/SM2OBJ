/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_GL_EXTENSIONS
#define FFW_GL_EXTENSIONS

#include <GL/glfw3.h>

#include "../math/math.h"

#include <string>
#include <vector>

/*!
    @ingroup Graphics
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Core
    */
    struct monitor{
        /*!
            @memberof monitor
            @ingroup Core
        */
        std::string name;
        /*!
            @memberof monitor
            @ingroup Core
        */
        vec2i resolution;
        /*!
            @memberof monitor
            @ingroup Core
        */
        vec3i bitDepth;
        /*!
            @memberof monitor
            @ingroup Core
        */
        int refreshRate;
        /*!
            @memberof monitor
            @ingroup Core
        */
        vec2i position;
        /*!
            @memberof monitor
            @ingroup Core
        */
        vec2i physicalSize;
        GLFWmonitor* ptr;
    };
    /*!
        @memberof ffw
        @ingroup Core
    */
    struct monitorMode{
        /*!
            @memberof monitorMode
            @ingroup Core
        */
        vec2i resolution;
        /*!
            @memberof monitorMode
            @ingroup Core
        */
        vec3i bitDepth;
        /*!
            @memberof monitorMode
            @ingroup Core
        */
        int refreshRate;
    };
    /*!
        @memberof ffw
        @ingroup Core
    */
    std::vector<monitor> getMonitors();
    /*!
        @memberof ffw
        @ingroup Core
    */
    monitor getPrimaryMonitor();
    /*!
        @memberof ffw
        @ingroup Core
    */
    std::vector<monitorMode> getMonitorModes(monitor Monitor);
};

#endif
