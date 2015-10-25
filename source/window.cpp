#include "window.hpp"

static sm2obj::window* windowPtr = NULL;

#define FRAMES_TOTAL 10

///=============================================================================
sm2obj::window::window(){
	exportThread.bindFunction(&sm2obj::window::exportThreadFunc, this);
	windowPtr = this;
}

///=============================================================================
sm2obj::window::~window(){
	exportThreadStop.store(true);
	exportThread.join();
}

///=============================================================================
void sm2obj::window::setup(){
	font = ffw::createUiFont(L"Segoe UI", 19, 550);
	if(font.isValid())this->setDefaultFont(&font);

	frame00 = ffw::createUiBitmap(L"data\\frame-00.bmp", 220, 240);
	frame04 = ffw::createUiBitmap(L"data\\frame-04.bmp", 480, 168);
	frame06 = ffw::createUiBitmap(L"data\\frame-06.bmp", 490, 108);

	ffw::vec2i windowSize(500, 300);

	buttonPrev = this->addButton(windowSize.x-330, windowSize.y-30, 100, 25, L"Prev");
	buttonNext = this->addButton(windowSize.x-220, windowSize.y-30, 100, 25, L"Next");
	buttonCancel = this->addButton(windowSize.x-110, windowSize.y-30, 100, 25, L"Cancel");

	widgetFrames.resize(FRAMES_TOTAL);

	// Frame 00 - Intro
	widgetFrames[0].push_back(this->addStaticImage(windowSize.x/2 - 110, windowSize.y/2 - 150, 220, 240, &frame00));
	widgetFrames[0].push_back(this->addLabel(windowSize.x/2 - 70, windowSize.y-60, 140, 20, L"Press Next to begin..."));

	// Frame 01 - StarMade folder
	widgetFrames[1].push_back(textInputStarMadeFolder = this->addTextInput(10, windowSize.y/2-50, windowSize.x-60, 25, L""));
	widgetFrames[1].push_back(buttonSelectStarMadeFolder = this->addButton(windowSize.x-40, windowSize.y/2-50, 30, 25, L"..."));
	widgetFrames[1].push_back(this->addLabel(10, windowSize.y/2-70, windowSize.x-20, 20, L"Please, select StarMade folder:"));
	widgetFrames[1].push_back(this->addLabel(10, windowSize.y/2, windowSize.x-20, 80,
		L"The selected folder must contain these folders:\n- blueprints\n- data\n- lib"));

	// Frame 02 - Blueprint selection
	widgetFrames[2].push_back(listBlueprints = this->addList(10, 30, windowSize.x-20, windowSize.y-50, ffw::uiList::vertical));
	widgetFrames[2].push_back(this->addLabel(10, 10, windowSize.x-20, 20, L"Please, select blueprint to export:"));

	// Frane 03 - Output folder
	widgetFrames[3].push_back(textInputOutputFolder = this->addTextInput(10, windowSize.y/2-50, windowSize.x-60, 25, L""));
	widgetFrames[3].push_back(buttonSelectOutputFolder = this->addButton(windowSize.x-40, windowSize.y/2-50, 30, 25, L"..."));
	widgetFrames[3].push_back(this->addLabel(10, windowSize.y/2-70, windowSize.x-20, 20, L"Please, select output folder:"));
	widgetFrames[3].push_back(this->addLabel(10, windowSize.y/2, windowSize.x-20, 80,
		L"OBJ and MTL files will be saved to this folder\nIf textures are enabled (check next slide) a folder \"textures\" will\nbe crated alongside."));

	// Frame 04 - UV Maps
	widgetFrames[4].push_back(this->addStaticImage(10, 10, 480, 168, &frame04));
	widgetFrames[4].push_back(radioUvMapsTiles = this->addRadio(30, 180, 200, 40, L"Separate textures per material"));
	widgetFrames[4].push_back(radioUvMapsAtlas = this->addRadio(windowSize.x-220, 180, 200, 40, L"Group textures to atlases"));
	widgetFrames[4].push_back(radioUvMapsNone = this->addRadio(windowSize.x/2 -100, 220, 200, 20, L"I don't want to use textures!"));
	widgetFrames[4].push_back(this->addLabel(10, windowSize.y-50, windowSize.x-20, 20, L"Note: Use atlases if not sure."));

	// Frame 05 - Texture options
	widgetFrames[5].push_back(this->addLabel(windowSize.x/2-160, windowSize.y/2-20, 150, 20, L"Texture tile size:"));
	widgetFrames[5].push_back(this->addCombo(windowSize.x/2-160, windowSize.y/2, 150, 20));
	auto combo = static_cast<ffw::uiCombo*>(widgetFrames[5].back());
	comboTextureSize = combo;
	combo->addItem(L"64 px");
	combo->addItem(L"128 px");
	combo->addItem(L"256 px");
	widgetFrames[5].push_back(this->addLabel(windowSize.x/2+10, windowSize.y/2-20, 150, 20, L"Texture format:"));
	widgetFrames[5].push_back(this->addCombo(windowSize.x/2+10, windowSize.y/2, 150, 20));
	combo = static_cast<ffw::uiCombo*>(widgetFrames[5].back());
	comboTextureFormat = combo;
	combo->addItem(L"PNG");
	combo->addItem(L"TGA");
	combo->addItem(L"BMP");
	combo->addItem(L"TIFF");
	widgetFrames[5].push_back(this->addLabel(10, windowSize.y-50, windowSize.x-20, 20, L"Note: Use 256px tiles as PNG if not sure."));

	// Frame 06 - Material options
	widgetFrames[6].push_back(this->addStaticImage(5, 30, 490, 108, &frame06));
	widgetFrames[6].push_back(this->addLabel(10, 10, windowSize.x-10, 20, L"Select which texture to use in MTL+OBJ & export:"));
	widgetFrames[6].push_back(checkboxMatDiffuse = this->addCheckbox(10, 140, 100, 20, L"Diffuse"));
	widgetFrames[6].push_back(checkboxMatEmissive = this->addCheckbox(110, 140, 100, 20, L"Emissive"));
	widgetFrames[6].push_back(checkboxMatAlpha = this->addCheckbox(210, 140, 100, 20, L"Alpha"));
	widgetFrames[6].push_back(radioMatBumps = this->addRadio(310, 140, 100, 20, L"Bumps"));
	widgetFrames[6].push_back(radioMatNormals = this->addRadio(410, 140, 100, 20, L"Normals"));
	widgetFrames[6].push_back(radioMatNoBumps = this->addRadio(360, 160, 100, 20, L"None"));
	widgetFrames[6].push_back(this->addLabel(10, 180, windowSize.x-20, 80,
		L"Diffuse - The color of the material\nEmissive - Light generated from the material (self illuminated blocks)\nAlpha - The transparency of the material\nBumps/Normals - The detailness of the material"));
	
	// Frame 07 - System options
	widgetFrames[7].push_back(this->addLabel(windowSize.x/2-70, windowSize.y/2, 200, 20, L"How many threads to use?"));
	widgetFrames[7].push_back(comboNumOfThreads = this->addCombo(windowSize.x/2-50, windowSize.y/2+20, 100, 20));
	combo = static_cast<ffw::uiCombo*>(widgetFrames[7].back());
	comboThreads = combo;
	for(int i = 0; i < 16; i++){
		combo->addItem(ffw::ansiToWstr(ffw::valToString(i+1)));
	}

	widgetFrames[7].push_back(checkboxExportAttachments = this->addCheckbox(windowSize.x/2-125, windowSize.y/2-60, 250, 20, L"Export ship's docked ships and turrets"));
	widgetFrames[7].push_back(this->addLabel(10, windowSize.y-50, windowSize.x-20, 20, L"Note: Do not use more threads than the number of CPU cores!"));

	// Frame 08 - Export type
	widgetFrames[8].push_back(buttonObjectPlusTextures = this->addButton(windowSize.x/2-100, windowSize.y/2-40, 200, 25, L"Object + Textures"));
	widgetFrames[8].push_back(buttonTexturesOnly = this->addButton(windowSize.x/2-100, windowSize.y/2, 200, 25, L"Textures only"));
	widgetFrames[8].push_back(buttonObjectOnly = this->addButton(windowSize.x/2-100, windowSize.y/2+40, 200, 25, L"Object only"));

	// Frame 09 - Export status
	widgetFrames[9].push_back(this->addGroup(10, 10, windowSize.x-20, windowSize.y-60, L"Export status:"));
	widgetFrames[9].push_back(labelBlockConfig = this->addLabel(20, 40, 250, 25, L""));
	widgetFrames[9].push_back(labelReadingMeta = this->addLabel(20, 70, 250, 25, L""));
	widgetFrames[9].push_back(labelLoadingChunks = this->addLabel(20, 100, 250, 25, L""));
	widgetFrames[9].push_back(labelGeneratingBlocks = this->addLabel(20, 130, 250, 25, L""));
	widgetFrames[9].push_back(labelCreatingPolys = this->addLabel(20, 160, 250, 25, L""));
	widgetFrames[9].push_back(labelMergingVertices = this->addLabel(20, 190, 250, 25, L""));
	widgetFrames[9].push_back(labelExportingTextures = this->addLabel(20, 220, 250, 25, L""));

	widgetFrames[9].push_back(progressBlockConfig = this->addProgressbar(300, 40, 170, 25));
	widgetFrames[9].push_back(progressReadingMeta = this->addProgressbar(300, 70, 170, 25));
	widgetFrames[9].push_back(progressLoadingChunks = this->addProgressbar(300, 100, 170, 25));
	widgetFrames[9].push_back(progressGeneratingBlocks = this->addProgressbar(300, 130, 170, 25));
	widgetFrames[9].push_back(progressCreatingPolys = this->addProgressbar(300, 160, 170, 25));
	widgetFrames[9].push_back(progressMergingVertices = this->addProgressbar(300, 190, 170, 25));
	widgetFrames[9].push_back(progressExportingTextures = this->addProgressbar(300, 220, 170, 25));

	currentFrame = frame::intro;
	hideAll();
	widgetFrames[0][0]->show();
	widgetFrames[0][1]->show();

	buttonPrev->disable();
	buttonCancel->disable();

	std::vector<std::string> missingValues;
	if(userDefaults.load(ffw::getExecutablePath() + "\\defaults.json", &missingValues)){
		ffw::log() << "User defaults loaded!";

		// StarMade input folder
		textInputStarMadeFolder->setValue(ffw::utf8ToWstr(userDefaults.inputStarMadeFolder));

		// Output folder
		textInputOutputFolder->setValue(ffw::utf8ToWstr(userDefaults.outputFolder));

		// Uv Maps options
		switch(userDefaults.uvMapsOptions){
			case 0: radioUvMapsNone->setValue(true); break;
			case 1: radioUvMapsTiles->setValue(true); break;
			case 2: radioUvMapsAtlas->setValue(true); break;
		}

		// Texture options
		comboTextureFormat->setSelected(userDefaults.textureFormat);
        comboTextureSize->setSelected(userDefaults.textureSize);

		// Material options
		checkboxMatDiffuse->setValue	(userDefaults.useDiffuseTextures);
        checkboxMatAlpha->setValue(userDefaults.useAlphaTextures);
        checkboxMatEmissive->setValue(userDefaults.useEmissiveTextures);
		if(userDefaults.useBumpsOrNormals){
			radioMatNormals->setValue(true);
		} else {
			radioMatBumps->setValue(true);
		}

		// System options
		comboNumOfThreads->setSelected(userDefaults.numOfThreads);
		checkboxExportAttachments->setValue(userDefaults.exportAttachments);

	} else {
		ffw::logWarning() << "User defaults failed to load! Missing values:";
        for(const auto& item : missingValues)ffw::logWarning() << "    > " << item;
	}
}

///=============================================================================
bool sm2obj::window::checkoutStarMadeFolder(){
	ffw::directory dir;
	starMadeFolder = ffw::wstrToAnsi(textInputStarMadeFolder->getValue());
	if(!dir.open(starMadeFolder)){
		ffw::logError() << "Failed to open StarMade directory! Is the path valid?";
		ffw::showModalError(this, L"Error!", L"Failed to open StarMade directory! Is the path valid?");
		return false;
	}

	bool hasBlueprints = false;
	bool hasData = false;

	for(const auto& d : dir.getDirs()){
		if(d == "data")hasData = true;
		if(d == "blueprints")hasBlueprints = true;
	}

	if(!(hasData && hasBlueprints)){
		ffw::logError() << "Invalid StarMade folder!";
		ffw::showModalError(this, L"Error!", L"Invalid StarMade folder!");
		return false;
	}

	if(!dir.open(starMadeFolder + "\\blueprints")){
		ffw::logError() << "Can't open blueprints folder! Is the path valid?";
		ffw::showModalError(this, L"Error!", L"Can't open blueprints folder! Is the path valid?");
		return false;
	}

	listBlueprints->clear();
	blueprintsList.clear();
	for(const auto& d : dir.getDirs()){
		if(d == "." || d == "..")continue;
		blueprintsList.push_back(d);
		listBlueprints->addItem(ffw::ansiToWstr(d));
	}

	ffw::logInfo() << "StarMade folder valid!";

	return true;
}

///=============================================================================
bool sm2obj::window::checkoutBlueprint(){
	int index = listBlueprints->getSelected();
	if(size_t(index) < 0 || index >= blueprintsList.size()){
		ffw::logError() << "Please, select blueprint before continuing!";
		ffw::showModalError(this, L"Error!", L"Please, select blueprint before continuing!");
		return false;
	}

	blueprintName = blueprintsList[index];
	return true;
}

///=============================================================================
bool sm2obj::window::checkoutOutputFolder(){
	outputFolder = ffw::wstrToAnsi(textInputOutputFolder->getValue());
	
	std::fstream test(outputFolder + "\\delete_me.txt", std::ios::trunc | std::ios::out);
	if(!test){
		ffw::logError() << "Please, select correct output folder before continuing!";
		ffw::showModalError(this, L"Error!", L"Please, select correct output folder before continuing!");
		return false;
	}
	
	system(std::string("DEL \"" + outputFolder + "\\delete_me.txt\"").c_str());
	return true;
}

///=============================================================================
bool sm2obj::window::checkoutUvMapsSettings(){
	if(radioUvMapsNone->getValue()){
		exportMaterials = false;
		buttonObjectPlusTextures->disable();
		buttonTexturesOnly->disable();
		buttonObjectOnly->enable();
		exportUV = false;
	} else {
		exportMaterials = true;
		buttonObjectPlusTextures->enable();
		buttonTexturesOnly->enable();
		buttonObjectOnly->enable();
		exportUV = true;
	}

	bool a = radioUvMapsAtlas->getValue();
	bool b = radioUvMapsNone->getValue();
	bool c = radioUvMapsTiles->getValue();

	if(radioUvMapsAtlas->getValue()){
		exportAtlas = true;
	} else {
		exportAtlas = false;
	}

	if(a || b || c)return true;

	ffw::logError() << "Please, select if you want to use tiles, atlases, or disable textures!";
	ffw::showModalError(this, L"Error!", L"Please, select if you want to use tiles, atlases, or disable textures!");

	return false;
}

///=============================================================================
bool sm2obj::window::checkoutTextureSettings(){
	int size = comboTextureSize->getSelected();
	int format = comboTextureFormat->getSelected();

	if(size < 0){
		ffw::logError() << "Please, select the size of tiles!";
		ffw::showModalError(this, L"Error!", L"Please, select the size of tiles!");
		return false;
	}

	if(format < 0){
		ffw::logError() << "Please, select the format of textures!";
		ffw::showModalError(this, L"Error!", L"Please, select the format of textures!");
		return false;
	}

	return true;
}

///=============================================================================
bool sm2obj::window::checkoutSystemSettings(){
	int num = comboThreads->getSelected();

	if(num < 0){
		ffw::logError() << "Please, select how many threads to use!";
		ffw::showModalError(this, L"Error!", L"Please, select how many threads to use!");
		return false;
	}

	return true;
}

///=============================================================================
bool sm2obj::window::checkoutMaterialSettings(){
	bool a = radioMatBumps->getValue();
	bool b = radioMatNormals->getValue();
	useBumps = a;
	if(a || b)return true;

	ffw::logError() << "Please, select if you want to use bump maps or normal maps!";
	ffw::showModalError(this, L"Error!", L"Please, select if you want to use bump maps or normal maps!");

	return false;
}

///=============================================================================
void sm2obj::window::nextFrame(){
	if(currentFrame == frame::starMadeFolderSelect){
		if(!checkoutStarMadeFolder())return;
	}

	if(currentFrame == frame::bleprintList){
		if(!checkoutBlueprint())return;
	}

	if(currentFrame == frame::outputFolderSelect){
		if(!checkoutOutputFolder())return;
	}

	if(currentFrame == frame::uvMapsSettings){
		if(!checkoutUvMapsSettings())return;
	}

	if(currentFrame == frame::textureSettings){
		if(!checkoutTextureSettings())return;
	}

	if(currentFrame == frame::materialSettings){
		if(!checkoutMaterialSettings())return;
	}

	if(currentFrame == frame::uvMapsSettings){
		if(radioUvMapsNone->getValue()){
			hideAll();
			currentFrame = frame::materialSettings;
		}
	}

	if(currentFrame == frame::systemSettings){
		if(!checkoutSystemSettings())return;
		buttonNext->disable();
	}
	
	if(currentFrame < FRAMES_TOTAL-1){
		buttonPrev->enable();
		for(const auto& w : widgetFrames[currentFrame]){
			w->hide();
		}
		currentFrame++;
		for(const auto& w : widgetFrames[currentFrame]){
			w->show();
		}
		if(currentFrame == FRAMES_TOTAL-1){
			buttonNext->disable();
		}
	}

	this->redraw();
}

///=============================================================================
void sm2obj::window::prevFrame(){
	if(currentFrame == frame::exportType){
		buttonNext->enable();
	}
	
	if(currentFrame > 0){
		buttonNext->enable();
		for(const auto& w : widgetFrames[currentFrame]){
			w->hide();
		}
		if(currentFrame == frame::systemSettings && radioUvMapsNone->getValue()){
			hideAll();
			currentFrame = frame::uvMapsSettings;
		} else {
			currentFrame--;
		}
		for(const auto& w : widgetFrames[currentFrame]){
			w->show();
		}
		if(currentFrame == 0){
			buttonPrev->disable();
		}
	}
}

///=============================================================================
void sm2obj::window::hideAll(){
	for(const auto& v : widgetFrames){
		for(const auto& w : v){
			w->hide();
		}
	}
}

///=============================================================================
void sm2obj::window::windowCloseEvent(){
	exportThreadStop.store(true);
	exportThread.join();

	saveUserDefaults();

	this->shouldClose(true);
}

///=============================================================================
void sm2obj::window::saveUserDefaults(){
	userDefaults.inputStarMadeFolder = ffw::wstrToUtf8(textInputStarMadeFolder->getValue());
	userDefaults.outputFolder = ffw::wstrToUtf8(textInputOutputFolder->getValue());

	if(radioUvMapsTiles->getValue())userDefaults.uvMapsOptions = 1;
	else if(radioUvMapsAtlas->getValue())userDefaults.uvMapsOptions = 2;
	else userDefaults.uvMapsOptions = 0;

	userDefaults.textureFormat = comboTextureFormat->getSelected();
	userDefaults.textureSize = comboTextureSize->getSelected();

	userDefaults.useDiffuseTextures = checkboxMatDiffuse->getValue();
	userDefaults.useAlphaTextures = checkboxMatAlpha->getValue();
	userDefaults.useEmissiveTextures = checkboxMatEmissive->getValue();

	userDefaults.useBumpsOrNormals = radioMatNormals->getValue();

	userDefaults.numOfThreads = comboNumOfThreads->getSelected();
	userDefaults.exportAttachments = checkboxExportAttachments->getValue();

	if(userDefaults.save(ffw::getExecutablePath() + "\\defaults.json")){
		ffw::log() << "User defaults saved!";
	} else {
		ffw::logWarning() << "User defaults failed to save!";
	}
}

///=============================================================================
void sm2obj::window::widgetEvent(const ffw::uiWidget* Widget){
	if(Widget == buttonNext)nextFrame();
	if(Widget == buttonPrev)prevFrame();

	if(Widget == buttonSelectStarMadeFolder){
		std::wstring path = ffw::openFolderDialog(L"Please, select StarMade folder",
			ffw::utf8ToWstr(userDefaults.inputStarMadeFolder));
		if(path.size() > 0){
			textInputStarMadeFolder->setValue(path);
		}
	}

	if(Widget == buttonSelectOutputFolder){
		std::wstring path = ffw::openFolderDialog(L"Please, select output folder",
			ffw::utf8ToWstr(userDefaults.outputFolder));
		if(path.size() > 0){
			textInputOutputFolder->setValue(path);
		}
	}

	if(Widget == radioUvMapsTiles){
		radioUvMapsTiles->setValue(true);
		radioUvMapsAtlas->setValue(false);
		radioUvMapsNone->setValue(false);
	}

	if(Widget == radioUvMapsAtlas){
		radioUvMapsTiles->setValue(false);
		radioUvMapsAtlas->setValue(true);
		radioUvMapsNone->setValue(false);
	}

	if(Widget == radioUvMapsNone){
		radioUvMapsTiles->setValue(false);
		radioUvMapsAtlas->setValue(false);
		radioUvMapsNone->setValue(true);
	}

	if(Widget == radioMatBumps){
		radioMatBumps->setValue(true);
		radioMatNormals->setValue(false);
		radioMatNoBumps->setValue(false);
	}

	if(Widget == radioMatNormals){
		radioMatBumps->setValue(false);
		radioMatNormals->setValue(true);
		radioMatNoBumps->setValue(false);
	}

	if(Widget == radioMatNoBumps){
		radioMatBumps->setValue(false);
		radioMatNormals->setValue(false);
		radioMatNoBumps->setValue(true);
	}

	if(Widget == buttonObjectPlusTextures){
		exportObject = true;
		exportTextures = true;
	}

	if(Widget == buttonTexturesOnly){
		exportObject = false;
		exportTextures = true;
	}

	if(Widget == buttonObjectOnly){
		exportObject = true;
		exportTextures = false;
	}

	// Start export
	if(Widget == buttonObjectPlusTextures || Widget == buttonTexturesOnly || Widget == buttonObjectOnly){
		nextFrame();
		exportThread.start(NULL);
		buttonPrev->disable();
		buttonNext->disable();
		buttonCancel->enable();
	}

	if(Widget == buttonCancel){
		if(exportFinished){
			this->shouldClose(true);
		} else {
			// Wait for thread
			exportThreadStop.store(true);
			exportThread.join();
			ffw::showModalWarning(this, L"Warning!", L"Export cancelled by user! The exported object/textures may be corrupted!");
			this->shouldClose(true);
		}
		saveUserDefaults();
	}
}
