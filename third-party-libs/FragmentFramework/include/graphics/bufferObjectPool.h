/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_BUFFER_OBJECT_POOL
#define FFW_BUFFER_OBJECT_POOL

#include "../dll.h"
#include <GL/glfw3.h>
#include <GL/glext.h>
#include <vector>
#include <iostream>

/*!
    @ingroup Graphics
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup Graphics
    */
	class FFW_API bufferObjectPool {
    public:

		bufferObjectPool();
        ~bufferObjectPool();
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        bool init(GLenum ObjectType, GLsizei Increment);
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        bool isLoaded() const;
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        GLsizei allocate(GLsizei Size);
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        bool release(GLsizei Offset);
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        bool uploadData(const void* Data, GLsizei Offset, GLsizei Size);
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        bool deleteBuffer();
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        void bind();
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        void unbind();
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        GLuint getBuffer() const;
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        GLsizei getSize() const;
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        GLenum getObjectType() const;

        struct block {
            GLsizei pos;
            GLsizei size;
        };

    private:
        //bool createBuffer(GLsizei Size);
        GLsizei getAligned(GLsizei Value);
        void increaseSize(GLsizei Min);
        void decreaseSize(GLsizei Max);

        void createThisBuffer(GLuint* Ptr, GLenum Type, GLsizei Size);
        void deleteThisBuffer(GLuint* Ptr);
        void copyThisBuffer(GLuint From, GLuint To, GLsizei FromOffset, GLsizei ToOffset, GLsizei Size);
        void clearMemory(GLuint Ptr, GLsizei Pos, GLsizei Size);

        GLenum objectType;
        bool loaded;
        // IBO pointer
        GLuint buffer;
        // Size of buffer
        GLsizei bufferSize;
        GLsizei increment;
        bool initialized;

        std::vector<block>* blocks;

        PFNGLGENBUFFERSPROC glGenBuffers;
        PFNGLBINDBUFFERPROC glBindBuffer;
        PFNGLBUFFERDATAPROC glBufferData;
        PFNGLBUFFERSUBDATAPROC glBufferSubData;
        PFNGLDELETEBUFFERSPROC glDeleteBuffers;
        PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData;
    };
};
#endif

