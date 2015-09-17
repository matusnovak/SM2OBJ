/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TEXTURE_3D
#define FFW_TEXTURE_3D

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
	class FFW_API texture3D: public texture {
    public:
        static bool checkCompability(const renderContext* Renderer);

		texture3D();
        ~texture3D();
        /*!
            @memberof texture3D
            @ingroup Graphics
        */
        bool create(const ffw::renderContext* Renderer, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum InternalFormat, GLenum Format, GLenum PixelFormat);
        /*!
            @memberof texture3D
            @ingroup Graphics
        */
        bool setPixels(GLint Level, GLint Xoffset, GLint Yoffset, GLint Zoffset, GLsizei Width, GLsizei Height, GLsizei Depth, const void* Pixels);
		/*!
            @memberof texture3D
            @ingroup Graphics
		*/
		bool getPixels(void* Pixels);
    };
};
#endif

