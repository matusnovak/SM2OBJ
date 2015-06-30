# SM2OBJ - StarMade Blueprint to OBJ exporter

This program will exports blueprints from StarMade into the OBJ file alongside with UV maps and textures (in four available formats: PNG, BMP, TGA, TIFF). The latest version of block configuration and textures are used to export the blueprint, these files are extracted directly from StarMade installation folder.

**Check out main thread at StarMadeDock.net [here](http://starmadedock.net/threads/i-made-a-obj-exporter-for-blueprints-now-you-can-import-your-ships-to-any-3d-modeling-program.7994/)**

## This software uses following libraries

* [FragmentFramework](http://matusnovak.github.io/fragmentframework/index.html) - A framework and a wrapper for several libraries listed in [FFW home page](http://matusnovak.github.io/fragmentframework/index.html) 
* [Zlib](http://www.zlib.net/) - Data decompression, required to decompress chunks.

## How to export the blueprint

This exporter comes with a GUI for easier use. The binary release can be found [here at github](https://github.com/matusnovak/SM2OBJ/releases). If you want only the exporter itself, see the code example below.

![GUI Screenshot](http://i.imgur.com/rvtr1BR.png)

Before you continue, make sure that you have at least 500 MB of empty HDD space. This space is used only for temporary use. The target OBJ file will be much smaller. If you are exporting extremely large structures, the used space can rise up to 2 GB.

1. Select your input blueprint folder. Make sure the folder is not renamed and the original name is used (the name you used while saving the blueprint in-game) (Letter case must match!).

2. Select the "data" folder of your StarMade. This folder must contain both "config" and "textures" sub folders. Block IDs and textures will be extracted from here.

3. Select the output path. Make sure that the output folder does exist.

4. UV maps can be exported in three ways: exported as tiles (creates one material per one tile) or exported as atlas (creates one material per one atlas) or not being exported at all. It is recommended to use an atlas if the blueprint is going to be used in Unreal Engine, Unity 3D or any other game engine.

5. Disabling this option (not recommended) will lower the output side of the OBJ and increases import speed.

6. Select which textures should all materials use (will affect both tiles and atlases).

7. This affects the spectacular (shininess) of all materials. (This may not affect the materials at all in certain applications).

8. Write a number of how many threads this export should use. (Using more threads than the number of cores your CPU has can result in lower performance).

9. Select this option if you want your attachments (ships and turrets) to be exported alongside with the OBJ file. Note that objects are NOT merged together. After importing the OBJ into your favorite 3D editor, all attachments will be separated and located at [0,0,0] This ensures that the pivot of all ships and turrets is the axis of the rotation. However, the center of the mothership is located at the ship's core. This is due to the limitations of the OBJ file.

10. Select the output folder for the textures. Make sure that the folder is valid, otherwise an error will appear. 

11. Output format of the textures. PNG is recommended due to compression. Note that changing this option will affect the exported materials.

12. This option needs to match option number 4. 

13. Select the size of the tiles. If the textures are being exported as atlases, this will affect the export. (64px tile = 1024px atlas; 128px tile = 2048px atlas; 256px tile = 4096px atlas).

14. Normals can be converted into bump maps, or not. Use the original normal maps if you are importing the OBJ in the game engine.

## How to export blueprints using source code only
```C++
#include "source/exporter/textureExport.h"
#include "source/exporter/exportBlueprint.h"

void sm2obj::window::callbackExportExit(bool Success){
	// Success <- true if the exporter finished without error
}

void sm2obj::window::callbackExportProgress(int Progress, int Total){
	// Progress <- current progress
	// Total <- progress out of maximum
}

void sm2obj::window::callbackExportLogDebug(const std::string& Message){
	// Debug message
}

void sm2obj::window::callbackExportLogError(const std::string& Message){
	// Error message
	// After this error, the exportExitFunc function will
	// be automatically called with "false" as argument.
}

void sm2obj::window::callbackExportLogWarning(const std::string& Message){
	// Warning message
	// If this function is called, the exported OBJ might not be
	// valid! Always check for warning messages!
}

void sm2obj::window::callbackExportLogInfo(const std::string& Message){
	// Info message
	// This serves only for information about current progress
}

int main(){
	// First, you need to set the callbacks for log messages
	// Member non-static functions are not allowed!
	sm2obj::config::exportLogErrorFunc = &callbackExportLogError;
    sm2obj::config::exportLogDebugFunc = &callbackExportLogDebug;
    sm2obj::config::exportLogInfoFunc = &callbackExportLogInfo;
    sm2obj::config::exportLogWarningFunc = &callbackExportLogWarning;
    sm2obj::config::exportExitFunc = &callbackExportExit;
    sm2obj::config::exportProgressFunc = &callbackExportProgress;

	// Exporting the blueprint

	// Input and output folders (UTF-8 compatible)
	std::string blueprintFolder 
		= "C:\\Program Files(x86)\\StarMade\\Blueprints\\...";
	std::string starMadeConfigFolder
		= "C:\\Program Files(x86)\\StarMade\\data\\config";
	std::string outputFolder = "C:\\output";
	
	// Output name without file extension
	std::string outputName = "Blueprint";
	
	// Threads
	int numOfThreads = 8;
	
	// Set the texture extension
	config::imageExtension = "png";
	
	// Material options (see options #4, #5, #6 and #7 in GUI screenshot)
	bool exportMaterials = true;
	bool exportDiffuse = true;
    bool exportAlpha = true;
    bool exportNormal = true;
    bool exportEmissive = true;
    bool specularHighloght = false;
    bool exportUvs = true;
    bool useAtlas = false; // If true, the atlases will be used

    // Attachments options
    bool attachments = true;
	
	// Start the exported by running this function
	// You can run this function multiple times in parallel
	// with different blueprints. 
	// However, variables that are set by sm2obj::config::
	// cannot be changed!
	// The return value is either 0 (error) or 1 (success)
	// The return type is void*
	sm2obj::exportBlueprint(starMadeConfigFolder, blueprintFolder,
	                outputFolder, outputName, exportUvs, useAtlas,
	                exportMaterials, exportDiffuse, exportAlpha,
	                exportNormal, exportEmissive, specularHighloght,
	                numOfThreads, attachments);

	// Exporting textures
	
	// Set the texture function
	// Can be either ffw::savePNG, ffw::saveBMP,
	// ffw::saveTGA, ffw::saveTIFF or ffw::savePBM
	sm2obj::config::imageSaverFunc = &ffw::savePNG;
	// Set file extention 
	sm2obj::config::imageExtension = "png";
	
	// Input and output folders (UTF-8 compatible)
	std::string inputFolder
		= "C:\\Program Files(x86)\\StarMade\\data" + 
		  "\\textures\\block\\Default\\256";
	std::string starMadeConfigFolder
		= "C:\\Program Files(x86)\\StarMade\\data\\config";
	std::string outputFolder = "C:\\output\\textures";	

	// Texture size
	// This needs to match variable "inputFolder"
	int textureSize = 256;
	
	// Convert normal maps to bump maps
	// If false, original normals will be used
	bool normals = false;

	// Export as separated tiles
	sm2obj::exportTextures(inputFolder, outputFolder, normals);

	// Or export as atlases
	//sm2obj::exportAtlases(inputFolder, outputFolder, normals);
	//sm2obj::exportEmissiveAtlas(starMadeConfigFolder, outputFolder, textureSize);
	
	return 0;
}
```

## Error messages

  * __Failed to read block types from: ...__
  * __Failed to read block config from: ...__
    * The block configuration file might be missing, invalid or the data path is not correct.
  * __Failed to load processed raw chunk data! Chunk index: ...__
  * __Failed to save processed raw chunk data! Chunk index: ...__
  * __Failed to save chunk vertices! Chunk index: ...__
  * __Failed to save chunk indices! Chunk index: ...__
  * __Error, failed to open vertex temp data! Index: "__
  * 
    * The chunk has not beed saved to the temp folder. The program might not have permissions to create/modify files or you are low on HDD space.
  * __Error while reading chunk header!__
    * The blueprint might be corrupted!
  * __Failed to open OBJ file for writing!__
  * __Failed to open MTL file for writing!__
    * The target output folder is invalid, you are low on HDD space or the program does not have permissions to create/modify files
  * __Failed to open folder: ...__
    * The folder does not exists.
  * __Error while retrieving file position from file name!__
    * It is necessary that all smd2 files are in this format: "Blueprint name" + "0.0.0.smd2" The last three digits indicated coordinate offset.
  * __Failed to open file:__
    * The file does not exists or the program might not have permissions to open files.
  * __File is invalid! File is too small. Expected at least 49156 bytes__
    * This is the minimal size of empty smd2 file which contains only chunk indices. The file might be corrupted if the size is lower.
  * __Failed to open meta file from: ...__
    * The meta file is missing or the program does not have permission to do it.
  * __Failed to read next attachment path from meta: ...__
    * Either you are trying to export old blueprint, or the meta file is corrupted.
  * __Failed to save texture: ...__
    * The output folder of the textures is invalid.
  * __Failed to load texture: ...__
    * The StarMade data folder does not contains textures or the program might not have permission to read files.

## Warning messages
  * __Error reading type ID / type name / icon / name / texture / type / light source / block style at line: ...__
    * The block config is invalid.
  * __Could not find ID for type: ...__
    * The block type ID listed in BlockConfig.xml is missing. The block inside the XML file should be listed as: &lt;Block icon="530" name="Grey Hull" textureId="33, 33, 33, 33, 33, 33" type="Grey_Hull"&gt; If not, the warning message is generated.
  * __Can not find block ID: ...__
    * There is a block that does not have a type ID listed in BlockTypes.properties file.
  * __Chunk error while reading chunk header! Wrong relative position!__
    * The chunk is corrupted. This only affects one 16x16x16 chunk, not whole file.
  * __Chunk failed to load! Z-Lib init error!__
    * This is internal zlib library error. There is not answer for this warning.
  * __Can not decompress data! Chunk might be corrupted!__
    * This message appears if the chunk does not have 12288 bytes after decompression.
  * __Error while saving chunk to temp!__
  * __Error loading chunk file index: ...__
    * The chunk has not beed saved to the temp folder. The program might not have permissions to create/modify files or you are low on HDD space.


## How to import exported OBJ to Blender

Import the OBJ as usual and make sure you check "search for textures" in import options. Materials should appear alongside with textures. If not, copy .obj and .mtl file to "texture" folder (which was created if you checked "export textures") and import it again. 

Blender will not load properly alpha textures. (This is Blender issue) You will need to fix them manualy. Also, self illuminated blocks does not import properly.

## How to import exported OBJ to 3Ds Max

When importing, select "Blender" preset from drop-down list, check "Import materials" and leave "Object scale" at 1.0

It may tell you that textures have not been found. It will give you an option to add a search patch. Point it to the exported texture folder.

## How to import exported OBJ to Unreal Engine

I highly recommend to use atlases instead of tiles due to the performance. Also, you will need to import the OBJ into any other 3D modeling software and export it to the FBX format. Lightmap UV maps are not generated by SM2OBJ, you will to create them yourself (or do not use lightmaps at all and use dynamic lightning only).

## Performance

The export should not use more than 10MB of RAM. If you use more threads, the RAM usage will rise by ~5MB per thread.

## Bugs

* Not having enough HDD space may crash the program.

## Source files

After downloading the source code, you will get these files and folders:

* **source/** - GUI window classes.
* **source/exported** - Source files of the exporter only.
* **third-party-libs/** - Contains [FragmentFramework](http://matusnovak.github.io/fragmentframework/index.html) and [Zlib](http://www.zlib.net/) (both include headers and binaries)
* **resources/** - Resource file and application icon.
* **LICENSE** - License file.
* **README.md** - You are reading it now.
* **SM2OBJ.cbp** - Code::Blocks project file.

**Source files of the exporter inside the source/exporter folder:**

* **blockConfig.cpp** - Loads block config from StarMade data folder. 
* **blockConstructor.cpp** - Constructs blocks vertices and indices.
* **blockExtractor.cpp** - Exports vertices and indices as a text to temporary files.
* **blockVerticesData.cpp** - Contains blocks vertex, face and UV data exported from OBJ. (block, wdge, tetra, penta and corner).
* **config.cpp** - Configuration class.
* **constants.cpp** - Constants. Nothing more to say about this file.
* **exportBlueprint.cpp** - Main program flow.
* **chunkHeader.cpp** - Loads a header from smd2 file.
* **chunkLoader.cpp** - Loads and decompress chunk data.
* **chunkTempLoader.cpp** - Used for temporary saving decompressed chunks.
* **loadMeta.cpp** - Loads meta file (meta.smbpm).
* **materialExporter.cpp** - Exports material to the mtl file.
* **polygonFiltering.cpp** - Filters polygons (ones that occupies same space and removes unnecessary vertices).
* **structures.h** - All main data structures used by whole program.
* **textureExport.cpp** - Exports and converts textures.

## How to compile:

The binary releases are compiled with MinGW-w64 i686 GCC 4.9.2 I suggest that you use the same compiler.

Prefer to use Code::Blocks project file `SM2OBJ.cbp`

Or, to compile with command line: Include all source files in the `source` and `source/exporter` folders. Add compile search path to third party libraries located in `third-party-libs\FragmentFramework\include` and `third-party-libs\zlib\include` No other libraries are needed. Only `FragmentFramework.dll` is needed to be linked with the exe file (zlib is already linked in this DLL).

If you are using Visual Studio, check [FragmentFramework](https://github.com/matusnovak/fragmentframework) repository for the VS 2013 version of the library in: /FragmentFramework/lib/msvc/.

## ToDo

* Add comments to the source files

## Please comment

If bug occurs or you have problems please report the issue. Use github's issue tracker.

If you have questions or suggestions please feel free to contact me at GitHub or at at my email address.

## Copyright and license

SM2OBJ is distributed under the MIT License.

Copyright (C) 2015 by Matus Novak matusnov@gmail.com
