/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_GRAPHICS_FRAMEBUFFER
#define FFW_GRAPHICS_FRAMEBUFFER

#include "../dll.h"
#include "graphicsTexture2D.h"

#include <GL/glfw3.h>
#include <GL/glext.h>

/*!
    @ingroup Graphics
*/
namespace ffw {
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

        @code
        // Example of framebuffer usage
        // Pointer to active render context
        ffw::renderContext* renderer;
        // FBO instance
        ffw::framebuffer fbo;

        // Initialize FBO
        if(fbo.init() == false){
            // Failed to initialize
            return -1;
        }
        // Start the process of creation
        if(fbo.createFboBegin(800, 600) == false){
            // Failed to create
            return -1;
        }
        // Add color attachment
        // 8 bit RGBA
        if(fbo.addColorAttachment(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE) == false){
            // Failed to add attachment
            return -1;
        }
        if(fbo.createFboEnd() == false){
            // Creation was unsuccessful!
            return -1;
        }

        // Start offscreen drawing
        // Remember last viewport state
        renderer->pushViewport();
        fbo.begin();
        // fbo.clean() is optional, use it to clear the attachments
        // Viewport needs to changed to fit FBO
        renderer->setViewport(800, 600);
        // Everything here will be drawn into the FBO
        // Draw red rectangle
        renderer->drawRectangle(100, 100, 200, 150, ffw::color(1.0f, 0.0f, 0.0f, 1.0f));
        // After the drawing deactivate the FBO
        fbo.end();

        // Restore saved viewport state
        renderer->popViewport();
        // Render the FBO directly on the screen
        // We need to get first (zeroth) color attachment
        renderer->drawTexture(0, 0, 800, 600, fbo.getColorAttachment(0), ffw::color(1.0f, 1.0f, 1.0f, 1.0f));
        // That is all...
        @endcode
    */
	class FFW_API framebuffer {
    public:
        framebuffer();
        ~framebuffer();
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Initializes required GL extensions

            @details This function needs to be called on
            each instance of this class.

            @warning Render context must be active and be on
            same thread before calling this function.

            @return True on success
        */
        bool init();
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Returns true if framebuffer is loaded

            @return True if loaded
        */
        bool isLoaded() const;
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Starts the process of framebuffer creation

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] Width  Width of framebuffer
            @param [in] Height Height of framebuffer

            @return True on success
        */
        bool createFboBegin(int Width, int Height);
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Adds depth attachment

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] InternalFormat Internal format of the depth attachment (eg, GL_DEPTH_COMPONENT32, ...)
            @param [in] Format         Format of the depth attachment (prefer to use GL_DEPTH_COMPONENT)
            @param [in] DataType       Data typeof the depth attachment (eg, GL_BYTE, GL_FLOAT, ...);

            @return True if attachment has been added
        */
        bool addDepthAttachment(GLenum InternalFormat, GLenum Format, GLenum DataType);
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Adds color attachment

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] InternalFormat Internal format of the color attachment (eg, GL_RGBA8, GL_RGBA16, ...)
            @param [in] Format         Format of the color attachment (eg, GL_RGB, GL_RGBA, GL_RED, ...)
            @param [in] DataType       Data type of the color attachment (eg, GL_BYTE, GL_FLOAT, ...);

            @return True if attachment has been added
        */
        bool addColorAttachment(GLenum InternalFormat, GLenum Format, GLenum DataType);
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Ends the process of framebuffer creation

            @warning Render context must be active and be on
            same thread before calling this function.

            @return True if ended successfully
        */
        bool createFboEnd();
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Resizes the framebuffer

            @details Resizes the framebuffer to new specified size.
            The data in each attachment will be lost!

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] Width  New width
            @param [in] Height New height

            @return True on success
        */
        bool resizeFbo(int Width, int Height);
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Deletes the framebuffer

            @warning Render context must be active and be on
            same thread before calling this function.

            @return True on success
        */
        bool deleteFbo();
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Activates the framebuffer

            @warning Render context must be active and be on
            same thread before calling this function.
        */
        void begin();
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Clears all attachments

            @warning Render context must be active and be on
            same thread before calling this function.
        */
		void clear();
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Deactivates the framebuffer

            @warning Render context must be active and be on
            same thread before calling this function.
        */
        void end();
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @brief Returns the pointer to color attachment

            @details Index of color attachment is same as the order
            of attachment cration.

            @param [in] Index on color attachment

            @return Pointer to color attachment
        */
        ffw::texture2D* getColorAttachment(int Index);
        /*!
            @memberof framebuffer
            @ingroup Graphics

            @memberof framebuffer
            @ingroup Graphics

            @brief Returns the pointer to depth attachment

            @return Pointer to depth attachment
        */
        ffw::texture2D* getDepthAttachment();

    private:
        // Is framebuffer loaded?
        bool initialized;
        bool loaded;
        int fboWidth;
        int fboHeight;
        bool usingDepth;
        GLuint fbo;

        ffw::texture2D depthAttachment;
        std::vector<ffw::texture2D>* colorAttachments;

        PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT;
        PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT;
        PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT;
        PFNGLGENRENDERBUFFERSEXTPROC glGenRenderbuffersEXT;
        PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT;
        PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT;
        PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT;
        PFNGLDELETERENDERBUFFERSEXTPROC glDeleteRenderbuffersEXT;
        PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT;
    };
};
#endif
