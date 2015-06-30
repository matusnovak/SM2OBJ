/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_QUATERNION_INL
#define FFW_QUATERNION_INL

///=============================================================================
inline ffw::quaternion::quaternion(){
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}

///=============================================================================
inline ffw::quaternion::quaternion(float X, float Y, float Z, float W){
    x = X;
    y = Y;
    z = Z;
    w = W;
}

///=============================================================================
inline ffw::quaternion::quaternion(const quaternion& Quat){
    x = Quat.x;
    y = Quat.y;
    z = Quat.z;
    w = Quat.w;
}

///=============================================================================
inline void ffw::quaternion::set(float X, float Y, float Z, float W){
    x = X;
    y = Y;
    z = Z;
    w = W;
}

///=============================================================================
inline void ffw::quaternion::set(const quaternion& Quat){
    x = Quat.x;
    y = Quat.y;
    z = Quat.z;
    w = Quat.w;
}

///=============================================================================
inline ffw::quaternion& ffw::quaternion::rotate(float Deg, float X, float Y, float Z){
    float angle = Deg*DEG_TO_RAD;
    double result = sin(angle/2.0);
    x = X * result;
    y = Y * result;
    z = Z * result;
    w = cos(angle/2.0);
    normalize();
    return *this;
}

///=============================================================================
inline ffw::quaternion& ffw::quaternion::rotateRad(float Rad, float X, float Y, float Z){
    double result = sin(Rad/2.0);
    x = X * result;
    y = Y * result;
    z = Z * result;
    w = cos(Rad/2.0);
    normalize();
    return *this;
}

///=============================================================================
inline ffw::quaternion  ffw::quaternion::operator *  (const quaternion& Quat) const{
    quaternion result;

    result.x = Quat.w*x + Quat.x*w + Quat.y*z - Quat.z*y;
    result.y = Quat.w*y - Quat.x*z + Quat.y*w + Quat.z*x;
    result.z = Quat.w*z + Quat.x*y - Quat.y*x + Quat.z*w;
    result.w = Quat.w*w - Quat.x*x - Quat.y*y - Quat.z*z;

    return result;
}

///=============================================================================
inline ffw::quaternion& ffw::quaternion::operator *= (const quaternion& Quat){
    float rx = Quat.w*x + Quat.x*w + Quat.y*z - Quat.z*y;
    float ry = Quat.w*y - Quat.x*z + Quat.y*w + Quat.z*x;
    float rz = Quat.w*z + Quat.x*y - Quat.y*x + Quat.z*w;
    float rw = Quat.w*w - Quat.x*x - Quat.y*y - Quat.z*z;

    x = rx;
    y = ry;
    z = rz;
    w = rw;

    return *this;
}

///=============================================================================
inline void ffw::quaternion::normalize(){
    float n = 1.0f/sqrt(x*x+y*y+z*z+w*w);
    x = x * n;
    y = y * n;
    z = z * n;
    w = w * n;
}

///=============================================================================
inline void ffw::quaternion::getEuler(float* Roll, float* Pitch, float* Yaw) const{
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
