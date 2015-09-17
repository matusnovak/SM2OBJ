/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_MEM_POOL
#define FFW_MEM_POOL

/*!
	@ingroup Math
*/
namespace ffw {
    /*!
		@memberof ffw
		@ingroup Math
	*/
    template <class T> struct memBlock {
        size_t pos;
        size_t size;
    };

    /*!
		@memberof ffw
		@ingroup Math
	*/
    template <class T> class memPool {
    public:
        /*!
            @memberof memPool
            @ingroup Math
        */
        memPool(size_t Increment, size_t Aligment);
        ~memPool();
        /*!
            @memberof memPool
            @ingroup Math
        */
        size_t allocate(size_t Size);
        /*!
            @memberof memPool
            @ingroup Math
        */
        bool release(size_t Ptr);
        /*!
            @memberof memPool
            @ingroup Math
        */
        T* begin();
        /*!
            @memberof memPool
            @ingroup Math
        */
        T* end();

    private:
        size_t getAligned(size_t Value);
        void increaseSize(size_t Min);
        void decreaseSize(size_t Max);

        T* buffer;
        size_t bufferSize;
        size_t increment;
        size_t aligment;
        std::vector<memBlock<T>> blocks;
    };
};

#include "memPool.inl"

#endif
