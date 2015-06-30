/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UTILS
#define FFW_SYS_UTILS

#include "../dll.h"
#include <string>

/*!
    @ingroup System
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup System
    */
	std::wstring FFW_API openFileDialog(const std::wstring& title, const std::wstring& Path);
    /*!
        @memberof ffw
        @ingroup System
    */
	std::wstring FFW_API openFolderDialog(const std::wstring& title, const std::wstring& Path);
    /*!
        @memberof ffw
        @ingroup System
    */
	void FFW_API openExplorer(const std::string& path);
    /*!
        @memberof ffw
        @ingroup System
    */
	void FFW_API createDirectory(const std::string& path);
    /*!
        @memberof ffw
        @ingroup System
    */
	std::string FFW_API getClipboard();
    /*!
        @memberof ffw
        @ingroup System
    */
	std::wstring FFW_API getClipboardWstr();
    /*!
        @memberof ffw
        @ingroup System
    */
	void FFW_API setClipboard(const std::string& Str);
    /*!
        @memberof ffw
        @ingroup System
    */
	void FFW_API setClipboard(const std::wstring& Str);
    /*!
        @memberof ffw
        @ingroup System
    */
	bool FFW_API captureScreen(unsigned char** pixels, int* width, int* height);
    /*!
        @memberof ffw
        @ingroup System
    */
	bool FFW_API captureScreenToFile(const std::string& path);
    /*!
        @memberof ffw
        @ingroup System
    */
	std::string FFW_API getExecutablePath();
};
#endif
