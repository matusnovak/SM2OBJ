/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

///=============================================================================
template <class T>
inline ffw::quat<T>::quat(){
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}

///=============================================================================
template <class T>
inline ffw::quat<T>::quat(T X, T Y, T Z, T W){
    x = X;
    y = Y;
    z = Z;
    w = W;
}

///=============================================================================
template <class T>
inline ffw::quat<T>::quat(const quat& Quat){
    x = Quat.x;
    y = Quat.y;
    z = Quat.z;
    w = Quat.w;
}

///=============================================================================
template <class T>
inline void ffw::quat<T>::set(T X, T Y, T Z, T W){
    x = X;
    y = Y;
    z = Z;
    w = W;
}

///=============================================================================
template <class T>
inline void ffw::quat<T>::set(const quat& Quat){
    x = Quat.x;
    y = Quat.y;
    z = Quat.z;
    w = Quat.w;
}

///=============================================================================
template <class T>
inline ffw::quat<T>& ffw::quat<T>::rotate(T Deg, T X, T Y, T Z){
    double angle = Deg*DEG_TO_RAD;
    double result = sin(angle/2.0);
    x = float(X * result);
    y = float(Y * result);
    z = float(Z * result);
    w = float(cos(angle/2.0));
    normalize();
    return *this;
}

///=============================================================================
template <class T>
inline ffw::quat<T>& ffw::quat<T>::rotateRad(T Rad, T X, T Y, T Z){
    double result = sin(Rad/2.0);
    x = float(X * result);
    y = float(Y * result);
    z = float(Z * result);
    w = float(cos(Rad/2.0));
    normalize();
    return *this;
}

///=============================================================================
template <class T>
inline ffw::quat<T> ffw::quat<T>::operator - () const{
    quat result;

    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = -w;

    return result;
}

///=============================================================================
template <class T>
inline ffw::quat<T> ffw::quat<T>::operator * (const quat& Quat) const{
    quat result;

    result.x = Quat.w*x + Quat.x*w + Quat.y*z - Quat.z*y;
    result.y = Quat.w*y - Quat.x*z + Quat.y*w + Quat.z*x;
    result.z = Quat.w*z + Quat.x*y - Quat.y*x + Quat.z*w;
    result.w = Quat.w*w - Quat.x*x - Quat.y*y - Quat.z*z;

    return result;
}

///=============================================================================
template <class T>
inline ffw::quat<T>& ffw::quat<T>::operator *= (const quat& Quat){
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
template <class T>
inline ffw::quat<T> ffw::quat<T>::operator * (T Value) const{
    quat result;

    result.x = x*Value;
    result.y = y*Value;
    result.z = z*Value;
    result.w = w*Value;

    return result;
}

///=============================================================================
template <class T>
inline ffw::quat<T>& ffw::quat<T>::operator *= (T Value){
    x *= Value;
    y *= Value;
    z *= Value;
    w *= Value;

    return *this;
}

///=============================================================================
template <class T>
inline ffw::quat<T> ffw::quat<T>::operator + (const quat& Quat) const{
    quat result;

    result.x = x + Quat.x;
    result.y = y + Quat.y;
    result.z = z + Quat.z;
    result.w = w + Quat.w;

    return result;
}

///=============================================================================
template <class T>
inline ffw::quat<T>& ffw::quat<T>::operator += (const quat& Quat){
    x += Quat.x;
    y += Quat.y;
    z += Quat.z;
    w += Quat.w;

    return *this;
}

///=============================================================================
template <class T>
inline ffw::quat<T> ffw::quat<T>::operator - (const quat& Quat) const{
    quat result;

    result.x = x - Quat.x;
    result.y = y - Quat.y;
    result.z = z - Quat.z;
    result.w = w - Quat.w;

    return result;
}

///=============================================================================
template <class T>
inline ffw::quat<T>& ffw::quat<T>::operator -= (const quat& Quat){
    x -= Quat.x;
    y -= Quat.y;
    z -= Quat.z;
    w -= Quat.w;

    return *this;
}

///=============================================================================
template <class T>
inline ffw::quat<T> ffw::quat<T>::operator / (T Value) const{
    quat result;
    float val = 1.0f / Value;

    result.x = x*val;
    result.y = y*val;
    result.z = z*val;
    result.w = w*val;

    return result;
}

///=============================================================================
template <class T>
inline ffw::quat<T>& ffw::quat<T>::operator /= (T Value){
    float val = 1.0f / Value;

    x *= val;
    y *= val;
    z *= val;
    w *= val;

    return *this;
}

///=============================================================================
template <class T>
inline void ffw::quat<T>::normalize(){
    float n = 1.0f/sqrt(x*x+y*y+z*z+w*w);
    x = x * n;
    y = y * n;
    z = z * n;
    w = w * n;
}

///=============================================================================
template <class T>
inline void ffw::quat<T>::getEuler(T* Roll, T* Pitch, T* Yaw) const{
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quatToEuler/
    T test = x*y + z*w;
    double heading;
    double attitude;
    double bank;

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

    if(Roll  != NULL)*Roll   = T(attitude  *DEG_TO_RAD);
    if(Pitch != NULL)*Pitch  = T(heading   *DEG_TO_RAD);
    if(Yaw   != NULL)*Yaw    = T(bank      *DEG_TO_RAD);
}

///=============================================================================
template <class T>
inline float ffw::quat<T>::length() const {
    return sqrt(x*x + y*y + z*z + w*w);
}

///=============================================================================
template <class T>
inline float ffw::quat<T>::lengthSqrd() const {
    return x*x + y*y + z*z + w*w;
}

///=============================================================================
template <class T>
inline ffw::quat<T> ffw::quat<T>::getConjugate() const {
    quat result;

    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = w;

    return result;
}

///=============================================================================
template <class T>
inline ffw::quat<T> ffw::quat<T>::getInversed() const {
    return getConjugate() / lengthSqrd();
}

///=============================================================================
template <class T>
inline ffw::quat<T>& ffw::quat<T>::inverse(){
    *this = getConjugate() / lengthSqrd();
    return *this;
}
