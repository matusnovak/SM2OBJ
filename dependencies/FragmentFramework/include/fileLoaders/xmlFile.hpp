/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_XML
#define FFW_LOAD_SAVE_XML

#include "../common.h"

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API decodeXML(const std::string& Str, ffw::var* Output);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	void FFW_API encodeXML(std::string* Output, ffw::var* Var, bool Formated, bool EscapeUnicode);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadXML(const std::string& Path, ffw::var* Output);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadXML(const std::wstring& Path, ffw::var* Output);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveXML(const std::string& Path, ffw::var* Input, bool Formated, bool EscapeUnicode);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveXML(const std::wstring& Path, ffw::var* Input, bool Formated, bool EscapeUnicode);
};

#endif
