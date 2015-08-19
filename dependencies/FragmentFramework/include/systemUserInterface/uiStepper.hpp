/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_STEPPER
#define FFW_SYS_UI_STEPPER

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiStepper: public uiWidget{
	public:
		uiStepper(void* Handle, int ID, int PosX, int PosY, int Width, int Height);
		~uiStepper();

		void disable() override;
		void enable() override;
		void setPos(int PosX, int PosY) override;
		void setSize(int Width, int Height) override;

		void setRange(int Min, int Max) const;
		void setValue(int Value) const;
		int getValue() const;

		static const size_t hash;
	};
};
#endif