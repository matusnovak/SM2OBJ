/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TEXTURE_BASE
#define FFW_TEXTURE_BASE

#include "../common.h"

/*!
    @ingroup Graphics
*/
namespace ffw {
	class renderContext;
	/*!
        @memberof ffw
        @ingroup Graphics

        @brief Base class for texture formats

        @warning Do not use this class! This class is useless
        without using derived classes.

        @sa texture2D, texture2DArray
    */
	class FFW_API texture {
    public:
        texture();
        virtual ~texture();
        /*!
            @memberof texture
            @ingroup Graphics
            @const

            @brief Returns true if texture is loaded

            @return True if loaded
        */
        bool isCreated() const;
        /*!
            @memberof texture
            @ingroup Graphics

            @brief Deletes the texture from GPU memory

            @warning Render context must be active and be on
            same thread before calling this function.

            @return True on success
        */
        void destroy();
        /*!
            @memberof texture
            @ingroup Graphics

            @brief Binds the texture

            @details Binds this texture to current render context.

            @warning Render context must be active and be on
            same thread before calling this function.
        */
        void bind() const;
        /*!
            @memberof texture
            @ingroup Graphics

            @brief Unbinds the texture

            @details Unbinds this from current render context.

            @note You do not need to call this function if you are
            binding multiple textures in series. Call this fuction only at the end.
            (eg, bind A, draw A, bind B, draw B, bind C, draw C, unbind C)

            @warning Render context must be active and be on
            same thread before calling this function.
        */
        void unbind() const;
        /*!
            @memberof texture
            @ingroup Graphics
            @const

            @brief Returns the GL integer pointer to the texture
        */
        unsigned int getHandle() const;
        /*!
            @memberof texture
            @ingroup Graphics
            @const

            @brief Returns width
        */
        int getWidth() const;
        /*!
            @memberof texture
            @ingroup Graphics
            @const

            @brief Returns height
        */
        int getHeight() const;
        /*!
            @memberof texture
            @ingroup Graphics
            @const

            @brief Returns number of layers of the texture

            @details This function has effect only for
            array type textures. Otherwise returns zero.

            @return Number of layers if texture is array, otherwise zero.
        */
        int getLayers() const;
        /*!
            @memberof texture
            @ingroup Graphics
            @const

            @brief Returns depth of the texture

            @details This function has effect only for
            3D type textures. Otherwise returns zero.

            @return Depth of texture if is 3D, otherwise zero.
        */
        int getDepth() const;
        /*!
            @memberof texture
            @ingroup Graphics
            @const

            @brief Returns the internal format

            @details Returns the internal format of the
            texture. (For example: GL_RGBA8, GL_RGBA16,
            GL_RGBA32F​, etc.)

            @return Internal format
        */
        unsigned int getInternalFormat() const;
        /*!
            @memberof texture
            @ingroup Graphics
            @const

            @brief Returns the format

            @details Returns the format of the texture.
            (For example: GL_RGB, GL_RGBA, GL_RED​, etc.)

            @return Internal format
        */
        unsigned int getFormat() const;
        /*!
            @memberof texture
            @ingroup Graphics
            @const

            @brief Returns the pixel format

            @details Returns the pixel format of the texture.
            (For example: GL_UNSIGNED_BYTE, GL_FLOAT, etc.)

            @return Internal format
        */
        unsigned int getPixelFormat() const;
        /*!
            @memberof texture
            @ingroup Graphics
            @const

            @brief Returns the texture format

            @details Returns the texture format of the texture.
            (For example: GL_TEXTURE_2D, GL_TEXTURE_2D_ARRAY, etc.)

            @return Internal format
        */
        unsigned int getTextureFormat() const;
        /*!
            @memberof texture
            @ingroup Graphics

            @brief Sets the environment mode

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] Target Target parameter
            @param [in] Name   Name of the parameter
            @param [in] Value  Value
        */
        void setEnvParami(unsigned int Target, unsigned int Name, int Value);
        /*!
            @memberof texture
            @ingroup Graphics

            @brief Sets the environment mode

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] Target Target parameter
            @param [in] Name   Name of the parameter
            @param [in] Value  Value
        */
        void setEnvParamf(unsigned int Target, unsigned int Name, float Value);
        /*!
            @memberof texture
            @ingroup Graphics

            @brief Sets the texture parameter

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] Name   Name of the parameter
            @param [in] Value  Value
        */
        void setTexParami(unsigned int Name, int Value);
        /*!
            @memberof texture
            @ingroup Graphics

            @brief Sets the texture parameter

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] Name   Name of the parameter
            @param [in] Value  Value
        */
        void setTexParamf(unsigned int Name, float Value);
        /*!
            @memberof texture
            @ingroup Graphics

            @brief Generates mipmaps

            @warning Render context must be active and be on
            same thread before calling this function.
        */
        void generateMipmaps();

    protected:
        bool loaded;
        unsigned int textureFormat;
        unsigned int internalFormat;
        unsigned int format;
        unsigned int pixelFormat;
        unsigned int buffer;

        int width;
        int height;
        int depth;
        int layers;
        bool mipmaps;
        bool initialized;

        const glExtensions* gl;
    };
};
#endif
