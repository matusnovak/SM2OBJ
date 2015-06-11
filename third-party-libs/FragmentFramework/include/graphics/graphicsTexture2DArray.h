/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_GRAPHICS_TEXTURE_2D_ARRAY
#define FFW_GRAPHICS_TEXTURE_2D_ARRAY

#include "graphicsTextureBase.h"

/*!
    @ingroup Graphics
*/
namespace ffw {
	/*!
        @memberof ffw
        @ingroup Graphics
        @inherit textureBase
        @sa textureBase
    */
	class FFW_API texture2DArray: public textureBase {
    public:
        texture2DArray();
        ~texture2DArray();
        /*!
            @memberof texture2DArray
            @ingroup Graphics

            @brief Creates instance to already existing 2D array texture

            @details This function only copies the data. Original texture
            will not be changed!

            @param [in] Buffer         GL integer pointer to the target texture
            @param [in] Width          Width of the target texture
            @param [in] Height         Height of the target texture
            @param [in] InternalFormat Internal format of the target texture (e.g, GL_RGB8, GL_RGBA16, ...)
            @param [in] Format         Format of the target texture (e.g, GL_RGB, GL_RGBA, GL_BGR, ...)
            @param [in] PixelFormat    Pixel format of the target texture (e.g, GL_BYTE, GL_FLOAT, GL_UNSIGNED_SHORT_4_4_4_4, ...)
        */
        bool makeInstance(GLuint Buffer, GLsizei Width, GLsizei Height, GLsizei Layers, GLenum InternalFormat, GLenum Format, GLenum PixelFormat);
        /*!
            @memberof texture2DArray
            @ingroup Graphics

            @brief Creates empty texture

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] Width          Width of the texture
            @param [in] Height         Height of the texture
            @param [in] Layers         Number of layers
            @param [in] InternalFormat Internal format of the texture (e.g, GL_RGB8, GL_RGBA16, ...)
            @param [in] Format         Format of the texture (e.g, GL_RGB, GL_RGBA, GL_BGR, ...)
            @param [in] PixelFormat    Pixel format of the texture (e.g, GL_BYTE, GL_FLOAT, GL_UNSIGNED_SHORT_4_4_4_4, ...)

            @return True on success
        */
        bool create(GLsizei Width, GLsizei Height, GLsizei Layers, GLenum InternalFormat, GLenum Format, GLenum PixelFormat);
        /*!
            @memberof texture2DArray
            @ingroup Graphics

            @brief Uploads pixels

            @details Xoffset and Yoffset defines the pixel offset
            from left bottom corner of the texture.

            @warning Render context must be active and be on
            same thread before calling this function.

            @param [in] Level       Target level of mipmap (default level is 0)
            @param [in] Xoffset     Offset position X
            @param [in] Yoffset     Offset position Y
            @param [in] Loffset     Offset of the layer
            @param [in] Width       Width of the pixel buffer
            @param [in] Height      Height of the pixel buffer
            @param [in] PixelFormat Pixel format of the pixel buffer (e.g, GL_BYTE, GL_FLOAT, ...)
            @param [in] Pixels      Pointer to the pixel buffer
        */
        bool upload(GLint Level, GLint Xoffset, GLint Yoffset, GLint Loffset, GLsizei Width, GLsizei Height, GLenum PixelFormat, unsigned char* pixels);
    };
};
#endif


