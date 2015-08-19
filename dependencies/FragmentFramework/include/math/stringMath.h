/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_STRING_MATH
#define FFW_STRING_MATH

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <comdef.h>
#include <stdexcept>

/*!
	@ingroup Math
*/
namespace ffw{
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Converts string value to arithmetic value.

		@param [in] Str String to convert

		@return Arithmetic value

		@code
		std::string str = "123.456";
		// To float
		float f = ffw::stringToVal<float>(str);
		// To double
		double d = ffw::stringToVal<double>(str);
		@endcode
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
		@memberof ffw
		@ingroup Math
		@inline

		@brief Converts arithmetic value to string.

		@param [in] value Value to convert

		@return std::string
	*/
    template <class T> std::string valToString(const T& Value);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Converts arithmetic value to string.

		@param [in] Value Value to convert
		@param [in] Dec   Number of decimals

		@return std::string
	*/
    template <class T> std::string valToString(T Value, unsigned int Dec);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Converts hex string value to arithmetic value.

		@param [in] Str String to convert

		@return Arithmetic value
	*/
    template<typename T> T hexToVal(const std::string& Str);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Converts arithmetic value to hex string.

		@param [in] Value Arithmetic value to convert

		@return Hex string
	*/
    template<typename T> std::string valToHex(const T& Value);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Tokenize the string

		@details Create tokens from string based on provided delimiter.

		@param [in] Line String to extract tokens from
		@param [in] Delim Token delimiter

		@return std::vector of tokens

		@code
		std::string str = "  this is   a  sentence! ";
		// Split string to tokens by space
		std::vector<std::string> tokens = ffw::getTokens(str, ' ');
		// Print tokens
		for(const auto& token : tokens){
            std::cout << token << std::endl;
		}
		// This will print:
		// "this"
		// "is"
		// "a"
		// "sentence!"
		@endcode
	*/
	template<class T> std::vector<T> getTokens(const T& Line, char Delim);
	/*!
		@memberof ffw
		@ingroup Math
		@inline
	*/
	template<class T> unsigned int getTokensNum(const T& Line, char Delim);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Converts multi-byte string to single-byte ANSI string.

		@param [in] Str Multi-byte string to convert

		@return Converted ANSI string
    */
    std::string wstrToAnsi(const std::wstring& Str);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Converts ANSI single-byte string to multi-byte string.

		@param [in] Str String to convert

		@return Converted multi-byte string
    */
    std::wstring ansiToWstr(const std::string& Str);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Converts multi-byte string to single-byte UTF-8 string.

		@param [in] Str Multi-byte string to convert

		@return Converted UTF-8 string
    */
    std::string wstrToUtf8(const std::wstring& Str);
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Converts UTF-8 single-byte string to multi-byte string.

		@param [in] Str String to convert

		@return Converted multi-byte string
    */
    std::wstring utf8ToWstr(const std::string& Str);
};

#include "stringMath.inl"

#endif
