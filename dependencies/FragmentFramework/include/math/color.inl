/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

///=============================================================================
inline ffw::color::color(){
    r = 1.0f;
    g = 1.0f;
    b = 1.0f;
    a = 1.0f;
}

///=============================================================================
inline ffw::color::color(float R, float G, float B, float A){
    r = R;
    g = G;
    b = B;
    a = A;
}

///=============================================================================
inline ffw::color::color(float R, float G, float B){
    r = R;
    g = G;
    b = B;
    a = 1.0f;
}

///=============================================================================
inline ffw::color::color(float Grey){
    r = Grey;
    g = Grey;
    b = Grey;
    a = 1.0f;
}

///=============================================================================
inline void ffw::color::set(float R, float G, float B, float A){
    r = R;
    g = G;
    b = B;
    a = A;
}

///=============================================================================
inline void ffw::color::set(float R, float G, float B){
    r = R;
    g = G;
    b = B;
    a = 1.0f;
}

///=============================================================================
inline void ffw::color::set(float Grey){
    r = Grey;
    g = Grey;
    b = Grey;
    a = 1.0f;
}

///=============================================================================
inline void ffw::color::setUbyte(unsigned char R, unsigned char G, unsigned char B, unsigned char A){
    r = float(R)/255.0f;
    g = float(G)/255.0f;
    b = float(B)/255.0f;
    a = float(A)/255.0f;
}

///=============================================================================
inline void ffw::color::setUbyte(unsigned char R, unsigned char G, unsigned char B){
    r = float(R)/255.0f;
    g = float(G)/255.0f;
    b = float(B)/255.0f;
    a = 1.0f;
}

///=============================================================================
inline void ffw::color::setUbyte(unsigned char Grey){
    r = float(Grey)/255.0f;
    g = float(Grey)/255.0f;
    b = float(Grey)/255.0f;
    a = 1.0f;
}

///=============================================================================
inline ffw::color& ffw::color::operator =  (const color &Col){
    r = Col.r;
    g = Col.g;
    b = Col.b;
    a = Col.a;
    return *this;
}

///=============================================================================
inline ffw::color  ffw::color::operator +  (const color &Col) const{
    return ffw::color(r + Col.r, g + Col.g, b + Col.b, a + Col.a);
}

///=============================================================================
inline ffw::color& ffw::color::operator += (const color &Col){
    r += Col.r;
    g += Col.g;
    b += Col.b;
    a += Col.a;
    return *this;
}

///=============================================================================
inline ffw::color  ffw::color::operator -  (const color &Col) const{
    return ffw::color(r - Col.r, g - Col.g, b - Col.b, a - Col.a);
}

///=============================================================================
inline ffw::color& ffw::color::operator -= (const color &Col){
    r -= Col.r;
    g -= Col.g;
    b -= Col.b;
    a -= Col.a;
    return *this;
}

///=============================================================================
inline ffw::color& ffw::color::clamp(){
    if(r > 1.0f)r = 1.0f;
    if(r < 0.0f)r = 0.0f;

    if(g > 1.0f)g = 1.0f;
    if(g < 0.0f)g = 0.0f;

    if(b > 1.0f)b = 1.0f;
    if(b < 0.0f)b = 0.0f;

    if(a > 1.0f)a = 1.0f;
    if(a < 0.0f)a = 0.0f;
    return *this;
}

///=============================================================================
inline ffw::color& ffw::color::normalize(){
    float l = sqrt(r*r + g*g + b*b);
    r /= l;
    g /= l;
    b /= l;
    if(a > 1.0f)a = 1.0f;
    return *this;
}
