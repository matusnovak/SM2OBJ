/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_TEXT_INPUT
#define FFW_SYS_UI_TEXT_INPUT

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
	class FFW_API uiTextInput: public uiWidget{
	public:
		/*!
		 * @memberof uiTextInput
		 * @ingroup User-Interface
		 */
		uiTextInput(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		~uiTextInput();
		/*!
		 * @memberof uiTextInput
		 * @ingroup User-Interface
		 */
		void setValue(const std::wstring& Value);
		/*!
		 * @memberof uiTextInput
		 * @ingroup User-Interface
		 */
		void setLimit(size_t Limit);
		/*!
		 * @memberof uiTextInput
		 * @ingroup User-Interface
		 * @const
		 */
		std::wstring getValue() const;
		/*!
		 * @memberof uiTextInput
		 * @ingroup User-Interface
		 * @const
		 */
		int getTextLength() const;

		static const size_t hash;
	};
};
#endif