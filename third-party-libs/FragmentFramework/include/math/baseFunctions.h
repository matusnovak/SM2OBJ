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

		@brief Linear interpolation of 2D vector

		@param [in] A      First value
		@param [in] B      Second value
		@param [in] Weight Alpha value

		@return Interpolated 2D vector
	*/
    template <class T> vec2<T> lerp(const vec2<T>& A, const vec2<T>& B, float Weight);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Linear interpolation of 3D vector

		@param [in] A      First value
		@param [in] B      Second value
		@param [in] Weight Alpha value

		@return Interpolated 3D vector
	*/
    template <class T> vec3<T> lerp(const vec3<T>& A, const vec3<T>& B, float Weight);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Linear interpolation of 4D vector

		@param [in] A      First value
		@param [in] B      Second value
		@param [in] Weight Alpha value

		@return Interpolated 4D vector
	*/
    template <class T> vec4<T> lerp(const vec4<T>& A, const vec4<T>& B, float Weight);
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

		@brief Normalizes 2D vectors

		@param [in] V Vector to normalize

		@return Normalized 2D vector
	*/
    template <class T> vec2<T> normalize(const vec2<T>& V);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Normalizes 3D vectors

		@param [in] V Vector to normalize

		@return Normalized 3D vector
	*/
    template <class T> vec3<T> normalize(const vec3<T>& V);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Normalizes 4D vectors

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
    mat4 makeProjectionMatrix(float FieldOfView, float Aspect, float Near, float Far);
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
    mat4 makeLookAtMatrix(const vec3f& Eyes, const vec3f& Target, const vec3f& UpVector);
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
    mat4 makeFpsCameraMatrix(const vec3f& Eyes, float Pitch, float Yaw);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Generates random integer between 0 and 2^32-1

        @details The generated value will never be equal to 2^32-1

        @return Random integer
	*/
	uint32_t getRandom();
	/*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Generates random float between 0.0f and 1.0f

        @details The generated value will never be equal to 1.0f

        @return Random float
	*/
	float getRandomf();
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
	uint32_t getRandom(uint32_t Min, uint32_t Max);
	/*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Sets randomness seed
	*/
	void setRandomSeed(uint32_t Seed);
	/*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Returns absolute value of float

        @param [in] Val Value

        @return Absolute value
	*/
	float getAbsf(float Val);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Returns absolute value of double

        @param [in] Val Value

        @return Absolute value
	*/
	double getAbsd(double Val);
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
	template<class T> float clamp(T Val, T Min, T Max);
	/*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Clamps value of float

        @details Returns 0.0 if value is less than 0.0
        or returns 1.0 if value is greater than 1.0f
        Otherwise returns same value.

        @param [in] Val Value

        @return Clamped value
	*/
	float clampf(float Val);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

        @brief Clamps value of double

        @details Returns 0.0 if value is less than 0.0
        or returns 1.0 if value is greater than 1.0f
        Otherwise returns same value.

        @param [in] Val Value

        @return Clamped value
	*/
	double clampd(double Val);
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
	float remap(float Value, float InMin, float InMax, float OutMin, float OutMax);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	uint32_t nextPowOfTwo(uint32_t Value);
	/*!
        @memberof ffw
		@ingroup Math
		@inline
	*/
	mat4 makeRotationMatrix(quaternion& Q);
};

#include "baseFunctions.inl"

#endif

