/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_WINDOW_CALLBACK_STATE
#define FFW_WINDOW_CALLBACK_STATE

namespace ffw {
	class mouse {
	public:
		static int pressed;
		static int released;
		static int left;
		static int right;
		static int middle;
		static int xbutton1;
		static int xbutton2;
	};
};

#endif