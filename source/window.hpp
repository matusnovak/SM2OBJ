/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_WINDOW
#define SM2OBJ_WINDOW

#include <ffw.h>
#include "defaults.h"
#include "exporter/exportBlueprint.h"
#include "exporter/textureExport.h"

namespace sm2obj {
    class window: public ffw::uiWindow {
	public:
		window();
		~window();
	private:
		void setup() override;
		void windowCloseEvent() override;
		void widgetEvent(const ffw::uiWidget* Widget) override;
		void windowPosEvent(short PosX, short PosY) override;
		void windowSizeEvent(short Width, short Height) override;

		static void callbackLogError(const std::string& Message);
		static void callbackLogInfo(const std::string& Message);
		static void callbackLogDebug(const std::string& Message);
		static void callbackLogWarning(const std::string& Message);
		static void callbackProgress(int Progress, int Total);
		static void callbackExit(bool Success);

		ffw::uiFont font;
	public:
		ffw::uiButton* buttonSelectInputFolder;
		ffw::uiTextInput* textInputFolder;
		ffw::uiButton* buttonSelectInputData;
		ffw::uiTextInput* textInputData;
		ffw::uiButton* buttonSelectOutputFolder;
		ffw::uiTextInput* textOutputFolder;
		ffw::uiCombo* comboUvMapSettings;
		ffw::uiCheckbox* checkboxExportMaterials;
		ffw::uiCheckbox* checkboxExportDiffuse;
		ffw::uiCheckbox* checkboxExportAlpha;
		ffw::uiCheckbox* checkboxExportNormal;
		ffw::uiCheckbox* checkboxExportEmissive;
		ffw::uiCheckbox* checkboxExportSpecular;
		ffw::uiTextInput* textNumOfThreads;
		ffw::uiCheckbox* checkboxAttachments;
		ffw::uiButton* buttonExportObject;
		ffw::uiButton* buttonSelectTextureOutput;
		ffw::uiTextInput* textTextureOutput;
		ffw::uiCombo* comboTextureFormat;
		ffw::uiCombo* comboTextureType;
		ffw::uiCombo* comboTextureSize;
		ffw::uiCombo* comboTextureNormals;
		ffw::uiButton* buttonExportTextures;
		ffw::uiProgressbar* progressbar;
		ffw::uiLabel* progress;
		bool logWarning;
	private:
		sm2obj::defaults userDefaults;
		ffw::thread exportThread;
		ffw::mutex exportThreadMutex;
		void* exportBlueprintFunc(void* Data);
		void* exportTexturesFunc(void* Data);
    };
};

#endif
