/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_SCROLLBAR
#define FFW_SYS_UI_SCROLLBAR

#include "uiWidget.hpp"

/*!
 * @ingroup User-Interface
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 * @inherit uiWidget
	 */
	class FFW_API uiScrollbar: public uiWidget{
	public:
		/*!
		 * @memberof uiScrollbar
		 * @ingroup User-Interface
		 */
		uiScrollbar(void* Handle, int ID, int PosX, int PosY, int Width, int Height, int Style);
		~uiScrollbar();
		/*!
		 * @memberof uiScrollbar
		 * @ingroup User-Interface
		 */
		void setValue(int Value);
		/*!
		 * @memberof uiScrollbar
		 * @ingroup User-Interface
		 */
		void setRange(int Min, int Max);
		/*!
		 * @memberof uiScrollbar
		 * @ingroup User-Interface
		 */
		void setStep(int Step);
		/*!
		 * @memberof uiScrollbar
		 * @ingroup User-Interface
		 * @const
		 */
		int getValue() const;
		/*!
		 * @memberof uiScrollbar
		 * @ingroup User-Interface
		 */
		static const int horizontal = 0;
		/*!
		 * @memberof uiScrollbar
		 * @ingroup User-Interface
		 */
		static const int vertical = 1;
		static const size_t hash;
		friend class uiWindow;
	private:
		int step;
	};
};
#endif