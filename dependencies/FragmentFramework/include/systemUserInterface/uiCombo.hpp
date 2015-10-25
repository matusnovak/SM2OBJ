/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_COMBO
#define FFW_SYS_UI_COMBO

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
	class FFW_API uiCombo: public uiWidget{
	public:
		/*!
		 * @memberof uiCombo
		 * @ingroup User-Interface
		 */
		uiCombo(void* Handle, int ID, int PosX, int PosY, int Width, int Height);
		~uiCombo();
		/*!
		 * @memberof uiCombo
		 * @ingroup User-Interface
		 */
		void addItem(const std::wstring& Text);
		/*!
		 * @memberof uiCombo
		 * @ingroup User-Interface
		 * @const
		 */
		int getSelected() const;
		/*!
		 * @memberof uiCombo
		 * @ingroup User-Interface
		 */
		void setSelected(int Index);

		static const size_t hash;
	};
};
#endif