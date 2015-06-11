/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_VAR_OBJECT_INL
#define FFW_VAR_OBJECT_INL

///=============================================================================
inline ffw::varObject::varObject(){
}

///=============================================================================
inline ffw::varObject::varObject(const varObject& Object){
    varMap = Object.varMap;
}

///=============================================================================
inline ffw::varObject::varObject(varObject&& Object){
    varMap = std::move(Object.varMap);
}

///=============================================================================
inline ffw::varObject::varObject(std::initializer_list<std::pair<const std::string, var>> List){
    varMap = List;
}

///=============================================================================
inline ffw::var& ffw::varObject::at(const std::string& Key){
    return varMap.at(Key);
}

///=============================================================================
inline const ffw::var& ffw::varObject::at(const std::string& Key) const {
    return varMap.at(Key);
}

///=============================================================================
inline std::map<std::string, ffw::var>::iterator ffw::varObject::begin(){
    return varMap.begin();
}

///=============================================================================
inline std::map<std::string, ffw::var>::iterator ffw::varObject::end(){
    return varMap.end();
}

///=============================================================================
inline void ffw::varObject::clear(){
    varMap.clear();
}

///=============================================================================
inline size_t ffw::varObject::count(const std::string& Key) const {
    return varMap.count(Key);
}

///=============================================================================
inline std::map<std::string, ffw::var>::iterator ffw::varObject::erase(const std::map<std::string, ffw::var>::iterator Pos){
    return varMap.erase(Pos);
}

///=============================================================================
inline std::map<std::string, ffw::var>::size_type ffw::varObject::erase(const std::string& Key){
    return varMap.erase(Key);
}

///=============================================================================
inline std::map<std::string, ffw::var>::iterator ffw::varObject::erase(const std::map<std::string, ffw::var>::iterator First, const std::map<std::string, ffw::var>::iterator Last){
    return varMap.erase(First, Last);
}

///=============================================================================
inline std::map<std::string, ffw::var>::iterator ffw::varObject::find(const std::string& Key){
    return varMap.find(Key);
}

///=============================================================================
inline std::pair<std::map<std::string, ffw::var>::iterator, bool> ffw::varObject::insert(const std::pair<std::string, ffw::var>& Value){
    return varMap.insert(Value);
}

///=============================================================================
inline std::pair<std::map<std::string, ffw::var>::iterator, bool> ffw::varObject::insert(std::pair<std::string, ffw::var>&& Value){
    return varMap.insert(Value);
}

///=============================================================================
inline std::map<std::string, ffw::var>::iterator ffw::varObject::insert(const std::map<std::string, ffw::var>::iterator Pos, const std::pair<std::string, ffw::var>& Value){
    return varMap.insert(Pos, Value);
}

///=============================================================================
inline std::map<std::string, ffw::var>::iterator ffw::varObject::insert(const std::map<std::string, ffw::var>::iterator Pos, std::pair<std::string, ffw::var>&& Value){
    return varMap.insert(Pos, Value);
}

///=============================================================================
inline void ffw::varObject::insert(std::map<std::string, var>::iterator First, std::map<std::string, var>::iterator Last){
    varMap.insert(First, Last);
}

///=============================================================================
inline void ffw::varObject::insert(std::initializer_list<std::pair<const std::string, ffw::var>> List){
    varMap.insert(List);
}

///=============================================================================
inline std::map<std::string, ffw::var>::reverse_iterator ffw::varObject::rend(){
    return varMap.rend();
}

///=============================================================================
inline bool ffw::varObject::exists(const std::string& Key) const {
    return varMap.find(Key) != varMap.end();
}

///=============================================================================
inline size_t ffw::varObject::size() const {
    return varMap.size();
}

///=============================================================================
inline ffw::varObject& ffw::varObject::operator = (const ffw::varObject& Object){
    varMap = Object.varMap;
    return *this;
}

///=============================================================================
inline ffw::varObject& ffw::varObject::operator = (ffw::varObject&& Object){
    varMap = std::move(Object.varMap);
    return *this;
}

inline ffw::varObject& ffw::varObject::operator = (std::initializer_list<std::pair<const std::string, ffw::var>> List){
    varMap = List;
    return *this;
}

///=============================================================================
inline ffw::var& ffw::varObject::operator [] (const std::string& Key){
    return varMap.at(Key);
}

///=============================================================================
inline const ffw::var& ffw::varObject::operator [] (const std::string& Key) const {
    return varMap.at(Key);
}

#endif
