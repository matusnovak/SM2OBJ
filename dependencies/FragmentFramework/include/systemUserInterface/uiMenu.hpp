/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_MENU
#define FFW_SYS_UI_MENU

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
	class FFW_API uiMenu: public uiWidget{
	public:
		/*!
		 * @memberof uiMenu
		 * @ingroup User-Interface
		 */
		uiMenu(void* Handle, int ID);
		~uiMenu();

		static const size_t hash;
	};
};
#endif