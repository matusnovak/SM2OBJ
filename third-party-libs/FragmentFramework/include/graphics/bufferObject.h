/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_BUFFER_OBJECT
#define FFW_BUFFER_OBJECT

#include "../dll.h"
#include <GL/glfw3.h>
#include <GL/glext.h>

/*!
    @ingroup Graphics
*/
namespace ffw {
	/*!
        @memberof ffw
        @ingroup Graphics
    */
	class FFW_API bufferObject {
    public:
        bufferObject();
		~bufferObject();
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bool init(GLenum ObjectType);
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bool isLoaded() const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bool createBuffer(const void* data, GLsizei Size, GLenum Type);
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bool uploadData(const void* data, GLsizei Offset, GLsizei Size);
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bool deleteBuffer();
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bool bind();
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		void unbind();
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		GLuint getBuffer() const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		GLsizei getSize() const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		GLenum getType() const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		GLenum getObjectType() const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bool copyFrom(bufferObject* Other, GLintptr Offset1, GLintptr Offset2, GLsizeiptr Size);
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bufferObject& operator = (const bufferObject& Other);

    private:
        GLenum type;
        GLenum objectType;
        bool loaded;
        // VBO pointer
        GLuint buffer;
        // Size of buffer
        GLsizei size;
        bool initialized;

        PFNGLGENBUFFERSPROC glGenBuffers;
        PFNGLBINDBUFFERPROC glBindBuffer;
        PFNGLBUFFERDATAPROC glBufferData;
        PFNGLBUFFERSUBDATAPROC glBufferSubData;
        PFNGLDELETEBUFFERSPROC glDeleteBuffers;
        PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData;
    };
};
#endif

