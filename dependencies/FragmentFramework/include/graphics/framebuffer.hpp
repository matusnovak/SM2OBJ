/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_GRAPHICS_FRAMEBUFFER
#define FFW_GRAPHICS_FRAMEBUFFER

#include "../config.h"
#include <vector>
#include "texture2D.hpp"
#include "../gl/extensions.hpp"

/*!
    @ingroup Graphics
*/
namespace ffw {
    class renderContext;
    /*!
        @memberof ffw
        @ingroup Graphics

        @brief Object on graphics card that can serve as offscreen rendering

        @details Framebuffer (or short FBO) contains single or multiple attachments.
        These attachments are textures, either color texture or depth buffer. The maximum
        number of possible attachments is defined by each graphics card. Framebuffer can
        be activated or deactivated while render context is active. Everything drawn while
        the FBO is active will not be rendered directly on the screen, instead the result
        will be stored in attachment(s). The framebuffer texture can be used as any other
        2D texture.
    */
	class FFW_API framebuffer {
    public:
        framebuffer();
        ~framebuffer();
        /*!
            @memberof framebuffer
            @ingroup Graphics
        */
        bool init(const renderContext* Context);
        /*!
            @memberof framebuffer
            @ingroup Graphics
        */
        bool isCreated() const;
        /*!
            @memberof framebuffer
            @ingroup Graphics
            @return True on success
        */
        bool create();
        /*!
            @memberof framebuffer
            @ingroup Graphics
            @return True if attachment has been added
        */
        bool addDepthAttachment(const ffw::texture2D* DepthTexture);
        /*!
            @memberof framebuffer
            @ingroup Graphics
        */
        bool addColorAttachment(const ffw::texture2D* ColorTexture);
		/*!
            @memberof framebuffer
            @ingroup Graphics
        */
		bool checkStatus();
        /*!
            @memberof framebuffer
            @ingroup Graphics
            @return True on success
        */
        bool resize();
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Deletes the framebuffer

            @warning Render context must be active and be on
            same thread before calling this function.

            @return True on success
        */
        bool destroy();
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Activates the framebuffer

            @warning Render context must be active and be on
            same thread before calling this function.
        */
        void bind();
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Clears all attachments

            @warning Render context must be active and be on
            same thread before calling this function.
        */
        void unbind();

    private:
        // Is framebuffer loaded?
        bool initialized;
        bool created;
        unsigned int fbo;
		int colorCount;
        const glExtensions* gl;
    };
};
#endif
