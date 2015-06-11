# SM2OBJ - StarMade Blueprint to OBJ exporter

This program will exports blueprints from StarMade into an OBJ file. Texture export is also available in four formats (PNG, BMP, TIFF and TGA). This will load block config and textures from your StarMade installation. See "How to export blueprints" below.

**Check out main thread at StarMadeDock.net [here](http://starmadedock.net/threads/i-made-a-obj-exporter-for-blueprints-now-you-can-import-your-ships-to-any-3d-modeling-program.7994/)**

## This software uses following libraries:

* [FragmentFramework](http://matusnovak.github.io/fragmentframework/index.html) - A framework and a wrapper for several libraries listed in [FFW home page](http://matusnovak.github.io/fragmentframework/index.html) It is used as a main library and it does most of the work.
* [Zlib](http://www.zlib.net/) - Data decompression, required by loading chunks.
* [WxWidgets](https://www.wxwidgets.org/) - GUI for easier exporting

## How to export blueprints with the GUI

This exporter comes with a GUI for easier use. There is a binary release [here at github](https://github.com/matusnovak/SM2OBJ/releases). If you want only the exporter itself, see code example below.

![GUI Screenshot](http://i.imgur.com/hSQIBGL.png)

* Select your blueprint by navigating to the StarMade folder. Remember to select the file which has tree zeros at the end of the file name.
* Select the "data" folder of your StarMade. This folder must contains both "config" and "textures" sub folders. Block IDs and textures will be extracted from this folder.
* Select output path. Make sure that output is valid! Both textures (inside folder named "textures") and *.obj file with *.mtl file will be saved here.
* Check "export materials" You can disable this if you want. You can also select which textures you wish to be exported.
* Select how many threads this program should use. If you have 4 core CPU, use 4 threads and so on...
* Check "export textures" This needs to be done only once. PNG format is recommended by default.
* Before you continue, make sure you have at least 500 MB of empty HDD space. This space is used only for temporary uses. The target OBJ file will be much smaller. If you are exporting extremely large structures, the used temporary space can be up to 2+GB.
* Click "Start Exporting" and watch console output for error messages.
* Happy exporting!

## How to export blueprints using source code only
```C++
#include "source/mainExporter.h"
int main(){
	// Always make sure you set these variables!
	// Leaving them undefined may crash the program
	// Set texture export
	textureExport = true;
	// Set materials export
	materialExport = true;
	// Number of threads to use
	threadsCount = 4;
	// Path to the blueprint file
	filePath = "C:\\StarMade\\blueprints\\...";
	// Path to StarMade data folder
	// Make sure you won't add \ at the end!
	starMadeDataFolder = "C:\\StarMade\\data";
	// Where to create an OBJ file
	fileOutputFolder = "C:\\output";
	// Name of an OBJ file
	fileName = "blueprint";
	// Export all textures
	exportDiffuse = true;
	exportBump = true;
	exportAlpha = true;
	// Use specular highlight
	// Disable this if you do not want shiny materials
	useSpecularHighlight = false;
	// Export UV maps
	uvsExport = true;
	// Select texture format
	imageSaver = &ffw::savePNG;
	imageExtension = "png";
	// Or use one of these:
	// imageSaver = &ffw::saveBMP;
	// imageExtension = "bmp";
	// imageSaver = &ffw::saveTGA;
	// imageExtension = "tga";
	// imageSaver = &ffw::saveTIFF;
	// imageExtension = "tiff";
	
	// Run the exporter
	runExporter(NULL);
	return 0;
}
```

## How to import exported OBJ to Blender

Import the OBJ as usual and make sure you check "search for textures" in import options. Materials should appear alongside with textures. If not, copy .obj and .mtl file to "texture" folder (which was created if you checked "export textures") and import it again. 

Blender will not load properly alpha textures. (This is Blender issue) You will need to fix them manualy. Also, self illuminated blocks does not import properly too.

## How to import exported OBJ to 3Ds Max

When importing, select "Blender" preset from drop-down list, check "Import materials" and leave "Object scale" at 1.0

It may tell you that textures have not been found. It will give you an option to add a search patch. Point it to the exported texture folder.

## Performance

The export should not use more than 10MB of RAM (yes, mega bytes, not jiga bytes). If you use more threads, the RAM usage will rise by ~5MB per thread.

## Bugs

* Not having enough HDD space may crash the program.

## Source files

After downloading the source code, you will get these files and folders:

* **source/** - Source code for the exporter, no GUI files here.
* **third-party-libs/** - Contains [FragmentFramework](http://matusnovak.github.io/fragmentframework/index.html) and [Zlib](http://www.zlib.net/) (both include headers and binaries)
* **widgets/** - Source code for GUI, more precisely the class for the frame window.
* **wxsmith/** - XML file used by WxSmith
* **LICENSE** - License file
* **README.md** - You are reading it now.
* **SM2OBJ.cbp** - Code::Blocks project file
* **resource.rc** - Required by the GUI

Note that you will need to download and compile the WxWidgets yourself. The library is not distributed with this project! Does not apply if you exclude the GUI from source.

**Source files of the exporter inside the source/ folder:**

* **mainExporter.cpp** - Main program flow.
* **blockConfig.cpp** - Loads block config from StarMade data folder. 
* **blockConstructor.cpp** - Constructs blocks vertices and indices.
* **blockExtractor.cpp** - Exports vertices and indices as a text to temporary files.
* **blockVerticesData.cpp** - Contains blocks vertex, face and UV data exported from OBJ. (block, wdge, tetra, penta and corner).
* **chunkHeader.cpp** - Loads a header from smd2 file.
* **chunkLoader.cpp** - Loads and decompress chunk data.
* **chunkTempLoader.cpp** - Used for temporary saving decompressed chunks.
* **config.cpp** - Config file, here are the variables that are used in the code example above.
* **materialExporter.cpp** - Exports material to the mtl file.
* **polygonFiltering.cpp** - Filters polygons (ones that occupies same space and removes unnecessary vertices).
* **textureExport.cpp** - Exports and converts textures.

## How to compile:

The binary releases are compiled with MinGW-w64 i686 GCC 4.9.2 I suggest that you use the same compiler.

Use Code::Blocks project `SM2OBJ.cbp` file or:

To compile without the GUI, include all source files in the `source` folder and you also need to provide compiler search paths to these folders:
* `third-party-libs\FragmentFramework\include`
* `third-party-libs\zlib\include`

Next, link `FragmentFramework` DLL located inside the `third-party-libs\FragmentFramework\lib` folder. (Zlib 1.2.8 is already included inside the FragmentFramework.dll)

If you are using Visual Studio, check [FragmentFramework](https://github.com/matusnovak/fragmentframework) repository for the VS 2013 version of the library in: /FragmentFramework/lib/msvc/.

## Copyright and license

SM2OBJ is distributed under the MIT License.

Copyright (C) 2015 by Matus Novak matusnov@gmail.com
