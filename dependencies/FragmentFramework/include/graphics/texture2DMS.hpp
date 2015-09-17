/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TEXTURE_2D_MS
#define FFW_TEXTURE_2D_MS

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
	class FFW_API texture2DMS: public texture {
    public:
        static bool checkCompability(const renderContext* Renderer);
		
		texture2DMS();
        ~texture2DMS();
        /*!
            @memberof texture2DMS
            @ingroup Graphics
        */
        bool create(const ffw::renderContext* Renderer, GLsizei Width, GLsizei Height, GLenum InternalFormat, GLenum Format, GLenum PixelFormat, GLint Samples);
    };
};
#endif

