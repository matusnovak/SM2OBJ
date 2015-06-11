/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_VEC3_INL
#define FFW_VEC3_INL

///=============================================================================
template <class T>
inline ffw::vec3<T>::vec3(){
    x = 0;
    y = 0;
    z = 0;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>::vec3(T X, T Y, T Z){
    x = X;
    y = Y;
    z = Z;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>::vec3(T Value){
    x = Value;
    y = Value;
    z = Value;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>::vec3(const vec3<T>& V){
    x = V.x;
    y = V.y;
    z = V.z;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>::vec3(std::initializer_list<T> List){
    if(List.size() != 3){
        x = 0;
        y = 0;
        z = 0;
        return;
    }
    x = *(List.begin());
    y = *(List.begin()+1);
    z = *(List.begin()+2);
}

///=============================================================================
template <class T>
inline void ffw::vec3<T>::set(T X, T Y, T Z){
    x = X;
    y = Y;
    z = Z;
}

///=============================================================================
template <class T>
inline void ffw::vec3<T>::set(T Value){
    x = Value;
    y = Value;
    z = Value;
}

///=============================================================================
template <class T>
inline void ffw::vec3<T>::set(const vec3<T>& V){
    x = V.x;
    y = V.y;
    z = V.z;
}

///=============================================================================
template <class T>
inline void ffw::vec3<T>::set(std::initializer_list<T> List){
    if(List.size() != 3)return;
    x = *(List.begin());
    y = *(List.begin()+1);
    z = *(List.begin()+2);
}

///=============================================================================
template <class T>
inline ffw::vec3<T>  ffw::vec3<T>::operator - () const{
    return vec3<T>(-x, -y, -z);
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::operator =  (const vec3<T>& V){
    x = V.x;
    y = V.y;
    z = V.z;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>  ffw::vec3<T>::operator +  (const vec3<T>& V) const{
    return vec3<T>(x + V.x, y + V.y, z + V.z);
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::operator += (const vec3<T>& V){
    x += V.x;
    y += V.y;
    z += V.z;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>  ffw::vec3<T>::operator -  (const vec3<T>& V) const{
    return vec3<T>(x - V.x, y - V.y, z - V.z);
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::operator -= (const vec3<T>& V){
    x -= V.x;
    y -= V.y;
    z -= V.z;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>  ffw::vec3<T>::operator /  (const vec3<T>& V) const{
    return vec3<T>(x / V.x, y / V.y, z / V.z);
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::operator /= (const vec3<T>& V){
    x /= V.x;
    y /= V.y;
    z /= V.z;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>  ffw::vec3<T>::operator *  (const vec3<T>& V) const{
    return vec3<T>(x * V.x, y * V.y, z * V.z);
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::operator *= (const vec3<T>& V){
    x *= V.x;
    y *= V.y;
    z *= V.z;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::operator =  (const T& Val){
    x = Val;
    y = Val;
    z = Val;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>  ffw::vec3<T>::operator +  (const T& Val) const{
    return vec3<T>(x + Val, y + Val, z + Val);
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::operator += (const T& Val){
    x += Val;
    y += Val;
    z += Val;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>  ffw::vec3<T>::operator -  (const T& Val) const{
    return vec3<T>(x - Val, y - Val, z - Val);
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::operator -= (const T& Val){
    x -= Val;
    y -= Val;
    z -= Val;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>  ffw::vec3<T>::operator /  (const T& Val) const{
    return vec3<T>(x / Val, y / Val, z / Val);
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::operator /= (const T& Val){
    x /= Val;
    y /= Val;
    z /= Val;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>  ffw::vec3<T>::operator *  (const T& Val) const{
    return vec3<T>(x * Val, y * Val, z * Val);
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::operator *= (const T& Val){
    x *= Val;
    y *= Val;
    z *= Val;
    return *this;
}

///=============================================================================
template <class T>
inline bool ffw::vec3<T>::operator != (const vec3<T>& V) const{
    return (x != V.x || y != V.y || z != V.z);
}

///=============================================================================
template <class T>
inline bool ffw::vec3<T>::operator == (const vec3<T>& V) const{
    return (x == V.x && y == V.y && z == V.z);
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::rotateByAxis(const float Deg, vec3<T> Axis){
    //Axis.normalize();
    float rad = Deg*0.01745329251;
    float sina = sin(rad);
    float cosa = cos(rad);
    float cosb = 1.0f - cosa;
    vec3<T> v = *this;

    x = v.x*(Axis.x*Axis.x*cosb + cosa)        + v.y*(Axis.x*Axis.y*cosb - Axis.z*sina) + v.z*(Axis.x*Axis.z*cosb + Axis.y*sina);
    y = v.x*(Axis.y*Axis.x*cosb + Axis.z*sina) + v.y*(Axis.y*Axis.y*cosb + cosa)        + v.z*(Axis.y*Axis.z*cosb - Axis.x*sina);
    z = v.x*(Axis.z*Axis.x*cosb - Axis.y*sina) + v.y*(Axis.z*Axis.y*cosb + Axis.x*sina) + v.z*(Axis.z*Axis.z*cosb + cosa);
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::rotateX(const float Deg){
    T vy = y;
    T vz = z;
    //x = vx;
    y = cos(Deg*0.01745329251)*vy - sin(Deg*0.01745329251)*vz;
    z = sin(Deg*0.01745329251)*vy + cos(Deg*0.01745329251)*vz;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::rotateY(const float Deg){
    T vx = x;
    T vz = z;
    x = cos(Deg*0.01745329251)*vx + sin(Deg*0.01745329251)*vz;
    //y = vy;
    z = -sin(Deg*0.01745329251)*vx + cos(Deg*0.01745329251)*vz;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::rotateZ(const float Deg){
    T vx = x;
    T vy = y;
    x = cos(Deg*0.01745329251)*vx - sin(Deg*0.01745329251)*vy;
    y = sin(Deg*0.01745329251)*vx + cos(Deg*0.01745329251)*vy;
    //z = vz;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::rotateXRad(const float Rad){
    T vy = y;
    T vz = z;
    //x = vx;
    y = cos(Rad)*vy - sin(Rad)*vz;
    z = sin(Rad)*vy + cos(Rad)*vz;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::rotateYRad(const float Rad){
    T vx = x;
    T vz = z;
    x = cos(Rad)*vx + sin(Rad)*vz;
    //y = vy;
    z = -sin(Rad)*vx + cos(Rad)*vz;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::rotateZRad(const float Rad){
    T vx = x;
    T vy = y;
    x = cos(Rad)*vx - sin(Rad)*vy;
    y = sin(Rad)*vx + cos(Rad)*vy;
    //z = vz;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::normalize(){
    float l = sqrtf(x*x + y*y + z*z);
    if( l > 0 ) {
        x = x/l;
        y = y/l;
        z = z/l;
    }
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec3<T>& ffw::vec3<T>::scale(const T Val){
    x = x*Val;
    y = y*Val;
    z = z*Val;
    return *this;
}

///=============================================================================
template <class T>
inline float ffw::vec3<T>::length() const{
    return sqrtf(x*x + y*y + z*z);
}

///=============================================================================
template <class T>
inline T ffw::vec3<T>::lengthSqrd() const{
    return (x*x + y*y + z*z);
}

#endif
