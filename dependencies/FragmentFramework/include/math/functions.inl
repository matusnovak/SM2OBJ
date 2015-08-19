/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_BASE_FUNCTIONS_INL
#define FFW_BASE_FUNCTIONS_INL

///=============================================================================
template <class T>
inline T ffw::lerp(const T& A, const T& B, float Weight) {
    return (1-Weight)*A + Weight*B;
}

///=============================================================================
template <class T>
inline float dot(const ffw::vec2<T>& V1, const ffw::vec2<T>& V2){
    return (V1.x*V2.x + V1.y*V2.y);
}

///=============================================================================
template <class T>
inline float ffw::dot(const ffw::vec3<T>& V1, const ffw::vec3<T>& V2){
    return (V1.x*V2.x + V1.y*V2.y + V1.z*V2.z);
}

///=============================================================================
template <class T>
inline ffw::vec3<T> ffw::cross(const ffw::vec3<T>& V1, const ffw::vec3<T>& V2){
    ffw::vec3<T> product;
    product.x = V1.y*V2.z - V1.z*V2.y;
    product.y = V1.z*V2.x - V1.x*V2.z;
    product.z = V1.x*V2.y - V1.y*V2.x;
    return product;
}

///=============================================================================
template <class T>
inline ffw::vec2<T> ffw::normalize(const vec2<T>& V){
    ffw::vec2<T> result;
    float l = sqrtf(V.x*V.x + V.y*V.y);
    if( l > 0 ) {
        result.x = V.x/l;
        result.y = V.y/l;
    }
    return result;
}

///=============================================================================
template <class T>
inline ffw::vec3<T> ffw::normalize(const vec3<T>& V){
    ffw::vec3<T> result;
    float l = sqrtf(V.x*V.x + V.y*V.y + V.z*V.z);
    if( l > 0 ) {
        result.x = V.x/l;
        result.y = V.y/l;
        result.z = V.z/l;
    }
    return result;
}

///=============================================================================
template <class T>
inline ffw::vec4<T> ffw::normalize(const vec4<T>& V){
    ffw::vec4<T> result;
    float l = sqrtf(V.x*V.x + V.y*V.y + V.z*V.z + V.w*V.w);
    if( l > 0 ) {
        result.x = V.x/l;
        result.y = V.y/l;
        result.z = V.z/l;
        result.w = V.w/l;
    }
    return result;
}

///=============================================================================
inline ffw::quaternion ffw::normalize(const quaternion& Q){
    quaternion result;
    float n = 1.0f/sqrt(Q.x*Q.x+Q.y*Q.y+Q.z*Q.z+Q.w*Q.w);
    result.x = Q.x * n;
    result.y = Q.y * n;
    result.z = Q.z * n;
    result.w = Q.w * n;
    return result;
}

///=============================================================================
template <class T>
inline float ffw::angle(const ffw::vec3<T>& V1, const ffw::vec3<T>& V2){
    float dot = (V1.x*V2.x + V1.y*V2.y + V1.z*V2.z);
    float V1Length = sqrtf(V1.x*V1.x + V1.y*V1.y + V1.z*V1.z);
    float V2Length = sqrtf(V2.x*V2.x + V2.y*V2.y + V2.z*V2.z);
    return acos(dot / (V1Length*V2Length))*57.29577951;
}

///=============================================================================
template <class T>
inline float ffw::angle(const ffw::vec2<T>& V1, const ffw::vec2<T>& V2){
    float dot = (V1.x*V2.x + V1.y*V2.y);
    float V1Length = sqrtf(V1.x*V1.x + V1.y*V1.y);
    float V2Length = sqrtf(V2.x*V2.x + V2.y*V2.y);
    return acos(dot / (V1Length*V2Length))*57.29577951;
}

///=============================================================================
template <class T>
inline float ffw::angleRad(const ffw::vec3<T>& V1, const ffw::vec3<T>& V2){
    float dot = (V1.x*V2.x + V1.y*V2.y + V1.z*V2.z);
    float V1Length = sqrtf(V1.x*V1.x + V1.y*V1.y + V1.z*V1.z);
    float V2Length = sqrtf(V2.x*V2.x + V2.y*V2.y + V2.z*V2.z);
    return acos(dot / (V1Length*V2Length));
}

///=============================================================================
template <class T>
inline float ffw::angleRad(const ffw::vec2<T>& V1, const ffw::vec2<T>& V2){
    float dot = (V1.x*V2.x + V1.y*V2.y);
    float V1Length = sqrtf(V1.x*V1.x + V1.y*V1.y);
    float V2Length = sqrtf(V2.x*V2.x + V2.y*V2.y);
    return acos(dot / (V1Length*V2Length));
}

///=============================================================================
template<class T>
inline T ffw::clamp(T Val, T Min, T Max){
    return std::max(Min, std::min(Val, Max));
}

///=============================================================================
template<class T>
inline T ffw::remap(T Value, T InMin, T InMax, T OutMin, T OutMax){
    return (Value - InMin) / (InMax - InMin) * (OutMax - OutMin) + OutMin;
}

///=============================================================================
inline unsigned long ffw::nextPowOfTwo(unsigned long Value){
    unsigned long P = 1;
    while(P < Value){
        P *= 2;
    }
    return P;
}

///=============================================================================
inline ffw::mat4 ffw::makeRotationMatrix(const ffw::quaternion& Q){
    mat4 m;

    m[0] = 1.0f - 2.0f * (Q.y * Q.y + Q.z * Q.z);    m[4] = 2.0f * (Q.x * Q.y + Q.z * Q.w);         m[8] = 2.0f * (Q.x * Q.z - Q.y * Q.w);
    m[1] = 2.0f * (Q.x * Q.y - Q.z * Q.w);           m[5] = 1.0f - 2.0f * (Q.x * Q.x + Q.z * Q.z);  m[9] = 2.0f * (Q.y * Q.z + Q.x * Q.w);
    m[2] = 2.0f * (Q.x * Q.z + Q.y * Q.w);           m[6] = 2.0f * (Q.y * Q.z - Q.x * Q.w);         m[10] = 1.0f - 2.0f * (Q.x * Q.x + Q.y * Q.y);

    return m;
}

///=============================================================================
template<class T>
inline ffw::vec3<T> ffw::vec2ToVec3(const vec2<T>& Vec){
    return vec3<T>(Vec.x, Vec.y, 0);
}

///=============================================================================
template<class T>
inline ffw::vec4<T> ffw::vec3ToVec4(const ffw::vec3<T>& Vec){
    return vec4<T>(Vec.x, Vec.y, Vec.z, 0);
}

///=============================================================================
template<class T>
inline ffw::vec3<T> ffw::vec2ToVec3(const ffw::vec2<T>& Vec, T Z){
    return vec3<T>(Vec.x, Vec.y, Z);
}

///=============================================================================
template<class T>
inline ffw::vec4<T> ffw::vec3ToVec4(const ffw::vec3<T>& Vec, T W){
    return vec4<T>(Vec.x, Vec.y, Vec.z, W);
}

///=============================================================================
template<class T>
inline ffw::vec3<T> ffw::vec4ToVec3(const ffw::vec4<T>& Vec){
    return vec3<T>(Vec.x, Vec.y, Vec.z);
}

///=============================================================================
template<class T>
inline ffw::vec2<T> ffw::vec3ToVec2(const ffw::vec3<T>& Vec){
    return vec3<T>(Vec.x, Vec.y);
}

///=============================================================================
inline ffw::vec3f ffw::quatToVec3(const ffw::quaternion& Quat){
    return vec3f(Quat.x, Quat.y, Quat.z);
}

///=============================================================================
inline ffw::vec4f ffw::quatToVec4(const ffw::quaternion& Quat){
    return vec4f(Quat.x, Quat.y, Quat.z, Quat.w);
}

///=============================================================================
template<class T> ffw::quaternion ffw::vec4ToQuat(const ffw::vec4<T>& Vec){
    return quaternion(Vec.x, Vec.y, Vec.z, Vec.w);
}

///=============================================================================
#ifdef _USING_MSVC
inline unsigned short ffw::byteSwap16(unsigned short Value){
	return _byteswap_ushort(Value);
}

inline unsigned long ffw::byteSwap32(unsigned long Value){
	return _byteswap_ulong(Value);
}

inline unsigned long long ffw::byteSwap64(unsigned long long Value){
	return _byteswap_uint64(Value);
}
#endif

#ifdef _USING_MINGW
inline unsigned short ffw::byteSwap16(unsigned short Value){
	return __builtin_bswap16(Value);
}

inline unsigned long ffw::byteSwap32(unsigned long Value){
	return __builtin_bswap32(Value);
}

inline unsigned long long ffw::byteSwap64(unsigned long long Value){
	return __builtin_bswap64(Value);
}
#endif

///=============================================================================
template <class T>
inline std::ostream& ffw::operator << (std::ostream& os, const ffw::vec2<T>& V){
    os << V.x << ", " << V.y;
    return os;
}

///=============================================================================
template <class T>
inline std::ostream& ffw::operator << (std::ostream& os, const ffw::vec3<T>& V){
    os << V.x << ", " << V.y << ", " << V.z;
    return os;
}

///=============================================================================
template <class T>
inline std::ostream& ffw::operator << (std::ostream& os, const ffw::vec4<T>& V){
    os << V.x << ", " << V.y << ", " << V.z << ", " << V.w;
    return os;
}

///=============================================================================
inline std::ostream& ffw::operator << (std::ostream& os, const ffw::quaternion& Q){
    os << Q.x << ", " << Q.y << ", " << Q.z << ", " << Q.w;
    return os;
}

///=============================================================================
inline std::ostream& ffw::operator << (std::ostream& os, const ffw::color& C){
    os << C.r << ", " << C.g << ", " << C.b << ", " << C.a;
    return os;
}

#endif

