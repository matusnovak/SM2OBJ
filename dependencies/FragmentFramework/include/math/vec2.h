/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_VEC2
#define FFW_VEC2

/*!
	@ingroup Math
*/
namespace ffw {
    /*!
		@memberof ffw
		@ingroup Math

        @brief 2D vector
	*/
    template <class T> struct vec2 {
    public:
        /*!
			@memberof vec2
			@ingroup Math

            @brief X component
		*/
        T x;
        /*!
			@memberof vec2
			@ingroup Math

            @brief Y component
		*/
        T y;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Constructor

            @details Sets all components to zero.
		*/
        vec2();
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Constructor

            @param [in] X Component X
            @param [in] Y Component Y
		*/
        vec2(T X, T Y);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Constructor

            @param [in] Value Value of all components
		*/
        vec2(T Value);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Constructor

            @details Copies value from another vector.

            @param [in] V Another vector
		*/
        vec2(const vec2<T>& V);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Constructor

            @param [in] List Bracket list

            @code
            ffw::vec2<float> v{1.0f, 1.5f};
            @endcode
		*/
        vec2(std::initializer_list<T> List);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Sets the vector

            @param [in] X Component X
            @param [in] Y Component Y
		*/
        void set(T X, T Y);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Sets the vector

            @details Sets same value for all component.

            @param [in] Value Value of all components
		*/
        void set(T Value);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Sets the vector

            @details Copies value from another vector.

            @param [in] V Another vector
		*/
        void set(const vec2<T>& V);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Sets the vector

            @param [in] List Bracket list

            @code
            ffw::vec2<float> v;
            v.set({1.0f, 1.5f});
            @endcode
		*/
        void set(std::initializer_list<T> List);
		/*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Returns negative value

            @details Returns negative value of vector if used as unary minus.

            @return Inversed vector
		*/
        vec2<T> operator - () const;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Assign a value

            @return Reference to object
		*/
        vec2<T>& operator =  (const vec2<T>& V);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Addition

            @return Product of addition
		*/
        vec2<T>  operator +  (const vec2<T>& V) const;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Addition assignment

            @return Reference to object
		*/
        vec2<T>& operator += (const vec2<T>& V);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Subtraction

            @return Product of substraction
		*/
        vec2<T>  operator -  (const vec2<T>& V) const;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Subtraction assignment

            @return Reference to object
		*/
        vec2<T>& operator -= (const vec2<T>& V);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Division

            @return Product of division
		*/
        vec2<T>  operator /  (const vec2<T>& V) const;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Division assignment

            @return Reference to object
		*/
        vec2<T>& operator /= (const vec2<T>& V);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Multiplication

            @return Product of multiplication
		*/
        vec2<T>  operator *  (const vec2<T>& V) const;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Multiplication assignment

            @return Reference to object
		*/
        vec2<T>& operator *= (const vec2<T>& V);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Assign a value

            @return Reference to object
		*/
        vec2<T>& operator =  (const T& Val);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Addition

            @return Product of addition
		*/
        vec2<T>  operator +  (const T& Val) const;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Addition assignment

            @return Reference to object
		*/
        vec2<T>& operator += (const T& Val);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Subtraction

            @return Product of substraction
		*/
        vec2<T>  operator -  (const T& Val) const;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Subtraction assignment

            @return Reference to object
		*/
        vec2<T>& operator -= (const T& Val);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Division

            @return Product of division
		*/
        vec2<T>  operator /  (const T& Val) const;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Division assignment

            @return Reference to object
		*/
        vec2<T>& operator /= (const T& Val);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Multiplication

            @return Product of multiplication
		*/
        vec2<T>  operator *  (const T& Val) const;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Multiplication assignment

            @return Reference to object
		*/
        vec2<T>& operator *= (const T& Val);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Checks if two vectors are not equal

            @return True if not equal
		*/
        bool operator != (const vec2<T>& V) const;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Checks if two vectors are equal

            @return True if equal
		*/
        bool operator == (const vec2<T>& V) const;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Roatates the vector

            @param [in] Deg Degrees

            @return Reference to object
		*/
        vec2<T>& rotate(const float Deg);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Rotates the vector

            @param [in] Rad Radians

            @return Reference to object
		*/
        vec2<T>& rotateRad(const float Rad);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Normalizes the vector to length of 1.0

            @return Reference to object
		*/
        vec2<T>& normalize();
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Scales the vector by given value

            @param [in] Val Scale

            @return Reference to object
		*/
        vec2<T>& scale(const T Val);
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Returns length of vector

            @return Length of vector
		*/
        float length() const;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

            @brief Returns squared length of vector

            @return Squared length of vector
		*/
        T lengthSqrd() const;
        /*!
			@memberof vec2
			@ingroup Math
			@inline

			@brief Explicit operator to cast between different data types
		*/
		template <class S> explicit operator vec2<S>() const;
    };

    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec2<float> vec2f;
    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec2<int> vec2i;
    /*!
		@memberof ffw
		@ingroup Math
	*/
    typedef vec2<double> vec2d;
};

#include "vec2.inl"

#endif
