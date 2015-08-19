/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_ICON_TOGGLE
#define FFW_SYS_UI_ICON_TOGGLE

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiIconToggle: public uiWidget{
	public:
		uiIconToggle(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const ffw::uiBitmap* Bitmap);
		~uiIconToggle();

		void disable() override;
		void enable() override;
		void setPos(int PosX, int PosY) override;
		void setSize(int Width, int Height) override;

		bool getValue() const;
		void setValue(bool Value) const;
		void setBitmap(const ffw::uiBitmap* Bitmap);

		static const size_t hash;

		static const int bitmapIcon = 0;
		static const int resourceIcon = 1;
	};
};
#endif