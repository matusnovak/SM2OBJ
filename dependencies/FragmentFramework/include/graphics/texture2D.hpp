/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TEXTURE_2D
#define FFW_TEXTURE_2D

#include "texture.hpp"

/*!
 * @ingroup Graphics
 */
namespace ffw {
	/*!
     * @memberof ffw
     * @ingroup Graphics
     * @inherit texture
     * @sa texture
     */
	class FFW_API texture2D: public texture {
    public:
		/*!
		 * @memberof texture2D
		 * @ingroup Graphics
		 * @static
		 */
        static bool checkCompability(const renderContext* Renderer);
		
		texture2D();
        ~texture2D();
        /*!
         * @memberof texture2D
         * @ingroup Graphics
		 *
         * @brief Creates empty texture
		 *
         * @param Width          Width of the texture
         * @param Height         Height of the texture
         * @param InternalFormat Internal format of the texture (e.g, GL_RGB8, GL_RGBA16, ...)
         * @param Format         Format of the texture (e.g, GL_RGB, GL_RGBA, GL_BGR, ...)
         * @param PixelFormat    Pixel format of the texture (e.g, GL_BYTE, GL_FLOAT, GL_UNSIGNED_SHORT_4_4_4_4, ...)
		 *
         * @return True on success
         */
        bool create(const ffw::renderContext* Renderer, GLsizei Width, GLsizei Height, GLenum InternalFormat, GLenum Format, GLenum PixelFormat);
		bool createFromFile(const ffw::renderContext* Renderer, const std::string& Path);
		bool createFromFile(const ffw::renderContext* Renderer, const std::wstring& Path);
        /*!
         * @memberof texture2D
         * @ingroup Graphics
		 *
         * @brief Uploads pixels
		 *
         * @details Xoffset and Yoffset defines the pixel
         * offset from left bottom corner of the texture.
		 *
         * @param Level   Target level of mipmap (default level is 0)
         * @param Xoffset Position offset X
         * @param Yoffset Position offset Y
         * @param Width   Width of the pixel buffer
         * @param Height  Height of the pixel buffer
         * @param Pixels  Pointer to the pixel buffer
         */
        bool setPixels(GLint Level, GLint Xoffset, GLint Yoffset, GLsizei Width, GLsizei Height, const void* Pixels);
		/*!
         * @memberof texture2D
         * @ingroup Graphics
         */
		bool getPixels(void* Pixels);
    };
};
#endif

