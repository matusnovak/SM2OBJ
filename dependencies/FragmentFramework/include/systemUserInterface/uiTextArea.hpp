/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_TEXT_AREA
#define FFW_SYS_UI_TEXT_AREA

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiTextArea: public uiWidget{
	public:
		uiTextArea(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const std::wstring& Label, bool HScroll, bool VScroll);
		~uiTextArea();

		void disable() override;
		void enable() override;
		void setPos(int PosX, int PosY) override;
		void setSize(int Width, int Height) override;

		void setValue(const std::wstring& Value) const;
		void setLimit(size_t Limit) const;
		std::wstring getValue() const;
		int getTextLength() const;
		static const size_t hash;
	};
};
#endif