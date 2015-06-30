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
inline ffw::vec2<T> ffw::lerp(const ffw::vec2<T>& A, const ffw::vec2<T>& B, float Weight) {
    vec2<T> result;
    result.x = A.x*(1-Weight) + B.x*Weight;
    result.y = A.y*(1-Weight) + B.y*Weight;
    return result;
}

///=============================================================================
template <class T>
inline ffw::vec3<T> ffw::lerp(const ffw::vec3<T>& A, const ffw::vec3<T>& B, float Weight) {
    vec3<T> result;
    result.x = A.x*(1-Weight) + B.x*Weight;
    result.y = A.y*(1-Weight) + B.y*Weight;
    result.z = A.z*(1-Weight) + B.z*Weight;
    return result;
}

///=============================================================================
template <class T>
inline ffw::vec4<T> ffw::lerp(const ffw::vec4<T>& A, const ffw::vec4<T>& B, float Weight) {
    vec4<T> result;
    result.x = A.x*(1-Weight) + B.x*Weight;
    result.y = A.y*(1-Weight) + B.y*Weight;
    result.z = A.z*(1-Weight) + B.z*Weight;
    result.w = A.w*(1-Weight) + B.w*Weight;
    return result;
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
inline ffw::mat4 ffw::makeProjectionMatrix(float FieldOfView, float Aspect, float Near, float Far){
    float halfFov = FieldOfView/2.0f;
	float tanFov = tanf(halfFov*(float)DEG_TO_RAD);
    ffw::mat4 mat;
    mat.ptr[0] = 1.0f / (Aspect * tanFov);
    mat.ptr[5] = 1.0f / tanFov;
    mat.ptr[10] = (Near + Far) / (Near - Far);
    mat.ptr[11] = -1.0f;
    mat.ptr[14] = (2.0f * Far * Near) / (Near - Far);
    return mat;
}

///=============================================================================
inline ffw::mat4 ffw::makeLookAtMatrix(const ffw::vec3f& Eyes, const ffw::vec3f& Target, const ffw::vec3f& UpVector){
    ffw::mat4 mat;
    ffw::vec3f f = ffw::normalize(Target - Eyes);
    ffw::vec3f s = ffw::normalize(ffw::cross(f, UpVector));
    ffw::vec3f u = ffw::cross(s, f);

    mat[0]  =  s.x;
    mat[4]  =  s.y;
    mat[8]  =  s.z;
    mat[3]  =  0.0f;
    mat[1]  =  u.x;
    mat[5]  =  u.y;
    mat[9]  =  u.z;
    mat[7]  =  0.0f;
    mat[2]  = -f.x;
    mat[6]  = -f.y;
    mat[10] = -f.z;
    mat[11] =  0.0f;
    mat[12] = -ffw::dot(s, Eyes);
    mat[13] = -ffw::dot(u, Eyes);
    mat[14] =  ffw::dot(f, Eyes);
    mat[15] =  1.0f;

    return mat;
}

///=============================================================================
inline ffw::mat4 ffw::makeFpsCameraMatrix(const ffw::vec3f& Eyes, float Pitch, float Yaw){
	float cPitch = (float)cos(Pitch*DEG_TO_RAD);
	float sPitch = (float)sin(Pitch*DEG_TO_RAD);
	float cYaw = (float)cos(Yaw*DEG_TO_RAD);
	float sYaw = (float)sin(Yaw*DEG_TO_RAD);

    ffw::mat4 mat;
    ffw::vec3f s(cYaw, 0, -sYaw);
    ffw::vec3f u(sYaw * sPitch, cPitch, cYaw * sPitch);
    ffw::vec3f f(sYaw * cPitch, -sPitch, cPitch * cYaw);

    mat[0]  =  s.x;
    mat[4]  =  s.y;
    mat[8]  =  s.z;
    mat[3]  =  0.0f;
    mat[1]  =  u.x;
    mat[5]  =  u.y;
    mat[9]  =  u.z;
    mat[7]  =  0.0f;
    mat[2]  = -f.x;
    mat[6]  = -f.y;
    mat[10] = -f.z;
    mat[11] =  0.0f;
    mat[12] = -ffw::dot(s, Eyes);
    mat[13] = -ffw::dot(u, Eyes);
    mat[14] =  ffw::dot(f, Eyes);
    mat[15] =  1.0f;

    return mat;
}

///=============================================================================
inline uint32_t ffw::getRandom() {
    uint32_t t;

    t = randX ^ (randX << 11);
    randX = randY; randY = randZ; randZ = randW;
    return randW = randW ^ (randW >> 19) ^ (t ^ (t >> 8));
}

///=============================================================================
inline float ffw::getRandomf(){
    return float(getRandom())/4294967296.0f;
}

///=============================================================================
inline uint32_t ffw::getRandom(uint32_t Min, uint32_t Max){
    return getRandom() % Max + Min;
}

///=============================================================================
inline float ffw::getAbsf(float Val){
    if(Val > 0.0f)return Val;
    else return -Val;
}

///=============================================================================
inline double ffw::getAbsd(double Val){
    if(Val > 0.0)return Val;
    else return -Val;
}

///=============================================================================
template<class T>
inline float ffw::clamp(T Val, T Min, T Max){
    if(Val < Min)return Min;
    else if(Val > Max)return Max;
    return Val;
}

///=============================================================================
inline float ffw::clampf(float Val){
    if(Val < 0.0f)return 0.0f;
    else if(Val > 1.0f)return 1.0f;
    return Val;
}

///=============================================================================
inline double ffw::clampd(double Val){
    if(Val < 0.0)return 0.0f;
    else if(Val > 1.0)return 1.0;
    return Val;
}

///=============================================================================
inline float ffw::remap(float Value, float InMin, float InMax, float OutMin, float OutMax){
    return (Value - InMin) / (InMax - InMin) * (OutMax - OutMin) + OutMin;
}

///=============================================================================
inline uint32_t ffw::nextPowOfTwo(uint32_t Value){
    uint32_t P = 1;
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

#endif

