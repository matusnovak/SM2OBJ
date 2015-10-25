/*** This file is part of FragmentFramework project ***/

#ifndef FFW_VAR
#define FFW_VAR

/*!
 * @ingroup Math
 * @brief FFW
 */
namespace ffw {

    struct var;
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 *
     * @brief Var - JSON-like Array
	 */
    struct varArray {
    public:
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 */
        varArray();
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 */
        varArray(varArray&& Array);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 */
        varArray(const varArray& Array);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 *
         * @brief Constructor
		 * @details Initializes array from initializer list, for example:
		 *
		 * ```C++
		 * ffw::var arr = ffw::varArray { "hello", "world", 123, 3.14f, false, NULL };
		 * ```
		 */
        varArray(std::initializer_list<var> List);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 *
         * @brief Adds new element to the end
		 */
        void push_back(const var& Value);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 *
         * @brief Removes last added element
		 */
        void pop_back();
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        std::vector<var>::iterator begin();
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        std::vector<var>::iterator end();
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        void resize(size_t Size);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        void resize(size_t Size, const var& Value);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        size_t size() const;
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        void reserve(size_t Size);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        void clear();
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        void assign(size_t Size, const var& Value);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        void assign(std::initializer_list<var> List);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        var& front();
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        const var& front() const;
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Returns pointer to raw array
		 */
        var* data();
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Returns pointer to raw array
		 */
        const var* data() const;
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        std::vector<var>::reverse_iterator rend();
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        std::vector<var>::iterator insert(std::vector<var>::const_iterator Pos, const var& Value);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        std::vector<var>::iterator insert(std::vector<var>::const_iterator Pos, size_t Size, const var& Value);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        std::vector<var>::iterator insert(std::vector<var>::const_iterator Pos, var&& Value);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        std::vector<var>::iterator insert(std::vector<var>::const_iterator Pos, std::vector<var>::iterator First, std::vector<var>::iterator Last);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        std::vector<var>::iterator insert(std::vector<var>::const_iterator Pos, std::initializer_list<var> List);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        var& at(size_t i);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        const var& at(size_t i) const;
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        varArray& operator = (const varArray& Array);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        varArray& operator = (varArray&& Array);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        varArray& operator = (std::initializer_list<var> List);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 */
        var& operator [] (size_t i);
        /*!
		 * @memberof varArray
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        const var& operator [] (size_t i) const;

    protected:
        std::vector<var> varVec;
    };

    /*!
	 * @memberof ffw
	 * @ingroup Math
	 *
     * @brief Var - JSON-like Object
	 */
    struct varObject {
    public:
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Constructor
		 */
        varObject();
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Constructor
		 */
        varObject(const varObject& Object);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Constructor
		 */
        varObject(varObject&& Object);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 *
		 * @brief Constructor
		 * @details Initializes object from array of pairs, for example:
		 *
		 * ```C++
		 * ffw::var obj = ffw::varObject {
		 *     {"first", "hello"},
		 *     {"second", "world"},
		 *     {"number", 123},
		 *     {"pi-const", 3.14f},
		 *     {"test", true}
		 * };
		 * ```
		 *
		 * is equivalent to JSON structure:
		 * 
		 * ```
		 * {
		 *     "first" : "hello",
		 *     "second" : "world",
		 *     "number" : 123,
		 *     "pi-const" : 3.14f,
		 *     "test" : true
		 * }
		 * ```
		 */
        varObject(std::initializer_list<std::pair<const std::string, var>> List);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        var& at(const std::string& Key);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        const var& at(const std::string& Key) const;
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        std::map<std::string, var>::iterator begin();
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        std::map<std::string, var>::iterator end();
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        void clear();
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        size_t count(const std::string& Key) const;
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        std::map<std::string, var>::iterator  erase(const std::map<std::string, var>::iterator Pos);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        std::map<std::string, var>::size_type erase(const std::string& Key);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        std::map<std::string, var>::iterator erase(const std::map<std::string, var>::iterator First, const std::map<std::string, var>::iterator Last);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        std::map<std::string, var>::iterator find(const std::string& Key);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        std::pair<std::map<std::string, var>::iterator, bool> insert(const std::pair<std::string, var>& Value);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        std::pair<std::map<std::string, var>::iterator, bool> insert(std::pair<std::string, var>&& Value);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        std::map<std::string, var>::iterator insert (const std::map<std::string, var>::iterator Pos, const std::pair<std::string, var>& Value);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        std::map<std::string, var>::iterator insert(const std::map<std::string, var>::iterator Pos, std::pair<std::string, var>&& Value);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        void insert(std::map<std::string, var>::iterator First, std::map<std::string, var>::iterator Last);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        void insert(std::initializer_list<std::pair<const std::string, var>> List);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        std::map<std::string, var>::reverse_iterator rend();
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 * @const
		 *
		 * @brief Checks if a key with given string exists
		 */
        bool contains(const std::string& Key) const;
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        size_t size() const;
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        varObject& operator = (const varObject& Object);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        varObject& operator = (varObject&& Object);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        varObject& operator = (std::initializer_list<std::pair<const std::string, var>> List);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 */
        var& operator [] (const std::string& Key);
        /*!
		 * @memberof varObject
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        const var& operator [] (const std::string& Key) const;

    protected:
        std::map<std::string, var> varMap;
    };

    /*!
	 * @memberof ffw
	 * @ingroup Math
	 *
     * @brief Var - JSON-like data type
	 */
    struct var {
    public:
        /*!
		 * @memberof var
		 * @ingroup Math
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
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var();
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var(var&& Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var(const var& Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var(const int Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var(const float Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var(const bool Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var(const char* Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var(const std::string& Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var(const varArray& Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var(const varObject& Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var(std::nullptr_t);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        explicit operator int () const {
            if(varType != type::vInt)return 0;
            return varTypeInt;
        }
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        explicit operator float () const {
            if(varType != type::vFloat)return 0.0f;
            return varTypeFloat;
        }
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        explicit operator bool () const {
            if(varType != type::vBool)return false;
            return varTypeBool;
        }
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        explicit operator std::string () const {
            if(varType != type::vString)return "";
            return varTypeString;
        }
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        explicit operator varArray () const {
            if(varType != type::vArray)return varArray();
            return varTypeArray;
        }
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        explicit operator varObject () const {
            if(varType != type::vObject)return varObject();
            return varTypeObject;
        }
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        explicit operator std::nullptr_t () const {
            return nullptr;
        }
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var& operator = (var&& a);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var& operator = (const var& Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var& operator = (const int Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var& operator = (const float Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var& operator = (const bool Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var& operator = (const char* Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var& operator = (const std::string& Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var& operator = (const varObject& Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var& operator = (const varArray& Value);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        var& operator = (std::nullptr_t);
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        type getType() const;
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        int& getAsInt();
		/*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        const int& getAsInt() const;
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        float& getAsFloat();
		/*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        const float& getAsFloat() const;
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        bool& getAsBool();
		/*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        const bool& getAsBool() const;
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        std::string& getAsString();
		/*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        const std::string& getAsString() const;
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        varArray& getAsArray();
		/*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        const varArray& getAsArray() const;
        /*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 */
        varObject& getAsObject();
		/*!
		 * @memberof var
		 * @ingroup Math
		 * @inline
		 * @const
		 */
        const varObject& getAsObject() const ;

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
