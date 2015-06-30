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
inline std::ostream& ffw::operator << (std::ostream& os, const ffw::color& C){
    os << C.r << ", " << C.g << ", " << C.b << ", " << C.a;
    return os;
}

#endif
