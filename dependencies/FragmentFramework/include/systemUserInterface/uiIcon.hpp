/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_ICON
#define FFW_SYS_UI_ICON

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiIcon: public uiWidget{
	public:
		uiIcon(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const ffw::uiBitmap* Bitmap);
		~uiIcon();

		void disable() override;
		void enable() override;
		void setPos(int PosX, int PosY) override;
		void setSize(int Width, int Height) override;
		void setBitmap(const ffw::uiBitmap* Bitmap);

		static const size_t hash;

		static const int bitmapIcon = 0;
		static const int resourceIcon = 1;
	};
};
#endif