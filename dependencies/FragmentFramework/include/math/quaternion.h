/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_quat
#define FFW_quat

/*!
 * @ingroup Math
 * @brief FFW
 */
namespace ffw {
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 *
     * @brief Quaternion
	 */
    template <class T> struct quat {
    public:
        /*!
		 * @memberof quat
		 * @ingroup Math
         * @brief X component
		 */
        T x;
        /*!
		 * @memberof quat
		 * @ingroup Math
         * @brief Y component
		 */
        T y;
        /*!
		 * @memberof quat
		 * @ingroup Math
         * @brief Z component
		 */
        T z;
        /*!
		 * @memberof quat
		 * @ingroup Math
         * @brief W component
		 */
        T w;
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 * @details Sets the quaternion to default rotation [0.0f, 0.0f, 0.0f, 1.0f]
		 */
        quat();
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 */
        quat(T X, T Y, T Z, T W);
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 * @details Copies value from another quaternion
		 */
        quat(const quat<T>& Quat);
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the quaternion
		 */
        void set(T X, T Y, T Z, T W);
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the quaternion
		 */
        void set(const quat<T>& Quat);
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 *
         * @brief Rotates the quat by degress in given axis
		 * @param Deg - Degrees
		 * @param X - axis of rotation
		 * @param Y - axis of rotation
		 * @param Z - axis of rotation
		 */
        quat& rotate(T Deg, T X, T Y, T Z);
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 *
         * @brief Rotates the quat by radians in given axis
		 * @param Deg - Degrees
		 * @param X - axis of rotation
		 * @param Y - axis of rotation
		 * @param Z - axis of rotation
		 */
        quat& rotateRad(T Rad, T X, T Y, T Z);
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        quat operator - () const;
        /*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        quat  operator * (const quat& Quat) const;
        /*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 */
        quat& operator *= (const quat& Quat);
        /*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        quat  operator * (T Value) const;
        /*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 */
        quat& operator *= (T Value);
        /*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        quat  operator + (const quat& Quat) const;
        /*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 */
        quat& operator += (const quat& Quat);
        /*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        quat  operator - (const quat& Quat) const;
        /*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 */
        quat& operator -= (const quat& Quat);
        /*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        quat  operator / (T Value) const;
        /*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 */
        quat& operator /= (T Value);
        /*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Normalizes the quaternion to length of 1.0
		 */
        void normalize();
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Gets the euler angles of the quaterion
		 * @details Parameters can be NULL
		 */
        void getEuler(T* Roll, T* Pitch, T* Yaw) const;
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Returns the length of the quaternion
		 */
        float length() const;
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Returns the squared length of the quaternion
		 */
        float lengthSqrd() const;
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Returns conjuagate of the quaternion
		 * @details The quaternion is not modified by this function.
		 */
		quat getConjugate() const;
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Returns inversed quaternion
		 * @details The quaternion is not modified by this function.
		 */
		quat getInversed() const;
		/*!
		 * @memberof quat
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Inverses the quaternion
		 */
		quat& inverse();
    };
	typedef quat<float> quatf;
	typedef quat<double> quatd;
};

#include "quaternion.inl"

#endif
