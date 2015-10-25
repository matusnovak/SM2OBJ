/*** This file is part of FragmentFramework project ***/

#ifndef FFW_MEM_POOL
#define FFW_MEM_POOL

namespace ffw {
    template <class T> struct memBlock {
        size_t pos;
        size_t size;
    };

    template <class T> class memPool {
    public:
        memPool(size_t Increment, size_t Aligment);
        ~memPool();
        size_t allocate(size_t Size);
        bool release(size_t Ptr);
        T* begin();
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
