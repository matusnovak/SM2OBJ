/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_CHECKBOX
#define FFW_SYS_UI_CHECKBOX

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
	class FFW_API uiCheckbox: public uiWidget{
	public:
		/*!
		 * @memberof uiCheckbox
		 * @ingroup User-Interface
		 */
		uiCheckbox(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		~uiCheckbox();
		/*!
		 * @memberof uiCheckbox
		 * @ingroup User-Interface
		 * @const
		 */
		bool getValue() const;
		/*!
		 * @memberof uiCheckbox
		 * @ingroup User-Interface
		 */
		void setValue(bool Value);

		static const size_t hash;
	};
};
#endif