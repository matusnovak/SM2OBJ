/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_RING_BUFFER
#define FFW_RING_BUFFER

/*!
 * @ingroup Math
 * @brief FFW
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 *
     * @brief Thread safe ring buffer
	 */
	template<class T> class ringBuffer {
	public:
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 * @name ringBuffer
		 *
         * @brief Constructor
		 * @details Initializes the ring with no elements.
		 * You will need to call function crate(size_t) to allocate space.
		 */
		ringBuffer();
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 * @name ringBuffer
		 *
         * @brief Constructor
		 * @details Initializes the ring with given size.
		 */
		ringBuffer(size_t Size);
		virtual ~ringBuffer();
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 *
         * @brief Returns back element
		 */
		T* back();
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 *
         * @brief Allocates elements
		 */
		void create(size_t Size);
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 *
         * @brief Adds new element to the tail
		 * @details Returns false if ring is full or if ring has not
		 * been created.
		 */
		bool push(const T& Item);
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 *
         * @brief Returns element from the head
		 * @details Returns false if there is no element to pop.
		 */
		bool pop(T* Item);
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @brief Returns size of whole ring
		 */
		size_t getRange() const;
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @brief Returns current number of elements
		 */
		size_t getSize() const;
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 * @const
		 * 
         * @brief Checks if ring is full
		 */
		bool isFull() const;
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @brief Checks if ring is empty
		 */
		bool isEmpty() const;
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 * @const
		 * 
         * @brief Returns the index of the tail
		 */
		size_t getTail() const;
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @brief Returns the index of the head
		 */
		size_t getHead() const;
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 *
         * @brief Cleares the buffer and sets the range to zero
		 * @details To reuse the ring, create(size_t) must be called.
		 */
		void clear();
		/*!
		 * @memberof ringBuffer
		 * @ingroup Math
		 * @inline
		 *
         * @brief Resets the tail and head, does not affect the buffer size
		 */
		void reset();
	private:
		std::atomic<size_t> head;
		std::atomic<size_t> tail;
		std::vector<T> elements;
		size_t size;
	};
};

#include "ringBuffrt.inl"

#endif