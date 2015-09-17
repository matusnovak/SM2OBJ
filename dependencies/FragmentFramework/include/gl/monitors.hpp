/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_GL_MONITORS
#define FFW_GL_MONITORS

#include "../common.h"

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
        void* ptr;
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
    std::vector<monitor> FFW_API getMonitors();
    /*!
        @memberof ffw
        @ingroup Core
    */
    monitor FFW_API getPrimaryMonitor();
    /*!
        @memberof ffw
        @ingroup Core
    */
    std::vector<monitorMode> FFW_API getMonitorModes(monitor Monitor);
};

#endif
