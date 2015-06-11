/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_TXT
#define FFW_LOAD_SAVE_TXT

#include "../dll.h"
#include <string>
#include <vector>

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadTXT(const std::string& path, std::string* data);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveTXT(const std::string& path, const std::string& data);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadTXT(const std::string& path, std::vector<std::string>* data);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveTXT(const std::string& path, const std::vector<std::string>& data);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadTXT(const std::wstring& path, std::string* data);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveTXT(const std::wstring& path, const std::string& data);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadTXT(const std::wstring& path, std::vector<std::string>* data);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveTXT(const std::wstring& path, const std::vector<std::string>& data);
};
#endif
