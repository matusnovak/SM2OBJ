/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_RANGE
#define FFW_RANGE
/*!
	@ingroup Math
*/
namespace ffw{
    /*!
		@memberof ffw
		@ingroup Math
	*/
    template <class T> class rangeIterator{
    public:
        /*!
            @memberof rangeIterator
            @ingroup Math
        */
        rangeIterator(T Value);
        /*!
            @memberof rangeIterator
            @ingroup Math
        */
        bool operator != (const rangeIterator& Other) const;
        /*!
            @memberof rangeIterator
            @ingroup Math
        */
        const T& operator*() const;
        /*!
            @memberof rangeIterator
            @ingroup Math
        */
        rangeIterator& operator ++ ();

    private:
        T value;
    };

    /*!
		@memberof ffw
		@ingroup Math
	*/
	template <class T> class range{
    public:
        /*!
            @memberof range
            @ingroup Math
        */
        range(T Min, T Max);
        /*!
            @memberof range
            @ingroup Math
        */
        range(T Max);
        /*!
            @memberof range
            @ingroup Math
        */
        rangeIterator<T> begin();
        /*!
            @memberof range
            @ingroup Math
        */
        rangeIterator<T> end();

    private:
        T min;
        T max;
    };
};

#include "range.inl"

#endif
