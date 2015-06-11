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
    template <class T> inline T stringToVal(const std::string& Str);

    template <> inline float                stringToVal<float>              (const std::string& Str){return std::stof(Str);}
    template <> inline double               stringToVal<double>             (const std::string& Str){return std::stod(Str);}
    template <> inline long double          stringToVal<long double>        (const std::string& Str){return std::stold(Str);}
    template <> inline short                stringToVal<short>              (const std::string& Str){return std::stoi(Str);}
    template <> inline int                  stringToVal<int>                (const std::string& Str){return std::stoi(Str);}
    template <> inline long                 stringToVal<long>               (const std::string& Str){return std::stol(Str);}
    template <> inline long long            stringToVal<long long>          (const std::string& Str){return std::stoll(Str);}
    template <> inline unsigned short       stringToVal<unsigned short>     (const std::string& Str){return (unsigned short)std::stoul(Str);}
    template <> inline unsigned int         stringToVal<unsigned int>       (const std::string& Str){return std::stoul(Str);}
    template <> inline unsigned long        stringToVal<unsigned long>      (const std::string& Str){return std::stoul(Str);}
    template <> inline unsigned long long   stringToVal<unsigned long long> (const std::string& Str){return std::stoull(Str);}
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Converts arithmetic value to string.

		@param [in] value Value to convert

		@return std::string
	*/
    template <class T> inline std::string valToString(const T& Value){
        return std::to_string(Value);
    }
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Converts arithmetic value to string.

		@param [in] Value Value to convert
		@param [in] Dec   Number of decimals

		@return std::string
	*/
    template <class T> inline std::string valToString(T Value, unsigned int Dec){
        std::ostringstream ostr;
        ostr.precision(Dec);
        ostr << std::fixed << Value;
        return ostr.str();
    }
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Converts hex string value to arithmetic value.

		@param [in] Str String to convert

		@return Arithmetic value
	*/
    template<typename T> inline T hexToVal(const std::string& Str) {
        try {
            return std::stoul(Str, nullptr, 16);
        } catch (std::invalid_argument e){
            return 0;
        } catch (std::out_of_range e){
            return 0;
        }
        return 0;
    }
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Converts arithmetic value to hex string.

		@param [in] Value Arithmetic value to convert

		@return Hex string
	*/
    template<typename T> inline std::string valToHex(const T& Value) {
        std::stringstream ss;
        ss << std::hex << Value;
        std::string h = ss.str();
        if(h.size() < sizeof(T)*2){
            return std::string(sizeof(T)*2 - h.size(), '0') + h;
        }
        return h;
    }
    /*!
		@memberof ffw
		@ingroup Math
		@inline

		@brief Tokenize the string.

		@details Create tokens from string based on provided delimiter.
		
		@param [in] Line String to extract tokens from
		@param [in] Delim Token delimiter
		
		@return std::vector of tokens

		@code
		std::string str = "  this is   a  sentence! ";
		// Split string to tokens by space
		std::vector<std::string> tokens = ffw::getTokens(str, ' ');
		// Print tokens
		for(int i = 0; i < tokens.size(); i++){
            std::cout << "token: " << i << " = " << tokens[i] << std::endl;
		}
		// This will print:
		// token: 0 = this
		// token: 1 = is
		// token: 2 = a
		// token: 3 = sentence!
		@endcode
	*/
    inline std::vector<std::string> getTokens(const std::string& Line, char Delim){
        std::vector<std::string> vec;
        std::string temp = "";
        for(unsigned int i = 0; i < Line.size(); i++){
            if(Line[i] != Delim)temp += Line[i];
            else {
                if(temp.size() > 0){
                    vec.push_back(temp);
                    temp = "";
                }
            }
            if(i == Line.size()-1 && Line[i] != Delim)vec.push_back(temp);
        }
        return vec;
    }
    /*!
		@memberof ffw
		@ingroup Math
		@inline
		
		@brief Converts multi-byte string to single-byte ANSI string.
		
		@param [in] Str Multi-byte string to convert
		
		@return Converted ANSI string
    */
    inline std::string wstrToAnsi(std::wstring Str){
        int size = WideCharToMultiByte(CP_ACP, 0, Str.c_str(), Str.size(), NULL, 0, NULL, NULL);
        std::string out(size, ' ');
        WideCharToMultiByte(CP_ACP, 0, Str.c_str(), Str.size(), &out[0], size, 0, 0);
        return out;

    }
    /*!
		@memberof ffw
		@ingroup Math
		@inline
		
		@brief Converts ANSI single-byte string to multi-byte string.
		
		@param [in] Str String to convert
		
		@return Converted multi-byte string
    */
    inline std::wstring ansiToWstr(std::string Str){
        int size = MultiByteToWideChar(CP_ACP, 0, Str.c_str(), Str.size(), NULL, 0);
        std::wstring out(size, L' ');
        MultiByteToWideChar(CP_ACP, 0, Str.c_str(), Str.size(), &out[0], size);
        return out;
    }
    /*!
		@memberof ffw
		@ingroup Math
		@inline
		
		@brief Converts multi-byte string to single-byte UTF-8 string.
		
		@param [in] Str Multi-byte string to convert
		
		@return Converted UTF-8 string
    */
    inline std::string wstrToUtf8(std::wstring Str){
        int size = WideCharToMultiByte(CP_UTF8, 0, Str.c_str(), Str.size(), NULL, 0, NULL, NULL);
        std::string out(size, ' ');
        WideCharToMultiByte(CP_UTF8, 0, Str.c_str(), Str.size(), &out[0], size, 0, 0);
        return out;

    }
    /*!
		@memberof ffw
		@ingroup Math
		@inline
		
		@brief Converts UTF-8 single-byte string to multi-byte string.
		
		@param [in] Str String to convert
		
		@return Converted multi-byte string
    */
    inline std::wstring utf8ToWstr(std::string Str){
        int size = MultiByteToWideChar(CP_UTF8, 0, Str.c_str(), Str.size(), NULL, 0);
        std::wstring out(size, L' ');
        MultiByteToWideChar(CP_UTF8, 0, Str.c_str(), Str.size(), &out[0], size);
        return out;
    }
};

#endif
