/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_ICON
#define FFW_SYS_UI_ICON

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
	class FFW_API uiIcon: public uiWidget{
	public:
		/*!
		 * @memberof uiIcon
		 * @ingroup User-Interface
		 */
		uiIcon(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const ffw::uiBitmap* Bitmap);
		~uiIcon();
		/*!
		 * @memberof uiIcon
		 * @ingroup User-Interface
		 */
		void setBitmap(const ffw::uiBitmap* Bitmap);

		static const size_t hash;
	};
};
#endif