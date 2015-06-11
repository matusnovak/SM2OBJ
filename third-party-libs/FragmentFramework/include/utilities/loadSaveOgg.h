/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_OGG
#define FFW_LOAD_SAVE_OGG

#include "../dll.h"
#include <string>

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadOGG(const std::string& Path, unsigned char** Data, int* BitsPerSample, size_t* Size, int* ByteRate, int* SampleRate, int* NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveOGG(const std::string& Path, unsigned char* Data, int BitsPerSample, size_t Size, int ByteRate, int SampleRate, int NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadOGG(const std::wstring& Path, unsigned char** Data, int* BitsPerSample, size_t* Size, int* ByteRate, int* SampleRate, int* NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveOGG(const std::wstring& Path, unsigned char* Data, int BitsPerSample, size_t Size, int ByteRate, int SampleRate, int NumChannels);
};
#endif


