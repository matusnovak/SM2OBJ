/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_STRING_MATH
#define FFW_STRING_MATH

/*!
	@ingroup Math
*/
namespace ffw{
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 * 
	 * @brief Converts string value to arithmetic value.
	 * @return Arithmetic value
	 * @exceptions Produces std::exception if string is invalid.
	 * 
	 * @details
	 * ```C++
	 * std::string str = "123.456";
	 * // To float
	 * float f = ffw::stringToVal<float>(str);
	 * // To double
	 * double d = ffw::stringToVal<double>(str);
	 * ```
	 */
    template <class T> T stringToVal(const std::string& Str);

    template <> float                stringToVal<float>              (const std::string& Str);
    template <> double               stringToVal<double>             (const std::string& Str);
    template <> long double          stringToVal<long double>        (const std::string& Str);
    template <> short                stringToVal<short>              (const std::string& Str);
    template <> int                  stringToVal<int>                (const std::string& Str);
    template <> long                 stringToVal<long>               (const std::string& Str);
    template <> long long            stringToVal<long long>          (const std::string& Str);
    template <> unsigned short       stringToVal<unsigned short>     (const std::string& Str);
    template <> unsigned int         stringToVal<unsigned int>       (const std::string& Str);
    template <> unsigned long        stringToVal<unsigned long>      (const std::string& Str);
    template <> unsigned long long   stringToVal<unsigned long long> (const std::string& Str);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *
	 * @brief Converts value to string
	 */
    template <class T> std::string valToString(const T& Value);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *
	 * @brief Converts value to string
	 * @details Converts from string to value in given decimal points
	 */
    template <class T> std::string valToString(T Value, unsigned int Dec);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *
	 * @brief Converts string to value
	 */
    template<typename T> T hexToVal(const std::string& Str);
    /*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *
	 * @brief Converts value to hex in string format
	 */
    template<typename T> std::string valToHex(const T& Value);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *
	 * @brief Tokenizes the string
	 * @details Create tokens from string based on provided delimiter.
	 * @param Line String to extract tokens from
	 * @param Delim Token delimiter
	 * @return std::vector of tokens
	 * @details
	 * ```C++
	 * std::string str = "  this is   a  sentence! ";
	 * // Split string to tokens by space
	 * std::vector<std::string> tokens = ffw::getTokens(str, ' ');
	 * // Print tokens
	 * for(const auto& token : tokens){
	 *     std::cout << token << std::endl;
	 * }
	 * // This will print:
	 * // "this"
	 * // "is"
	 * // "a"
	 * // "sentence!"
	 * ```
	 */
	template<class T> std::vector<T> getTokens(const T& Line, char Delim);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *
	 * @brief Returns the number of tokens that will be crated by function getTokens()
	 * @sa getTokens
	 */
	template<class T> unsigned int getTokensNum(const T& Line, char Delim);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *
	 * @brief Converts multi-byte string to single-byte ANSI string
	 */
    std::string FFW_API wstrToAnsi(const std::wstring& Str);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *
	 * @brief Converts ANSI single-byte string to multi-byte string
	 */
    std::wstring FFW_API ansiToWstr(const std::string& Str);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *
	 * @brief Converts multi-byte string to single-byte UTF-8 string
	 */
    std::string FFW_API wstrToUtf8(const std::wstring& Str);
	/*!
	 * @memberof ffw
	 * @ingroup Math
	 * @inline
	 *
	 * @brief Converts UTF-8 single-byte string to multi-byte string
	 */
    std::wstring FFW_API utf8ToWstr(const std::string& Str);
};

#include "stringMath.inl"

#endif
