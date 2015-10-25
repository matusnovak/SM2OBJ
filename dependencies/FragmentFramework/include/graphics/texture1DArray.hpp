/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TEXTURE_1D_ARRAY
#define FFW_TEXTURE_1D_ARRAY

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
	class FFW_API texture1DArray: public texture {
    public:
		/*!
		 * @memberof texture1DArray
		 * @ingroup Graphics
		 * @static
		 */
        static bool checkCompability(const renderContext* Renderer);
		
		texture1DArray();
        ~texture1DArray();
        /*!
         * @memberof texture1DArray
         * @ingroup Graphics
         */
        bool create(const ffw::renderContext* Renderer, GLsizei Width, GLsizei Layers, GLenum InternalFormat, GLenum Format, GLenum PixelFormat);
        /*!
         * @memberof texture1DArray
         * @ingroup Graphics
         */
        bool setPixels(GLint Level, GLint Xoffset, GLint Loffset, GLsizei Width, const void* pixels);
		/*!
         * @memberof texture1DArray
         * @ingroup Graphics
         */
		bool getPixels(void* pixels);
    };
};
#endif


