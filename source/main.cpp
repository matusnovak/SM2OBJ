/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "window.hpp"

///=============================================================================
int main(){
    // Initialize logger
    ffw::logger::initLogger();

	// Window instance
	sm2obj::window win;

	// Window arguments
	ffw::uiWindowArgs args;
	args.minimize = true;
	args.maximize = false;
	args.closeable = true;
	args.border = true;
	args.resizable = false;
	args.customBcgColor = false;
	//args.bcgColor.set(0.5f, 1.6f, 0.6f);
	args.pos.set(-1, -1);
	args.size.set(490, 615);
	args.title = L"SM2OBJ";

	// Create window
	if(!win.create(args)){
		ffw::logger().error() << "Failed to create window!";
	}

	// Update window while it is not closed (closed != hidden)
	while(!win.isClosed()){
		win.update();
	}

	// Destroy window after we are done
	win.destroy();

	// Return success
    return 0;
}
