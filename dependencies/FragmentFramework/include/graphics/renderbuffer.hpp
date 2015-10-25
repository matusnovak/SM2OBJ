/*** This file is part of FragmentFramework project ***/

#ifndef FFW_RENDERBUFFER
#define FFW_RENDERBUFFER

#include "../common.h"

/*!
 * @ingroup Graphics
 */
namespace ffw {
	class renderContext;
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 */
	class FFW_API renderbuffer {
    public:
        renderbuffer();
        virtual ~renderbuffer();
        /*!
		 * @memberof renderbuffer
		 * @ingroup Graphics
		 * @const
		 * @brief Checks if the renderbuffer is created
		 */
        bool isCreated() const;
        /*!
		 * @memberof renderbuffer
		 * @ingroup Graphics
		 * @brief Destroys the renderbuffer
		 */
        void destroy();
        /*!
		 * @memberof renderbuffer
		 * @ingroup Graphics
		 * @const
		 * @brief Binds the renderbuffer
		 */
        void bind() const;
        /*!
		 * @memberof renderbuffer
		 * @ingroup Graphics
		 * @const
		 * @brief Unbinds the renderbuffer
		 */
        void unbind() const;
        /*!
		 * @memberof renderbuffer
		 * @ingroup Graphics
		 * @const
		 * @brief Returns the handle to the renderbuffer (OpenGL pointer)
		 */
        unsigned int getHandle() const;
        /*!
		 * @memberof renderbuffer
		 * @ingroup Graphics
		 * @const
		 * @brief Returns the width
		 */
        int getWidth() const;
        /*!
		 * @memberof renderbuffer
		 * @ingroup Graphics
		 * @const
		 * @brief Returns the height
		 */
        int getHeight() const;
        /*!
		 * @memberof renderbuffer
		 * @ingroup Graphics
		 * @const
		 * @brief Returns the internal format
		 */
        unsigned int getInternalFormat() const;

    protected:
        bool loaded;
        unsigned int internalFormat;
        unsigned int buffer;

        int width;
        int height;

        const glExtensions* gl;
    };
};
#endif
