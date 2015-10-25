/*** This file is part of FragmentFramework project ***/

#ifndef FFW_BUFFER_OBJECT
#define FFW_BUFFER_OBJECT

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
	class FFW_API bufferObject {
    public:
        /*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @static
		 */
		static bool checkCompability(const renderContext* Renderer);
		/*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Constructor
		 */
		bufferObject(unsigned int ObjectType);
		virtual ~bufferObject();
        /*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Checks if object is created
		 */
		bool isCreated() const;
        /*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Creates an object
		 */
		bool create(const renderContext* Renderer, const void* Data, int Size, unsigned int Type);
        /*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Sets (uploads) data
		 */
		bool setData(const void* Data, int Offset, int Size);
		/*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Maps a buffer to specific pointer
		 */
        bool mapBuffer(void** Pointer, unsigned int Access) const;
        /*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Unmaps a buffer
		 */
        bool unmapBuffer() const;
        /*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Destroys an object
		 */
		bool destroy();
        /*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Binds
		 */
		bool bind() const;
        /*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Unbinds
		 */
		void unbind() const;
        /*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Returns buffer handle (OpenGL pointer)
		 */
		unsigned int getBuffer() const;
        /*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Returns buffer size
		 */
		int getSize() const;
        /*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Returns buffer type
		 */
		unsigned int getType() const;
        /*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Returns object type
		 */
		unsigned int getObjectType() const;
        /*!
		 * @memberof bufferObject
		 * @ingroup Graphics
		 * @brief Copies data from another buffer
		 */
		bool copyFrom(const bufferObject* Other, ptrdiff_t Offset1, ptrdiff_t Offset2, ptrdiff_t Size);

    private:
        unsigned int type;
        const unsigned int objectType;
        bool loaded;
        unsigned int buffer;
        int size;

        const glExtensions* gl;
    };

	class FFW_API vbo: public bufferObject {
	public:
		vbo():bufferObject(GL_ARRAY_BUFFER){}
		virtual ~vbo(){}
	};

	class FFW_API ibo: public bufferObject {
	public:
		ibo():bufferObject(GL_ELEMENT_ARRAY_BUFFER){}
		virtual ~ibo(){}
	};
};
#endif

