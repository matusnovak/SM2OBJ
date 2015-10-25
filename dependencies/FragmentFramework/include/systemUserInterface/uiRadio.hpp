/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_RADIO
#define FFW_SYS_UI_RADIO

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
	class FFW_API uiRadio: public uiWidget{
	public:
		/*!
		 * @memberof uiRadio
		 * @ingroup User-Interface
		 */
		uiRadio(void* Handle, int ID, int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		~uiRadio();
		/*!
		 * @memberof uiRadio
		 * @ingroup User-Interface
		 * @const
		 */
		bool getValue() const;
		/*!
		 * @memberof uiRadio
		 * @ingroup User-Interface
		 */
		void setValue(bool Value);

		static const size_t hash;
	};
};
#endif