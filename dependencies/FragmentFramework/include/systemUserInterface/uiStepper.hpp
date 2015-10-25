/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_STEPPER
#define FFW_SYS_UI_STEPPER

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
	class FFW_API uiStepper: public uiWidget{
	public:
		/*!
		 * @memberof uiStepper
		 * @ingroup User-Interface
		 */
		uiStepper(void* Handle, int ID, int PosX, int PosY, int Width, int Height);
		~uiStepper();
		/*!
		 * @memberof uiStepper
		 * @ingroup User-Interface
		 */
		void setRange(int Min, int Max);
		/*!
		 * @memberof uiStepper
		 * @ingroup User-Interface
		 */
		void setValue(int Value);
		/*!
		 * @memberof uiStepper
		 * @ingroup User-Interface
		 * @const
		 */
		int getValue() const;

		static const size_t hash;
	};
};
#endif