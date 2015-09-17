/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_mat4x4
#define FFW_mat4x4

/*!
 * @ingroup Math
 * @brief FFW
 */
namespace ffw {
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 *
     * @brief 4x4 Matrix
	 */
    template <class T> struct mat4x4 {
    public:
        /*!
		 * @memberof mat4x4
		 * @ingroup Math
         * @brief Array that holds all indices in
		 * @details Indices are layed out in same way as OpenGL matrices.
		 * This ensures that there is no confusion while using the shaders.
		 * 
		 * 12th, 13th, and 14th element holds the XYZ transformation (counting from zero).
		 */
		T ptr[16];
        /*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 * @details Creates an identity matrix (0th, 5th, 10th, and 15th elements
		 * are set to 1.0 while rest of them are set to 0.0)
		 */
        mat4x4();
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 */
        mat4x4(T xx, T yx, T zx, T wx, T xy, T yy, T zy, T wy, T xz, T yz, T zz, T wz, T xw, T yw, T zw, T ww);
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 * @details Creates an identity matrix (0th, 5th, 10th, and 15th elements
		 * are set to the specified value while rest of them are set to 0.0)
		 */
        mat4x4(T Val);
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 * @details Creates an matrix from initializer list length of 16 elements.
		 */
        mat4x4(std::initializer_list<T> List);
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the matrix
		 */
        void set(T xx, T yx, T zx, T wx, T xy, T yy, T zy, T wy, T xz, T yz, T zz, T wz, T xw, T yw, T zw, T ww);
        /*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the matrix
		 * @details Sets the matrix from array of 16 elements.
		 */
        void set(T m[16]);
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the matrix
		 * @details Constructs identity matrix where 0th, 5th, 10th, and 15th elements
		 * are set to the value specified while rest of the elements are set to zero.
		 */
        void set(T Val);
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Sets the matrix
		 * @details Sets the matrix from initializer list length of 16 elements.
		 */
        void set(std::initializer_list<T> List);
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 *
         * @brief Returns the pointer to array of indices.
		 */
        T* getPtr();
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @brief Returns the pointer to array of indices.
		 * @details Const version.
		 */
		const T* getPtr() const;
        /*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @brief Copies value from another matrix
		 */
        mat4x4<T>& operator = (const mat4x4<T>& m);
        /*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @details Returns a product of two matrices
		 */
        mat4x4<T> operator * (const mat4x4<T>& m) const;
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @details Multiplies this matrix with another
		 */
        mat4x4<T>& operator *= (const mat4x4<T>& m);
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @details Returns a product of matrix x vector multiplication
		 */
		template <class S> vec4<S> operator * (const vec4<S>& V) const;
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @details Returns a product of matrix x vector multiplication.
		 * Made for 3D vectors where bottom row of the matrix gets ignored.
		 */
		template <class S> vec3<S> operator * (const vec3<S>& V) const;
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @brief Access invidual indices
		 */
        T& operator [] (int x);
        /*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @brief Access invidual indices
		 * @details Const version
		 */
        const T& operator [] (int x) const;
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @brief Rotates the matrix by quaternion
		 */
		mat4x4<T>& rotate(const quat<T>& Q);
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @brief Translated the matrix in given direction
		 */
		mat4x4<T>& translate(T X, T Y, T Z);
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @brief Scales the matrix
		 */
		mat4x4<T>& scale(T X, T Y, T Z);
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @brief Transpose matrix
		 */
		mat4x4<T>& transpose();
		/*!
		 * @memberof mat4x4
		 * @ingroup Math
		 * @inline
		 * @const
		 *
         * @brief Inverse matrix
		 */
		mat4x4<T>& inverse();
    };
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 */
	typedef mat4x4<float> mat4x4f;
};

#include "mat4.inl"

#endif

