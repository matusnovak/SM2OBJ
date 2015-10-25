/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TEXTURE_1D
#define FFW_TEXTURE_1D

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
	class FFW_API texture1D: public texture {
    public:
		/*!
		 * @memberof texture1D
		 * @ingroup Graphics
		 * @static
		 */
        static bool checkCompability(const renderContext* Renderer);
		
		texture1D();
        ~texture1D();
        /*!
         * @memberof texture1D
         * @ingroup Graphics
         */
        bool create(const ffw::renderContext* Renderer, GLsizei Width, GLenum InternalFormat, GLenum Format, GLenum PixelFormat);
        /*!
         * @memberof texture1D
         * @ingroup Graphics
         */
        bool setPixels(GLint Level, GLint Xoffset, GLsizei Width, const void* Pixels);
		/*!
         * @memberof texture1D
         * @ingroup Graphics
         */
		bool getPixels(void* Pixels);
    };
};
#endif

