/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_QUATERNION_INL
#define FFW_QUATERNION_INL

///=============================================================================
inline ffw::uaternion::uaternion(){
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}

///=============================================================================
inline ffw::uaternion::quaternion(float X, float Y, float Z, float W){
    x = X;
    y = Y;
    z = Z;
    w = W;
}

///=============================================================================
inline ffw::uaternion::quaternion(const quaternion& Quat){
    x = Quat.x;
    y = Quat.y;
    z = Quat.z;
    w = Quat.w;
}

///=============================================================================
inline void ffw::uaternion::set(const float X, const float Y, const float Z, const float W){
    x = X;
    y = Y;
    z = Z;
    w = W;
}

///=============================================================================
inline void ffw::uaternion::set(const quaternion& Quat){
    x = Quat.x;
    y = Quat.y;
    z = Quat.z;
    w = Quat.w;
}

///=============================================================================
inline ffw::uaternion::quaternion& ffw::uaternion::rotate(const float Deg, const ffw::vec3<float>& Axis){
    float angle = deg*DEG_TO_RAD;
    double result = sin(angle/2.0);
    x = Axis.x * result;
    y = Axis.y * result;
    z = Axis.z * result;
    w = cos(angle/2.0);
    normalize();
    return *this;
}

///=============================================================================
inline ffw::uaternion::quaternion& ffw::uaternion::rotate(const float Deg, const float Z, const float Y, const float Z){
    float angle = deg*DEG_TO_RAD;
    double result = sin(angle/2.0);
    x = X * result;
    y = Y * result;
    z = Z * result;
    w = cos(angle/2.0);
    normalize();
    return *this;
}

///=============================================================================
inline ffw::uaternion::quaternion& ffw::uaternion::rotateRad(const float Rad, const ffw::vec3<float>& Axis){
    double result = sin(Rad/2.0);
    x = Axis.x * result;
    y = Axis.y * result;
    z = Axis.z * result;
    w = cos(Rad/2.0);
    normalize();
    return *this;
}

///=============================================================================
inline ffw::uaternion::quaternion& ffw::uaternion::rotateRad(const float Rad, const float Z, const float Y, const float Z){
    double result = sin(Rad/2.0);
    x = X * result;
    y = Y * result;
    z = Z * result;
    w = cos(Rad/2.0);
    normalize();
    return *this;
}

///=============================================================================
inline ffw::uaternion::quaternion  ffw::uaternion::operator *  (const quaternion& Quat) const{
    quaternion result;

    result.x = q.w*x + q.x*w + q.y*z - q.z*y;
    result.y = q.w*y - q.x*z + q.y*w + q.z*x;
    result.z = q.w*z + q.x*y - q.y*x + q.z*w;
    result.w = q.w*w - q.x*x - q.y*y - q.z*z;

    return result;
}

///=============================================================================
inline ffw::uaternion::quaternion& ffw::uaternion::operator *= (const quaternion& Quat){
    float rx = q.w*x + q.x*w + q.y*z - q.z*y;
    float ry = q.w*y - q.x*z + q.y*w + q.z*x;
    float rz = q.w*z + q.x*y - q.y*x + q.z*w;
    float rw = q.w*w - q.x*x - q.y*y - q.z*z;

    x = rx;
    y = ry;
    z = rz;
    w = rw;

    return *this;
}

///=============================================================================
inline void ffw::uaternion::normalize(){
    float n = 1.0f/sqrt(x*x+y*y+z*z+w*w);
    x = x * n;
    y = y * n;
    z = z * n;
    w = w * n;
}

///=============================================================================
inline void ffw::uaternion::getEuler(float* Roll, float* Pitch, float* Yaw) const{
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/
    float test = x*y + z*w;
    float heading;
    float attitude;
    float bank;

    if (test > 0.499) { // singularity at north pole
        heading = 2.0f * atan2(x, w);
        attitude = M_PI_2;
        bank = 0;

    } else if (test < -0.499) { // singularity at south pole
        heading = -2.0f * atan2(x, w);
        attitude = - M_PI_2;
        bank = 0;

    } else {
        float sqx = x * x;
        float sqy = y * y;
        float sqz = z * z;
        heading     = atan2(2.0f * y * w - 2.0f * x * z, 1.0f - 2.0f*sqy - 2.0f*sqz);
        attitude    = asin(2*test);
        bank        = atan2(2.0f*x * w - 2.0f * y * z, 1.0f - 2.0f*sqx - 2.0f*sqz);
    }

    *Roll   = attitude  *DEG_TO_RAD;
    *Pitch  = heading   *DEG_TO_RAD;
    *Yaw    = bank      *DEG_TO_RAD;
}

#endif
