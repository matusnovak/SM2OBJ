/*** This file is part of FragmentFramework project ***/

#ifndef FFW_GL_MONITORS
#define FFW_GL_MONITORS

#include "../common.h"

/*!
 * @ingroup GL
 */
namespace ffw{
    /*!
	 * @memberof ffw
	 * @ingroup GL
	 */
    struct monitor{
        /*!
		 * @memberof monitor
		 * @ingroup GL
		 */
        std::string name;
        /*!
		 * @memberof monitor
		 * @ingroup GL
		 */
        vec2i resolution;
        /*!
		 * @memberof monitor
		 * @ingroup GL
		 */
        vec3i bitDepth;
        /*!
		 * @memberof monitor
		 * @ingroup GL
		 */
        int refreshRate;
        /*!
		 * @memberof monitor
		 * @ingroup GL
		 */
        vec2i position;
        /*!
		 * @memberof monitor
		 * @ingroup GL
		 */
        vec2i physicalSize;
        void* ptr;
    };
    /*!
	 * @memberof ffw
	 * @ingroup GL
	 */
    struct monitorMode{
        /*!
		 * @memberof monitorMode
		 * @ingroup GL
		 */
        vec2i resolution;
        /*!
		 * @memberof monitorMode
		 * @ingroup GL
		 */
        vec3i bitDepth;
        /*!
		 * @memberof monitorMode
		 * @ingroup GL
		 */
        int refreshRate;
    };
    /*!
	 * @memberof ffw
	 * @ingroup GL
	 */
    std::vector<monitor> FFW_API getMonitors();
    /*!
	 * @memberof ffw
	 * @ingroup GL
	 */
    monitor FFW_API getPrimaryMonitor();
    /*!
	 * @memberof ffw
	 * @ingroup GL
	 */
    std::vector<monitorMode> FFW_API getMonitorModes(monitor Monitor);
};

#endif
