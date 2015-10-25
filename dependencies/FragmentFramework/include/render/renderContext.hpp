/*** This file is part of FragmentFramework project ***/

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
 * @defgroup Render
 * @brief Render brief
 */

/*!
 * @ingroup Render
 * @brief FFW brief
 */
namespace ffw {
    /*!
     * @memberof ffw
     * @ingroup Render
     */
    bool FFW_API initGraphics();
    /*!
     * @memberof ffw
     * @ingroup Render
     */
	void FFW_API terminateGraphics();
	/*!
     * @memberof ffw
     * @ingroup Render
     */
    class FFW_API renderContext {
    public:
        renderContext();
        virtual ~renderContext();
        /*!
		 * @memberof renderContext
		 * @ingroup Render
		 * @pure
		 */
        virtual void setViewport(int PosX, int PosY, int Width, int Height) = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Render
		 * @pure
		 */
        virtual const ffw::mat4x4f& getViewMatrix() const = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Render
		 * @pure
		 */
        virtual void getViewport(int *PosX, int *PosY, int *Width, int *Height) const = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Render
		 * @pure
		 */
        virtual void* getGlextFunc(const std::string& FunctionName) const = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Render
		 * @pure
		 */
        virtual bool isGlextFuncPresent(const std::string& FunctionName) const = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Render
		 * @pure
		 */
        virtual void setSwapInterval(int Interval) = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Render
		 * @pure
		 */
        virtual const glExtensions& getGlExtensions() const = 0;
        /*!
		 * @memberof renderContext
		 * @ingroup Render
		 * @pure
		 */
        virtual const drawShaders& getdrawShaders() const = 0 ;
    };
}

#endif
