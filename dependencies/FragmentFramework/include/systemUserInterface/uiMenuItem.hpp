/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_MENU_ITEM
#define FFW_SYS_UI_MENU_ITEM

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiMenuItem: public uiWidget{
	public:
		uiMenuItem(void* Handle, int ID, const std::wstring& Label);
		~uiMenuItem();

		void disable() override;
		void enable() override;

		static const size_t hash;
	private:
		void* parentMenu;
	};
};
#endif