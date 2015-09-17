/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_VEC4
#define FFW_VEC4

/*!
 * @ingroup Math
 * @brief FFW
 */
namespace ffw {
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 *
     * @brief 4D vector
	 */
    template <class T> struct vec4 {
    public:
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 *
         * @brief X component
		 */
        T x;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 *
         * @brief Y component
		 */
        T y;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 *
         * @brief Z component
		 */
        T z;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 *
         * @brief W component
		 */
        T w;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 * @details X, Y, Z, and W are set to zero.
		 */
        vec4();
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 */
        vec4(T X, T Y, T Z, T W);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 * @details X, Y, Z, and W are set to the same value.
		 */
        vec4(T Value);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 */
        vec4(const vec4<T>& V);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 * @details Initializes vector from bracket list, for example:
		 *
		 * ```C++
		 * ffw::vec4f v ({0.707f, 3.14f, 1.414f, 92.0f});
		 * // Or
		 * ffw::vec4f v {0.707f, 3.14f, 1.414f, 92.0f};
		 * // Or
		 * ffw::vec4f v = {0.707f, 3.14f, 1.414f, 92.0f};
		 * ```
		 */
        vec4(std::initializer_list<T> List);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the vector
		 */
        void set(T X, T Y, T Z, T W);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 
		 * @inline
		 *
         * @brief Sets the vector
		 * @details X, Y, Z, and W are set to the same value.
		 */
        void set(T Value);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the vector
		 */
        void set(const vec4<T>& V);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the vector
		 */
        void set(std::initializer_list<T> List);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>  operator - () const;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>& operator =  (const vec4<T>& V);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>  operator +  (const vec4<T>& V) const;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>& operator += (const vec4<T>& V);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>  operator -  (const vec4<T>& V) const;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>& operator -= (const vec4<T>& V);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 
		 * @inline
		 */
        vec4<T>  operator /  (const vec4<T>& V) const;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>& operator /= (const vec4<T>& V);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>  operator *  (const vec4<T>& V) const;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>& operator *= (const vec4<T>& V);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>& operator =  (const T& Val);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>  operator +  (const T& Val) const;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>& operator += (const T& Val);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>  operator -  (const T& Val) const;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>& operator -= (const T& Val);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>  operator /  (const T& Val) const;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>& operator /= (const T& Val);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>  operator *  (const T& Val) const;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        vec4<T>& operator *= (const T& Val);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        bool operator != (const vec4<T>& V) const;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 */
        bool operator == (const vec4<T>& V) const;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Normalizes the vector
		 */
        vec4<T>& normalize();
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Scales the vector by given value
		 */
        vec4<T>& scale(const T Val);
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Returns the length of the vector
		 */
        float length() const;
        /*!
		 * @memberof vec4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Returns the squared length of the vector
		 */
        T lengthSqrd() const;
        /*!
		 * @memberof vec4
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
		 * ffw::vec4<int> vi (21, 42, 41, 92);
		 * ffw::vec4<float> vf = vi;
		 * 
		 * // The right way:
		 * ffw::vec4<int> vi (21, 42, 41, 92);
		 * ffw::vec4<float> vf = static_cast<ffw::vec4<float>>(vi);
		 * ```
		 */
		template <class S> explicit operator vec4<S>() const;
    };
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 */
    typedef vec4<float> vec4f;
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 */
    typedef vec4<int> vec4i;
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 */
    typedef vec4<double> vec4d;
};

#include "vec4.inl"

#endif
