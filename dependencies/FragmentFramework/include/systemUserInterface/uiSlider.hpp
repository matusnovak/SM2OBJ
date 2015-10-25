/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_SLIDER
#define FFW_SYS_UI_SLIDER

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
	class FFW_API uiSlider: public uiWidget{
	public:
		/*!
		 * @memberof uiSlider
		 * @ingroup User-Interface
		 */
		uiSlider(void* Handle, int ID, int PosX, int PosY, int Width, int Height);
		~uiSlider();
		/*!
		 * @memberof uiSlider
		 * @ingroup User-Interface
		 */
		void setRange(int Min, int Max);
		/*!
		 * @memberof uiSlider
		 * @ingroup User-Interface
		 */
		void setStep(int Step);
		/*!
		 * @memberof uiSlider
		 * @ingroup User-Interface
		 */
		void setValue(int Value);
		/*!
		 * @memberof uiSlider
		 * @ingroup User-Interface
		 * @const
		 */
		int getValue() const;

		static const size_t hash;
	};
};
#endif