/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_WIDGET
#define FFW_SYS_UI_WIDGET

#include "../common.h"

#include "uiFont.hpp"
#include "uiBitmap.hpp"

namespace ffw{
	class uiWidget;
};

namespace ffw{
	class FFW_API uiWidget{
	public:
		uiWidget(size_t ID);
		virtual ~uiWidget();

		void setFont(const ffw::uiFont* Font);

		virtual void hide();
		virtual void show();
		virtual void enable();
		virtual void disable();
		virtual void setPos(int PosX, int PosY);
		virtual void setSize(int Width, int Height);
		const ffw::vec2i& getPos() const;
		const ffw::vec2i& getSize() const;
		bool isEnabled() const;
		bool isVisible() const;

		friend class uiWindow;

		// Can not be moved nor copied
		uiWidget(uiWidget&& Other) = delete;
		uiWidget(const uiWidget& Other) = delete;
		uiWidget& operator = (uiWidget&& Other) = delete;
		uiWidget& operator = (const uiWidget& Other) = delete;
	protected:
		void* hwnd;
		int id;
		bool visible;
		bool enabled;

		ffw::vec2i size;
		ffw::vec2i pos;
	};
};
#endif
