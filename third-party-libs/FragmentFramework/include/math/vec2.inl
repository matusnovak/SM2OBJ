/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_VEC2_INL
#define FFW_VEC2_INL

///=============================================================================
template <class T>
inline ffw::vec2<T>::vec2(){
    x = 0;
    y = 0;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>::vec2(T X, T Y){
    x = X;
    y = Y;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>::vec2(T Value){
    x = Value;
    y = Value;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>::vec2(const vec2<T>& V){
    x = V.x;
    y = V.y;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>::vec2(std::initializer_list<T> List){
    if(List.size() != 2){
        x = 0;
        y = 0;
        return;
    }
    x = *(List.begin());
    y = *(List.begin()+1);
}

///=============================================================================
template <class T>
inline void ffw::vec2<T>::set(T X, T Y){
    x = X;
    y = Y;
}

///=============================================================================
template <class T>
inline void ffw::vec2<T>::set(T Value){
    x = Value;
    y = Value;
}

///=============================================================================
template <class T>
inline void ffw::vec2<T>::set(const vec2<T>& V){
    x = V.x;
    y = V.y;
}

///=============================================================================
template <class T>
inline void ffw::vec2<T>::set(std::initializer_list<T> List){
    if(List.size() != 2)return;
    x = *(List.begin());
    y = *(List.begin()+1);
}

template <class T>
inline ffw::vec2<T>  ffw::vec2<T>::operator - () const{
    return vec2<T>(-x, -y);
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::operator =  (const vec2<T>& V){
    x = V.x;
    y = V.y;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>  ffw::vec2<T>::operator +  (const vec2<T>& V) const{
    return vec2<T>(x + V.x, y + V.y);
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::operator += (const vec2<T>& V){
    x += V.x;
    y += V.y;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>  ffw::vec2<T>::operator -  (const vec2<T>& V) const{
    return vec2<T>(x - V.x, y - V.y);
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::operator -= (const vec2<T>& V){
    x -= V.x;
    y -= V.y;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>  ffw::vec2<T>::operator /  (const vec2<T>& V) const{
    return vec2<T>(x / V.x, y / V.y);
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::operator /= (const vec2<T>& V){
    x /= V.x;
    y /= V.y;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>  ffw::vec2<T>::operator *  (const vec2<T>& V) const{
    return vec2<T>(x * V.x, y * V.y);
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::operator *= (const vec2<T>& V){
    x *= V.x;
    y *= V.y;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::operator =  (const T& Val){
    x = Val;
    y = Val;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>  ffw::vec2<T>::operator +  (const T& Val) const{
    return vec2<T>(x + Val, y + Val);
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::operator += (const T& Val){
    x += Val;
    y += Val;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>  ffw::vec2<T>::operator -  (const T& Val) const{
    return vec2<T>(x - Val, y - Val);
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::operator -= (const T& Val){
    x -= Val;
    y -= Val;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>  ffw::vec2<T>::operator /  (const T& Val) const{
    return vec2<T>(x / Val, y / Val);
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::operator /= (const T& Val){
    x /= Val;
    y /= Val;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>  ffw::vec2<T>::operator *  (const T& Val) const{
    return vec2<T>(x * Val, y * Val);
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::operator *= (const T& Val){
    x *= Val;
    y *= Val;
    return *this;
}

///=============================================================================
template <class T>
inline bool ffw::vec2<T>::operator != (const vec2<T>& V) const{
    return (x != V.x || y != V.y);
}

///=============================================================================
template <class T>
inline bool ffw::vec2<T>::operator == (const vec2<T>& V) const{
    return (x == V.x && y == V.y);
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::rotate(const float Deg){
    vec2<T> v = *this;
    x = cos(Deg*0.01745329251)*v.x - sin(Deg*0.01745329251)*v.y;
    y = sin(Deg*0.01745329251)*v.x + cos(Deg*0.01745329251)*v.y;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::rotateRad(const float Rad){
    vec2<T> v = *this;
    x = cos(Rad)*v.x - sin(Rad)*v.y;
    y = sin(Rad)*v.x + cos(Rad)*v.y;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::normalize(){
    float l = sqrtf(x*x + y*y);
    if( l > 0 ) {
        x = x/l;
        y = y/l;
    }
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec2<T>& ffw::vec2<T>::scale(const T Val){
    x = x*Val;
    y = y*Val;
    return *this;
}

///=============================================================================
template <class T>
inline float ffw::vec2<T>::length() const{
    return sqrtf(x*x + y*y);
}

///=============================================================================
template <class T>
inline T ffw::vec2<T>::lengthSqrd() const{
    return (x*x + y*y);
}

#endif
