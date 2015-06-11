/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_MAT4_INL
#define FFW_MAT4_INL

///=============================================================================
inline ffw::mat4::mat4(){
    ptr[0] = 1.0f;  ptr[4] = 0.0f;  ptr[8]  = 0.0f; ptr[12] = 0.0f;
    ptr[1] = 0.0f;  ptr[5] = 1.0f;  ptr[9]  = 0.0f; ptr[13] = 0.0f;
    ptr[2] = 0.0f;  ptr[6] = 0.0f;  ptr[10] = 1.0f; ptr[14] = 0.0f;
    ptr[3] = 0.0f;  ptr[7] = 0.0f;  ptr[11] = 0.0f; ptr[15] = 1.0f;
}

///=============================================================================
inline ffw::mat4::mat4( float xx, float yx, float zx, float wx,
                        float xy, float yy, float zy, float wy,
                        float xz, float yz, float zz, float wz,
                        float xw, float yw, float zw, float ww){
    ptr[0] = xx;    ptr[4] = yx;    ptr[8]  = zx;   ptr[12] = wx;
    ptr[1] = xy;    ptr[5] = yy;    ptr[9]  = zy;   ptr[13] = wy;
    ptr[2] = xz;    ptr[6] = yz;    ptr[10] = zz;   ptr[14] = wz;
    ptr[3] = xw;    ptr[7] = yw;    ptr[11] = zw;   ptr[15] = ww;
}

///=============================================================================
inline ffw::mat4::mat4(float Val){
    ptr[0] = Val;   ptr[4] = 0.0f;  ptr[8]  = 0.0f; ptr[12] = 0.0f;
    ptr[1] = 0.0f;  ptr[5] = Val;   ptr[9]  = 0.0f; ptr[13] = 0.0f;
    ptr[2] = 0.0f;  ptr[6] = 0.0f;  ptr[10] = Val;  ptr[14] = 0.0f;
    ptr[3] = 0.0f;  ptr[7] = 0.0f;  ptr[11] = 0.0f; ptr[15] = Val;
}

///=============================================================================
inline ffw::mat4::mat4(std::initializer_list<float> List){
    if(List.size() != 16){
        ptr[0] = 1.0f;  ptr[4] = 0.0f;  ptr[8]  = 0.0f; ptr[12] = 0.0f;
        ptr[1] = 0.0f;  ptr[5] = 1.0f;  ptr[9]  = 0.0f; ptr[13] = 0.0f;
        ptr[2] = 0.0f;  ptr[6] = 0.0f;  ptr[10] = 1.0f; ptr[14] = 0.0f;
        ptr[3] = 0.0f;  ptr[7] = 0.0f;  ptr[11] = 0.0f; ptr[15] = 1.0f;
        return;
    }
    for(int i = 0; i < 16; i++){
        ptr[i] = *(List.begin()+i);
    }
}

///=============================================================================
inline void ffw::mat4::set( float xx, float yx, float zx, float wx,
                            float xy, float yy, float zy, float wy,
                            float xz, float yz, float zz, float wz,
                            float xw, float yw, float zw, float ww){
    ptr[0] = xx;    ptr[4] = yx;    ptr[8]  = zx;   ptr[12] = wx;
    ptr[1] = xy;    ptr[5] = yy;    ptr[9]  = zy;   ptr[13] = wy;
    ptr[2] = xz;    ptr[6] = yz;    ptr[10] = zz;   ptr[14] = wz;
    ptr[3] = xw;    ptr[7] = yw;    ptr[11] = zw;   ptr[15] = ww;
}

///=============================================================================
inline void ffw::mat4::set(float Val){
    ptr[0] = Val;   ptr[4] = 0.0f;  ptr[8]  = 0.0f; ptr[12] = 0.0f;
    ptr[1] = 0.0f;  ptr[5] = Val;   ptr[9]  = 0.0f; ptr[13] = 0.0f;
    ptr[2] = 0.0f;  ptr[6] = 0.0f;  ptr[10] = Val;  ptr[14] = 0.0f;
    ptr[3] = 0.0f;  ptr[7] = 0.0f;  ptr[11] = 0.0f; ptr[15] = Val;
}

///=============================================================================
inline void ffw::mat4::set(float m[16]){
    ptr[0] = m[0];    ptr[4] = m[4];    ptr[8]  = m[8];   ptr[12] = m[12];
    ptr[1] = m[1];    ptr[5] = m[5];    ptr[9]  = m[9];   ptr[13] = m[13];
    ptr[2] = m[2];    ptr[6] = m[6];    ptr[10] = m[10];  ptr[14] = m[14];
    ptr[3] = m[3];    ptr[7] = m[7];    ptr[11] = m[11];  ptr[15] = m[15];
}

///=============================================================================
inline void ffw::mat4::set(std::initializer_list<float> List){
    if(List.size() != 16){
        return;
    }
    for(int i = 0; i < 16; i++){
        ptr[i] = *(List.begin()+i);
    }
}

///=============================================================================
inline float* ffw::mat4::getMatrix(){
    return &ptr[0];
}

///=============================================================================
inline ffw::mat4& ffw::mat4::operator = (const ffw::mat4 &m){
    ptr[0] = m.ptr[0];  ptr[4] = m.ptr[4];  ptr[8]  = m.ptr[8];     ptr[12] = m.ptr[12];
    ptr[1] = m.ptr[1];  ptr[5] = m.ptr[5];  ptr[9]  = m.ptr[9];     ptr[13] = m.ptr[13];
    ptr[2] = m.ptr[2];  ptr[6] = m.ptr[6];  ptr[10] = m.ptr[10];    ptr[14] = m.ptr[14];
    ptr[3] = m.ptr[3];  ptr[7] = m.ptr[7];  ptr[11] = m.ptr[11];    ptr[15] = m.ptr[15];
    return *this;
}

///=============================================================================
inline ffw::mat4  ffw::mat4::operator * (const ffw::mat4 &m) const{
    mat4 r;
    r.ptr[0] = ptr[0]*m.ptr[0] + ptr[4]*m.ptr[1] + ptr[8]*m.ptr[2] + ptr[12]*m.ptr[3];  r.ptr[4] = ptr[0]*m.ptr[4] + ptr[4]*m.ptr[5] + ptr[8]*m.ptr[6] + ptr[12]*m.ptr[7];  r.ptr[8] = ptr[0]*m.ptr[8] + ptr[4]*m.ptr[9] + ptr[8]*m.ptr[10] + ptr[12]*m.ptr[11];  r.ptr[12] = ptr[0]*m.ptr[12] + ptr[4]*m.ptr[13] + ptr[8]*m.ptr[14] + ptr[12]*m.ptr[15];
    r.ptr[1] = ptr[1]*m.ptr[0] + ptr[5]*m.ptr[1] + ptr[9]*m.ptr[2] + ptr[13]*m.ptr[3];  r.ptr[5] = ptr[1]*m.ptr[4] + ptr[5]*m.ptr[5] + ptr[9]*m.ptr[6] + ptr[13]*m.ptr[7];  r.ptr[9] = ptr[1]*m.ptr[8] + ptr[5]*m.ptr[9] + ptr[9]*m.ptr[10] + ptr[13]*m.ptr[11];  r.ptr[13] = ptr[1]*m.ptr[12] + ptr[5]*m.ptr[13] + ptr[9]*m.ptr[14] + ptr[13]*m.ptr[15];
    r.ptr[2] = ptr[2]*m.ptr[0] + ptr[6]*m.ptr[1] + ptr[10]*m.ptr[2] + ptr[14]*m.ptr[3];  r.ptr[6] = ptr[2]*m.ptr[4] + ptr[6]*m.ptr[5] + ptr[10]*m.ptr[6] + ptr[14]*m.ptr[7];  r.ptr[10] = ptr[2]*m.ptr[8] + ptr[6]*m.ptr[9] + ptr[10]*m.ptr[10] + ptr[14]*m.ptr[11];  r.ptr[14] = ptr[2]*m.ptr[12] + ptr[6]*m.ptr[13] + ptr[10]*m.ptr[14] + ptr[14]*m.ptr[15];
    r.ptr[3] = ptr[3]*m.ptr[0] + ptr[7]*m.ptr[1] + ptr[11]*m.ptr[2] + ptr[15]*m.ptr[3];  r.ptr[7] = ptr[3]*m.ptr[4] + ptr[7]*m.ptr[5] + ptr[11]*m.ptr[6] + ptr[15]*m.ptr[7];  r.ptr[11] = ptr[3]*m.ptr[8] + ptr[7]*m.ptr[9] + ptr[11]*m.ptr[10] + ptr[15]*m.ptr[11];  r.ptr[15] = ptr[3]*m.ptr[12] + ptr[7]*m.ptr[13] + ptr[11]*m.ptr[14] + ptr[15]*m.ptr[15];
    return r;
}

///=============================================================================
inline ffw::mat4&  ffw::mat4::operator *= (const ffw::mat4 &m){
    mat4 r;
    r.ptr[0] = ptr[0]*m.ptr[0] + ptr[4]*m.ptr[1] + ptr[8]*m.ptr[2] + ptr[12]*m.ptr[3];  r.ptr[4] = ptr[0]*m.ptr[4] + ptr[4]*m.ptr[5] + ptr[8]*m.ptr[6] + ptr[12]*m.ptr[7];  r.ptr[8] = ptr[0]*m.ptr[8] + ptr[4]*m.ptr[9] + ptr[8]*m.ptr[10] + ptr[12]*m.ptr[11];  r.ptr[12] = ptr[0]*m.ptr[12] + ptr[4]*m.ptr[13] + ptr[8]*m.ptr[14] + ptr[12]*m.ptr[15];
    r.ptr[1] = ptr[1]*m.ptr[0] + ptr[5]*m.ptr[1] + ptr[9]*m.ptr[2] + ptr[13]*m.ptr[3];  r.ptr[5] = ptr[1]*m.ptr[4] + ptr[5]*m.ptr[5] + ptr[9]*m.ptr[6] + ptr[13]*m.ptr[7];  r.ptr[9] = ptr[1]*m.ptr[8] + ptr[5]*m.ptr[9] + ptr[9]*m.ptr[10] + ptr[13]*m.ptr[11];  r.ptr[13] = ptr[1]*m.ptr[12] + ptr[5]*m.ptr[13] + ptr[9]*m.ptr[14] + ptr[13]*m.ptr[15];
    r.ptr[2] = ptr[2]*m.ptr[0] + ptr[6]*m.ptr[1] + ptr[10]*m.ptr[2] + ptr[14]*m.ptr[3];  r.ptr[6] = ptr[2]*m.ptr[4] + ptr[6]*m.ptr[5] + ptr[10]*m.ptr[6] + ptr[14]*m.ptr[7];  r.ptr[10] = ptr[2]*m.ptr[8] + ptr[6]*m.ptr[9] + ptr[10]*m.ptr[10] + ptr[14]*m.ptr[11];  r.ptr[14] = ptr[2]*m.ptr[12] + ptr[6]*m.ptr[13] + ptr[10]*m.ptr[14] + ptr[14]*m.ptr[15];
    r.ptr[3] = ptr[3]*m.ptr[0] + ptr[7]*m.ptr[1] + ptr[11]*m.ptr[2] + ptr[15]*m.ptr[3];  r.ptr[7] = ptr[3]*m.ptr[4] + ptr[7]*m.ptr[5] + ptr[11]*m.ptr[6] + ptr[15]*m.ptr[7];  r.ptr[11] = ptr[3]*m.ptr[8] + ptr[7]*m.ptr[9] + ptr[11]*m.ptr[10] + ptr[15]*m.ptr[11];  r.ptr[15] = ptr[3]*m.ptr[12] + ptr[7]*m.ptr[13] + ptr[11]*m.ptr[14] + ptr[15]*m.ptr[15];
    *this = r;
    return *this;
}

///=============================================================================
inline float& ffw::mat4::operator [] (int x){
    return ptr[x];
}

#endif
