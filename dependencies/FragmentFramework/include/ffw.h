/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FRAGMENT_FRAMEWORK
#define FRAGMENT_FRAMEWORK

#include "config.h"
#include "gl/monitors.hpp"
#include "gl/extensions.hpp"
#include "graphics/basicDraw.hpp"
#include "graphics/bufferObjectPool.hpp"
#include "graphics/bufferObject.hpp"
#include "graphics/framebuffer.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture2D.hpp"
#include "graphics/texture2DArray.hpp"
#include "graphics/font.hpp"
#include "math/math.h"
#include "network/networkUtils.hpp"
#include "network/udpListener.hpp"
#include "network/udpSender.hpp"
#include "network/tcpServer.hpp"
#include "network/tcpClient.hpp"
#include "serial/serialManager.hpp"
#include "systemUserInterface/uiWindow.hpp"
#include "systemUserInterface/uiButton.hpp"
#include "systemUtils/directory.hpp"
#include "systemUtils/win32SysUtils.hpp"
#include "utilities/fileUtilities.hpp"
#include "fileLoaders/bmpFile.hpp"
#include "fileLoaders/jsonFile.hpp"
#include "fileLoaders/objFile.hpp"
#include "fileLoaders/pbmFile.hpp"
#include "fileLoaders/pngFile.hpp"
#include "fileLoaders/jpgFile.hpp"
#include "fileLoaders/txtFile.hpp"
#include "fileLoaders/tgaFile.hpp"
#include "fileLoaders/tiffFile.hpp"
#include "fileLoaders/wavFile.hpp"
#include "fileLoaders/xmlFile.hpp"
#include "fileLoaders/oggFile.hpp"
#include "utilities/file.hpp"
#include "utilities/logger.hpp"
#include "utilities/thread.hpp"
#include "utilities/usleep.hpp"
#include "utilities/mutex.hpp"
#include "utilities/timer.hpp"
#include "utilities/serialization.hpp"
#include "render/renderContext.hpp"
#include "render/appRenderWindow.hpp"

#endif
