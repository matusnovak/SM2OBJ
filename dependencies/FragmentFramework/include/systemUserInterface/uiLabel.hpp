/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_LABEL
#define FFW_SYS_UI_LABEL

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiLabel: public uiWidget{
	public:
		uiLabel(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const std::wstring& Label, const ffw::color& Color);
		~uiLabel();

		void setPos(int PosX, int PosY) override;
		void setSize(int Width, int Height) override;

		void setValue(const std::wstring& Label);

		static const size_t hash;

		friend class uiWindow;
	private:
		ffw::color col;
	};
};
#endif