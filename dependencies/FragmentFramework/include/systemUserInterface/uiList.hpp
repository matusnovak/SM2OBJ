/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_LIST
#define FFW_SYS_UI_LIST

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
	class FFW_API uiList: public uiWidget{
	public:
		/*!
		 * @memberof uiList
		 * @ingroup User-Interface
		 */
		uiList(void* Handle, int ID, int PosX, int PosY, int Width, int Height, int Scroll);
		~uiList();
		/*!
		 * @memberof uiList
		 * @ingroup User-Interface
		 */
		void addItem(const std::wstring& Text);
		/*!
		 * @memberof uiList
		 * @ingroup User-Interface
		 * @const
		 */
		int getSelected() const;
		/*!
		 * @memberof uiList
		 * @ingroup User-Interface
		 */
		void setSelected(int Index);
		/*!
		 * @memberof uiList
		 * @ingroup User-Interface
		 */
		void clear();
		static const size_t hash;
		/*!
		 * @memberof uiList
		 * @ingroup User-Interface
		 */
		static const int noScroll = 0;
		/*!
		 * @memberof uiList
		 * @ingroup User-Interface
		 */
		static const int horizontal = 1;
		/*!
		 * @memberof uiList
		 * @ingroup User-Interface
		 */
		static const int vertical = 2;
	};
};
#endif