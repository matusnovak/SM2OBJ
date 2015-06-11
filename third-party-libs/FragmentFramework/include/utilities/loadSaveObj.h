/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_OBJ
#define FFW_LOAD_SAVE_OBJ

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
	bool FFW_API loadOBJ(const std::string& Path, float** Vertices, unsigned int* NumVertices);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadOBJ(const std::wstring& Path, float** Vertices, unsigned int* NumVertices);
};
#endif
