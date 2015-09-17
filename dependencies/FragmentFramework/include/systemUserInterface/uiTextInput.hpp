/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_TEXT_INPUT
#define FFW_SYS_UI_TEXT_INPUT

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiTextInput: public uiWidget{
	public:
		uiTextInput(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		~uiTextInput();
		void setValue(const std::wstring& Value);
		void setLimit(size_t Limit);
		std::wstring getValue() const;
		int getTextLength() const;

		static const size_t hash;
	};
};
#endif