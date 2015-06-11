/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TYPE_OPERATORS_INL
#define FFW_TYPE_OPERATORS_INL

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
template <class T>
ffw::vec4<T> ffw::operator * (ffw::mat4& M, const ffw::vec4<T> &V){
    ffw::vec4<T> r;

    r.x = V.x*M[0]; + V.y*M[4]; + V.z*M[8];  + V.w*M[12];
    r.y = V.x*M[1]; + V.y*M[5]; + V.z*M[9];  + V.w*M[13];
    r.z = V.x*M[2]; + V.y*M[6]; + V.z*M[10]; + V.w*M[14];
    r.w = V.x*M[3]; + V.y*M[7]; + V.z*M[11]; + V.w*M[15];

    return r;
}

#endif
