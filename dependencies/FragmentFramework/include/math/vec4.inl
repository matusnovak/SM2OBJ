/*** This file is part of FragmentFramework project ***/

///=============================================================================
template <class T>
inline ffw::vec4<T>::vec4(){
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>::vec4(T X, T Y, T Z, T W){
    x = X;
    y = Y;
    z = Z;
    w = W;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>::vec4(T Value){
    x = Value;
    y = Value;
    z = Value;
    w = Value;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>::vec4(const vec4<T>& V){
    x = V.x;
    y = V.y;
    z = V.z;
    w = V.w;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>::vec4(std::initializer_list<T> List){
    if(List.size() != 4){
        x = 0;
        y = 0;
        z = 0;
        w = 0;
        return;
    }
    x = *(List.begin());
    y = *(List.begin()+1);
    z = *(List.begin()+2);
    w = *(List.begin()+3);
}

///=============================================================================
template <class T>
inline void ffw::vec4<T>::set(T X, T Y, T Z, T W){
    x = X;
    y = Y;
    z = Z;
    w = W;
}

///=============================================================================
template <class T>
inline void ffw::vec4<T>::set(T Value){
    x = Value;
    y = Value;
    z = Value;
    w = Value;
}

///=============================================================================
template <class T>
inline void ffw::vec4<T>::set(const vec4<T>& V){
    x = V.x;
    y = V.y;
    z = V.z;
    w = V.w;
}

///=============================================================================
template <class T>
inline void ffw::vec4<T>::set(std::initializer_list<T> List){
    if(List.size() != 4)return;
    x = *(List.begin());
    y = *(List.begin()+1);
    z = *(List.begin()+2);
    w = *(List.begin()+2);
}

///=============================================================================
template <class T>
inline ffw::vec4<T>  ffw::vec4<T>::operator - () const{
    return vec4<T>(-x, -y, -z, -w);
}

///=============================================================================
template <class T>
inline ffw::vec4<T>& ffw::vec4<T>::operator =  (const vec4<T>& V){
    x = V.x;
    y = V.y;
    z = V.z;
    w = V.w;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>  ffw::vec4<T>::operator +  (const vec4<T>& V) const{
    return vec4<T>(x + V.x, y + V.y, z + V.z, w + V.w);
}

///=============================================================================
template <class T>
inline ffw::vec4<T>& ffw::vec4<T>::operator += (const vec4<T>& V){
    x += V.x;
    y += V.y;
    z += V.z;
    w += V.w;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>  ffw::vec4<T>::operator -  (const vec4<T>& V) const{
    return vec4<T>(x - V.x, y - V.y, z - V.z, w - V.w);
}

///=============================================================================
template <class T>
inline ffw::vec4<T>& ffw::vec4<T>::operator -= (const vec4<T>& V){
    x -= V.x;
    y -= V.y;
    z -= V.z;
    w -= V.w;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>  ffw::vec4<T>::operator /  (const vec4<T>& V) const{
    return vec4<T>(x / V.x, y / V.y, z / V.z, w / V.w);
}

///=============================================================================
template <class T>
inline ffw::vec4<T>& ffw::vec4<T>::operator /= (const vec4<T>& V){
    x /= V.x;
    y /= V.y;
    z /= V.z;
    w /= V.w;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>  ffw::vec4<T>::operator *  (const vec4<T>& V) const{
    return vec4<T>(x * V.x, y * V.y, z * V.z, w * V.w);
}

///=============================================================================
template <class T>
inline ffw::vec4<T>& ffw::vec4<T>::operator *= (const vec4<T>& V){
    x *= V.x;
    y *= V.y;
    z *= V.z;
    w *= V.w;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>& ffw::vec4<T>::operator =  (const T& Val){
    x = Val;
    y = Val;
    z = Val;
    w = Val;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>  ffw::vec4<T>::operator +  (const T& Val) const{
    return vec4<T>(x + Val, y + Val, z + Val, w + Val);
}

///=============================================================================
template <class T>
inline ffw::vec4<T>& ffw::vec4<T>::operator += (const T& Val){
    x += Val;
    y += Val;
    z += Val;
    w += Val;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>  ffw::vec4<T>::operator -  (const T& Val) const{
    return vec4<T>(x - Val, y - Val, z - Val, w - Val);
}

///=============================================================================
template <class T>
inline ffw::vec4<T>& ffw::vec4<T>::operator -= (const T& Val){
    x -= Val;
    y -= Val;
    z -= Val;
    w -= Val;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>  ffw::vec4<T>::operator /  (const T& Val) const{
    return vec4<T>(x / Val, y / Val, z / Val, w / Val);
}

///=============================================================================
template <class T>
inline ffw::vec4<T>& ffw::vec4<T>::operator /= (const T& Val){
    x /= Val;
    y /= Val;
    z /= Val;
    w /= Val;
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>  ffw::vec4<T>::operator *  (const T& Val) const{
    return vec4<T>(x * Val, y * Val, z * Val, w * Val);
}

///=============================================================================
template <class T>
inline ffw::vec4<T>& ffw::vec4<T>::operator *= (const T& Val){
    x *= Val;
    y *= Val;
    z *= Val;
    w *= Val;
    return *this;
}

///=============================================================================
template <class T>
inline bool ffw::vec4<T>::operator != (const vec4<T>& V) const{
    return (x != V.x || y != V.y || z != V.z || w != V.w);
}

///=============================================================================
template <class T>
inline bool ffw::vec4<T>::operator == (const vec4<T>& V) const{
    return (x == V.x && y == V.y && z == V.z && w == V.w);
}

///=============================================================================
template <class T>
inline ffw::vec4<T>& ffw::vec4<T>::normalize(){
    float l = sqrtf(x*x + y*y + z*z + w*w);
    if( l > 0 ) {
        x = x/l;
        y = y/l;
        z = z/l;
        w = w/l;
    }
    return *this;
}

///=============================================================================
template <class T>
inline ffw::vec4<T>& ffw::vec4<T>::scale(const T Val){
    x = x*Val;
    y = y*Val;
    z = z*Val;
    w = w*Val;
    return *this;
}

///=============================================================================
template <class T>
inline float ffw::vec4<T>::length() const{
    return sqrtf(x*x + y*y + z*z + w*w);
}

///=============================================================================
template <class T>
inline T ffw::vec4<T>::lengthSqrd() const{
    return (x*x + y*y + z*z + w*w);
}

///=============================================================================
template <class T>
template <class S>
inline ffw::vec4<T>::operator ffw::vec4<S>() const {
    return ffw::vec4<S>((S)x, (S)y, (S)z, (S)w);
}
