/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_VEC4
#define FFW_VEC4

/*!
	@ingroup Math
*/
namespace ffw {
    /*!
		@memberof ffw
		@ingroup Math
		
		@brief 4D vector
	*/
    template <class T> struct vec4 {
    public:
        /*!
			@memberof vec4
			@ingroup Math
			
			@brief X component
		*/
        T x;
        /*!
			@memberof vec4
			@ingroup Math
			
			@brief Y component
		*/
        T y;
        /*!
			@memberof vec4
			@ingroup Math
			
			@brief Z component
		*/
        T z;
        /*!
			@memberof vec4
			@ingroup Math
			
			@brief W component
		*/
        T w;
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Constructor
            
            @details Sets all components to zero.
		*/
        vec4();
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Constructor
            
            @param [in] X Component X
            @param [in] Y Component Y
			@param [in] Z Component Z
			@param [in] W Component W
		*/
        vec4(T X, T Y, T Z, T W);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Constructor
            
            @param [in] Value Value of all components
		*/
        vec4(T Value);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Constructor
            
            @details Copies value from another vector.
            
            @param [in] V Another vector
		*/
        vec4(const vec4<T>& V);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Constructor
            
            @param [in] List Bracket list
            
            @code
            ffw::vec4<float> v{1.0f, 1.5f, 0.2f, -9.0f};
            @endcode
		*/
        vec4(std::initializer_list<T> List);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Sets the vector
            
            @param [in] X Component X
            @param [in] Y Component Y
			@param [in] Z Component Z
			@param [in] W Component W
		*/
        void set(T X, T Y, T Z, T W);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Sets the vector
            
            @details Sets same value for all component.
            
            @param [in] Value Value of all components
		*/
        void set(T Value);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Sets the vector
            
            @details Copies value from another vector.
            
            @param [in] V Another vector
		*/
        void set(const vec4<T>& V);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Sets the vector
            
            @param [in] List Bracket list
            
            @code
            ffw::vec4<float> v;
            v.set({1.0f, 1.5f, 0.2f, -9.0f});
            @endcode
		*/
        void set(std::initializer_list<T> List);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Subtraction
            
            @details Returns negative value of vector if used as unary minus.
            
            @return Negative vector
		*/
        vec4<T>  operator - () const;
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Assign a value
            
            @return Reference to object
		*/
        vec4<T>& operator =  (const vec4<T>& V);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Addition
            
            @return Product of addition
		*/
        vec4<T>  operator +  (const vec4<T>& V) const;
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Addition assignment
            
            @return Reference to object
		*/
        vec4<T>& operator += (const vec4<T>& V);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Subtraction
            
            @return Product of substraction
		*/
        vec4<T>  operator -  (const vec4<T>& V) const;
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Subtraction assignment
            
            @return Reference to object
		*/
        vec4<T>& operator -= (const vec4<T>& V);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Division
            
            @return Product of division
		*/
        vec4<T>  operator /  (const vec4<T>& V) const;
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Division assignment
            
            @return Reference to object
		*/
        vec4<T>& operator /= (const vec4<T>& V);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Multiplication
            
            @return Product of multiplication
		*/
        vec4<T>  operator *  (const vec4<T>& V) const;
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Multiplication assignment
            
            @return Reference to object
		*/
        vec4<T>& operator *= (const vec4<T>& V);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			 @brief Assign a value
            
            @return Reference to object
		*/
        vec4<T>& operator =  (const T& Val);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Addition
            
            @return Product of addition
		*/
        vec4<T>  operator +  (const T& Val) const;
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Addition assignment
            
            @return Reference to object
		*/
        vec4<T>& operator += (const T& Val);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Subtraction
            
            @return Product of substraction
		*/
        vec4<T>  operator -  (const T& Val) const;
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Subtraction assignment
            
            @return Reference to object
		*/
        vec4<T>& operator -= (const T& Val);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Division
            
            @return Product of division
		*/
        vec4<T>  operator /  (const T& Val) const;
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Division assignment
            
            @return Reference to object
		*/
        vec4<T>& operator /= (const T& Val);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Multiplication
            
            @return Product of multiplication
		*/
        vec4<T>  operator *  (const T& Val) const;
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Multiplication assignment
            
            @return Reference to object
		*/
        vec4<T>& operator *= (const T& Val);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Checks if two vectors are not equal
            
            @return True if not equal
		*/
        bool operator != (const vec4<T>& V) const;
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Checks if two vectors are equal
            
            @return True if equal
		*/
        bool operator == (const vec4<T>& V) const;
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Normalizes the vector to length of 1.0
            
            @return Reference to object
		*/
        vec4<T>& normalize();
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Scales the vector by given value
            
            @param [in] Val Scale
            
            @return Reference to object
		*/
        vec4<T>& scale(const T Val);
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Returns length of vector
            
            @return Length of vector
		*/
        float length() const;
        /*!
			@memberof vec4
			@ingroup Math
			@inline
			
			@brief Returns squared length of vector
            
            @return Squared length of vector
		*/
        T lengthSqrd() const;
    };
};
#endif

#include "vec4.inl"

