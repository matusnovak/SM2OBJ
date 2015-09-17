/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_GROUP
#define FFW_SYS_UI_GROUP

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiGroup: public uiWidget{
	public:
		uiGroup(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		~uiGroup();

		static const size_t hash;
	};
};
#endif