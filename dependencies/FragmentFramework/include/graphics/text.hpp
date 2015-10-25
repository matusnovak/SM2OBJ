/*** This file is part of FragmentFramework project ***/

#ifndef FFW_GRAPHICS_TEXT
#define FFW_GRAPHICS_TEXT

#include "../common.h"
#include "bufferObject.hpp"

/*!
 * @ingroup Graphics
 */
namespace ffw {
	class renderContext;
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 */
	class FFW_API text {
    public:
		/*!
		 * @memberof text
		 * @ingroup Graphics
		 * @static
		 */
        static bool checkCompability(const renderContext* Renderer);
		
		text();
        ~text();
        /*!
		 * @memberof text
		 * @ingroup Graphics
		 * @brief Creates the text from vertex array
		 * @note You do not need to call this function. This is being handled
		 * by font class internally!
		 */
        bool create(const renderContext* Renderer, float* Vertices, size_t Size);
        /*!
		 * @memberof text
		 * @ingroup Graphics
		 * @brief Destroys the text
		 */
        void destroy();
        /*!
		 * @memberof text
		 * @ingroup Graphics
		 * @brief Returns the size of the text in bytes
		 */
        size_t getSize() const;
        /*!
		 * @memberof text
		 * @ingroup Graphics
		 * @brief Checks if text is crated
		 */
        bool isCreated() const;
        /*!
		 * @memberof text
		 * @ingroup Graphics
		 * @brief Binds the text
		 */
        void bind() const;
        /*!
		 * @memberof text
		 * @ingroup Graphics
		 * @brief Unbinds the text
		 */
        void unbind() const;

    private:
        bool loaded;
        ffw::vbo vbo;
        unsigned int size;

        int shaderViewLoc;
        int shaderTexSampleLoc;
        int shaderColorLoc;
        int shaderPositionLoc;
        int shaderTexCoordsLoc;
        int shaderOffsetLoc;
        bool shaderUniform;
    };
};
#endif
