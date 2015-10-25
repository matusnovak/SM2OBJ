/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_ICON_TOGGLE
#define FFW_SYS_UI_ICON_TOGGLE

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
	class FFW_API uiIconToggle: public uiWidget{
	public:
		/*!
		 * @memberof uiIconToggle
		 * @ingroup User-Interface
		 */
		uiIconToggle(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const ffw::uiBitmap* Bitmap);
		~uiIconToggle();
		/*!
		 * @memberof uiIconToggle
		 * @ingroup User-Interface
		 * @const
		 */
		bool getValue() const;
		/*!
		 * @memberof uiIconToggle
		 * @ingroup User-Interface
		 */
		void setValue(bool Value);
		/*!
		 * @memberof uiIconToggle
		 * @ingroup User-Interface
		 */
		void setBitmap(const ffw::uiBitmap* Bitmap);

		static const size_t hash;
	};
};
#endif