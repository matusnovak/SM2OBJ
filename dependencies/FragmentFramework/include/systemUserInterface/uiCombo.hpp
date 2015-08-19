/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_COMBO
#define FFW_SYS_UI_COMBO

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiCombo: public uiWidget{
	public:
		uiCombo(void* Handle, int ID, int PosX, int PosY, int Width, int Height);
		~uiCombo();

		void disable() override;
		void enable() override;
		void setPos(int PosX, int PosY) override;
		void setSize(int Width, int Height) override;

		void addItem(const std::wstring& Text) const;
		int getSelected() const;
		void setSelected(int Index) const;

		static const size_t hash;
	};
};
#endif