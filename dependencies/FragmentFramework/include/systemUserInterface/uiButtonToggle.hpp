/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_BUTTON_TOGGLE
#define FFW_SYS_UI_BUTTON_TOGGLE

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
	class FFW_API uiButtonToggle: public uiWidget{
	public:
		/*!
		 * @memberof uiButtonToggle
		 * @ingroup User-Interface
		 */
		uiButtonToggle(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		~uiButtonToggle();
		/*!
		 * @memberof uiButtonToggle
		 * @ingroup User-Interface
		 * @const
		 */
		bool getValue() const;
		/*!
		 * @memberof uiButtonToggle
		 * @ingroup User-Interface
		 */
		void setValue(bool Value);
		/*!
		 * @memberof uiButtonToggle
		 * @ingroup User-Interface
		 */
		void setLabel(const std::wstring& Label);

		static const size_t hash;
	};
};
#endif