/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_JSON
#define FFW_LOAD_SAVE_JSON

#include "../common.h"

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API decodeJSON(const std::string& Str, ffw::var* Output);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	void FFW_API encodeJSON(std::string* Output, ffw::var* Var, bool Formated, bool EscapeUnicode);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadJSON(const std::string& Path, ffw::var* Output);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadJSON(const std::wstring& Path, ffw::var* Output);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveJSON(const std::string& Path, ffw::var* Input, bool Formated, bool EscapeUnicode);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveJSON(const std::wstring& Path, ffw::var* Input, bool Formated, bool EscapeUnicode);
};

#endif
