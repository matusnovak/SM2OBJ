/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_RADIO
#define FFW_SYS_UI_RADIO

#include "uiWidget.hpp"

namespace ffw{
	class FFW_API uiRadio: public uiWidget{
	public:
		uiRadio(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		~uiRadio();
		bool getValue() const;
		void setValue(bool Value);

		static const size_t hash;
	};
};
#endif