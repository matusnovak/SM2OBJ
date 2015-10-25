/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TEXTURE_2D_ARRAY_MS
#define FFW_TEXTURE_2D_ARRAY_MS

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
	class FFW_API texture2DArrayMS: public texture {
    public:
		/*!
		 * @memberof texture2DArrayMS
		 * @ingroup Graphics
		 * @static
		 */
        static bool checkCompability(const renderContext* Renderer);
		
		texture2DArrayMS();
        ~texture2DArrayMS();
        /*!
         * @memberof texture2DArrayMS
         * @ingroup Graphics
         */
        bool create(const ffw::renderContext* Renderer, GLsizei Width, GLsizei Height, GLsizei Layers, GLenum InternalFormat, GLenum Format, GLenum PixelFormat, GLint Samples);
    };
};
#endif


