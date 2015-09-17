/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_RANGE
#define FFW_RANGE

/*!
 * @ingroup Math
 * @brief FFW
 */
namespace ffw{
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 *
     * @brief Range iterator
	 */
    template <class T> class rangeIterator{
    public:
        /*!
		 * @memberof rangeIterator
		 * @ingroup Math
		 * @inline
		 */
        rangeIterator(T Value);
        /*!
		 * @memberof rangeIterator
		 * @ingroup Math
		 * @inline
		 */
        bool operator != (const rangeIterator& Other) const;
        /*!
		 * @memberof rangeIterator
		 * @ingroup Math
		 * @inline
		 */
        const T& operator*() const;
        /*!
		 * @memberof rangeIterator
		 * @ingroup Math
		 * @inline
		 */
        rangeIterator& operator ++ ();

    private:
        T value;
    };

    /*!
	 * @memberof ffw
	 * @ingroup Math
	 *
     * @brief Range for 'for' loop
	 */
	template <class T> class range{
    public:
        /*!
		 * @memberof range
		 * @ingroup Math
		 * @inline
		 */
        range(T Min, T Max);
        /*!
		 * @memberof range
		 * @ingroup Math
		 * @inline
		 */
        range(T Max);
        /*!
		 * @memberof range
		 * @ingroup Math
		 * @inline
		 */
        rangeIterator<T> begin();
        /*!
		 * @memberof range
		 * @ingroup Math
		 * @inline
		 */
        rangeIterator<T> end();

    private:
        T min;
        T max;
    };
};

#include "range.inl"

#endif
