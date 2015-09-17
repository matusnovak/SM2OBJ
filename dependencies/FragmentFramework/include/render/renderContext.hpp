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

#include "../common.h"
#include "../gl/monitors.hpp"
#include "../gl/extensions.hpp"
#include "../graphics/drawShaders.hpp"

/*!
 * @defgroup Core
 * @brief Core brief
 */

/*!
 * @ingroup Core
 * @brief FFW brief
 */
namespace ffw {
    /*!
     * @memberof ffw
     * @ingroup Core
     */
    bool FFW_API initGraphics();
    /*!
     * @memberof ffw
     * @ingroup Core
     */
	void FFW_API terminateGraphics();
	/*!
     * @memberof ffw
     * @ingroup Core
     */
    class FFW_API renderContext {
    public:
        renderContext();
        virtual ~renderContext();
        /*!
		 * @memberof renderContext
		 * @ingroup Core
		 * @pure
		 */
        virtual void setViewport(int PosX, int PosY, int Width, int Height) = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Core
		 * @pure
		 */
        virtual const ffw::mat4x4f& getViewMatrix() const = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Core
		 * @pure
		 */
        virtual void getViewport(int *PosX, int *PosY, int *Width, int *Height) const = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Core
		 * @pure
		 */
        virtual void* getGlextFunc(const std::string& FunctionName) const = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Core
		 * @pure
		 */
        virtual bool isGlextFuncPresent(const std::string& FunctionName) const = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Core
		 * @pure
		 */
        virtual void setSwapInterval(int Interval) = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Core
		 * @pure
		 */
        virtual const glExtensions& getGlExtensions() const = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Core
		 * @pure
		 */
        virtual const drawShaders& getdrawShaders() const = 0 ;
    };
}

#endif
