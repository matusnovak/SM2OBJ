/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_FONT
#define FFW_UI_FONT

#include "../common.h"

/*!
 * @ingroup User-Interface
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 */
	class FFW_API uiFont{
	public:
		/*!
		 * @memberof uiFont
		 * @ingroup User-Interface
		 */
		uiFont();
		uiFont(uiFont&& Other);
		uiFont(const uiFont& Other) = delete;
		~uiFont();
		/*!
		 * @memberof uiFont
		 * @ingroup User-Interface
		 * @const
		 */
		operator bool() const;
		/*!
		 * @memberof uiFont
		 * @ingroup User-Interface
		 * @const
		 */
		bool isValid() const;
		/*!
		 * @memberof uiFont
		 * @ingroup User-Interface
		 */
		uiFont& operator = (uiFont&& Other);
		uiFont& operator = (const uiFont& Other) = delete;

		friend class uiWidget;
		friend uiFont FFW_API createUiFont(const std::wstring& Name, int Size, int Weight);
	private:
		void* data;
	};
	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 */
	uiFont FFW_API createUiFont(const std::wstring& Name, int Size, int Weight);
};

#endif