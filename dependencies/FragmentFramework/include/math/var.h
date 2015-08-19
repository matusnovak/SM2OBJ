/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_VAR
#define FFW_VAR

#include <vector>
#include <map>
#include <initializer_list>

/*!
	@ingroup Math
*/
namespace ffw {

    struct var;
    /*!
        @memberof ffw
        @ingroup Math
    */
    struct varArray {
    public:
        /*!
            @memberof varArray
            @ingroup Math
        */
        varArray();
        /*!
            @memberof varArray
            @ingroup Math
        */
        varArray(varArray&& Array);
        /*!
            @memberof varArray
            @ingroup Math
        */
        varArray(const varArray& Array);
        /*!
            @memberof varArray
            @ingroup Math
        */
        varArray(std::initializer_list<var> List);
        /*!
            @memberof varArray
            @ingroup Math
        */
        void push_back(const var& Value);
        /*!
            @memberof varArray
            @ingroup Math
        */
        void pop_back();
        /*!
            @memberof varArray
            @ingroup Math
        */
        std::vector<var>::iterator begin();
        /*!
            @memberof varArray
            @ingroup Math
        */
        std::vector<var>::iterator end();
        /*!
            @memberof varArray
            @ingroup Math
        */
        void resize(size_t Size);
        /*!
            @memberof varArray
            @ingroup Math
        */
        void resize(size_t Size, const var& Value);
        /*!
            @memberof varArray
            @ingroup Math
        */
        size_t size() const;
        /*!
            @memberof varArray
            @ingroup Math
        */
        void reserve(size_t Size);
        /*!
            @memberof varArray
            @ingroup Math
        */
        void clear();
        /*!
            @memberof varArray
            @ingroup Math
        */
        void assign(size_t Size, const var& Value);
        /*!
            @memberof varArray
            @ingroup Math
        */
        void assign(std::initializer_list<var> List);
        /*!
            @memberof varArray
            @ingroup Math
        */
        var& front();
        /*!
            @memberof varArray
            @ingroup Math
        */
        const var& front() const;
        /*!
            @memberof varArray
            @ingroup Math
        */
        var* data();
        /*!
            @memberof varArray
            @ingroup Math
        */
        const var* data() const;
        /*!
            @memberof varArray
            @ingroup Math
        */
        std::vector<var>::reverse_iterator rend();
        /*!
            @memberof varArray
            @ingroup Math
        */
        std::vector<var>::iterator insert(std::vector<var>::const_iterator Pos, const var& Value);
        /*!
            @memberof varArray
            @ingroup Math
        */
        std::vector<var>::iterator insert(std::vector<var>::const_iterator Pos, size_t Size, const var& Value);
        /*!
            @memberof varArray
            @ingroup Math
        */
        std::vector<var>::iterator insert(std::vector<var>::const_iterator Pos, var&& Value);
        /*!
            @memberof varArray
            @ingroup Math
        */
        std::vector<var>::iterator insert(std::vector<var>::const_iterator Pos, std::vector<var>::iterator First, std::vector<var>::iterator Last);
        /*!
            @memberof varArray
            @ingroup Math
        */
        std::vector<var>::iterator insert(std::vector<var>::const_iterator Pos, std::initializer_list<var> List);
        /*!
            @memberof varArray
            @ingroup Math
        */
        var& at(size_t i);
        /*!
            @memberof varArray
            @ingroup Math
        */
        const var& at(size_t i) const;
        /*!
            @memberof varArray
            @ingroup Math
        */
        varArray& operator = (const varArray& Array);
        /*!
            @memberof varArray
            @ingroup Math
        */
        varArray& operator = (varArray&& Array);
        /*!
            @memberof varArray
            @ingroup Math
        */
        varArray& operator = (std::initializer_list<var> List);
        /*!
            @memberof varArray
            @ingroup Math
        */
        var& operator [] (size_t i);
        /*!
            @memberof varArray
            @ingroup Math
        */
        const var& operator [] (size_t i) const;

    protected:
        std::vector<var> varVec;
    };

    /*!
		@memberof ffw
		@ingroup Math
	*/
    struct varObject {
    public:
        /*!
            @memberof varObject
            @ingroup Math
        */
        varObject();
        /*!
            @memberof varObject
            @ingroup Math
        */
        varObject(const varObject& Object);
        /*!
            @memberof varObject
            @ingroup Math
        */
        varObject(varObject&& Object);
        /*!
            @memberof varObject
            @ingroup Math
        */
        varObject(std::initializer_list<std::pair<const std::string, var>> List);
        /*!
            @memberof varObject
            @ingroup Math
        */
        var& at(const std::string& Key);
        /*!
            @memberof varObject
            @ingroup Math
        */
        const var& at(const std::string& Key) const;
        /*!
            @memberof varObject
            @ingroup Math
        */
        std::map<std::string, var>::iterator begin();
        /*!
            @memberof varObject
            @ingroup Math
        */
        std::map<std::string, var>::iterator end();
        /*!
            @memberof varObject
            @ingroup Math
        */
        void clear();
        /*!
            @memberof varObject
            @ingroup Math
        */
        size_t count(const std::string& Key) const;
        /*!
            @memberof varObject
            @ingroup Math
        */
        std::map<std::string, var>::iterator  erase(const std::map<std::string, var>::iterator Pos);
        /*!
            @memberof varObject
            @ingroup Math
        */
        std::map<std::string, var>::size_type erase(const std::string& Key);
        /*!
			@memberof varObject
			@ingroup Math
			@inline
		*/
        std::map<std::string, var>::iterator erase(const std::map<std::string, var>::iterator First, const std::map<std::string, var>::iterator Last);
        /*!
            @memberof varObject
            @ingroup Math
        */
        std::map<std::string, var>::iterator find(const std::string& Key);
        /*!
            @memberof varObject
            @ingroup Math
        */
        std::pair<std::map<std::string, var>::iterator, bool> insert(const std::pair<std::string, var>& Value);
        /*!
            @memberof varObject
            @ingroup Math
        */
        std::pair<std::map<std::string, var>::iterator, bool> insert(std::pair<std::string, var>&& Value);
        /*!
            @memberof varObject
            @ingroup Math
        */
        std::map<std::string, var>::iterator insert (const std::map<std::string, var>::iterator Pos, const std::pair<std::string, var>& Value);
        /*!
            @memberof varObject
            @ingroup Math
        */
        std::map<std::string, var>::iterator insert(const std::map<std::string, var>::iterator Pos, std::pair<std::string, var>&& Value);
        /*!
            @memberof varObject
            @ingroup Math
        */
        void insert(std::map<std::string, var>::iterator First, std::map<std::string, var>::iterator Last);
        /*!
            @memberof varObject
            @ingroup Math
        */
        void insert(std::initializer_list<std::pair<const std::string, var>> List);
        /*!
            @memberof varObject
            @ingroup Math
        */
        std::map<std::string, var>::reverse_iterator rend();
        /*!
            @memberof varObject
            @ingroup Math
        */
        bool contains(const std::string& Key) const;
        /*!
            @memberof varObject
            @ingroup Math
        */
        size_t size() const;
        /*!
            @memberof varObject
            @ingroup Math
        */
        varObject& operator = (const varObject& Object);
        /*!
            @memberof varObject
            @ingroup Math
        */
        varObject& operator = (varObject&& Object);
        /*!
            @memberof varObject
            @ingroup Math
        */
        varObject& operator = (std::initializer_list<std::pair<const std::string, var>> List);
        /*!
            @memberof varObject
            @ingroup Math
        */
        var& operator [] (const std::string& Key);
        /*!
            @memberof varObject
            @ingroup Math
        */
        const var& operator [] (const std::string& Key) const;

    protected:
        std::map<std::string, var> varMap;
    };

    /*!
		@memberof ffw
		@ingroup Math
	*/
    struct var {
    public:
        /*!
            @memberof var
            @ingroup Math
        */
        enum type {
            vNull,
            vInt,
            vFloat,
            vBool,
            vString,
            vArray,
            vObject
        };
        /*!
            @memberof var
            @ingroup Math
        */
        var();
        /*!
            @memberof var
            @ingroup Math
        */
        var(var&& Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var(const var& Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var(const int Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var(const float Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var(const bool Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var(const char* Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var(const std::string& Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var(const varArray& Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var(const varObject& Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var(std::nullptr_t);
        /*!
            @memberof var
            @ingroup Math
        */
        explicit operator int () const {
            if(varType != type::vInt)return 0;
            return varTypeInt;
        }
        /*!
            @memberof var
            @ingroup Math
        */
        explicit operator float () const {
            if(varType != type::vFloat)return 0.0f;
            return varTypeFloat;
        }
        /*!
            @memberof var
            @ingroup Math
        */
        explicit operator bool () const {
            if(varType != type::vBool)return false;
            return varTypeBool;
        }
        /*!
            @memberof var
            @ingroup Math
        */
        explicit operator std::string () const {
            if(varType != type::vString)return "";
            return varTypeString;
        }
        /*!
            @memberof var
            @ingroup Math
        */
        explicit operator varArray () const {
            if(varType != type::vArray)return varArray();
            return varTypeArray;
        }
        /*!
            @memberof var
            @ingroup Math
        */
        explicit operator varObject () const {
            if(varType != type::vObject)return varObject();
            return varTypeObject;
        }
        /*!
            @memberof var
            @ingroup Math
        */
        explicit operator std::nullptr_t () const {
            return nullptr;
        }
        /*!
            @memberof var
            @ingroup Math
        */
        var& operator = (var&& a);
        /*!
            @memberof var
            @ingroup Math
        */
        var& operator = (const var& Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var& operator = (const int Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var& operator = (const float Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var& operator = (const bool Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var& operator = (const char* Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var& operator = (const std::string& Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var& operator = (const varObject& Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var& operator = (const varArray& Value);
        /*!
            @memberof var
            @ingroup Math
        */
        var& operator = (std::nullptr_t);
        /*!
            @memberof var
            @ingroup Math
        */
        type getType() const;
        /*!
            @memberof var
            @ingroup Math
        */
        int& getAsInt();
        /*!
            @memberof var
            @ingroup Math
        */
        float& getAsFloat();
        /*!
            @memberof var
            @ingroup Math
        */
        bool& getAsBool();
        /*!
            @memberof var
            @ingroup Math
        */
        std::string& getAsString();
        /*!
            @memberof var
            @ingroup Math
        */
        varArray& getAsArray();
        /*!
            @memberof var
            @ingroup Math
        */
        varObject& getAsObject();

    protected:
        int varTypeInt;
        float varTypeFloat;
        bool varTypeBool;
        std::string varTypeString;
        varObject varTypeObject;
        varArray varTypeArray;
        type varType;
    };
};

#include "var.inl"
#include "varArray.inl"
#include "varObject.inl"

#endif
