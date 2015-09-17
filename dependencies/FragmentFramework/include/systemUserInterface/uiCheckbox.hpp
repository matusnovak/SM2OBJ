/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_CHECKBOX
#define FFW_SYS_UI_CHECKBOX

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiCheckbox: public uiWidget{
	public:
		uiCheckbox(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		~uiCheckbox();
		bool getValue() const;
		void setValue(bool Value);

		static const size_t hash;
	};
};
#endif