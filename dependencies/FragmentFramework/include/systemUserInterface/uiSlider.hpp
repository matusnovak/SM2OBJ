/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_SLIDER
#define FFW_SYS_UI_SLIDER

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiSlider: public uiWidget{
	public:
		uiSlider(void* Handle, int ID, int PosX, int PosY, int Width, int Height);
		~uiSlider();
		void setRange(int Min, int Max);
		void setStep(int Step);
		void setValue(int Value);
		int getValue() const;

		static const size_t hash;
	};
};
#endif