/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_MENU_FOLDER
#define FFW_SYS_UI_MENU_FOLDER

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
	class FFW_API uiMenuFolder: public uiWidget{
	public:
		/*!
		 * @memberof uiMenuFolder
		 * @ingroup User-Interface
		 */
		uiMenuFolder(void* Handle, int ID, const std::wstring& Label);
		~uiMenuFolder();
		/*!
		 * @memberof uiMenuFolder
		 * @ingroup User-Interface
		 * @override
		 */
		void disable() override;
		/*!
		 * @memberof uiMenuFolder
		 * @ingroup User-Interface
		 * @override
		 */
		void enable() override;

		static const size_t hash;
	private:
		void* parentMenu;
	};
};
#endif