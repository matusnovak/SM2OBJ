/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_VEC2
#define FFW_VEC2

/*!
 * @ingroup Math
 * @brief FFW
 */
namespace ffw {
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 *
     * @brief 2D vector
	 */
    template <class T> struct vec2 {
    public:
        /*!
		 * @memberof vec2
		 * @ingroup Math
         * @brief X component
		 */
        T x;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 *
         * @brief Y component
		 */
        T y;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 *
         * @brief Constructor
		 * @details Both X and Y are set to zero.
		 */
        vec2();
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 */
        vec2(T X, T Y);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 * @details Both X and Y are set to the same value.
		 */
        vec2(T Value);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 */
        vec2(const vec2<T>& V);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 * @details Initializes vector from bracket list, for example:
		 *
		 * ```C++
		 * ffw::vec2f v ({0.707f, 3.14f});
		 * // Or
		 * ffw::vec2f v {0.707f, 3.14f};
		 * // Or
		 * ffw::vec2f v = {0.707f, 3.14f};
		 * ```
		 */
        vec2(std::initializer_list<T> List);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the vector
		 */
        void set(T X, T Y);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the vector
		 * @details Both X and Y are set to the same value
		 */
        void set(T Value);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the vector
		 */
        void set(const vec2<T>& V);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the vector
		 */
        void set(std::initializer_list<T> List);
		/*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec2<T> operator - () const;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 */
        vec2<T>& operator =  (const vec2<T>& V);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec2<T>  operator +  (const vec2<T>& V) const;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 */
        vec2<T>& operator += (const vec2<T>& V);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec2<T>  operator -  (const vec2<T>& V) const;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 */
        vec2<T>& operator -= (const vec2<T>& V);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec2<T>  operator /  (const vec2<T>& V) const;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 */
        vec2<T>& operator /= (const vec2<T>& V);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec2<T>  operator *  (const vec2<T>& V) const;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 */
        vec2<T>& operator *= (const vec2<T>& V);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 */
        vec2<T>& operator =  (const T& Val);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec2<T>  operator +  (const T& Val) const;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 */
        vec2<T>& operator += (const T& Val);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec2<T>  operator -  (const T& Val) const;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 */
        vec2<T>& operator -= (const T& Val);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec2<T>  operator /  (const T& Val) const;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 */
        vec2<T>& operator /= (const T& Val);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec2<T>  operator *  (const T& Val) const;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 */
        vec2<T>& operator *= (const T& Val);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        bool operator != (const vec2<T>& V) const;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        bool operator == (const vec2<T>& V) const;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Rotates the vector by degrees
		 */
        vec2<T>& rotate(const float Deg);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Rotates the vector by radians
		 */
        vec2<T>& rotateRad(const float Rad);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Normalizes the vector
		 */
        vec2<T>& normalize();
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Scales the vector by given value
		 */
        vec2<T>& scale(const T Val);
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Returns the length of the vector
		 */
        float length() const;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Returns the squared length of the vector
		 */
        T lengthSqrd() const;
        /*!
		 * @memberof vec2
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Explicit cast operator
		 * @details Use this if you want to cast from one type
		 * to another, for example:
		 *
		 * ```C++
		 * // The wrong way, procudes an error:
		 * ffw::vec2<int> vi (21, 42);
		 * ffw::vec2<float> vf = vi;
		 * 
		 * // The right way:
		 * ffw::vec2<int> vi (21, 42);
		 * ffw::vec2<float> vf = static_cast<ffw::vec2<float>>(vi);
		 * ```
		 */
		template <class S> explicit operator vec2<S>() const;
    };
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 */
    typedef vec2<float> vec2f;
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 */
    typedef vec2<int> vec2i;
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 */
    typedef vec2<double> vec2d;
};

#include "vec2.inl"

#endif
