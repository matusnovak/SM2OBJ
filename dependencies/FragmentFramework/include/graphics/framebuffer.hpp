/*** This file is part of FragmentFramework project ***/

#ifndef FFW_GRAPHICS_FRAMEBUFFER
#define FFW_GRAPHICS_FRAMEBUFFER

#include "../common.h"
#include "texture2D.hpp"
#include "texture2DMS.hpp"
#include "renderbuffer2D.hpp"
#include "renderbuffer2DMS.hpp"

/*!
    @ingroup Graphics
*/
namespace ffw {
    class renderContext;
    /*!
     * @memberof ffw
     * @ingroup Graphics
	 *
     * @brief Object on graphics card that can serve as offscreen rendering
	 *
     * @details Framebuffer (or short FBO) contains single or multiple attachments.
     * These attachments are textures, either color texture or depth buffer. The maximum
     * number of possible attachments is defined by each graphics card. Framebuffer can
     * be activated or deactivated while render context is active. Everything drawn while
     * the FBO is active will not be rendered directly on the screen, instead the result
     * will be stored in attachment(s). The framebuffer texture can be used as any other
     * 2D texture.
     */
	class FFW_API framebuffer {
    public:
		/*!
		 * @memberof framebuffer
		 * @ingroup Graphics
		 * @static
		 */
        static bool checkCompability(const renderContext* Renderer);
		framebuffer();
        ~framebuffer();
        /*!
         * @memberof framebuffer
         * @ingroup Graphics
         */
        bool isCreated() const;
        /*!
         * @memberof framebuffer
         * @ingroup Graphics
         * @return True on success
         */
        bool create(const renderContext* Renderer);
        /*!
         * @memberof framebuffer
         * @ingroup Graphics
         * @return True if attachment has been added
         */
        bool addColorTexture(const ffw::texture2D* DepthTexture);
        /*!
         * @memberof framebuffer
         * @ingroup Graphics
         */
        bool addDepthTexture(const ffw::texture2D* ColorTexture);
		/*!
         * @memberof framebuffer
         * @ingroup Graphics
         * @return True if attachment has been added
         */
        bool addColorTextureMS(const ffw::texture2DMS* DepthTexture);
        /*!
         * @memberof framebuffer
         * @ingroup Graphics
         */
        bool addDepthTextureMS(const ffw::texture2DMS* ColorTexture);
		/*!
         * @memberof framebuffer
         * @ingroup Graphics
         * @return True if attachment has been added
         */
        bool addColorRenderbuffer(const ffw::renderbuffer2D* DepthTexture);
        /*!
         * @memberof framebuffer
         * @ingroup Graphics
         */
        bool addDepthRenderbuffer(const ffw::renderbuffer2D* ColorTexture);
		/*!
         * @memberof framebuffer
         * @ingroup Graphics
         * @return True if attachment has been added
         */
        bool addColorRenderbufferMS(const ffw::renderbuffer2DMS* DepthTexture);
        /*!
         * @memberof framebuffer
         * @ingroup Graphics
         */
        bool addDepthRenderbufferMS(const ffw::renderbuffer2DMS* ColorTexture);
		/*!
         * @memberof framebuffer
         * @ingroup Graphics
         */
		bool checkStatus();
		/*!
         * @memberof texture
         * @ingroup Graphics
         * @const
         * @brief Checks if texture is loaded
         */
		unsigned int getHandle() const;
        /*!
         * @memberof framebuffer
         * @ingroup Graphics
         * @brief Returns framebuffer handle (OpenGL pointer)
         */
        bool destroy();
        /*!
         * @memberof framebuffer
         * @ingroup Graphics
         * @brief Activates the framebuffer
         */
        void bind() const;
        /*!
         * @memberof framebuffer
         * @ingroup Graphics
         * @brief Clears all attachments
         */
        void unbind() const;

    private:
        bool created;
        unsigned int fbo;
		int colorCount;
        const glExtensions* gl;
    };
};
#endif
