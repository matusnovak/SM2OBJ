/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_RENDERBUFFER_2D
#define FFW_RENDERBUFFER_2D

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
	class FFW_API renderbuffer2D: public renderbuffer {
    public:
        static bool checkCompability(const renderContext* Renderer);
		
		renderbuffer2D();
        ~renderbuffer2D();
		/*!
            @memberof renderbuffer2D
            @ingroup Graphics
            @const
        */
		bool create(const ffw::renderContext* Renderer, GLsizei Width, GLsizei Height, GLenum InternalFormat);
    };
};
#endif
