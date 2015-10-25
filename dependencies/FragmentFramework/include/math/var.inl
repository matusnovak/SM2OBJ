/*** This file is part of FragmentFramework project ***/

///=============================================================================
inline ffw::var::var(){
    varType = type::vNull;
}

///=============================================================================
inline ffw::var::var(var&& Value){
    varType = Value.getType();
    varTypeInt      = std::move(Value.varTypeInt);
    varTypeFloat    = std::move(Value.varTypeFloat);
    varTypeBool     = std::move(Value.varTypeBool);
    varTypeString   = std::move(Value.varTypeString);
    varTypeArray    = std::move(Value.varTypeArray);
    varTypeObject   = std::move(Value.varTypeObject);
}

///=============================================================================
inline ffw::var::var(const var& Value){
    *this = Value;
}

///=============================================================================
inline ffw::var::var(const int Value){
    varType = type::vInt;
    varTypeInt = Value;
}

///=============================================================================
inline ffw::var::var(const float Value){
    varTypeFloat = Value;
    varType = type::vFloat;
}

///=============================================================================
inline ffw::var::var(const bool Value){
    varTypeBool = Value;
    varType = type::vBool;
}

///=============================================================================
inline ffw::var::var(const char* Value){
    varTypeString = Value;
    varType = type::vString;
}

///=============================================================================
inline ffw::var::var(const std::string& Value){
    varTypeString = Value;
    varType = type::vString;
}

///=============================================================================
inline ffw::var::var(const varArray& Value){
    varTypeArray = Value;
    varType = type::vArray;
}

///=============================================================================
inline ffw::var::var(const varObject& Value){
    varTypeObject = Value;
    varType = type::vObject;
}

///=============================================================================
inline ffw::var::var(std::nullptr_t){
    varType = type::vNull;
}

///=============================================================================
inline ffw::var& ffw::var::operator = (var&& Value){
    varType = Value.getType();
    varTypeInt      = std::move(Value.varTypeInt);
    varTypeFloat    = std::move(Value.varTypeFloat);
    varTypeBool     = std::move(Value.varTypeBool);
    varTypeString   = std::move(Value.varTypeString);
    varTypeArray    = std::move(Value.varTypeArray);
    varTypeObject   = std::move(Value.varTypeObject);

    return *this;
}

///=============================================================================
inline ffw::var& ffw::var::operator = (const var& Value){
    if(varType == type::vArray && Value.getType() != type::vArray)varTypeArray.clear();
    else if(varType == type::vObject && Value.getType() != type::vObject)varTypeObject.clear();

    varType = Value.getType();
    switch (varType){
        case type::vInt:        varTypeInt      = (int)Value;           break;
        case type::vFloat:      varTypeFloat    = (float)Value;         break;
        case type::vBool:       varTypeBool     = (bool)Value;          break;
        case type::vString:     varTypeString   = (std::string)Value;   break;
        case type::vArray:      varTypeArray    = (varArray)Value;      break;
        case type::vObject:     varTypeObject   = (varObject)Value;     break;
        case type::vNull: break;
    };
    return *this;
}

///=============================================================================
inline ffw::var& ffw::var::operator = (const int Value){
    if(varType == type::vObject)varTypeObject.clear();
    else if(varType == type::vArray)varTypeArray.clear();
    varTypeInt = Value;
    varType = type::vInt;
    return *this;
}

///=============================================================================
inline ffw::var& ffw::var::operator = (const float Value){
    if(varType == type::vObject)varTypeObject.clear();
    else if(varType == type::vArray)varTypeArray.clear();
    varTypeFloat = Value;
    varType = type::vFloat;
    return *this;
}

///=============================================================================
inline ffw::var& ffw::var::operator = (const bool Value){
    if(varType == type::vObject)varTypeObject.clear();
    else if(varType == type::vArray)varTypeArray.clear();
    varTypeBool = Value;
    varType = type::vBool;
    return *this;
}

///=============================================================================
inline ffw::var& ffw::var::operator = (const char* Value) {
    if(varType == type::vObject)varTypeObject.clear();
    else if(varType == type::vArray)varTypeArray.clear();
    varTypeString = Value;
    varType = type::vString;
    return *this;
}

///=============================================================================
inline ffw::var& ffw::var::operator = (const std::string& Value){
    if(varType == type::vObject)varTypeObject.clear();
    else if(varType == type::vArray)varTypeArray.clear();
    varTypeString = Value;
    varType = type::vString;
    return *this;
}

///=============================================================================
inline ffw::var& ffw::var::operator = (const varArray& Value){
    if(varType == type::vObject)varTypeObject.clear();
    varTypeArray = Value;
    varType = type::vArray;
    return *this;
}

///=============================================================================
inline ffw::var& ffw::var::operator = (const varObject& Value){
    if(varType == type::vArray)varTypeArray.clear();
    varTypeObject = Value;
    varType = type::vObject;
    return *this;
}

///=============================================================================
inline ffw::var& ffw::var::operator = (std::nullptr_t){
    if(varType == type::vObject)varTypeObject.clear();
    else if(varType == type::vArray)varTypeArray.clear();
    varType = type::vNull;
    return *this;
}

///=============================================================================
inline ffw::var::type ffw::var::getType() const {
    return varType;
}

///=============================================================================
inline int& ffw::var::getAsInt(){
    return varTypeInt;
}

///=============================================================================
inline float& ffw::var::getAsFloat(){
    return varTypeFloat;
}

///=============================================================================
inline bool& ffw::var::getAsBool(){
    return varTypeBool;
}

///=============================================================================
inline std::string& ffw::var::getAsString(){
    return varTypeString;
}

///=============================================================================
inline ffw::varArray& ffw::var::getAsArray(){
    return varTypeArray;
}

///=============================================================================
inline ffw::varObject& ffw::var::getAsObject(){
    return varTypeObject;
}

///=============================================================================
inline const int& ffw::var::getAsInt() const {
    return varTypeInt;
}

///=============================================================================
inline const float& ffw::var::getAsFloat() const {
    return varTypeFloat;
}

///=============================================================================
inline const bool& ffw::var::getAsBool() const {
    return varTypeBool;
}

///=============================================================================
inline const std::string& ffw::var::getAsString() const {
    return varTypeString;
}

///=============================================================================
inline const ffw::varArray& ffw::var::getAsArray() const {
    return varTypeArray;
}

///=============================================================================
inline const ffw::varObject& ffw::var::getAsObject() const {
    return varTypeObject;
}