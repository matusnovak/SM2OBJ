/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_WINDOW
#define SM2OBJ_WINDOW

#include <tchar.h>
#include <windows.h>
#include "defaults.h"

namespace sm2obj {
    class window {
    public:
        window();
        ~window();

        int create(HINSTANCE hThisInstance, int nCmdShow);

    private:
        void destroy();
        void createWidgets(HWND hwnd);
        void widgetCallback(HWND hwnd, WPARAM wParam);
        static window* instance;
        static HWND* hwndPtr;
        static LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam , LPARAM lParam);

        static ffw::thread exportThread;
        static ffw::mutex exportThreadMutex;
        static void* exportObjectFunc(void* Data);
        static void* exportTextuesFunc(void* Data);

        static void callbackExportExit(bool Success);
        static void callbackExportProgress(int Progress, int Total);
        static void callbackExportLogDebug(const std::string& Message);
        static void callbackExportLogError(const std::string& Message);
        static void callbackExportLogWarning(const std::string& Message);
        static void callbackExportLogInfo(const std::string& Message);

        WNDCLASSEX wincl;
        MSG msg;
        static HWND hwnd;
        static bool warningLog;

        WPARAM buttonSelectInputFolderID;
        WPARAM buttonSelectInputDataID;
        WPARAM buttonSelectOutputFolderID;
        WPARAM buttonSelectTextureFolderID;
        WPARAM textInputInputFolderID;
        WPARAM textInputInputDataID;
        WPARAM textInputOutputFolderID;
        WPARAM textInputTextureFolderID;
        WPARAM comboUvMapSettingsID;
        WPARAM checkboxExportMaterialsID;
        WPARAM checkboxExportDiffuseID;
        WPARAM checkboxExportAlphaID;
        WPARAM checkboxExportNormalID;
        WPARAM checkboxExportEmissiveID;
        WPARAM checkboxSpecularHighlightID;
        WPARAM textInputNumOfThreadsID;
        WPARAM comboTextureFormatID;
        WPARAM comboTextureTypeID;
        WPARAM comboTextureSizeID;
        WPARAM comboTextureNormalsID;
        WPARAM buttonExportTexturesID;
        WPARAM progressbarID;
        WPARAM labelProgressTextID;
        WPARAM buttonExportObjectID;
        WPARAM checkboxExportAttachmentsID;

        HWND buttonSelectInputFolder;
        HWND buttonSelectInputData;
        HWND buttonSelectOutputFolder;
        HWND buttonSelectTextureFolder;
        HWND textInputInputFolder;
        HWND textInputInputData;
        HWND textInputOutputFolder;
        HWND textInputTextureFolder;
        HWND comboUvMapSettings;
        HWND checkboxExportMaterials;
        HWND checkboxExportDiffuse;
        HWND checkboxExportAlpha;
        HWND checkboxExportNormal;
        HWND checkboxExportEmissive;
        HWND textInputNumOfThreads;
        HWND comboTextureFormat;
        HWND comboTextureType;
        HWND comboTextureSize;
        HWND comboTextureNormals;
        HWND buttonExportTextures;
        HWND progressbar;
        HWND labelProgressText;
        HWND buttonExportObject;
        HWND checkboxSpecularHighlight;
        HWND checkboxExportAttachments;
    };
};

#endif
