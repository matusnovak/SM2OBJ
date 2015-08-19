/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_FILE_UTILITIES
#define FFW_FILE_UTILITIES

#include "../config.h"
#include <string>

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities

        @details
    */
    enum imageType {
        BITMAP_1 = 1,
        GRAYSCALE_4 = 2,
        GRAYSCALE_ALPHA_4 = 3,
        GRAYSCALE_8 = 4,
        GRAYSCALE_ALPHA_8 = 5,
        GRAYSCALE_16 = 6,
        GRAYSCALE_ALPHA_16 = 7,
        GRAYSCALE_32 = 8,
        GRAYSCALE_ALPHA_32 = 9,
        RGB_565 = 10,
        RGB_888 = 11,
        RGB_161616 = 12,
        RGB_323232 = 13,
        RGB_ALPHA_5551 = 14,
        RGB_ALPHA_4444 = 15,
        RGB_ALPHA_8888 = 16,
        RGB_ALPHA_16161616 = 17,
        RGB_ALPHA_32323232 = 18,
    };
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
