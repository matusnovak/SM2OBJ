/*** This file is part of FragmentFramework project ***/

#ifndef FFW_RENDERBUFFER_2D_MS
#define FFW_RENDERBUFFER_2D_MS

#include "renderbuffer.hpp"

/*!
 * @ingroup Graphics
 */
namespace ffw {
	class renderContext;
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @inherits renderbuffer
	 * @brief 2D Multisampled Renderbuffer
	 */
	class FFW_API renderbuffer2DMS: public renderbuffer {
    public:
		/*!
		 * @memberof renderbuffer2DMS
		 * @ingroup Graphics
		 * @static
		 */
        static bool checkCompability(const renderContext* Renderer);
		
		renderbuffer2DMS();
        ~renderbuffer2DMS();
		/*!
		 * @memberof renderbuffer2DMS
		 * @ingroup Graphics
		 * @brief Creates the renderbuffer
		 */
		bool create(const ffw::renderContext* Renderer, GLsizei Width, GLsizei Height, GLenum InternalFormat, GLint Samples);
    };
};
#endif
