/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_FONT
#define FFW_UI_FONT

#include "../common.h"

namespace ffw{
	class uiFont;

	uiFont FFW_API createUiFont(const std::wstring& Name, int Size, int Weight);

	class FFW_API uiFont{
	public:
		uiFont();
		~uiFont();

		operator bool() const;
		bool isValid() const;

		uiFont(uiFont&& Other);
		uiFont& operator = (uiFont&& Other);

		uiFont& operator = (const uiFont& Other) = delete;
		uiFont(const uiFont& Other) = delete;

		friend class uiWidget;
		friend uiFont FFW_API createUiFont(const std::wstring& Name, int Size, int Weight);
	private:
		void* data;
	};
};

#endif