/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_BASE_FUNCTIONS
#define FFW_BASE_FUNCTIONS

/*!
	@ingroup Math
*/
namespace ffw{
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Linear interpolation

		@param [in] A      First value
		@param [in] B      Second value
		@param [in] Weight Alpha value

		@return Interpolated value
	*/
    template <class T> T lerp(const T& A, const T& B, float Weight);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Dot product of two 2D vectors

		@param [in] V1 First vector
		@param [in] V2 Second vector

		@return Dot product
	*/
    template <class T> float dot(const vec2<T>& V1, const vec2<T>& V2);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Dot product of two 3D vectors

		@param [in] V1 First vector
		@param [in] V2 Second vector

		@return Dot product
	*/
    template <class T>  float dot(const vec3<T>& V1, const vec3<T>& V2);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Cross product of two 3D vectors

		@param [in] V1 First vector
		@param [in] V2 Second vector

		@return Cross product
	*/
    template <class T> vec3<T> cross(const vec3<T>& V1, const vec3<T>& V2);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Normalizes 2D vector

		@param [in] V Vector to normalize

		@return Normalized 2D vector
	*/
    template <class T> vec2<T> normalize(const vec2<T>& V);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Normalizes 3D vector

		@param [in] V Vector to normalize

		@return Normalized 3D vector
	*/
    template <class T> vec3<T> normalize(const vec3<T>& V);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Normalizes 4D vector

		@param [in] V Vector to normalize

		@return Normalized 4D vector
	*/
    template <class T> vec4<T> normalize(const vec4<T>& V);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Normalizes quaternion

		@param [in] Q Quaternion to normalize

		@return Normalized quaternion
	*/
    quaternion normalize(const quaternion& Q);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Returns angle between two 3D vectors

		@param [in] V1 First vector
		@param [in] V2 Second vector

		@return Angle between vector in degrees
	*/
    template <class T> float angle(const vec3<T>& V1, const vec3<T>& V2);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Returns angle between two 2D vectors

		@param [in] V1 First vector
		@param [in] V2 Second vector

		@return Angle between vector in degrees
	*/
    template <class T> float angle(const vec2<T>& V1, const vec2<T>& V2);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Returns angle between two 3D vectors

		@param [in] V1 First vector
		@param [in] V2 Second vector

		@return Angle between vector in radians
	*/
    template <class T> float angleRad(const vec3<T>& V1, const vec3<T>& V2);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Returns angle between two 2D vectors

		@param [in] V1 First vector
		@param [in] V2 Second vector

		@return Angle between vector in radians
	*/
    template <class T> float angleRad(const vec2<T>& V1, const vec2<T>& V2);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Creates projection matrix

		@param [in] FieldOfView Vertical field of view
		@param [in] Aspect      Aspect ratio
		@param [in] Near        Near plane distance
		@param [in] Far         Far plane distance

		@return Projection matrix
	*/
    mat4 FFW_API makeProjectionMatrix(float FieldOfView, float Aspect, float Near, float Far);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Creates view matrix

        @details Creates view matrix. Use vec3f(0.0f, 1.0f, 0.0f) as UpVector.

        @sa makeFpsCameraMatrix

		@param [in] Eyes     Position of eyes
		@param [in] Target   Position of target to look at
		@param [in] UpVector Up vector

		@return View matrix
	*/
    mat4 FFW_API makeLookAtMatrix(const vec3f& Eyes, const vec3f& Target, const vec3f& UpVector);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Creates view matrix

        @sa makeLookAtMatrix

		@param [in] Eyes  Position of eyes
		@param [in] Pitch Lateral axis of rotation (use values between -90 and +90)
		@param [in] Yaw   Vertical axis of rotation (use values between 0 and +360)

		@return View matrix
	*/
    mat4 FFW_API makeFpsCameraMatrix(const vec3f& Eyes, float Pitch, float Yaw);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Generates random integer between 0 and 2^32-1

        @details The generated value will never be equal to 2^32-1

        @return Random integer
	*/
	unsigned long FFW_API getRandom();
	/*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Generates random float between 0.0f and 1.0f

        @details The generated value will never be equal to 1.0f

        @return Random float
	*/
	float FFW_API getRandomf();
	/*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Generates random integer between given values

        @details Generated value will never be equal to Max

        @param [in] Min Minimal value
        @param [in] Max Maximal value

        @return Random integer
	*/
	unsigned long FFW_API getRandom(unsigned long Min, unsigned long Max);
	/*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Sets randomness seed
	*/
	void FFW_API setRandomSeed(unsigned long Seed);
	/*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Clamps value

        @details Clamps value based on provided arguments.

        @param [in] Val Input value;
        @param [in] Min Minimum;
        @param [in] Max Maximum;

        @return Clamped value
	*/
	template<class T> T clamp(T Val, T Min, T Max);
	/*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Clamps value between 0.0 <-> 1.0 range

        @details Returns 0.0 if value is less than 0.0
        or returns 1.0 if value is greater than 1.0f
        Otherwise returns same value. Must be float or double.

        @param [in] Val Value

        @return Clamped value
	*/
	template<class T> T clamp(T Val);
	/*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Remaps value to new range

        @param [in] Value Value to convert
        @param [in] InMin Lower bound of input value
        @param [in] InMax Upper bound of input value
        @param [in] OutMin Lower bound of output value
        @param [in] OutMax Upper bound of output value

        @return Remapped value

        @code
        float f = 0.87f;
        float mapped = ffw::remap(f, 0.0, 1.0, 0.0, 100.0);
        std::cout << "Remapped value of " << f << " is " << mapped << std::endl;
        // Prints: Remapped value of 0.87 is 87
        @endcode
	*/
	template<class T> T remap(T Value, T InMin, T InMax, T OutMin, T OutMax);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	unsigned long nextPowOfTwo(unsigned long Value);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	mat4 makeRotationMatrix(const quaternion& Q);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	template<class T> vec3<T> vec2ToVec3(const vec2<T>& Vec);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	template<class T> vec4<T> vec3ToVec4(const vec3<T>& Vec);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	template<class T> vec3<T> vec2ToVec3(const vec2<T>& Vec, T Z);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	template<class T> vec4<T> vec3ToVec4(const vec3<T>& Vec, T W);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	template<class T> vec3<T> vec4ToVec3(const vec4<T>& Vec);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	template<class T> vec2<T> vec3ToVec2(const vec3<T>& Vec);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	vec3f quatToVec3(const quaternion& Quat);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	vec4f quatToVec4(const quaternion& Quat);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	template<class T> quaternion vec4ToQuat(const vec4<T>& Vec);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	unsigned short byteSwap16(unsigned short Value);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	unsigned long byteSwap32(unsigned long Value);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	unsigned long long byteSwap64(unsigned long long Value);
	/*!
		@memberof ffw
		@ingroup Math
		@inline
	*/
    template <class T> std::ostream& operator << (std::ostream& os, const vec2<T>& V);
    /*!
		@memberof ffw
		@ingroup Math
		@inline
	*/
    template <class T> std::ostream& operator << (std::ostream& os, const vec3<T>& V);
    /*!
		@memberof ffw
		@ingroup Math
		@inline
	*/
    template <class T> std::ostream& operator << (std::ostream& os, const vec4<T>& V);
    /*!
		@memberof ffw
		@ingroup Math
		@inline
	*/
	std::ostream& operator << (std::ostream& os, const color& C);
    /*!
		@memberof ffw
		@ingroup Math
		@inline
	*/
	std::ostream& operator << (std::ostream& os, const quaternion& Q);
};

#include "functions.inl"

#endif

