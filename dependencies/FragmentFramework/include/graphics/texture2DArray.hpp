/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TEXTURE_2D_ARRAY
#define FFW_TEXTURE_2D_ARRAY

#include "texture.hpp"

/*!
    @ingroup Graphics
*/
namespace ffw {
	/*!
        @memberof ffw
        @ingroup Graphics
        @inherit texture
        @sa texture
    */
	class FFW_API texture2DArray: public texture {
    public:
        static bool checkCompability(const renderContext* Renderer);
		
		texture2DArray();
        ~texture2DArray();
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
        bool create(const ffw::renderContext* Renderer, GLsizei Width, GLsizei Height, GLsizei Layers, GLenum InternalFormat, GLenum Format, GLenum PixelFormat);
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
            @param [in] Pixels      Pointer to the pixel buffer
        */
        bool setPixels(GLint Level, GLint Xoffset, GLint Yoffset, GLint Loffset, GLsizei Width, GLsizei Height, const void* pixels);
		/*!
            @memberof texture2DArray
            @ingroup Graphics
		*/
		bool getPixels(void* pixels);
    };
};
#endif


