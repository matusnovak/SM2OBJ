/*** This file is part of FragmentFramework project ***/

#ifndef FFW_RENDERBUFFER_2D
#define FFW_RENDERBUFFER_2D

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
	 * @brief 2D Renderbuffer
	 */
	class FFW_API renderbuffer2D: public renderbuffer {
    public:
		/*!
		 * @memberof renderbuffer2D
		 * @ingroup Graphics
		 * @static
		 */
        static bool checkCompability(const renderContext* Renderer);
		
		renderbuffer2D();
        ~renderbuffer2D();
		/*!
		 * @memberof renderbuffer2D
		 * @ingroup Graphics
		 * @brief Creates the renderbuffer
		 */
		bool create(const ffw::renderContext* Renderer, GLsizei Width, GLsizei Height, GLenum InternalFormat);
    };
};
#endif
