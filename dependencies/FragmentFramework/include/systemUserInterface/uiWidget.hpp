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

/*!
 * @ingroup User-Interface
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 */
	class FFW_API uiWidget{
	public:
		/*!
		 * @memberof uiWidget
		 * @ingroup User-Interface
		 */
		uiWidget(size_t ID);
		uiWidget(uiWidget&& Other) = delete;
		uiWidget(const uiWidget& Other) = delete;
		virtual ~uiWidget();
		/*!
		 * @memberof uiWidget
		 * @ingroup User-Interface
		 */
		void setFont(const ffw::uiFont* Font);
		/*!
		 * @memberof uiWidget
		 * @ingroup User-Interface
		 */
		virtual void hide();
		/*!
		 * @memberof uiWidget
		 * @ingroup User-Interface
		 */
		virtual void show();
		/*!
		 * @memberof uiWidget
		 * @ingroup User-Interface
		 */
		virtual void enable();
		/*!
		 * @memberof uiWidget
		 * @ingroup User-Interface
		 */
		virtual void disable();
		/*!
		 * @memberof uiWidget
		 * @ingroup User-Interface
		 */
		virtual void setPos(int PosX, int PosY);
		/*!
		 * @memberof uiWidget
		 * @ingroup User-Interface
		 */
		virtual void setSize(int Width, int Height);
		/*!
		 * @memberof uiWidget
		 * @ingroup User-Interface
		 * @const
		 */
		const ffw::vec2i& getPos() const;
		/*!
		 * @memberof uiWidget
		 * @ingroup User-Interface
		 * @const
		 */
		const ffw::vec2i& getSize() const;
		/*!
		 * @memberof uiWidget
		 * @ingroup User-Interface
		 * @const
		 */
		bool isEnabled() const;
		/*!
		 * @memberof uiWidget
		 * @ingroup User-Interface
		 * @const
		 */
		bool isVisible() const;

		friend class uiWindow;

		// Can not be moved nor copied
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
