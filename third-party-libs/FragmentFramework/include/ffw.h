/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FRAGMENT_FRAMEWORK
#define FRAGMENT_FRAMEWORK

#ifdef _MSC_VER
#pragma warning( disable: 4251 )
#endif

#include "gl/renderUtilities.h"
#include "gl/monitors.h"
#include "graphics/bufferObjectPool.h"
#include "graphics/bufferObject.h"
#include "graphics/graphicsFramebuffer.h"
#include "graphics/graphicsShader.h"
#include "graphics/graphicsTexture2D.h"
#include "graphics/graphicsTexture2DArray.h"
#include "graphics/graphicsTrueType.h"
#include "math/math.h"
#include "math/stringMath.h"
#include "network/networkUtils.h"
#include "network/udpListener.h"
#include "network/udpSender.h"
#include "network/tcpServer.h"
#include "network/tcpClient.h"
#include "serial/serialManager.h"
#include "systemUtils/listDirectory.h"
#include "systemUtils/win32SysUtils.h"
#include "userInterface/manager.h"
#include "userInterface/window.h"
#include "userInterface/widgetBox.h"
#include "userInterface/widgetButton.h"
#include "userInterface/widgetButtonIcon.h"
#include "userInterface/widgetLine.h"
#include "userInterface/widgetLabel.h"
#include "userInterface/widgetIcon.h"
#include "userInterface/widgetImage.h"
#include "userInterface/widgetImageDynamic.h"
#include "userInterface/widgetList.h"
#include "userInterface/widgetSwitch.h"
#include "userInterface/widgetCheckbox.h"
#include "userInterface/widgetProgressbar.h"
#include "userInterface/widgetSlider.h"
#include "userInterface/widgetScroller.h"
#include "userInterface/widgetTextInput.h"
#include "utilities/fileUtilities.h"
#include "utilities/loadSaveBmp.h"
#include "utilities/loadSaveJson.h"
#include "utilities/loadSaveObj.h"
#include "utilities/loadSavePbm.h"
#include "utilities/loadSavePng.h"
#include "utilities/loadSaveTxt.h"
#include "utilities/loadSaveTga.h"
#include "utilities/loadSaveTiff.h"
#include "utilities/loadSaveWav.h"
#include "utilities/loadSaveXml.h"
#include "utilities/loadSaveOgg.h"
#include "utilities/file.h"
#include "utilities/logger.h"
#include "utilities/thread.h"
#include "utilities/usleep.h"
#include "utilities/mutex.h"
#include "utilities/serialization.h"
#include "renderContext.h"
#include "window.h"

#endif
