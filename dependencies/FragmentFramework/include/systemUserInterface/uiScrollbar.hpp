/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_SCROLLBAR
#define FFW_SYS_UI_SCROLLBAR

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiScrollbar: public uiWidget{
	public:
		uiScrollbar(void* Handle, int ID, int PosX, int PosY, int Width, int Height, int Style);
		~uiScrollbar();
		void setValue(int Value);
		void setRange(int Min, int Max);
		void setStep(int Step);
		int getValue() const;

		static const int horizontal = 0;
		static const int vertical = 1;
		static const size_t hash;
		friend class uiWindow;
	private:
		int step;
	};
};
#endif