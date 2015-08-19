/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_BUFFER_OBJECT_POOL
#define FFW_BUFFER_OBJECT_POOL

#include "../config.h"
#include "../gl/extensions.hpp"
#include <vector>

/*!
    @ingroup Graphics
*/
namespace ffw {
    class renderContext;
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
        bool init(const renderContext* Context, unsigned int ObjectType, int Increment);
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        bool isCreated() const;
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        int allocate(int Size);
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        bool release(int Offset);
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        bool uploadData(const void* Data, int Offset, int Size);
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        bool destroy();
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        void bind() const;
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        void unbind() const;
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        unsigned int getBuffer() const;
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        int getSize() const;
        /*!
            @memberof bufferObjectPool
            @ingroup Graphics

        */
        unsigned int getObjectType() const;

        struct block {
            int pos;
            int size;
        };

    private:
        int getAligned(int Value);
        void increaseSize(int Min);
        void decreaseSize(int Max);

        void createThisBuffer(unsigned int* Ptr, GLenum Type, int Size);
        void deleteThisBuffer(unsigned int* Ptr);
        void copyThisBuffer(unsigned int From, unsigned int To, int FromOffset, int ToOffset, int Size);
        void clearMemory(unsigned int Ptr, int Pos, int Size);

        unsigned int objectType;
        bool loaded;
        unsigned int buffer;
        int bufferSize;
        int increment;
        bool initialized;

        std::vector<block> blocks;
        const glExtensions* gl;
    };
};
#endif

