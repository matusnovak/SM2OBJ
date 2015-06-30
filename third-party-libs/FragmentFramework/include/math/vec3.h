/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_VEC3
#define FFW_VEC3

/*!
	@ingroup Math
*/
namespace ffw {
    /*!
		@memberof ffw
		@ingroup Math

		@brief 3D vector
	*/
    template <class T> struct vec3 {
    public:
        /*!
			@memberof vec3
			@ingroup Math

			@brief X component
		*/
        T x;
        /*!
			@memberof vec3
			@ingroup Math

			@brief Y component
		*/
        T y;
        /*!
			@memberof vec3
			@ingroup Math

			@brief Z component
		*/
        T z;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Constructor

			@details Sets all components to zero.
		*/
        vec3();
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Constructor

            @param [in] X Component X
            @param [in] Y Component Y
			@param [in] Z Component Z
		*/
        vec3(T X, T Y, T Z);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Constructor

			@param [in] Value Value of all components
		*/
        vec3(T Value);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Constructor

            @details Copies value from another vector.

            @param [in] V Another vector
		*/
        vec3(const vec3<T>& V);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Constructor

            @param [in] List Bracket list

            @code
            ffw::vec3<float> v{1.0f, 1.5f, 0.2f};
            @endcode
		*/
        vec3(std::initializer_list<T> List);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Sets the vector

            @param [in] X Component X
            @param [in] Y Component Y
			@param [in] Z Component Z
		*/
        void set(T X, T Y, T Z);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Sets the vector

            @details Sets same value for all component.

            @param [in] Value Value of all components
		*/
        void set(T Value);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Sets the vector

            @details Copies value from another vector.

            @param [in] V Another vector
		*/
        void set(const vec3<T>& V);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Sets the vector

            @param [in] List Bracket list

            @code
            ffw::vec3<float> v;
            v.set({1.0f, 1.5f, 0.2f});
            @endcode
		*/
        void set(std::initializer_list<T> List);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Subtraction

            @details Returns negative value of vector if used as unary minus.

            @return Negative vector
		*/
        vec3<T> operator - () const;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Assign a value

            @return Reference to object
		*/
        vec3<T>& operator =  (const vec3<T>& V);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Addition

            @return Product of addition
		*/
        vec3<T>  operator +  (const vec3<T>& V) const;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Addition assignment

            @return Reference to object
		*/
        vec3<T>& operator += (const vec3<T>& V);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Subtraction

            @return Product of substraction
		*/
        vec3<T>  operator -  (const vec3<T>& V) const;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Subtraction assignment

            @return Reference to object
		*/
        vec3<T>& operator -= (const vec3<T>& V);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Division

            @return Product of division
		*/
        vec3<T>  operator /  (const vec3<T>& V) const;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Division assignment

            @return Reference to object
		*/
        vec3<T>& operator /= (const vec3<T>& V);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Multiplication

            @return Product of multiplication
		*/
        vec3<T>  operator *  (const vec3<T>& V) const;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Multiplication assignment

            @return Reference to object
		*/
        vec3<T>& operator *= (const vec3<T>& V);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Assign a value

            @return Reference to object
		*/
        vec3<T>& operator =  (const T& Val);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Addition

            @return Product of addition
		*/
        vec3<T>  operator +  (const T& Val) const;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Addition assignment

            @return Reference to object
		*/
        vec3<T>& operator += (const T& Val);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Subtraction

            @return Product of substraction
		*/
        vec3<T>  operator -  (const T& Val) const;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Subtraction assignment

            @return Reference to object
		*/
        vec3<T>& operator -= (const T& Val);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Division

            @return Product of division
		*/
        vec3<T>  operator /  (const T& Val) const;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Division assignment

            @return Reference to object
		*/
        vec3<T>& operator /= (const T& Val);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Multiplication

            @return Product of multiplication
		*/
        vec3<T>  operator *  (const T& Val) const;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Multiplication assignment

            @return Reference to object
		*/
        vec3<T>& operator *= (const T& Val);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Checks if two vectors are not equal

            @return True if not equal
		*/
        bool operator != (const vec3<T>& V) const;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Checks if two vectors are equal

            @return True if equal
		*/
        bool operator == (const vec3<T>& V) const;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Roatates the vector by given axis

            @param [in] Deg Degrees
			@param [in] Axis Axis of rotation

            @return Reference to object
		*/
        vec3<T>& rotateByAxis(const float Deg, vec3<T> Axis);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Roatates the vector on X axis

            @param [in] Deg Degrees

            @return Reference to object
		*/
        vec3<T>& rotateX(const float Deg);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Roatates the vector on Y axis

            @param [in] Deg Degrees

            @return Reference to object
		*/
        vec3<T>& rotateY(const float Deg);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Roatates the vector on Z axis

            @param [in] Deg Degrees

            @return Reference to object
		*/
        vec3<T>& rotateZ(const float Deg);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Roatates the vector on X axis

            @param [in] Rad Radians

            @return Reference to object
		*/
        vec3<T>& rotateXRad(const float Rad);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Roatates the vector on Y axis

            @param [in] Rad Radians

            @return Reference to object
		*/
        vec3<T>& rotateYRad(const float Rad);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Roatates the vector on Z axis

            @param [in] Rad Radians

            @return Reference to object
		*/
        vec3<T>& rotateZRad(const float Rad);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Roatates the vector by quaternion

            @param [in] Q Quaternion

            @return Reference to object
		*/
        vec3<T>& rotateByQuaternion(const ffw::quaternion& Q);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Normalizes the vector to length of 1.0

            @return Reference to object
		*/
        vec3<T>& normalize();
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Scales the vector by given value

            @param [in] Val Scale

            @return Reference to object
		*/
        vec3<T>& scale(const T Val);
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Returns length of vector

            @return Length of vector
		*/
        float length() const;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Returns squared length of vector

            @return Squared length of vector
		*/
        T lengthSqrd() const;
        /*!
			@memberof vec3
			@ingroup Math
			@inline

			@brief Explicit operator to cast between different data types
		*/
		template <class S> explicit operator vec3<S>() const;
    };

    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec3<float> vec3f;
    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec3<int> vec3i;
    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec3<double> vec3d;
};
#endif

#include "vec3.inl"

