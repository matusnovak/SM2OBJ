/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_WINDOW
#define SM2OBJ_WINDOW

#include <ffw.h>
#include "defaults.h"
//#include "exporter/exportBlueprint.h"
//#include "exporter/textureExport.h"

namespace sm2obj {
    class window: public ffw::uiWindow {
	public:
		window();
		~window();

		ffw::uiButton* buttonNext;
		ffw::uiButton* buttonPrev;
		ffw::uiButton* buttonCancel;

		ffw::uiTextInput* textInputStarMadeFolder;
		ffw::uiButton* buttonSelectStarMadeFolder;
		ffw::uiList* listBlueprints;
		ffw::uiTextInput* textInputOutputFolder;
		ffw::uiButton* buttonSelectOutputFolder;

		ffw::uiRadio* radioUvMapsTiles;
		ffw::uiRadio* radioUvMapsAtlas;
		ffw::uiRadio* radioUvMapsNone;

		ffw::uiRadio* radioMatBumps;
		ffw::uiRadio* radioMatNormals;
		ffw::uiRadio* radioMatNoBumps;

		ffw::uiCombo* comboTextureSize;
		ffw::uiCombo* comboTextureFormat;

		ffw::uiCheckbox* checkboxMatDiffuse;
		ffw::uiCheckbox* checkboxMatEmissive;
		ffw::uiCheckbox* checkboxMatAlpha;

		ffw::uiCheckbox* checkboxExportAttachments;
		ffw::uiCombo* comboNumOfThreads;

		ffw::uiCombo* comboThreads;

		ffw::uiButton* buttonObjectPlusTextures;
		ffw::uiButton* buttonTexturesOnly;
		ffw::uiButton* buttonObjectOnly;

		ffw::uiLabel* labelBlockConfig;
		ffw::uiLabel* labelReadingMeta;
		ffw::uiLabel* labelLoadingChunks;
		ffw::uiLabel* labelGeneratingBlocks;
		ffw::uiLabel* labelCreatingPolys;
		ffw::uiLabel* labelMergingVertices;
		ffw::uiLabel* labelExportingTextures;

		ffw::uiProgressbar* progressBlockConfig;
		ffw::uiProgressbar* progressReadingMeta;
		ffw::uiProgressbar* progressLoadingChunks;
		ffw::uiProgressbar* progressGeneratingBlocks;
		ffw::uiProgressbar* progressCreatingPolys;
		ffw::uiProgressbar* progressMergingVertices;
		ffw::uiProgressbar* progressExportingTextures;

	private:
		void setup() override;
		void windowCloseEvent() override;
		void widgetEvent(const ffw::uiWidget* Widget) override;
		//void windowMovedEvent(int PosX, int PosY) override;
		//void windowResizeEvent(int Width, int Height) override;

		/*static void callbackLogError(const std::string& Message);
		static void callbackLogInfo(const std::string& Message);
		static void callbackLogDebug(const std::string& Message);
		static void callbackLogWarning(const std::string& Message);
		static void callbackProgress(int Progress, int Total);
		static void callbackExit(bool Success);*/

		void nextFrame();
		void prevFrame();
		void hideAll();
		bool checkoutStarMadeFolder();
		bool checkoutBlueprint();
		bool checkoutOutputFolder();
		bool checkoutUvMapsSettings();
		bool checkoutTextureSettings();
		bool checkoutSystemSettings();
		bool checkoutMaterialSettings();
		void saveUserDefaults();

		ffw::uiFont font;
		std::vector<std::vector<ffw::uiWidget*>> widgetFrames;
		std::string starMadeFolder;
		std::string blueprintName;
		std::string outputFolder;
		std::vector<std::string> blueprintsList;
		bool exportMaterials;
		bool exportTextures;
		bool exportObject;
		bool exportAtlas;
		bool exportUV;
		bool useBumps;
		bool exportFinished;

		ffw::uiBitmap frame00;
		ffw::uiBitmap frame04;
		ffw::uiBitmap frame06;

		enum frame {
			intro = 0,
			starMadeFolderSelect = 1,
			bleprintList = 2,
			outputFolderSelect = 3,
			uvMapsSettings = 4,
			textureSettings = 5,
			materialSettings = 6,
			systemSettings = 7,
			exportType = 8,
			exportStatus = 9
		};
		int currentFrame;

		sm2obj::defaults userDefaults;
		volatile bool exportThreadStop;
		ffw::thread exportThread;
		ffw::mutex exportThreadMutex;
		void* exportThreadFunc(void* Data);
		//void* exportTexturesFunc(void* Data);
    };
};

#endif
