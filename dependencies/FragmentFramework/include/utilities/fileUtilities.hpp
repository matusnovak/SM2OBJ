/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_FILE_UTILITIES
#define FFW_FILE_UTILITIES

#include "../common.h"

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API checkIfFileExists(const std::string& Path);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API checkIfFileExists(const std::wstring& Path);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	void FFW_API getFilePathProperties(const std::string& Path, std::string *Directory, std::string *FileName, std::string *FileExtension);
};

#endif
