/*** This file is part of FragmentFramework project ***/

#ifndef FFW_VEC3
#define FFW_VEC3

/*!
 * @ingroup Math
 * @brief FFW
 */
namespace ffw {
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 *
     * @brief 3D vector
	 */
    template <class T> struct vec3 {
    public:
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 *
         * @brief X component
		 */
        T x;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 *
         * @brief Y component
		 */
        T y;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 *
         * @brief Z component
		 */
        T z;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 *
         * @brief Constructor
		 */
        vec3();
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 */
        vec3(T X, T Y, T Z);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 * @details X, Y, and Z are set to the same value.
		 */
        vec3(T Value);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 */
        vec3(const vec3<T>& V);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 * @details Initializes vector from bracket list, for example:
		 *
		 * ```C++
		 * ffw::vec3f v ({0.707f, 3.14f, 1.414f});
		 * // Or
		 * ffw::vec3f v {0.707f, 3.14f, 1.414f};
		 * // Or
		 * ffw::vec3f v = {0.707f, 3.14f, 1.414f};
		 * ```
		 */
        vec3(std::initializer_list<T> List);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the vector
		 */
        void set(T X, T Y, T Z);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the vector
		 */
        void set(T Value);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the vector
		 */
        void set(const vec3<T>& V);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the vector
		 */
        void set(std::initializer_list<T> List);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 */
        vec3<T> operator - () const;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 */
        vec3<T>& operator =  (const vec3<T>& V);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec3<T>  operator +  (const vec3<T>& V) const;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 */
        vec3<T>& operator += (const vec3<T>& V);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec3<T>  operator -  (const vec3<T>& V) const;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 */
        vec3<T>& operator -= (const vec3<T>& V);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec3<T>  operator /  (const vec3<T>& V) const;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 */
        vec3<T>& operator /= (const vec3<T>& V);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec3<T>  operator *  (const vec3<T>& V) const;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 */
        vec3<T>& operator *= (const vec3<T>& V);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 */
        vec3<T>& operator =  (const T& Val);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec3<T>  operator +  (const T& Val) const;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 */
        vec3<T>& operator += (const T& Val);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec3<T>  operator -  (const T& Val) const;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 */
        vec3<T>& operator -= (const T& Val);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec3<T>  operator /  (const T& Val) const;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 */
        vec3<T>& operator /= (const T& Val);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        vec3<T>  operator *  (const T& Val) const;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 */
        vec3<T>& operator *= (const T& Val);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        bool operator != (const vec3<T>& V) const;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        bool operator == (const vec3<T>& V) const;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Rotates the vector by degrees in given axis.
		 */
        vec3<T>& rotateByAxis(const float Deg, vec3<T> Axis);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Rotates the vector by degrees in X axis.
		 */
        vec3<T>& rotateX(const float Deg);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Rotates the vector by degrees in Y axis.
		 */
        vec3<T>& rotateY(const float Deg);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Rotates the vector by degrees in Z axis.
		 */
        vec3<T>& rotateZ(const float Deg);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Rotates the vector by radians in X axis.
		 */
        vec3<T>& rotateXRad(const float Rad);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Rotates the vector by radians in Y axis.
		 */
        vec3<T>& rotateYRad(const float Rad);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Rotates the vector by radians in Z axis.
		 */
        vec3<T>& rotateZRad(const float Rad);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Rotates the vector by quaternion
		 */
        vec3<T>& rotateByQuaternion(const ffw::quat<T>& Q);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Normalizes the vector
		 */
        vec3<T>& normalize();
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Scales the vector by given value
		 */
        vec3<T>& scale(const T Val);
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Returns the length of the vector
		 */
        float length() const;
        /*!
		 * @memberof vec3
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Returns the squared length of the vector
		 */
        T lengthSqrd() const;
        /*!
		 * @memberof vec3
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
		 * ffw::vec3<int> vi (21, 42, 92);
		 * ffw::vec3<float> vf = vi;
		 * 
		 * // The right way:
		 * ffw::vec3<int> vi (21, 42, 92);
		 * ffw::vec3<float> vf = static_cast<ffw::vec3<float>>(vi);
		 * ```
		 */
		template <class S> explicit operator vec3<S>() const;
    };
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 */
    typedef vec3<float> vec3f;
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 */
    typedef vec3<int> vec3i;
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 */
    typedef vec3<double> vec3d;
};

#include "vec3.inl"

#endif

