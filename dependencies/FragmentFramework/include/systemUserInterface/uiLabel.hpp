/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_LABEL
#define FFW_SYS_UI_LABEL

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
	class FFW_API uiLabel: public uiWidget{
	public:
		/*!
		 * @memberof uiLabel
		 * @ingroup User-Interface
		 */
		uiLabel(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const std::wstring& Label, const ffw::color& Color);
		~uiLabel();
		/*!
		 * @memberof uiLabel
		 * @ingroup User-Interface
		 */
		void setValue(const std::wstring& Label);
		/*!
		 * @memberof uiLabel
		 * @ingroup User-Interface
		 */
		void setColor(const ffw::color& Color);

		static const size_t hash;
		friend class uiWindow;
	private:
		ffw::color col;
	};
};
#endif