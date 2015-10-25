/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_BUTTON
#define FFW_SYS_UI_BUTTON

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
	class FFW_API uiButton: public uiWidget{
	public:
		/*!
		 * @memberof uiButton
		 * @ingroup User-Interface
		 */
		uiButton(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		~uiButton();
		/*!
		 * @memberof uiButton
		 * @ingroup User-Interface
		 */
		void setLabel(const std::wstring& Label);

		static const size_t hash;
	};
};
#endif