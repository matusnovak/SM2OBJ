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

		void disable() override;
		void enable() override;
		void setPos(int PosX, int PosY) override;
		void setSize(int Width, int Height) override;

		void setRange(int Min, int Max) const;
		void setStep(int Step) const;
		void setValue(int Value) const;
		int getValue() const;

		static const size_t hash;
	};
};
#endif