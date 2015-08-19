#include "window.hpp"

static sm2obj::window* windowPtr = NULL;

///=============================================================================
sm2obj::window::window(){
	windowPtr = this;
}

///=============================================================================
sm2obj::window::~window(){
}

///=============================================================================
void sm2obj::window::setup(){
	font = ffw::createUiFont(L"Segoe UI", 19, 550);
	if(font.isValid())this->setDefaultFont(&font);

	int posY = 5;
	int posYOff = 5;

	// Blueprint folder
	this->addLabel(5, 5, 480, 20, L"Select blueprint folder:");
	textInputFolder =
	this->addTextInput(5, 25, 430, 25, L"");
	buttonSelectInputFolder =
	this->addButton(440, 25, 45, 25, L"...");


	// StarMade data folder
	this->addLabel(5, 55, 480, 20, L"Select StarMade data folder:");
	textInputData =
	this->addTextInput(5, 75, 430, 25, L"");
	buttonSelectInputData =
	this->addButton(440, 75, 45, 25, L"...");

	// Output folder
	this->addLabel(5, 105, 480, 20, L"Select output folder for OBJ and MTL files:");
	textOutputFolder =
	this->addTextInput(5, 125, 430, 25, L"");
	buttonSelectOutputFolder =
	this->addButton(440, 125, 45, 25, L"...");

	// UV maps options
	this->addGroup(5, 155, 480, 55, L"UV maps options:");
	comboUvMapSettings =
	this->addCombo(10, 175, 470, 25);
	comboUvMapSettings->addItem(L"Do not export UV maps");
	comboUvMapSettings->addItem(L"Export UV maps and split tiles (separate material per tile)");
	comboUvMapSettings->addItem(L"Export UV maps and use atlas (single material per atlas)");

	// Material options
	this->addGroup(5, 215, 235, 115, L"Material options:");
	checkboxExportMaterials =
	this->addCheckbox(10, 235, 110, 20, L"Export materials");
	checkboxExportDiffuse =
	this->addCheckbox(10, 265, 110, 20, L"Diffuse");
	checkboxExportAlpha =
	this->addCheckbox(10, 285, 110, 20, L"Alpha");
	checkboxExportNormal =
	this->addCheckbox(120, 265, 110, 20, L"Normal/bump");
	checkboxExportEmissive =
	this->addCheckbox(120, 285, 110, 20, L"Emissive");

	// System options
	this->addGroup(250, 215, 235, 55, L"System options:");
	this->addLabel(255, 235, 190, 20, L"Number of threads (max 16):");
	textNumOfThreads =
	this->addTextInput(440, 235, 40, 20, L"1");

	// Attachments
	this->addGroup(250, 275, 235, 55, L"Attachment options:");
	checkboxAttachments =
	this->addCheckbox(255, 295, 225, 25, L"Export attached turrets/ships");

	// Export button
	buttonExportObject =
	this->addButton(170, 335, 140, 35, L"Export object");

	// Texture export options
	this->addGroup(5, 375, 480, 135, L"Texture export options:");
	this->addLabel(10, 395, 470, 20, L"Select output folder for textures:");
	textTextureOutput =
	this->addTextInput(10, 415, 420, 25, L"");
	buttonSelectTextureOutput =
	this->addButton(435, 415, 45, 25, L"...");

	// Texture format
	this->addLabel(10, 445, 100, 20, L"Texture format:");
	comboTextureFormat =
	this->addCombo(110, 445, 125, 25);
	comboTextureFormat->addItem(L"*.BMP");
	comboTextureFormat->addItem(L"*.PNG");
	comboTextureFormat->addItem(L"*.TGA");
	comboTextureFormat->addItem(L"*.TIFF");

	// Texture type
	this->addLabel(10, 475, 100, 20, L"Export as:");
	comboTextureType =
	this->addCombo(110, 475, 125, 25);
	comboTextureType->addItem(L"Separate tiles");
	comboTextureType->addItem(L"Whole atlas");

	// Texture size
	this->addLabel(245, 445, 100, 20, L"Tile size:");
	comboTextureSize =
	this->addCombo(350, 445, 130, 25);
	comboTextureSize->addItem(L"64px");
	comboTextureSize->addItem(L"128px");
	comboTextureSize->addItem(L"256px");

	// Texture normals
	this->addLabel(245, 475, 100, 20, L"Normals:");
	comboTextureNormals =
	this->addCombo(350, 475, 130, 25);
	comboTextureNormals->addItem(L"Use normals");
	comboTextureNormals->addItem(L"Convert to bump");

	// Export textures button
	buttonExportTextures =
	this->addButton(170, 515, 140, 35, L"Export textures");

	// Progressbar
	progressbar = this->addProgressbar(5, 560, 480, 25);
	progress = this->addLabel(5, 590, 480, 20, L"");

    std::vector<std::string> missingValues;
	if(userDefaults.load(ffw::getExecutablePath() + "\\defaults.json", &missingValues)){
		ffw::logger().print() << "User defaults loaded!";

		textInputFolder			->setValue		(ffw::utf8ToWstr(userDefaults.inputBlueprintFolder));
        textInputData			->setValue		(ffw::utf8ToWstr(userDefaults.inputDataFolder));
        textOutputFolder		->setValue		(ffw::utf8ToWstr(userDefaults.outputFileFolder));
        textTextureOutput		->setValue		(ffw::utf8ToWstr(userDefaults.outputTextureFolder));
        comboUvMapSettings		->setSelected	(userDefaults.uvMapsOptions);
        checkboxExportMaterials	->setValue		(userDefaults.exportMaterials);
        checkboxExportDiffuse	->setValue		(userDefaults.useDiffuseTextures);
        checkboxExportAlpha		->setValue		(userDefaults.useAlphaTextures);
        checkboxExportNormal	->setValue		(userDefaults.useNormalTextures);
        checkboxExportEmissive	->setValue		(userDefaults.useEmissiveTextures);
        textNumOfThreads		->setValue		(ffw::utf8ToWstr(userDefaults.numOfThreads));
        comboTextureFormat		->setSelected	(userDefaults.textureOutputFormat);
        comboTextureNormals		->setSelected	(userDefaults.textureNormals);
        comboTextureType		->setSelected	(userDefaults.textureExportType);
        comboTextureSize		->setSelected	(userDefaults.textureTileSize);
        checkboxAttachments		->setValue		(userDefaults.exportAttachments);
	} else {
		ffw::logger().warning() << "User defaults failed to load! Missing values:";
        for(const auto& item : missingValues)ffw::logger().warning() << "    > " << item;
	}

	ffw::var data;
	std::string str;
	ffw::loadJSON("defaults.json", &data);
	ffw::encodeJSON(&str, &data, true, true);
	std::cout << str << std::endl;
}

///=============================================================================
void sm2obj::window::windowCloseEvent(){
	bruteforceExit();
	exportThread.join();

	userDefaults.inputBlueprintFolder	= ffw::wstrToUtf8(textInputFolder->getValue());
    userDefaults.inputDataFolder		= ffw::wstrToUtf8(textInputData->getValue());
    userDefaults.outputFileFolder		= ffw::wstrToUtf8(textOutputFolder->getValue());
    userDefaults.outputTextureFolder	= ffw::wstrToUtf8(textTextureOutput->getValue());
    userDefaults.uvMapsOptions			= comboUvMapSettings->getSelected();
    userDefaults.exportMaterials		= checkboxExportMaterials->getValue();
    userDefaults.useDiffuseTextures		= checkboxExportDiffuse->getValue();
    userDefaults.useAlphaTextures		= checkboxExportAlpha->getValue();
    userDefaults.useNormalTextures		= checkboxExportNormal->getValue();
    userDefaults.useEmissiveTextures	= checkboxExportEmissive->getValue();
    userDefaults.numOfThreads			= ffw::wstrToUtf8(textNumOfThreads->getValue());
    userDefaults.textureOutputFormat	= comboTextureFormat->getSelected();
    userDefaults.textureNormals			= comboTextureNormals->getSelected();
    userDefaults.textureExportType		= comboTextureType->getSelected();
    userDefaults.textureTileSize		= comboTextureSize->getSelected();
    userDefaults.exportAttachments		= checkboxAttachments->getValue();

	if(userDefaults.save(ffw::getExecutablePath() + "\\defaults.json")){
		ffw::logger().print() << "User defaults saved!";
	} else {
		ffw::logger().warning() << "User defaults failed to save!";
	}

	// Remove temp folder
    system(std::string("rmdir /Q /S " + ffw::getExecutablePath() + "\\temp").c_str());

	this->destroy();
}

///=============================================================================
void sm2obj::window::callbackLogError(const std::string& Message){
	ffw::logger().error() << Message;
	ffw::showModalError(windowPtr, L"Error", ffw::utf8ToWstr(Message));
}

///=============================================================================
void sm2obj::window::callbackLogInfo(const std::string& Message){
	ffw::logger().info() << Message;
	windowPtr->progress->setValue(ffw::utf8ToWstr(Message));
}

///=============================================================================
void sm2obj::window::callbackLogDebug(const std::string& Message){
	ffw::logger().debug() << Message;
}

///=============================================================================
void sm2obj::window::callbackLogWarning(const std::string& Message){
	ffw::logger().warning() << Message;
	windowPtr->logWarning = true;
}

///=============================================================================
void sm2obj::window::callbackProgress(int Progress, int Total){
	int p = (Progress / float(Total)) * 100;
	windowPtr->progressbar->setValue(p);
}

///=============================================================================
void sm2obj::window::callbackExit(bool Success){
	if(Success){
        if(windowPtr->logWarning){
            ffw::showModalWarning(windowPtr, L"Warning!", L"Blueprint exported! Process ended with warning(s)! Look for warning messages in log.txt for more information.");
        } else {
            ffw::showModalInfo(windowPtr, L"Success!", L"Blueprint exported! Process ended with no errors.");
        }
    }
    windowPtr->progressbar->setValue(0);
    windowPtr->progress->setValue(L"");
}

///=============================================================================
void* sm2obj::window::exportBlueprintFunc(void* Data){
	exportThreadMutex.lock();
	logWarning = false;

    exportBlueprintArgs args;

    // Input/output folders
    args.inputConfigFolder = ffw::wstrToUtf8(textInputData->getValue()) + "\\config";
    args.inputFolder = ffw::wstrToUtf8(textInputFolder->getValue());
    args.outputFolder = ffw::wstrToUtf8(textOutputFolder->getValue());

    // Output name
    size_t pos = args.inputFolder.find_last_of('\\');
    if(pos != std::string::npos && pos != args.inputFolder.size()-1){
        args.outputName = args.inputFolder.substr(pos+1, args.inputFolder.size()-pos-1);
        callbackLogDebug("Output name: " + args.outputName);
    } else {
        callbackLogError("Could not detect blueprint folder name! Make sure the path is correct!");
        exportThreadMutex.unlock();
        return NULL;
    }

    // These arguments are not needed
    args.textureExtension = "";
    args.imageSaver = NULL;
    args.normalToBump = NULL;
    args.width = 0;

    // UV options
    int uvOption = comboUvMapSettings->getSelected();
    if(uvOption == 0){
        args.useAtlas = false;
        args.exportUV = false;
    } else if(uvOption == 1){
        args.exportUV = true;
        args.useAtlas = false;
    } else if(uvOption == 2){
        args.exportUV = true;
        args.useAtlas = true;
    } else {
        callbackLogError("Please, select what to do with UV maps!");
        exportThreadMutex.unlock();
        return NULL;
    }

    // Material options
    args.exportMaterials = checkboxExportMaterials->getValue();
    args.exportDiffuse = checkboxExportDiffuse->getValue();
    args.exportAlpha = checkboxExportAlpha->getValue();
    args.exportNormals = checkboxExportNormal->getValue();
    args.exportEmissive = checkboxExportEmissive->getValue();
    args.specularHighlight = true;

    // Thread options
    args.numOfThreads = 0;
    try {
        args.numOfThreads = ffw::stringToVal<int>(ffw::wstrToUtf8(textNumOfThreads->getValue()));
    } catch (std::exception e){
        callbackLogError("Wrong number of threads! Please, write a number");
        exportThreadMutex.unlock();
        return NULL;
    }

    if(args.numOfThreads < 1 || args.numOfThreads > 16){
        callbackLogError("Wrong number of threads! Use values between 1 and 16");
        exportThreadMutex.unlock();
        return NULL;
    }

    // Texture extension
    switch(comboTextureFormat->getSelected()){
    case 0: args.textureExtension = "bmp"; break;
    case 1: args.textureExtension = "png"; break;
    case 2: args.textureExtension = "tga"; break;
    case 3: args.textureExtension = "tiff"; break;
    default: callbackLogError("Please, select texture format!"); exportThreadMutex.unlock(); return NULL;
    };

    // Attachment options
    args.exportAttachments = checkboxAttachments->getValue();

    // Callbacks
    args.callbackLogError = &this->callbackLogError;
    args.callbackLogInfo = &this->callbackLogInfo;
    args.callbackLogDebug = &this->callbackLogDebug;
    args.callbackLogWarning = &this->callbackLogWarning;
    args.callbackProgress = &this->callbackProgress;
    args.callbackTerminate = &this->callbackExit;

    callbackLogDebug("Input config folder: " + args.inputConfigFolder);
    callbackLogDebug("Input blueprint folder: " + args.inputFolder);
    callbackLogDebug("Output folder: " + args.outputFolder);
    callbackLogDebug("Output file name: " + args.outputName);
    callbackLogDebug("Export UVs: " + ffw::valToString(args.exportUV));
    callbackLogDebug("Use atlas: " + ffw::valToString(args.useAtlas));
    callbackLogDebug("Use diffuse textures: " + ffw::valToString(args.exportDiffuse));
    callbackLogDebug("Use alpha textures: " + ffw::valToString(args.exportAlpha));
    callbackLogDebug("Use normal textures: " + ffw::valToString(args.exportNormals));
    callbackLogDebug("Use emissive textures: " + ffw::valToString(args.exportEmissive));
    callbackLogDebug("number of threads: " + ffw::valToString(args.numOfThreads));
    callbackLogDebug("Export attachments: " + ffw::valToString(args.exportAttachments));

    exportBlueprint(args);
    exportThreadMutex.unlock();
	return NULL;
}

///=============================================================================
void* sm2obj::window::exportTexturesFunc(void* Data){
    exportThreadMutex.lock();
	logWarning = false;

    exportBlueprintArgs args;

    // Input/output folders
    args.inputConfigFolder = ffw::wstrToUtf8(textInputData->getValue()) + "\\config";
    args.inputFolder = ffw::wstrToUtf8(textInputData->getValue());
    args.outputFolder = ffw::wstrToUtf8(textTextureOutput->getValue());

    // Texture extension
    switch(comboTextureFormat->getSelected()){
    case 0: args.textureExtension = "bmp"; args.imageSaver = &ffw::saveBMP; break;
    case 1: args.textureExtension = "png"; args.imageSaver = &ffw::savePNG; break;
    case 2: args.textureExtension = "tga"; args.imageSaver = &ffw::saveTGA; break;
    case 3: args.textureExtension = "tiff"; args.imageSaver = &ffw::saveTIFF; break;
    default: callbackLogError("Please, select texture format!"); exportThreadMutex.unlock(); return NULL;
    };

    // Texture size
    switch(comboTextureSize->getSelected()){
    case 0: args.inputFolder += "\\textures\\block\\Default\\64"; args.width = 64; break;
    case 1: args.inputFolder += "\\textures\\block\\Default\\128"; args.width = 128; break;
    case 2: args.inputFolder += "\\textures\\block\\Default\\256"; args.width = 256; break;
    default: callbackLogError("Please, select tile size!"); exportThreadMutex.unlock(); return NULL;
    };

    // Texture normals
    switch(comboTextureNormals->getSelected()){
    case 0: args.normalToBump = false; break;
    case 1: args.normalToBump = true; break;
    default: callbackLogError("Please, select what to do with normals!"); exportThreadMutex.unlock(); return NULL;
    };

    // Texture type
    if(comboTextureType->getSelected() < 0 || comboTextureType->getSelected() > 1){
        callbackLogError("Please, select export type of textures! (Separate tiles or use whole atlas)");
        exportThreadMutex.unlock(); return NULL;
    }

    // Callbacks
    args.callbackLogError = &this->callbackLogError;
    args.callbackLogInfo = &this->callbackLogInfo;
    args.callbackLogDebug = &this->callbackLogDebug;
    args.callbackLogWarning = &this->callbackLogWarning;
    args.callbackProgress = &this->callbackProgress;
    args.callbackTerminate = &this->callbackExit;

    callbackLogDebug("StarMade texture folder: " + args.inputFolder);
    callbackLogDebug("Texture output folder: " + args.outputFolder);
    callbackLogDebug("Convert normals: " + ffw::valToString(args.normalToBump));
    callbackLogDebug("Use atlas instead of splitting tiles: " + ffw::valToString(comboTextureType->getSelected()));

    if(comboTextureType->getSelected() == 0){
        exportTextures(args);
    } else if(comboTextureType->getSelected() == 1){
        if(exportAtlases(args))
            exportEmissiveAtlas(args);
    }

    exportThreadMutex.unlock();
	return NULL;
}

///=============================================================================
void sm2obj::window::widgetEvent(const ffw::uiWidget* Widget){
	// "Widget" is a pointer to a widget which was triggered by user interaction
	// To test which widget was triggered, simply compare pointers

	if(Widget == buttonSelectInputData){
		std::wstring currentFolder = textInputData->getValue();
		textInputData->setValue(ffw::openFolderDialog(L"Select StarMade data folder:", currentFolder));
	}

	if(Widget == buttonSelectInputFolder){
		std::wstring currentFolder = textInputFolder->getValue();
		textInputFolder->setValue(ffw::openFolderDialog(L"Select blueprint folder:", currentFolder));
	}

	if(Widget == buttonSelectOutputFolder){
		std::wstring currentFolder = textOutputFolder->getValue();
		textOutputFolder->setValue(ffw::openFolderDialog(L"Select output folder:", currentFolder));
	}

	if(Widget == buttonSelectTextureOutput){
		std::wstring currentFolder = textTextureOutput->getValue();
		textTextureOutput->setValue(ffw::openFolderDialog(L"Select texture output folder:", currentFolder));
	}

	if(Widget == buttonExportObject){
		if(!exportThreadMutex.tryLock()){
			ffw::showModalError(this, L"Error", L"Process has already started!");
			return;
		} else {
		    exportThreadMutex.unlock();
		    exportThread.bindFunction(std::bind(&sm2obj::window::exportBlueprintFunc, this, std::placeholders::_1));
		    exportThread.start(NULL);
		}
	}

	if(Widget == buttonExportTextures){
		if(!exportThreadMutex.tryLock()){
			ffw::showModalError(this, L"Error", L"Process has already started!");
			return;
		} else {
		    exportThreadMutex.unlock();
		    exportThread.bindFunction(std::bind(&sm2obj::window::exportTexturesFunc, this, std::placeholders::_1));
		    exportThread.start(NULL);
		}
	}
}

///=============================================================================
void sm2obj::window::windowPosEvent(short PosX, short PosY){
}

///=============================================================================
void sm2obj::window::windowSizeEvent(short Width, short Height){
}


