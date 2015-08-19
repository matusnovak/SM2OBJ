/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_QUATERNION
#define FFW_QUATERNION

/*!
	@ingroup Math
*/
namespace ffw {
    /*!
		@memberof ffw
		@ingroup Math

		@brief Quaternion
	*/
    struct quaternion {
    public:
        /*!
			@memberof quaternion
			@ingroup Math

			@brief X component
		*/
        float x;
        /*!
			@memberof quaternion
			@ingroup Math

			@brief Y component
		*/
        float y;
        /*!
			@memberof quaternion
			@ingroup Math

			@brief Z component
		*/
        float z;
        /*!
			@memberof quaternion
			@ingroup Math

			@brief W component
		*/
        float w;
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Constructor

            @details Sets the quaternion to (0.0f, 0.0f, 0.0f, 1.0f)
		*/
        quaternion();
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Constructor

            @param [in] X Component X
            @param [in] Y Component Y
			@param [in] Z Component Z
			@param [in] W Component W
		*/
        quaternion(float X, float Y, float Z, float W);
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Constructor

            @details Copies value from another quaternion.

            @param [in] V Another quaternion
		*/
        quaternion(const quaternion& Quat);
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Sets the quaternion

            @param [in] X Component X
            @param [in] Y Component Y
			@param [in] Z Component Z
			@param [in] W Component W
		*/
        void set(float X, float Y, float Z, float W);
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Sets the quaternion

            @details Copies value from another quaternion.

            @param [in] V Another quaternion
		*/
        void set(const quaternion& Quat);
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Rotates the quaternion by degress

			@details Quaternion is automaticaly normalized after this operation!

			@param [in] Deg Degrees
			@param [in] X X component of axis of rotation
			@param [in] Y Y component of axis of rotation
			@param [in] Z Z component of axis of rotation

			@return Reference to object
		*/
        quaternion& rotate(float Deg, float X, float Y, float Z);
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Rotates the quaternion by radians

			@details Quaternion is automaticaly normalized after this operation!

			@param [in] Rad Radians
			@param [in] X X component of axis of rotation
			@param [in] Y Y component of axis of rotation
			@param [in] Z Z component of axis of rotation

			@return Reference to object
		*/
        quaternion& rotateRad(float Rad, float X, float Y, float Z);
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

            @brief Unary minus

            @return Quaternion
		*/
        quaternion operator - () const;
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Multiplication

			@return Product of multiplication
		*/
        quaternion  operator * (const quaternion& Quat) const;
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Multiplication assigment

			@return Reference to object
		*/
        quaternion& operator *= (const quaternion& Quat);
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Multiplication by scalar

			@return Product of multiplication
		*/
        quaternion  operator * (float Value) const;
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Multiplication assigment by scalar

			@return Reference to object
		*/
        quaternion& operator *= (float Value);
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Addition

			@return Product of addition
		*/
        quaternion  operator + (const quaternion& Quat) const;
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Addition assigment

			@return Reference to object
		*/
        quaternion& operator += (const quaternion& Quat);
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Subtraction

			@return Product of substraction
		*/
        quaternion  operator - (const quaternion& Quat) const;
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Subtraction assigment

			@return Reference to object
		*/
        quaternion& operator -= (const quaternion& Quat);
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Division by scalar

			@return Product of multiplication
		*/
        quaternion  operator / (float Value) const;
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Division assigment by scalar

			@return Reference to object
		*/
        quaternion& operator /= (float Value);
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Normalizes the quaternion
		*/
        void normalize();
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Get euler angles of quaterion

			@param [out] Roll Roll in degrees
			@param [out] Pitch Pitch in degrees
			@param [out] Yaw Yaw in degrees
		*/
        void getEuler(float* Roll, float* Pitch, float* Yaw) const;
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Returns length of quaternion
		*/
        float getLength() const;
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Returns squared length of quaternion
		*/
        float getLengthSquared() const;
        /*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Returns conjugate
		*/
		quaternion getConjugate() const;
		/*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Returns inversed quaternion
		*/
		quaternion getInversed() const;
		/*!
			@memberof quaternion
			@ingroup Math
			@inline

			@brief Inverses this quaternion

			@return Reference to object
		*/
		quaternion& inverse();
    };
};

#include "quaternion.inl"

#endif
