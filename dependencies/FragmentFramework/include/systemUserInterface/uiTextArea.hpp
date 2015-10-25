/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_TEXT_AREA
#define FFW_SYS_UI_TEXT_AREA

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
	class FFW_API uiTextArea: public uiWidget{
	public:
		/*!
		 * @memberof uiTextArea
		 * @ingroup User-Interface
		 */
		uiTextArea(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const std::wstring& Label, bool HScroll, bool VScroll, bool ReadOnly);
		~uiTextArea();
		void setValue(const std::wstring& Value);
		/*!
		 * @memberof uiTextArea
		 * @ingroup User-Interface
		 */
		void append(const std::wstring& Value);
		/*!
		 * @memberof uiTextArea
		 * @ingroup User-Interface
		 */
		void setLimit(size_t Limit);
		/*!
		 * @memberof uiTextArea
		 * @ingroup User-Interface
		 * @const
		 */
		std::wstring getValue() const;
		/*!
		 * @memberof uiTextArea
		 * @ingroup User-Interface
		 * @const
		 */
		int getTextLength() const;

		static const size_t hash;
	};
};
#endif