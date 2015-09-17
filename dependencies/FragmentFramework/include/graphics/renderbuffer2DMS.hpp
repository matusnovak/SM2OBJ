/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_RENDERBUFFER_2D_MS
#define FFW_RENDERBUFFER_2D_MS

#include "renderbuffer.hpp"

/*!
    @ingroup Graphics
*/
namespace ffw {
	class renderContext;
	/*!
        @memberof ffw
        @ingroup Graphics
    */
	class FFW_API renderbuffer2DMS: public renderbuffer {
    public:
        static bool checkCompability(const renderContext* Renderer);
		
		renderbuffer2DMS();
        ~renderbuffer2DMS();
		/*!
            @memberof renderbuffer2DMS
            @ingroup Graphics
        */
		bool create(const ffw::renderContext* Renderer, GLsizei Width, GLsizei Height, GLenum InternalFormat, GLint Samples);
    };
};
#endif
