/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_GRAPHICS_TEXTURE_BASE
#define FFW_GRAPHICS_TEXTURE_BASE

#include "../dll.h"
#include "../utilities/loadSaveBmp.h"

#include <GL/glfw3.h>
#include <GL/glext.h>

/*!
    @ingroup Graphics
*/
namespace ffw {
	/*!
        @memberof ffw
        @ingroup Graphics

        @brief Base class for texture formats

        @warning Do not use this class! This class is useless
        without using derived classes.

        @sa texture2D, texture2DArray
    */
	class FFW_API textureBase {
    public:
        textureBase();
        virtual ~textureBase();
        /*!
            @memberof textureBase
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
            @memberof textureBase
            @ingroup Graphics
            @const

            @brief Returns true if texture is loaded

            @return True if loaded
        */
        bool isLoaded() const;
        /*!
            @memberof textureBase
            @ingroup Graphics

            @brief Deletes the texture from GPU memory

            @warning Render context must be active and be on
            same thread before calling this function.

            @return True on success
        */
        bool deleteTexture();
        /*!
            @memberof textureBase
            @ingroup Graphics

            @brief Binds the texture

            @details Binds this texture to current render context.

            @warning Render context must be active and be on
            same thread before calling this function.
        */
        bool bind();
        /*!
            @memberof textureBase
            @ingroup Graphics

            @brief Unbinds the texture

            @details Unbinds this from current render context.

            @note You do not need to call this function if you are
            binding multiple textures in series. Call this fuction only at the end.
            (eg, bind A, draw A, bind B, draw B, bind C, draw C, unbind C)

            @warning Render context must be active and be on
            same thread before calling this function.
        */
        void unbind();
        /*!
            @memberof textureBase
            @ingroup Graphics
            @const

            @brief Returns the GL integer pointer to the texture

            @return GL integer pointer to the texture
        */
        GLuint getTexture() const;
        /*!
            @memberof textureBase
            @ingroup Graphics
            @const

            @brief Returns width of the texture

            @return Width
        */
        GLsizei getWidth() const;
        /*!
            @memberof textureBase
            @ingroup Graphics
            @const

            @brief Returns height of the texture

            @return Height
        */
        GLsizei getHeight() const;
        /*!
            @memberof textureBase
            @ingroup Graphics
            @const

            @brief Returns number of layers of the texture

            @details This function has effect only for
            array type textures. Otherwise returns zero.

            @return Number of layers if texture is array, otherwise zero.
        */
        GLsizei getLayers() const;
        /*!
            @memberof textureBase
            @ingroup Graphics
            @const

            @brief Returns depth of the texture

            @details This function has effect only for
            3D type textures. Otherwise returns zero.

            @return Depth of texture if is 3D, otherwise zero.
        */
        GLsizei getDepth() const;
        /*!
            @memberof textureBase
            @ingroup Graphics
            @const

            @brief Returns the internal format

            @details Returns the internal format of the
            texture. (For example: GL_RGBA8, GL_RGBA16,
            GL_RGBA32F​, etc.)

            @return Internal format
        */
        GLenum getInternalFormat() const;
        /*!
            @memberof textureBase
            @ingroup Graphics
            @const

            @brief Returns the format

            @details Returns the format of the texture.
            (For example: GL_RGB, GL_RGBA, GL_RED​, etc.)

            @return Internal format
        */
        GLenum getFormat() const;
        /*!
            @memberof textureBase
            @ingroup Graphics
            @const

            @brief Returns the pixel format

            @details Returns the pixel format of the texture.
            (For example: GL_UNSIGNED_BYTE, GL_FLOAT, etc.)

            @return Internal format
        */
        GLenum getPixelFormat() const;
        /*!
            @memberof textureBase
            @ingroup Graphics
            @const

            @brief Returns the texture format

            @details Returns the texture format of the texture.
            (For example: GL_TEXTURE_2D, GL_TEXTURE_2D_ARRAY, etc.)

            @return Internal format
        */
        GLenum getTextureFormat() const;
        /*!
            @memberof textureBase
            @ingroup Graphics

            @brief Sets the environment mode

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] Target Target parameter
            @param [in] Name   Name of the parameter
            @param [in] Value  Value
        */
        void setEnvParami(GLenum Target, GLenum Name, GLint Value);
        /*!
            @memberof textureBase
            @ingroup Graphics

            @brief Sets the environment mode

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] Target Target parameter
            @param [in] Name   Name of the parameter
            @param [in] Value  Value
        */
        void setEnvParamf(GLenum Target, GLenum Name, GLfloat Value);
        /*!
            @memberof textureBase
            @ingroup Graphics

            @brief Sets the texture parameter

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] Name   Name of the parameter
            @param [in] Value  Value
        */
        void setTexParami(GLenum Name, GLint Value);
        /*!
            @memberof textureBase
            @ingroup Graphics

            @brief Sets the texture parameter

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] Name   Name of the parameter
            @param [in] Value  Value
        */
        void setTexParamf(GLenum Name, GLfloat Value);
        /*!
            @memberof textureBase
            @ingroup Graphics

            @brief Generates mipmaps

            @warning Render context must be active and be on
            same thread before calling this function.
        */
        void generateMipmaps();

    protected:
        bool loaded;
        bool instance;
        GLenum textureFormat;
        GLenum internalFormat;
        GLenum format;
        GLenum pixelFormat;
        GLuint buffer;

        GLsizei width;
        GLsizei height;
        GLsizei depth;
        GLsizei layers;
        bool mipmaps;
        bool initialized;

        PFNGLTEXIMAGE3DPROC glTexImage3D;
        PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D;
        PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
    };
};
#endif
