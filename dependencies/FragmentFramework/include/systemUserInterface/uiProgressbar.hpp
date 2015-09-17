/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_PROGRESSBAR
#define FFW_SYS_UI_PROGRESSBAR

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiProgressbar: public uiWidget{
	public:
		uiProgressbar(void* Handle, int ID, int PosX, int PosY, int Width, int Height);
		~uiProgressbar();
		void setValue(int Value);

		static const size_t hash;
	};
};
#endif