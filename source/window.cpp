/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "window.h"
#include "CommCtrl.h"
#include "widgets.h"
#include <iostream>
#include <ffw.h>
#include "exporter/textureExport.h"
#include "exporter/exportBlueprint.h"
#include <zlib.h>

static int id = 100;

static int getNewId(){
    id++;
    return id;
}

sm2obj::defaults userInput;
sm2obj::window* sm2obj::window::instance;
HWND* sm2obj::window::hwndPtr;
HWND sm2obj::window::hwnd;
ffw::thread sm2obj::window::exportThread;
ffw::mutex sm2obj::window::exportThreadMutex;
bool sm2obj::window::warningLog;

sm2obj::window::window(){
    instance = this;

    buttonSelectInputFolderID   = getNewId();
    buttonSelectInputDataID     = getNewId();
    buttonSelectOutputFolderID  = getNewId();
    buttonSelectTextureFolderID = getNewId();
    textInputInputFolderID      = getNewId();
    textInputInputDataID        = getNewId();
    textInputOutputFolderID     = getNewId();
    textInputTextureFolderID    = getNewId();
    comboUvMapSettingsID        = getNewId();
    checkboxExportMaterialsID   = getNewId();
    checkboxExportDiffuseID     = getNewId();
    checkboxExportAlphaID       = getNewId();
    checkboxExportNormalID      = getNewId();
    checkboxExportEmissiveID    = getNewId();
    comboTextureNormalsID       = getNewId();
    textInputNumOfThreadsID     = getNewId();
    comboTextureFormatID        = getNewId();
    comboTextureTypeID          = getNewId();
    buttonExportTexturesID      = getNewId();
    comboTextureSizeID          = getNewId();
    progressbarID               = getNewId();
    labelProgressTextID         = getNewId();
    buttonExportObjectID        = getNewId();
    checkboxSpecularHighlightID = getNewId();
    checkboxExportAttachmentsID = getNewId();
}

sm2obj::window::~window(){
}

int sm2obj::window::create(HINSTANCE hThisInstance, int nCmdShow){
    config::exportLogErrorFunc = &callbackExportLogError;
    config::exportLogDebugFunc = &callbackExportLogDebug;
    config::exportLogInfoFunc = &callbackExportLogInfo;
    config::exportLogWarningFunc = &callbackExportLogWarning;
    config::exportExitFunc = &callbackExportExit;
    config::exportProgressFunc = &callbackExportProgress;

    ZeroMemory(&wincl, sizeof(wincl));

    wincl.style = 0;
    wincl.lpszMenuName = NULL;
    wincl.lpszClassName = "WindowClass";
    wincl.lpfnWndProc = this->WndProc;
    wincl.hInstance = hThisInstance;
    wincl.hIconSm = LoadIcon(NULL, IDC_ICON);
    wincl.hIcon = LoadIcon(NULL, IDC_ICON);
    wincl.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wincl.cbWndExtra = 0;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.cbClsExtra = 0;

    if(!RegisterClassEx(&wincl)){
        MessageBox(NULL, "Could not register window!", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "Window", WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION , CW_USEDEFAULT, CW_USEDEFAULT, 500, 660, NULL, NULL, hThisInstance, NULL);

    if (hwnd == NULL){
        MessageBox(NULL, "Could not create window!", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, 0, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;

}

void sm2obj::window::destroy(){
    userInput.inputBlueprintFolder = getTextInputValue(textInputInputFolder);
    userInput.inputDataFolder = getTextInputValue(textInputInputData);
    userInput.outputFileFolder = getTextInputValue(textInputOutputFolder);
    userInput.outputTextureFolder = getTextInputValue(textInputTextureFolder);
    userInput.uvMapsOptions = getComboValue(comboUvMapSettings);
    userInput.exportMaterials = getCheckboxValue(checkboxExportMaterials);
    userInput.useDiffuseTextures = getCheckboxValue(checkboxExportDiffuse);
    userInput.useAlphaTextures = getCheckboxValue(checkboxExportAlpha);
    userInput.useNormalTextures = getCheckboxValue(checkboxExportNormal);
    userInput.useEmissiveTextures = getCheckboxValue(checkboxExportEmissive);
    userInput.specularHighlight = getCheckboxValue(checkboxSpecularHighlight);
    userInput.numOfThreads = getTextInputValue(textInputNumOfThreads);
    userInput.textureOutputFormat = getComboValue(comboTextureFormat);
    userInput.textureNormals = getComboValue(comboTextureNormals);
    userInput.textureExportType = getComboValue(comboTextureType);
    userInput.textureTileSize = getComboValue(comboTextureSize);
    userInput.exportAttachments = getCheckboxValue(checkboxExportAttachments);
    userInput.save(ffw::getExecutablePath() + "\\user-input.json");
}

void sm2obj::window::callbackExportExit(bool Success){
    if(Success){
        if(warningLog){
            showModalWarning(hwnd, "Warning!", "Blueprint exported! Process ended with warning(s)! Look for warning messages in log.txt for more information.");
        } else {
            showModalInfo(hwnd, "Success!", "Blueprint exported! Process ended with no errors.");
        }
    }
}

void sm2obj::window::callbackExportProgress(int Progress, int Total){
    int p = (Progress / float(Total)) * 100;
    setProgressbarValue(instance->progressbar, p);
}

void sm2obj::window::callbackExportLogDebug(const std::string& Message){
    ffw::logger().debug() << Message;
}

void sm2obj::window::callbackExportLogError(const std::string& Message){
    ffw::logger().error() << Message;
    showModalError(hwnd, "Error!", Message);

}

void sm2obj::window::callbackExportLogWarning(const std::string& Message){
    ffw::logger().warning() << Message;
    warningLog = true;
}

void sm2obj::window::callbackExportLogInfo(const std::string& Message){
    ffw::logger().print() << Message;
    setLabelValue(instance->labelProgressText, Message);
}

void* sm2obj::window::exportObjectFunc(void* Data){
    warningLog = false;
    callbackExportLogDebug("exportObjectFunc start");
    exportThreadMutex.lock();

    do{
        int textureFormat = getComboValue(instance->comboTextureFormat);
        if(textureFormat == 0){
            config::imageExtension = "png";
        } else if(textureFormat == 1){
            config::imageExtension = "bmp";
        } else if(textureFormat == 2){
            config::imageExtension = "tga";
        } else if(textureFormat == 3){
            config::imageExtension = "tiff";
        } else {
            callbackExportLogError("Please, select texture format!");
            break;
        }

        std::string blueprintFolder = getTextInputValue(instance->textInputInputFolder);
        if(blueprintFolder.size() == 0){
            callbackExportLogError("Please, select blueprint folder!");
            break;
        }

        std::string inputDataFolder = getTextInputValue(instance->textInputInputData);
        if(inputDataFolder.size() == 0){
            callbackExportLogError("Please, select StarMade data folder!");
            break;
        }
        inputDataFolder += "\\config";

        std::string outputFolder = getTextInputValue(instance->textInputOutputFolder);
        if(outputFolder.size() == 0){
            callbackExportLogError("Please, select output folder!");
            break;
        }

        if(blueprintFolder[blueprintFolder.size()] == '\\')blueprintFolder.pop_back();

        std::string outputName;
        size_t pos = blueprintFolder.find_last_of('\\');
        if(pos != std::string::npos && pos != blueprintFolder.size()-1){
            outputName = blueprintFolder.substr(pos+1, blueprintFolder.size()-pos-1);
            callbackExportLogDebug("Output name: " + outputName);
        } else {
            callbackExportLogError("Could not detect blueprint folder name! Make sure the path is correct!");
            break;
        }

        int numOfThreads;
        try {
            numOfThreads = ffw::stringToVal<int>(getTextInputValue(instance->textInputNumOfThreads));
        } catch (std::exception& e){
            callbackExportLogError("Wrong number of threads! Please, write a number");
            break;
        }

        if(numOfThreads <= 0 || numOfThreads > 16){
            callbackExportLogError("Wrong number of threads! Use values between 1 and 16");
            break;
        }

        bool exportMaterials = getCheckboxValue(instance->checkboxExportMaterials);
        bool exportDiffuse = getCheckboxValue(instance->checkboxExportDiffuse);
        bool exportAlpha = getCheckboxValue(instance->checkboxExportAlpha);
        bool exportNormal = getCheckboxValue(instance->checkboxExportNormal);
        bool exportEmissive = getCheckboxValue(instance->checkboxExportEmissive);
        bool specularHighloght = getCheckboxValue(instance->checkboxSpecularHighlight);
        bool attachments = getCheckboxValue(instance->checkboxExportAttachments);
        bool exportUvs;
        bool useAtlas;
        int uvOption = getComboValue(instance->comboUvMapSettings);

        if(uvOption == 0){
            useAtlas = false;
            exportUvs = false;
        } else if(uvOption == 1){
            exportUvs = true;
            useAtlas = false;
        } else if(uvOption == 2){
            exportUvs = true;
            useAtlas = true;
        } else {
            callbackExportLogError("Please, select what to do with UV maps!");
            break;
        }

        callbackExportLogDebug("Input config folder: " + inputDataFolder);
        callbackExportLogDebug("Input blueprint folder: " + blueprintFolder);
        callbackExportLogDebug("Output folder: " + outputFolder);
        callbackExportLogDebug("Output file name: " + outputName);
        callbackExportLogDebug("Export UVs: " + ffw::valToString(exportUvs));
        callbackExportLogDebug("Use atlas: " + ffw::valToString(useAtlas));
        callbackExportLogDebug("Use diffuse textures: " + ffw::valToString(exportDiffuse));
        callbackExportLogDebug("Use alpha textures: " + ffw::valToString(exportAlpha));
        callbackExportLogDebug("Use normal textures: " + ffw::valToString(exportNormal));
        callbackExportLogDebug("Use emissive textures: " + ffw::valToString(exportEmissive));
        callbackExportLogDebug("Use specular highlight: " + ffw::valToString(specularHighloght));
        callbackExportLogDebug("number of threads: " + ffw::valToString(numOfThreads));
        callbackExportLogDebug("Export attachments: " + ffw::valToString(attachments));

        exportBlueprint(inputDataFolder, blueprintFolder, outputFolder, outputName,
                        exportUvs, useAtlas, exportMaterials,
                        exportDiffuse, exportAlpha, exportNormal, exportEmissive,
                        specularHighloght, numOfThreads, attachments);

        // Remove temp folder
        system(std::string("rmdir /Q /S " + ffw::getExecutablePath() + "\\temp").c_str());

        setProgressbarValue(instance->progressbar, 0);
        setLabelValue(instance->labelProgressText, "Idle");
    }while(0);

    exportThreadMutex.unlock();
    callbackExportLogDebug("exportObjectFunc end");
    return NULL;
}

void* sm2obj::window::exportTextuesFunc(void* Data){
    warningLog = false;
    callbackExportLogDebug("exportTextuesFunc started");
    exportThreadMutex.lock();

    do{
        int textureFormat = getComboValue(instance->comboTextureFormat);
        if(textureFormat == 0){
            config::imageSaverFunc = &ffw::savePNG;
            config::imageExtension = "png";
        } else if(textureFormat == 1){
            config::imageSaverFunc = &ffw::saveBMP;
            config::imageExtension = "bmp";
        } else if(textureFormat == 2){
            config::imageSaverFunc = &ffw::saveTGA;
            config::imageExtension = "tga";
        } else if(textureFormat == 3){
            config::imageSaverFunc = &ffw::saveTIFF;
            config::imageExtension = "tiff";
        } else {
            callbackExportLogError("Please, select texture format!");
            break;
        }

        std::string inputFolder = getTextInputValue(instance->textInputInputData);
        if(inputFolder.size() == 0){
            callbackExportLogError("Please, select StarMade data folder!");
            break;
        }

        std::string inputDataFolder = getTextInputValue(instance->textInputInputData);
        if(inputDataFolder.size() == 0){
            callbackExportLogError("Please, select StarMade data folder!");
            break;
        }

        std::string outputFolder = getTextInputValue(instance->textInputTextureFolder);
        if(outputFolder.size() == 0){
            callbackExportLogError("Please, select texture output folder!");
            break;
        }

        int texture = getComboValue(instance->comboTextureSize);
        int textureSize;
        if(texture == 0){
            inputFolder += "\\textures\\block\\Default\\64";
            textureSize = 64;
        } else if(texture == 1){
            inputFolder += "\\textures\\block\\Default\\128";
            textureSize = 128;
        } else if(texture == 2){
            inputFolder += "\\textures\\block\\Default\\256";
            textureSize = 256;
        } else {
            callbackExportLogError("Please, select texture size!");
            break;
        }

        bool normals;
        int convertNormals = getComboValue(instance->comboTextureNormals);
        if(convertNormals == 0){
            normals = false;
        } else if(convertNormals == 1){
            normals = true;
        } else {
            callbackExportLogError("Please, select what to do with normals!");
            break;
        }

        int textureType = getComboValue(instance->comboTextureType);
        if(textureType == 0){
            //callbackExportLogDebug("Selected \"Split tiles\" option");
        } else if(textureType == 1){
            //callbackExportLogDebug("Selected \"Use atlas\" option");
        } else {
            callbackExportLogError("Please, select export type of textures! (Separate tiles or use whole atlas)");
            break;
        }

        callbackExportLogDebug("StarMade texture folder: " + inputFolder);
        callbackExportLogDebug("Texture output folder: " + outputFolder);
        callbackExportLogDebug("Convert normals: " + ffw::valToString(normals));
        callbackExportLogDebug("Use atlas instead of splitting tiles: " + ffw::valToString(textureType));

        if(textureType == 0){
            exportTextures(inputFolder, outputFolder, normals);
        } else {
            exportAtlases(inputFolder, outputFolder, normals);
            exportEmissiveAtlas(inputDataFolder + "\\config", outputFolder, textureSize);
        }

        setProgressbarValue(instance->progressbar, 0);
        setLabelValue(instance->labelProgressText, "Idle");
    } while(0);

    exportThreadMutex.unlock();
    callbackExportLogDebug("exportTextuesFunc ended");
    return NULL;
}

void sm2obj::window::widgetCallback(HWND hwnd, WPARAM wParam){
    if(wParam == buttonSelectInputFolderID){
        std::string currentPath = getTextInputValue(textInputInputFolder);
        std::wstring folder = ffw::openFolderDialog(L"Select blueprint folder", ffw::ansiToWstr(currentPath));
        if(folder.size() != 0){
            setTextInputValue(textInputInputFolder, ffw::wstrToAnsi(folder));
        }
    }

    if(wParam == buttonSelectInputDataID){
        std::string currentPath = getTextInputValue(textInputInputData);
        std::wstring folder = ffw::openFolderDialog(L"Select StarMade data folder", ffw::ansiToWstr(currentPath));
        if(folder.size() != 0){
            setTextInputValue(textInputInputData, ffw::wstrToAnsi(folder));
        }
    }

    if(wParam == buttonSelectOutputFolderID){
        std::string currentPath = getTextInputValue(textInputOutputFolder);
        std::wstring folder = ffw::openFolderDialog(L"Select output folder for OBJ and MTL file", ffw::ansiToWstr(currentPath));
        if(folder.size() != 0){
            setTextInputValue(textInputOutputFolder, ffw::wstrToAnsi(folder));
        }
    }

    if(wParam == buttonSelectTextureFolderID){
        std::string currentPath = getTextInputValue(textInputTextureFolder);
        std::wstring folder = ffw::openFolderDialog(L"Select output folder for textures", ffw::ansiToWstr(currentPath));
        if(folder.size() != 0){
            setTextInputValue(textInputTextureFolder, ffw::wstrToAnsi(folder));
        }
    }

    if(wParam == buttonExportObjectID){
        if(exportThreadMutex.tryLock()){
            exportThreadMutex.unlock();
            exportThread.bindFunction(&sm2obj::window::exportObjectFunc);
            exportThread.start(NULL);

        } else {
            showModalError(hwnd, "Error!", "Process has already begun");
        }
    }

    if(wParam == buttonExportTexturesID){
        if(exportThreadMutex.tryLock()){
            exportThreadMutex.unlock();
            exportThread.bindFunction(&sm2obj::window::exportTextuesFunc);
            exportThread.start(NULL);
        } else {
            showModalError(hwnd, "Error!", "Process has already begun");
        }
    }
}

void sm2obj::window::createWidgets(HWND hwnd){
    HFONT hFont = createFont("Segoe UI", 19, 550);

    int posY = 5;
    int posYoff = 5;
    HWND label0 = createLabel(hwnd, "Select blueprint folder:", 5, posY, 480, 20, 0);
    posY += 20;
    textInputInputFolder = createTextInput(hwnd, "", 5, posY, 430, 25, textInputInputFolderID);
    buttonSelectInputFolder = createButton(hwnd, "...", 440, posY, 45, 25, buttonSelectInputFolderID);
    posY += 30;

    HWND label1 = createLabel(hwnd, "Select StarMade data folder:", 5, posY, 480, 20, 0);
    posY += 20;
    textInputInputData = createTextInput(hwnd, "", 5, posY, 430, 25, textInputInputDataID);
    buttonSelectInputData = createButton(hwnd, "...", 440, posY, 45, 25, buttonSelectInputDataID);
    posY += 30;

    HWND label2 = createLabel(hwnd, "Select output folder for OBJ and MTL files:", 5, posY, 480, 20, 0);
    posY += 20;
    textInputOutputFolder = createTextInput(hwnd, "", 5, posY, 430, 25, textInputOutputFolderID);
    buttonSelectOutputFolder = createButton(hwnd, "...", 440, posY, 45, 25, buttonSelectOutputFolderID);
    posY += 30;

    HWND group0 = createGroup(hwnd, "UV maps options:", 5, posY, 480, 55, 0);
    posY += 20;
    comboUvMapSettings = createCombo(hwnd, "", 10, posY, 470, 25, comboUvMapSettingsID);
    addComboValue(comboUvMapSettings, "Do not export UV maps");
    addComboValue(comboUvMapSettings, "Export UV maps and split tiles (separate material per tile)");
    addComboValue(comboUvMapSettings, "Export UV maps and use atlas (single material per atlas)");

    posY += 40;
    posYoff = posY;
    HWND group1 = createGroup(hwnd, "Material options:", 5, posY, 235, 125, 0);
    posY += 20;
    checkboxExportMaterials = createCheckbox(hwnd, "Export materials", 10, posY, 110, 20, checkboxExportMaterialsID);
    posY += 30;
    checkboxExportDiffuse = createCheckbox(hwnd, "Diffuse", 10, posY, 110, 20, checkboxExportDiffuseID);
    checkboxExportAlpha = createCheckbox(hwnd, "Alpha", 10, posY +20, 110, 20, checkboxExportAlphaID);
    checkboxExportNormal = createCheckbox(hwnd, "Normal / bump", 10 + 110, posY, 110, 20, checkboxExportNormalID);
    checkboxExportEmissive = createCheckbox(hwnd, "Emissive", 10 + 110, posY +20, 110, 20, checkboxExportEmissiveID);
    posY += 50;
    checkboxSpecularHighlight = createCheckbox(hwnd, "Specular highlight", 10, posY, 200, 20, checkboxSpecularHighlightID);

    posY = posYoff;
    HWND group2 = createGroup(hwnd, "System options:", 250, posY, 235, 55, 0);
    posY += 20;
    HWND label3 = createLabel(hwnd, "Number of threads (max 16):", 255, posY, 190, 20, 0);
    textInputNumOfThreads = createTextInput(hwnd, "", 255+195, posY, 30, 25, textInputNumOfThreadsID);

    posY += 50;
    HWND group3 = createGroup(hwnd, "Attachments options:", 250, posY, 235, 55, 0);
    posY += 20;
    checkboxExportAttachments = createCheckbox(hwnd, "Export attached turrets/ships", 255, posY, 225, 25, checkboxExportAttachmentsID);

    posY += 40;
    buttonExportObject = createButton(hwnd, "Export object", 170, posY, 140, 35, buttonExportObjectID);

    posY += 40;
    HWND group4 = createGroup(hwnd, "Texture export options:", 5, posY, 480, 170, 0);
    posY += 20;
    HWND label4 = createLabel(hwnd, "Select output folder for textures:", 10, posY, 470, 20, 0);
    posY += 20;
    textInputTextureFolder = createTextInput(hwnd, "", 10, posY, 420, 25, textInputTextureFolderID);
    buttonSelectTextureFolder = createButton(hwnd, "...", 435, posY, 45, 25, buttonSelectTextureFolderID);
    posY += 30;
    posYoff = posY;
    HWND label5 = createLabel(hwnd, "Output format:", 10, posY, 100, 20, 0);
    comboTextureFormat = createCombo(hwnd, "", 110, posY, 125, 25, comboTextureFormatID);
    addComboValue(comboTextureFormat, "*.PNG");
    addComboValue(comboTextureFormat, "*.BMP");
    addComboValue(comboTextureFormat, "*.TGA");
    addComboValue(comboTextureFormat, "*.TIFF");
    posY += 30;
    HWND label6 = createLabel(hwnd, "Export as:", 10, posY, 100, 20, 0);
    comboTextureType = createCombo(hwnd, "", 110, posY, 125, 25, comboTextureTypeID);
    addComboValue(comboTextureType, "Separate tiles");
    addComboValue(comboTextureType, "Whole atlas");

    posY = posYoff;
    HWND label7 = createLabel(hwnd, "Tile size:", 245, posY, 100, 20, 0);
    comboTextureSize = createCombo(hwnd, "", 350, posY, 130, 25, comboTextureSizeID);
    addComboValue(comboTextureSize, "64px");
    addComboValue(comboTextureSize, "128px");
    addComboValue(comboTextureSize, "256px");
    posY += 30;
    HWND label8 = createLabel(hwnd, "Normals:", 245, posY, 100, 20, 0);
    comboTextureNormals = createCombo(hwnd, "", 350, posY, 130, 25, comboTextureNormalsID);
    addComboValue(comboTextureNormals, "Use original");
    addComboValue(comboTextureNormals, "Convert to bump");
    posY += 30;
    buttonExportTextures = createButton(hwnd, "Export textures", 170, posY, 140, 35, buttonExportTexturesID);

    posY += 55;
    progressbar = createProgressbar(hwnd, "", 5, posY, 480, 25, progressbarID);
    posY += 30;
    HWND label9 = createLabel(hwnd, "Status:", 5, posY, 45, 20, 0);
    labelProgressText = createLabel(hwnd, "Idle", 55, posY, 380, 20, labelProgressTextID);

    setWidgetFont(label0, hFont);
    setWidgetFont(label1, hFont);
    setWidgetFont(label2, hFont);
    setWidgetFont(label3, hFont);
    setWidgetFont(label4, hFont);
    setWidgetFont(label5, hFont);
    setWidgetFont(label6, hFont);
    setWidgetFont(label7, hFont);
    setWidgetFont(label8, hFont);
    setWidgetFont(label9, hFont);
    setWidgetFont(labelProgressText, hFont);
    setWidgetFont(textInputInputFolder, hFont);
    setWidgetFont(textInputInputData, hFont);
    setWidgetFont(textInputOutputFolder, hFont);
    setWidgetFont(textInputTextureFolder, hFont);
    setWidgetFont(buttonSelectInputFolder, hFont);
    setWidgetFont(buttonSelectInputData, hFont);
    setWidgetFont(buttonSelectOutputFolder, hFont);
    setWidgetFont(buttonSelectTextureFolder, hFont);
    setWidgetFont(comboUvMapSettings, hFont);
    setWidgetFont(checkboxExportMaterials, hFont);
    setWidgetFont(checkboxExportDiffuse, hFont);
    setWidgetFont(checkboxExportAlpha, hFont);
    setWidgetFont(checkboxExportNormal, hFont);
    setWidgetFont(checkboxExportEmissive, hFont);
    setWidgetFont(checkboxSpecularHighlight, hFont);
    setWidgetFont(checkboxExportAttachments, hFont);
    setWidgetFont(comboTextureFormat, hFont);
    setWidgetFont(comboTextureType, hFont);
    setWidgetFont(comboTextureSize, hFont);
    setWidgetFont(comboTextureNormals, hFont);
    setWidgetFont(buttonExportTextures, hFont);
    setWidgetFont(buttonExportObject, hFont);
    setWidgetFont(textInputNumOfThreads, hFont);
    setWidgetFont(group0, hFont);
    setWidgetFont(group1, hFont);
    setWidgetFont(group2, hFont);
    setWidgetFont(group3, hFont);
    setWidgetFont(group4, hFont);

    if(userInput.load(ffw::getExecutablePath() + "\\user-input.json")){
        setTextInputValue   (textInputInputFolder,      userInput.inputBlueprintFolder);
        setTextInputValue   (textInputInputData,        userInput.inputDataFolder);
        setTextInputValue   (textInputOutputFolder,     userInput.outputFileFolder);
        setTextInputValue   (textInputTextureFolder,    userInput.outputTextureFolder);
        setComboValue       (comboUvMapSettings,        userInput.uvMapsOptions);
        setCheckboxValue    (checkboxExportMaterials,   userInput.exportMaterials);
        setCheckboxValue    (checkboxExportDiffuse,     userInput.useDiffuseTextures);
        setCheckboxValue    (checkboxExportAlpha,       userInput.useAlphaTextures);
        setCheckboxValue    (checkboxExportNormal,      userInput.useNormalTextures);
        setCheckboxValue    (checkboxExportEmissive,    userInput.useEmissiveTextures);
        setCheckboxValue    (checkboxSpecularHighlight, userInput.specularHighlight);
        setTextInputValue   (textInputNumOfThreads,     userInput.numOfThreads);
        setComboValue       (comboTextureFormat,        userInput.textureOutputFormat);
        setComboValue       (comboTextureNormals,       userInput.textureNormals);
        setComboValue       (comboTextureType,          userInput.textureExportType);
        setComboValue       (comboTextureSize,          userInput.textureTileSize);
        setCheckboxValue    (checkboxExportAttachments, userInput.exportAttachments);
    }
}

LRESULT CALLBACK sm2obj::window::WndProc(HWND hwnd, UINT Msg, WPARAM wParam , LPARAM lParam){
    switch (Msg){

        case WM_CREATE:{
            instance->createWidgets(hwnd);
            break;
        }
        case WM_CTLCOLORSTATIC:{
            if(GetDlgItem(hwnd, 3) == (HWND)lParam){
                SetBkMode( (HDC)wParam, TRANSPARENT);
                SetTextColor((HDC)wParam, RGB(255,0,0));
                return (BOOL) GetStockObject(HOLLOW_BRUSH);
            }
        }
        case WM_COMMAND:{
            instance->widgetCallback(hwnd, wParam);
            break;
        }
        case WM_CLOSE:{
            instance->destroy();
            DestroyWindow(hwnd);
            break;
        }
        case WM_DESTROY:{
            PostQuitMessage(0);
            break;
        }
        default:{
            return DefWindowProc(hwnd, Msg, wParam, lParam);
        }
    }
    return 0;
}
