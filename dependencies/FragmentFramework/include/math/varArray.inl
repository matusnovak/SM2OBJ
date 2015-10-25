/*** This file is part of FragmentFramework project ***/

///=============================================================================
inline ffw::varArray::varArray(){
}

///=============================================================================
inline ffw::varArray::varArray(ffw::varArray&& Array){
    varVec = std::move(Array.varVec);
}

///=============================================================================
inline ffw::varArray::varArray(const ffw::varArray& Array){
    varVec = Array.varVec;
}

///=============================================================================
inline ffw::varArray::varArray(std::initializer_list<var> List){
    varVec = List;
}

///=============================================================================
inline void ffw::varArray::push_back(const ffw::var& Value){
    varVec.push_back(Value);
}

///=============================================================================
inline void ffw::varArray::pop_back(){
    varVec.pop_back();
}

///=============================================================================
inline std::vector<ffw::var>::iterator ffw::varArray::begin(){
    return varVec.begin();
}

///=============================================================================
inline std::vector<ffw::var>::iterator ffw::varArray::end(){
    return varVec.end();
}

///=============================================================================
inline void ffw::varArray::resize(size_t Size){
    varVec.resize(Size);
}

///=============================================================================
inline void ffw::varArray::resize(size_t Size, const ffw::var& Value){
    varVec.resize(Size, Value);
}

///=============================================================================
inline size_t ffw::varArray::size() const {
    return varVec.size();
}

///=============================================================================
inline void ffw::varArray::reserve(size_t Size){
    varVec.reserve(Size);
}

///=============================================================================
inline void ffw::varArray::clear(){
    varVec.clear();
}

///=============================================================================
inline void ffw::varArray::assign(size_t Size, const ffw::var& Value){
    varVec.assign(Size, Value);
}

///=============================================================================
inline void ffw::varArray::assign(std::initializer_list<ffw::var> List){
    varVec.assign(List);
}

///=============================================================================
inline ffw::var& ffw::varArray::front(){
    return varVec.front();
}

///=============================================================================
inline const ffw::var& ffw::varArray::front() const {
    return varVec.front();
}

///=============================================================================
inline ffw::var* ffw::varArray::data(){
    return varVec.data();
}

///=============================================================================
inline const ffw::var* ffw::varArray::data() const {
    return varVec.data();
}

///=============================================================================
inline std::vector<ffw::var>::reverse_iterator ffw::varArray::rend(){
    return varVec.rend();
}

///=============================================================================
inline std::vector<ffw::var>::iterator ffw::varArray::insert(std::vector<ffw::var>::const_iterator Pos, const ffw::var& Value){
    return varVec.insert(Pos, Value);
}

///=============================================================================
inline std::vector<ffw::var>::iterator ffw::varArray::insert(std::vector<ffw::var>::const_iterator Pos, size_t Size, const var& Value){
    return varVec.insert(Pos, Size, Value);
}

///=============================================================================
inline std::vector<ffw::var>::iterator ffw::varArray::insert(std::vector<ffw::var>::const_iterator Pos, ffw::var&& Value){
    return varVec.insert(Pos, Value);
}

///=============================================================================
inline std::vector<ffw::var>::iterator ffw::varArray::insert(std::vector<ffw::var>::const_iterator Pos, std::vector<var>::iterator First, std::vector<var>::iterator Last){
    return varVec.insert(Pos, First, Last);
}

///=============================================================================
inline std::vector<ffw::var>::iterator ffw::varArray::insert(std::vector<ffw::var>::const_iterator Pos, std::initializer_list<ffw::var> List){
    return varVec.insert(Pos, List);
}

///=============================================================================
inline ffw::varArray& ffw::varArray::operator = (const ffw::varArray& Array){
    varVec = Array.varVec;
    return *this;
}

///=============================================================================
inline ffw::varArray& ffw::varArray::operator = (ffw::varArray&& Array){
    varVec = std::move(Array.varVec);
    return *this;
}

///=============================================================================
inline ffw::varArray& ffw::varArray::operator = (std::initializer_list<ffw::var> List){
    varVec = List;
    return *this;
}

///=============================================================================
inline ffw::var& ffw::varArray::at(size_t i){
    return varVec.at(i);
}

///=============================================================================
inline const ffw::var& ffw::varArray::at(size_t i) const {
    return varVec.at(i);
}

///=============================================================================
inline ffw::var& ffw::varArray::operator[] (size_t i){
    return varVec.at(i);
}

///=============================================================================
inline const ffw::var& ffw::varArray::operator[] (size_t i) const {
    return varVec.at(i);
}
