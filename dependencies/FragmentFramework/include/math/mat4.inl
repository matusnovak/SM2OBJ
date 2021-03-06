/*** This file is part of FragmentFramework project ***/

///=============================================================================
template <class T>
inline ffw::mat4x4<T>::mat4x4(){
    ptr[0] = 1.0f;  ptr[4] = 0.0f;  ptr[8]  = 0.0f; ptr[12] = 0.0f;
    ptr[1] = 0.0f;  ptr[5] = 1.0f;  ptr[9]  = 0.0f; ptr[13] = 0.0f;
    ptr[2] = 0.0f;  ptr[6] = 0.0f;  ptr[10] = 1.0f; ptr[14] = 0.0f;
    ptr[3] = 0.0f;  ptr[7] = 0.0f;  ptr[11] = 0.0f; ptr[15] = 1.0f;
}

///=============================================================================
template <class T>
inline ffw::mat4x4<T>::mat4x4( T xx, T yx, T zx, T wx,
                        T xy, T yy, T zy, T wy,
                        T xz, T yz, T zz, T wz,
                        T xw, T yw, T zw, T ww){
    ptr[0] = xx;    ptr[4] = yx;    ptr[8]  = zx;   ptr[12] = wx;
    ptr[1] = xy;    ptr[5] = yy;    ptr[9]  = zy;   ptr[13] = wy;
    ptr[2] = xz;    ptr[6] = yz;    ptr[10] = zz;   ptr[14] = wz;
    ptr[3] = xw;    ptr[7] = yw;    ptr[11] = zw;   ptr[15] = ww;
}

///=============================================================================
template <class T>
inline ffw::mat4x4<T>::mat4x4(T Val){
    ptr[0] = Val;   ptr[4] = 0.0f;  ptr[8]  = 0.0f; ptr[12] = 0.0f;
    ptr[1] = 0.0f;  ptr[5] = Val;   ptr[9]  = 0.0f; ptr[13] = 0.0f;
    ptr[2] = 0.0f;  ptr[6] = 0.0f;  ptr[10] = Val;  ptr[14] = 0.0f;
    ptr[3] = 0.0f;  ptr[7] = 0.0f;  ptr[11] = 0.0f; ptr[15] = Val;
}

///=============================================================================
template <class T>
inline ffw::mat4x4<T>::mat4x4(std::initializer_list<T> List){
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
template <class T>
inline void ffw::mat4x4<T>::set( T xx, T yx, T zx, T wx,
                            T xy, T yy, T zy, T wy,
                            T xz, T yz, T zz, T wz,
                            T xw, T yw, T zw, T ww){
    ptr[0] = xx;    ptr[4] = yx;    ptr[8]  = zx;   ptr[12] = wx;
    ptr[1] = xy;    ptr[5] = yy;    ptr[9]  = zy;   ptr[13] = wy;
    ptr[2] = xz;    ptr[6] = yz;    ptr[10] = zz;   ptr[14] = wz;
    ptr[3] = xw;    ptr[7] = yw;    ptr[11] = zw;   ptr[15] = ww;
}

///=============================================================================
template <class T>
inline void ffw::mat4x4<T>::set(T Val){
    ptr[0] = Val;   ptr[4] = 0.0f;  ptr[8]  = 0.0f; ptr[12] = 0.0f;
    ptr[1] = 0.0f;  ptr[5] = Val;   ptr[9]  = 0.0f; ptr[13] = 0.0f;
    ptr[2] = 0.0f;  ptr[6] = 0.0f;  ptr[10] = Val;  ptr[14] = 0.0f;
    ptr[3] = 0.0f;  ptr[7] = 0.0f;  ptr[11] = 0.0f; ptr[15] = Val;
}

///=============================================================================
template <class T>
inline void ffw::mat4x4<T>::set(T m[16]){
    ptr[0] = m[0];    ptr[4] = m[4];    ptr[8]  = m[8];   ptr[12] = m[12];
    ptr[1] = m[1];    ptr[5] = m[5];    ptr[9]  = m[9];   ptr[13] = m[13];
    ptr[2] = m[2];    ptr[6] = m[6];    ptr[10] = m[10];  ptr[14] = m[14];
    ptr[3] = m[3];    ptr[7] = m[7];    ptr[11] = m[11];  ptr[15] = m[15];
}

///=============================================================================
template <class T>
inline void ffw::mat4x4<T>::set(std::initializer_list<T> List){
    if(List.size() != 16){
        return;
    }
    for(int i = 0; i < 16; i++){
        ptr[i] = *(List.begin()+i);
    }
}

///=============================================================================
template <class T>
inline T* ffw::mat4x4<T>::getPtr(){
    return &ptr[0];
}

///=============================================================================
template <class T>
inline const T* ffw::mat4x4<T>::getPtr() const {
    return &ptr[0];
}

///=============================================================================
template <class T>
inline ffw::mat4x4<T>& ffw::mat4x4<T>::operator = (const ffw::mat4x4<T> &m){
    ptr[0] = m.ptr[0];  ptr[4] = m.ptr[4];  ptr[8]  = m.ptr[8];     ptr[12] = m.ptr[12];
    ptr[1] = m.ptr[1];  ptr[5] = m.ptr[5];  ptr[9]  = m.ptr[9];     ptr[13] = m.ptr[13];
    ptr[2] = m.ptr[2];  ptr[6] = m.ptr[6];  ptr[10] = m.ptr[10];    ptr[14] = m.ptr[14];
    ptr[3] = m.ptr[3];  ptr[7] = m.ptr[7];  ptr[11] = m.ptr[11];    ptr[15] = m.ptr[15];
    return *this;
}

///=============================================================================
template <class T>
inline ffw::mat4x4<T>  ffw::mat4x4<T>::operator * (const ffw::mat4x4<T> &m) const{
    mat4x4 r;
    r.ptr[0] = ptr[0]*m.ptr[0] + ptr[4]*m.ptr[1] + ptr[8]*m.ptr[2] + ptr[12]*m.ptr[3];  r.ptr[4] = ptr[0]*m.ptr[4] + ptr[4]*m.ptr[5] + ptr[8]*m.ptr[6] + ptr[12]*m.ptr[7];  r.ptr[8] = ptr[0]*m.ptr[8] + ptr[4]*m.ptr[9] + ptr[8]*m.ptr[10] + ptr[12]*m.ptr[11];  r.ptr[12] = ptr[0]*m.ptr[12] + ptr[4]*m.ptr[13] + ptr[8]*m.ptr[14] + ptr[12]*m.ptr[15];
    r.ptr[1] = ptr[1]*m.ptr[0] + ptr[5]*m.ptr[1] + ptr[9]*m.ptr[2] + ptr[13]*m.ptr[3];  r.ptr[5] = ptr[1]*m.ptr[4] + ptr[5]*m.ptr[5] + ptr[9]*m.ptr[6] + ptr[13]*m.ptr[7];  r.ptr[9] = ptr[1]*m.ptr[8] + ptr[5]*m.ptr[9] + ptr[9]*m.ptr[10] + ptr[13]*m.ptr[11];  r.ptr[13] = ptr[1]*m.ptr[12] + ptr[5]*m.ptr[13] + ptr[9]*m.ptr[14] + ptr[13]*m.ptr[15];
    r.ptr[2] = ptr[2]*m.ptr[0] + ptr[6]*m.ptr[1] + ptr[10]*m.ptr[2] + ptr[14]*m.ptr[3];  r.ptr[6] = ptr[2]*m.ptr[4] + ptr[6]*m.ptr[5] + ptr[10]*m.ptr[6] + ptr[14]*m.ptr[7];  r.ptr[10] = ptr[2]*m.ptr[8] + ptr[6]*m.ptr[9] + ptr[10]*m.ptr[10] + ptr[14]*m.ptr[11];  r.ptr[14] = ptr[2]*m.ptr[12] + ptr[6]*m.ptr[13] + ptr[10]*m.ptr[14] + ptr[14]*m.ptr[15];
    r.ptr[3] = ptr[3]*m.ptr[0] + ptr[7]*m.ptr[1] + ptr[11]*m.ptr[2] + ptr[15]*m.ptr[3];  r.ptr[7] = ptr[3]*m.ptr[4] + ptr[7]*m.ptr[5] + ptr[11]*m.ptr[6] + ptr[15]*m.ptr[7];  r.ptr[11] = ptr[3]*m.ptr[8] + ptr[7]*m.ptr[9] + ptr[11]*m.ptr[10] + ptr[15]*m.ptr[11];  r.ptr[15] = ptr[3]*m.ptr[12] + ptr[7]*m.ptr[13] + ptr[11]*m.ptr[14] + ptr[15]*m.ptr[15];
    return r;
}

///=============================================================================
template <class T>
inline ffw::mat4x4<T>&  ffw::mat4x4<T>::operator *= (const ffw::mat4x4<T> &m){
    mat4x4 r;
    r.ptr[0] = ptr[0]*m.ptr[0] + ptr[4]*m.ptr[1] + ptr[8]*m.ptr[2] + ptr[12]*m.ptr[3];  r.ptr[4] = ptr[0]*m.ptr[4] + ptr[4]*m.ptr[5] + ptr[8]*m.ptr[6] + ptr[12]*m.ptr[7];  r.ptr[8] = ptr[0]*m.ptr[8] + ptr[4]*m.ptr[9] + ptr[8]*m.ptr[10] + ptr[12]*m.ptr[11];  r.ptr[12] = ptr[0]*m.ptr[12] + ptr[4]*m.ptr[13] + ptr[8]*m.ptr[14] + ptr[12]*m.ptr[15];
    r.ptr[1] = ptr[1]*m.ptr[0] + ptr[5]*m.ptr[1] + ptr[9]*m.ptr[2] + ptr[13]*m.ptr[3];  r.ptr[5] = ptr[1]*m.ptr[4] + ptr[5]*m.ptr[5] + ptr[9]*m.ptr[6] + ptr[13]*m.ptr[7];  r.ptr[9] = ptr[1]*m.ptr[8] + ptr[5]*m.ptr[9] + ptr[9]*m.ptr[10] + ptr[13]*m.ptr[11];  r.ptr[13] = ptr[1]*m.ptr[12] + ptr[5]*m.ptr[13] + ptr[9]*m.ptr[14] + ptr[13]*m.ptr[15];
    r.ptr[2] = ptr[2]*m.ptr[0] + ptr[6]*m.ptr[1] + ptr[10]*m.ptr[2] + ptr[14]*m.ptr[3];  r.ptr[6] = ptr[2]*m.ptr[4] + ptr[6]*m.ptr[5] + ptr[10]*m.ptr[6] + ptr[14]*m.ptr[7];  r.ptr[10] = ptr[2]*m.ptr[8] + ptr[6]*m.ptr[9] + ptr[10]*m.ptr[10] + ptr[14]*m.ptr[11];  r.ptr[14] = ptr[2]*m.ptr[12] + ptr[6]*m.ptr[13] + ptr[10]*m.ptr[14] + ptr[14]*m.ptr[15];
    r.ptr[3] = ptr[3]*m.ptr[0] + ptr[7]*m.ptr[1] + ptr[11]*m.ptr[2] + ptr[15]*m.ptr[3];  r.ptr[7] = ptr[3]*m.ptr[4] + ptr[7]*m.ptr[5] + ptr[11]*m.ptr[6] + ptr[15]*m.ptr[7];  r.ptr[11] = ptr[3]*m.ptr[8] + ptr[7]*m.ptr[9] + ptr[11]*m.ptr[10] + ptr[15]*m.ptr[11];  r.ptr[15] = ptr[3]*m.ptr[12] + ptr[7]*m.ptr[13] + ptr[11]*m.ptr[14] + ptr[15]*m.ptr[15];
    *this = r;
    return *this;
}

///=============================================================================
template <class T>
template <class S>
inline ffw::vec4<S> ffw::mat4x4<T>::operator * (const ffw::vec4<S>& V) const {
    ffw::vec4f r;
    r.x = V.x*ptr[0] + V.y*ptr[4] + V.z*ptr[8]  + V.w*ptr[12];
    r.y = V.x*ptr[1] + V.y*ptr[5] + V.z*ptr[9]  + V.w*ptr[13];
    r.z = V.x*ptr[2] + V.y*ptr[6] + V.z*ptr[10] + V.w*ptr[14];
    r.w = V.x*ptr[3] + V.y*ptr[7] + V.z*ptr[11] + V.w*ptr[15];
    return r;
}

///=============================================================================
template <class T> 
template <class S>
inline ffw::vec3<S> ffw::mat4x4<T>::operator * (const ffw::vec3<S>& V) const {
    ffw::vec3f r;
    r.x = V.x*ptr[0] + V.y*ptr[4] + V.z*ptr[8]  + ptr[12];
    r.y = V.x*ptr[1] + V.y*ptr[5] + V.z*ptr[9]  + ptr[13];
    r.z = V.x*ptr[2] + V.y*ptr[6] + V.z*ptr[10] + ptr[14];
    //r.w = V.x*ptr[3] + V.y*ptr[7] + V.z*ptr[11] + V.w*ptr[15];
    return r;
}

///=============================================================================
template <class T>
inline T& ffw::mat4x4<T>::operator [] (int x){
    return ptr[x];
}

///=============================================================================
template <class T>
inline const T& ffw::mat4x4<T>::operator [] (int x) const {
    return ptr[x];
}

///=============================================================================
template <class T>
inline ffw::mat4x4<T>& ffw::mat4x4<T>::rotate(const ffw::quat<T>& Q){
    mat4x4 m;

    m[0] = 1.0f - 2.0f * (Q.y * Q.y + Q.z * Q.z);    m[4] = 2.0f * (Q.x * Q.y + Q.z * Q.w);         m[8] = 2.0f * (Q.x * Q.z - Q.y * Q.w);
    m[1] = 2.0f * (Q.x * Q.y - Q.z * Q.w);           m[5] = 1.0f - 2.0f * (Q.x * Q.x + Q.z * Q.z);  m[9] = 2.0f * (Q.y * Q.z + Q.x * Q.w);
    m[2] = 2.0f * (Q.x * Q.z + Q.y * Q.w);           m[6] = 2.0f * (Q.y * Q.z - Q.x * Q.w);         m[10] = 1.0f - 2.0f * (Q.x * Q.x + Q.y * Q.y);

    (*this) *= m;

    return *this;
}

///=============================================================================
template <class T>
inline ffw::mat4x4<T>& ffw::mat4x4<T>::translate(T X, T Y, T Z){
    ptr[12] += X;
    ptr[13] += Y;
    ptr[14] += Z;

    return *this;
}

///=============================================================================
template <class T>
inline ffw::mat4x4<T>& ffw::mat4x4<T>::scale(T X, T Y, T Z){
    mat4x4 m;

    m[0] = X;
    m[5] = Y;
    m[10] = Z;

    (*this) *= m;

    return *this;
}

///=============================================================================
template <class T>
inline ffw::mat4x4<T>& ffw::mat4x4<T>::transpose(){
    T m04 = ptr[4];
    T m08 = ptr[8];
    T m09 = ptr[9];
    T m12 = ptr[12];
    T m13 = ptr[13];
    T m14 = ptr[14];

    ptr[4] = ptr[1];
    ptr[8] = ptr[2];
    ptr[9] = ptr[6];
    ptr[12] = ptr[3];
    ptr[13] = ptr[7];
    ptr[14] = ptr[11];

    ptr[1] = m04;
    ptr[2] = m08;
    ptr[6] = m09;
    ptr[3] = m12;
    ptr[7] = m13;
    ptr[11] = m14;

    return *this;
}

///=============================================================================
template <class T>
inline ffw::mat4x4<T>& ffw::mat4x4<T>::inverse(){
    T inv[16];

    inv[0] = ptr[5]  * ptr[10] * ptr[15] - ptr[5]  * ptr[11] * ptr[14] - ptr[9]  * ptr[6]  * ptr[15] + ptr[9]  * ptr[7]  * ptr[14] +ptr[13] * ptr[6]  * ptr[11] - ptr[13] * ptr[7]  * ptr[10];
    inv[4] = -ptr[4]  * ptr[10] * ptr[15] + ptr[4]  * ptr[11] * ptr[14] + ptr[8]  * ptr[6]  * ptr[15] - ptr[8]  * ptr[7]  * ptr[14] - ptr[12] * ptr[6]  * ptr[11] + ptr[12] * ptr[7]  * ptr[10];
    inv[8] = ptr[4]  * ptr[9] * ptr[15] - ptr[4]  * ptr[11] * ptr[13] - ptr[8]  * ptr[5] * ptr[15] + ptr[8]  * ptr[7] * ptr[13] + ptr[12] * ptr[5] * ptr[11] - ptr[12] * ptr[7] * ptr[9];
    inv[12] = -ptr[4]  * ptr[9] * ptr[14] + ptr[4]  * ptr[10] * ptr[13] +ptr[8]  * ptr[5] * ptr[14] - ptr[8]  * ptr[6] * ptr[13] - ptr[12] * ptr[5] * ptr[10] + ptr[12] * ptr[6] * ptr[9];
    inv[1] = -ptr[1]  * ptr[10] * ptr[15] + ptr[1]  * ptr[11] * ptr[14] + ptr[9]  * ptr[2] * ptr[15] - ptr[9]  * ptr[3] * ptr[14] - ptr[13] * ptr[2] * ptr[11] + ptr[13] * ptr[3] * ptr[10];
    inv[5] = ptr[0]  * ptr[10] * ptr[15] - ptr[0]  * ptr[11] * ptr[14] - ptr[8]  * ptr[2] * ptr[15] + ptr[8]  * ptr[3] * ptr[14] + ptr[12] * ptr[2] * ptr[11] - ptr[12] * ptr[3] * ptr[10];
    inv[9] = -ptr[0]  * ptr[9] * ptr[15] + ptr[0]  * ptr[11] * ptr[13] + ptr[8]  * ptr[1] * ptr[15] - ptr[8]  * ptr[3] * ptr[13] - ptr[12] * ptr[1] * ptr[11] + ptr[12] * ptr[3] * ptr[9];
    inv[13] = ptr[0]  * ptr[9] * ptr[14] - ptr[0]  * ptr[10] * ptr[13] - ptr[8]  * ptr[1] * ptr[14] + ptr[8]  * ptr[2] * ptr[13] + ptr[12] * ptr[1] * ptr[10] - ptr[12] * ptr[2] * ptr[9];
    inv[2] = ptr[1]  * ptr[6] * ptr[15] - ptr[1]  * ptr[7] * ptr[14] - ptr[5]  * ptr[2] * ptr[15] + ptr[5]  * ptr[3] * ptr[14] + ptr[13] * ptr[2] * ptr[7] - ptr[13] * ptr[3] * ptr[6];
    inv[6] = -ptr[0]  * ptr[6] * ptr[15] + ptr[0]  * ptr[7] * ptr[14] + ptr[4]  * ptr[2] * ptr[15] - ptr[4]  * ptr[3] * ptr[14] - ptr[12] * ptr[2] * ptr[7] + ptr[12] * ptr[3] * ptr[6];
    inv[10] = ptr[0]  * ptr[5] * ptr[15] - ptr[0]  * ptr[7] * ptr[13] - ptr[4]  * ptr[1] * ptr[15] + ptr[4]  * ptr[3] * ptr[13] + ptr[12] * ptr[1] * ptr[7] - ptr[12] * ptr[3] * ptr[5];
    inv[14] = -ptr[0]  * ptr[5] * ptr[14] + ptr[0]  * ptr[6] * ptr[13] + ptr[4]  * ptr[1] * ptr[14] - ptr[4]  * ptr[2] * ptr[13] - ptr[12] * ptr[1] * ptr[6] + ptr[12] * ptr[2] * ptr[5];
    inv[3] = -ptr[1] * ptr[6] * ptr[11] + ptr[1] * ptr[7] * ptr[10] + ptr[5] * ptr[2] * ptr[11] - ptr[5] * ptr[3] * ptr[10] - ptr[9] * ptr[2] * ptr[7] + ptr[9] * ptr[3] * ptr[6];
    inv[7] = ptr[0] * ptr[6] * ptr[11] - ptr[0] * ptr[7] * ptr[10] - ptr[4] * ptr[2] * ptr[11] + ptr[4] * ptr[3] * ptr[10] + ptr[8] * ptr[2] * ptr[7] - ptr[8] * ptr[3] * ptr[6];
    inv[11] = -ptr[0] * ptr[5] * ptr[11] + ptr[0] * ptr[7] * ptr[9] + ptr[4] * ptr[1] * ptr[11] - ptr[4] * ptr[3] * ptr[9] - ptr[8] * ptr[1] * ptr[7] + ptr[8] * ptr[3] * ptr[5];
    inv[15] = ptr[0] * ptr[5] * ptr[10] - ptr[0] * ptr[6] * ptr[9] - ptr[4] * ptr[1] * ptr[10] + ptr[4] * ptr[2] * ptr[9] + ptr[8] * ptr[1] * ptr[6] - ptr[8] * ptr[2] * ptr[5];

    T det = ptr[0] * inv[0] + ptr[1] * inv[4] + ptr[2] * inv[8] + ptr[3] * inv[12];

    det = 1.0f / det;

    for(int i = 0; i < 16; i++)ptr[i] = inv[i] * det;

    /*T det =
        ptr[3] *ptr[6] *ptr[9] *ptr[12] - ptr[2] *ptr[7] *ptr[9] *ptr[12] - ptr[3] *ptr[5] *ptr[10]*ptr[12] + ptr[1] *ptr[7] *ptr[10]*ptr[12] +
        ptr[2] *ptr[5] *ptr[11]*ptr[12] - ptr[1] *ptr[6] *ptr[11]*ptr[12] - ptr[3] *ptr[6] *ptr[8] *ptr[13] + ptr[2] *ptr[7] *ptr[8] *ptr[13] +
        ptr[3] *ptr[4] *ptr[10]*ptr[13] - ptr[0] *ptr[7] *ptr[10]*ptr[13] - ptr[2] *ptr[4] *ptr[11]*ptr[13] + ptr[0] *ptr[6] *ptr[11]*ptr[13] +
        ptr[3] *ptr[5] *ptr[8] *ptr[14] - ptr[1] *ptr[7] *ptr[8] *ptr[14] - ptr[3] *ptr[4] *ptr[9] *ptr[14] + ptr[0] *ptr[7] *ptr[9] *ptr[14] +
        ptr[1] *ptr[4] *ptr[11]*ptr[14] - ptr[0] *ptr[5] *ptr[11]*ptr[14] - ptr[2] *ptr[5] *ptr[8] *ptr[15] + ptr[1] *ptr[6] *ptr[8] *ptr[15] +
        ptr[2] *ptr[4] *ptr[9] *ptr[15] - ptr[0] *ptr[6] *ptr[9] *ptr[15] - ptr[1] *ptr[4] *ptr[10]*ptr[15] + ptr[0] *ptr[5] *ptr[10]*ptr[15];

    b[0]  = ptr[6] *ptr[11]*ptr[13] - ptr[7] *ptr[10]*ptr[13] + ptr[7] *ptr[9] *ptr[14] - ptr[5] *ptr[11]*ptr[14] - ptr[6] *ptr[9] *ptr[15] + ptr[5] *ptr[10]*ptr[15];
    b[1]  = ptr[3] *ptr[10]*ptr[13] - ptr[2] *ptr[11]*ptr[13] - ptr[3] *ptr[9] *ptr[14] + ptr[1] *ptr[11]*ptr[14] + ptr[2] *ptr[9] *ptr[15] - ptr[1] *ptr[10]*ptr[15];
    b[2]  = ptr[2] *ptr[7] *ptr[13] - ptr[3] *ptr[6] *ptr[13] + ptr[3] *ptr[5] *ptr[14] - ptr[1] *ptr[7] *ptr[14] - ptr[2] *ptr[5] *ptr[15] + ptr[1] *ptr[6] *ptr[15];
    b[3]  = ptr[3] *ptr[6] *ptr[9]  - ptr[2] *ptr[7] *ptr[9]  - ptr[3] *ptr[5] *ptr[10] + ptr[1] *ptr[7] *ptr[10] + ptr[2] *ptr[5] *ptr[11] - ptr[1] *ptr[6] *ptr[11];
    b[4]  = ptr[7] *ptr[10]*ptr[12] - ptr[6] *ptr[11]*ptr[12] - ptr[7] *ptr[8] *ptr[14] + ptr[4] *ptr[11]*ptr[14] + ptr[6] *ptr[8] *ptr[15] - ptr[4] *ptr[10]*ptr[15];
    b[5]  = ptr[2] *ptr[11]*ptr[12] - ptr[3] *ptr[10]*ptr[12] + ptr[3] *ptr[8] *ptr[14] - ptr[0] *ptr[11]*ptr[14] - ptr[2] *ptr[8] *ptr[15] + ptr[0] *ptr[10]*ptr[15];
    b[6]  = ptr[3] *ptr[6] *ptr[12] - ptr[2] *ptr[7] *ptr[12] - ptr[3] *ptr[4] *ptr[14] + ptr[0] *ptr[7] *ptr[14] + ptr[2] *ptr[4] *ptr[15] - ptr[0] *ptr[6] *ptr[15];
    b[7]  = ptr[2] *ptr[7] *ptr[8]  - ptr[3] *ptr[6] *ptr[8]  + ptr[3] *ptr[4] *ptr[10] - ptr[0] *ptr[7] *ptr[10] - ptr[2] *ptr[4] *ptr[11] + ptr[0] *ptr[6] *ptr[11];
    b[8]  = ptr[5] *ptr[11]*ptr[12] - ptr[7] *ptr[9] *ptr[12] + ptr[7] *ptr[8] *ptr[13] - ptr[4] *ptr[11]*ptr[13] - ptr[5] *ptr[8] *ptr[15] + ptr[4] *ptr[9] *ptr[15];
    b[9]  = ptr[3] *ptr[9] *ptr[12] - ptr[1] *ptr[11]*ptr[12] - ptr[3] *ptr[8] *ptr[13] + ptr[0] *ptr[11]*ptr[13] + ptr[1] *ptr[8] *ptr[15] - ptr[0] *ptr[9] *ptr[15];
    b[10] = ptr[1] *ptr[7] *ptr[12] - ptr[3] *ptr[5] *ptr[12] + ptr[3] *ptr[4] *ptr[13] - ptr[0] *ptr[7] *ptr[13] - ptr[1] *ptr[4] *ptr[15] + ptr[0] *ptr[5] *ptr[15];
    b[11] = ptr[3] *ptr[5] *ptr[8]  - ptr[1] *ptr[7] *ptr[8]  - ptr[3] *ptr[4] *ptr[9]  + ptr[0] *ptr[7] *ptr[9]  + ptr[1] *ptr[4] *ptr[11] - ptr[0] *ptr[5] *ptr[11];
    b[12] = ptr[6] *ptr[9] *ptr[12] - ptr[5] *ptr[10]*ptr[12] - ptr[6] *ptr[8] *ptr[13] + ptr[4] *ptr[10]*ptr[13] + ptr[5] *ptr[8] *ptr[14] - ptr[4] *ptr[9] *ptr[14];
    b[13] = ptr[1] *ptr[10]*ptr[12] - ptr[2] *ptr[9] *ptr[12] + ptr[2] *ptr[8] *ptr[13] - ptr[0] *ptr[10]*ptr[13] - ptr[1] *ptr[8] *ptr[14] + ptr[0] *ptr[9] *ptr[14];
    b[14] = ptr[2] *ptr[5] *ptr[12] - ptr[1] *ptr[6] *ptr[12] - ptr[2] *ptr[4] *ptr[13] + ptr[0] *ptr[6] *ptr[13] + ptr[1] *ptr[4] *ptr[14] - ptr[0] *ptr[5] *ptr[14];
    b[15] = ptr[1] *ptr[6] *ptr[8]  - ptr[2] *ptr[5] *ptr[8]  + ptr[2] *ptr[4] *ptr[9]  - ptr[0] *ptr[6] *ptr[9]  - ptr[1] *ptr[4] *ptr[10] + ptr[0] *ptr[5] *ptr[10];

    det = 1.0 / det;

    for(int i = 0; i < 16; i++){
        ptr[i] = b[i] * det;
    }*/

    return *this;
}
