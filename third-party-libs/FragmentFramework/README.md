![Logo](http://matusnovak.github.io/fragmentframework/images/ffw-logo-web.png)
=================

__More information including documentation and tutorials can be found at:__ __[http://matusnovak.github.io/fragmentframework/](http://matusnovak.github.io/fragmentframework/)__

__This project is work in progress and is not yet ready for stable release. Use at your own risk.__

FragmentFramework (or FFW for short) is an open source framework written in C++ designed for developing applications. This framework provides basic simple structure to write things easily with less code. Anyone can use this framework without greater knowledge of programming. This framework provides functions which can be used as a building blocks for applications of any kind. The core functions should provide sufficient exploitation for any problem.

This framework is currently supported __only on Windows__ platform (Linux support is planned). In order to use this framework you need MinGW-w32 version 4.9.2 or higher.

__This framework wraps together several common used libraries:__

* [OpenGL](http://www.opengl.org/) - 2D and 3D vector graphics
* [GLFW](http://www.glfw.org/) - Window context handling
* [Winsock](http://msdn.microsoft.com/en-us/library/windows/desktop/ms740673.aspx) - Network communication 
* [OpenAL](http://kcat.strangesoft.net/openal.html) - Audio context handling (optional as addon)
* [FFmpeg](https://www.ffmpeg.org/) - For playing video files (optional as addon)
* [FreeType](http://www.freetype.org/) - True Type Font floading
* [libpng](http://www.libpng.org/pub/png/libpng.html) - Loading PNG image files
* [libtiff](http://www.libtiff.org/) - Loading TIFF image files
* [tinyxml](http://www.grinninglizard.com/tinyxml2/index.html) - Loading XML files
* [Zlib](http://www.zlib.net/) - Data compression (also required by FreeType)
* [libogg](https://xiph.org/ogg/) - Opening OGG containers
* [libvorbis](https://xiph.org/vorbis/) - Compressing and decompressing OGG audio files

__This framework provides features such as:__

* __2D and 3D graphics__ - Basic shapes, shaders, buffer objects, etc...
* __Font__ - Rendering TTF fonts
* __Network__ - UDP listener and sender + TCP server and client
* __Serial__ - Serial port data sending and receiving
* __Sound__ - Sound playing (width addon)
* __Video__ - Video playing (width addon)
* __File loading__ - Loading and saving files such as: WAV, BMP, PBM, PNG, TIFF, TGA, OBJ
* __Structure parser__ - Parsing XML, INI and JSON from/to string or file
* __System spefici utilities__ - File/folder save/load dialogs, screen capture, clipboard, ...
* __Math__ - 2D, 3D, 4D vectors, matrices and quaternion
* __UserInterface__ - GUI windows including widgets
* and much more...

