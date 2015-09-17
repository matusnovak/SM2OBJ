/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_BASE_FUNCTIONS
#define FFW_BASE_FUNCTIONS

namespace ffw{
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Linear interpolation
	 *  
	 * @param A - first value
	 * @param B - second value
	 * @param Weight Ratio
	 */
    template <class T> T lerp(const T& A, const T& B, float Weight);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Returns dot product of two vectors
	 * 
	 * @param V1 - first vector
	 * @param V2 - second vector
	 */
    template <class T> float dot(const vec2<T>& V1, const vec2<T>& V2);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Returns dot product of two vectors
	 *  
	 * @param V1 - first vector
	 * @param V2 - second vector
	 */
    template <class T>  float dot(const vec3<T>& V1, const vec3<T>& V2);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Returns cross product of two vectors
	 *  
	 * @param V1 - first vector
	 * @param V2 - second vector
	 */
    template <class T> vec3<T> cross(const vec3<T>& V1, const vec3<T>& V2);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Normalizes a vector
	 *  
	 * @param V - input vector
	 */
    template <class T> vec2<T> normalize(const vec2<T>& V);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Normalizes a vector
	 *  
	 * @param V - input vector
	 */
    template <class T> vec3<T> normalize(const vec3<T>& V);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Normalizes a vector
	 *  
	 * @param V - input vector
	 */
    template <class T> vec4<T> normalize(const vec4<T>& V);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Normalizes a quaternion
	 *  
	 * @param V - input vector
	 */
    template <class T> quat<T> normalize(const quat<T>& Q);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Returns an angle in degrees between two vectors
	 *  
	 * @param V1 - first vector
	 * @param V2 - second vector
	 */
    template <class T> float angle(const vec3<T>& V1, const vec3<T>& V2);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Returns an angle in degrees between two vectors
	 *  
	 * @param V1 - first vector
	 * @param V2 - second vector
	 */
    template <class T> float angle(const vec2<T>& V1, const vec2<T>& V2);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Returns an angle in radians between two vectors
	 *  
	 * @param V1 - first vector
	 * @param V2 - second vector
	 */
    template <class T> float angleRad(const vec3<T>& V1, const vec3<T>& V2);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Returns an angle in radians between two vectors
	 *  
	 * @param V1 - first vector
	 * @param V2 - second vector
	 */
    template <class T> float angleRad(const vec2<T>& V1, const vec2<T>& V2);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Creates a projection matrix
	 *  
	 * @param FieldOfView - vertical field of view
	 * @param Aspect - aspect ratio
	 * @param Near - near plane distance
	 * @param Far - far plane distance
	 */
    mat4x4f FFW_API makeProjectionMatrix(float FieldOfView, float Aspect, float Near, float Far);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Creates a view matrix
	 *  
	 * @param Eyes - position of eyes
	 * @param Target - position of target to look at
	 * @param UpVector - up vector, use vec3f(0.0f, 1.0f, 0.0f)
	 */
    mat4x4f FFW_API makeLookAtMatrix(const vec3f& Eyes, const vec3f& Target, const vec3f& UpVector);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Creates a FPS-like view matrix
	 *  
	 * @param Eyes - position of eyes
	 * @param Pitch - lateral axis of rotation (use values between -90 and +90)
	 * @param Yaw - vertical axis of rotation (use values between 0 and +360)
	 */
    mat4x4f FFW_API makeFpsCameraMatrix(const vec3f& Eyes, float Pitch, float Yaw);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Generates random integer between 0 and 2^32-1
	 */
	unsigned long FFW_API getRandom();
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Generates random float bwteen 0.0 and 1.0
	 */
	float FFW_API getRandomf();
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Generates random integer
	 */
	unsigned long FFW_API getRandom(unsigned long Min, unsigned long Max);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Sets a seed for random generator
	 */
	void FFW_API setRandomSeed(unsigned long Seed);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Clamps a value between min amd max
	 */
	template<class T> T clamp(T Val, T Min, T Max);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Remaps a value from one range to another
	 *
	 * @details Remaps a vlue from given range to a new range.
	 * For example:
	 *
	 * ```C++
	 * float f = 0.87f;
     * float mapped = ffw::remap(f, 0.0, 1.0, 0.0, 100.0);
     * std::cout << "Remapped value of " << f << " is " << mapped << std::endl;
	 * ```
	 *
	 * Prints: Remapped value of 0.87 is 87
	 *
	 * @param Value - value to convert
	 * @param InMin - lower bound of input value
	 * @param InMax - upper bound of input value
	 * @param OutMin - lower bound of output value
	 * @param OutMax - upper bound of output value
	 */
	template<class T> T remap(T Value, T InMin, T InMax, T OutMin, T OutMax);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Returns next power of two for given value
	 */
	unsigned long nextPowOfTwo(unsigned long Value);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Creates a rotation matrix from quaternion
	 */
	template <class T> mat4x4<T> makeRotationMatrix(const quat<T>& Q);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Converts 2D vector to 3D vector
	 * @param Z - value of Z component
	 */
	template<class T> vec3<T> vec2ToVec3(const vec2<T>& Vec, T Z);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Converts 3D vector to 4D vector
	 * @param W - value of W component
	 */
	template<class T> vec4<T> vec3ToVec4(const vec3<T>& Vec, T W);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Converts 2D vector to 3D vector
	 * @details The Z component is set to zero
	 */
	template<class T> vec3<T> vec2ToVec3(const vec2<T>& Vec);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Converts 3D vector to 4D vector
	 * @details The W component is set to zero
	 */
	template<class T> vec4<T> vec3ToVec4(const vec3<T>& Vec);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Converts 4D vector to 3D vector, the 4th component is lost
	 */
	template<class T> vec3<T> vec4ToVec3(const vec4<T>& Vec);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Converts 3D vector to 2D vector, the 3rd component is lost
	 */
	template<class T> vec2<T> vec3ToVec2(const vec3<T>& Vec);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Converts quaternion to 3D vector, the 4th component is lost
	 */
	template <class T> vec3<T> quatToVec3(const quat<T>& Quat);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Converts quaternion to 4D vector
	 */
	template <class T> vec4<T> quatToVec4(const quat<T>& Quat);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Converts 4D vector to quaternion
	 */
	template<class T> quat<T> vec4ToQuat(const vec4<T>& Vec);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Swaps byte order (endianness)
	 */
	unsigned short byteSwap16(unsigned short Value);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Swaps byte order (endianness)
	 */
	unsigned long byteSwap32(unsigned long Value);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Swaps byte order (endianness)
	 */
	unsigned long long byteSwap64(unsigned long long Value);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Stream operator for 2D vector
	 */
    template <class T> std::ostream& operator << (std::ostream& os, const vec2<T>& V);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Stream operator for 3D vector
	 */
    template <class T> std::ostream& operator << (std::ostream& os, const vec3<T>& V);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Stream operator for 4D vector
	 */
    template <class T> std::ostream& operator << (std::ostream& os, const vec4<T>& V);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Stream operator for color
	 */
	std::ostream& operator << (std::ostream& os, const color& C);
   /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *  
	 * @brief Stream operator for quaternion
	 */
	template <class T> std::ostream& operator << (std::ostream& os, const quat<T>& Q);
};

#include "functions.inl"

#endif

