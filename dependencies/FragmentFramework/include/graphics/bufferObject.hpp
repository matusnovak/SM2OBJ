/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_BUFFER_OBJECT
#define FFW_BUFFER_OBJECT

#include "../config.h"
#include "../gl/extensions.hpp"

/*!
    @ingroup Graphics
*/
namespace ffw {
	class renderContext;
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
		bool init(const renderContext* Context, unsigned int ObjectType);
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bool isCreated() const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bool createBuffer(const void* Data, int Size, unsigned int Type);
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bool uploadData(const void* Data, int Offset, int Size);
		/*!
            @memberof bufferObject
            @ingroup Graphics

        */
        bool mapBuffer(void** Pointer, unsigned int Access) const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
        bool unmapBuffer() const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bool destroy();
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bool bind() const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		void unbind() const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		unsigned int getBuffer() const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		int getSize() const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		unsigned int getType() const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		unsigned int getObjectType() const;
        /*!
            @memberof bufferObject
            @ingroup Graphics

        */
		bool copyFrom(const bufferObject* Other, ptrdiff_t Offset1, ptrdiff_t Offset2, ptrdiff_t Size);

    private:
        unsigned int type;
        unsigned int objectType;
        bool loaded;
        unsigned int buffer;
        int size;
        bool initialized;

        const glExtensions* gl;
    };
};
#endif

