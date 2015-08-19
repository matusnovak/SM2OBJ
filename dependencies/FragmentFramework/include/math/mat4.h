/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_MAT4
#define FFW_MAT4

/*!
	@ingroup Math
*/
namespace ffw {
    /*!
		@memberof ffw
		@ingroup Math
	*/
    struct mat4 {
    public:
        float ptr[16];
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        mat4();
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        mat4(float xx, float yx, float zx, float wx, float xy, float yy, float zy, float wy, float xz, float yz, float zz, float wz, float xw, float yw, float zw, float ww);
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        mat4(float Val);
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        mat4(std::initializer_list<float> List);
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        void set(float xx, float yx, float zx, float wx, float xy, float yy, float zy, float wy, float xz, float yz, float zz, float wz, float xw, float yw, float zw, float ww);
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        void set(float m[16]);
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        void set(float Val);
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        void set(std::initializer_list<float> List);
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        float* getMatrix();
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        mat4&  operator =  (const mat4& m);
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        mat4   operator *  (const mat4& m) const;
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        mat4&  operator *= (const mat4& m);
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
		template <class T> vec4<T> operator * (const vec4<T>& V) const;
		/*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
		template <class T> vec3<T> operator * (const vec3<T>& V) const;
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        float& operator [] (int x);
        /*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
        const float& operator [] (int x) const;
		/*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
		mat4& rotate(const quaternion& Q);
		/*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
		mat4& translate(float X, float Y, float Z);
		/*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
		mat4& scale(float X, float Y, float Z);
		/*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
		mat4& transpose();
		/*!
			@memberof mat4
			@ingroup Math
			@inline
		*/
		mat4& inverse();
    };
};

#include "mat4.inl"

#endif

