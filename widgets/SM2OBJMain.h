#ifndef WIDGETTESTMAIN_H
#define WIDGETTESTMAIN_H

//(*Headers(SM2OBJFrame)
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/radiobut.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/gauge.h>
//*)

class SM2OBJFrame: public wxFrame
{
    public:

        SM2OBJFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~SM2OBJFrame();

    //private:

        //(*Handlers(SM2OBJFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);

        void OnStartExportClick(wxSpinEvent& event);
        void OnGetDataFolderPathClick(wxSpinEvent& event);
        void OnGetInputFilePathClick(wxSpinEvent& event);
        void OnGetOutputFolderPathClick(wxSpinEvent& event);
        //*)

        //(*Identifiers(SM2OBJFrame)
        static const long ID_StaticText3;
        static const long ID_StaticText7;
        static const long ID_StaticText9;
        static const long ID_StaticText8;
        static const long ID_StaticText4;
        static const long ID_StaticText1;
        static const long ID_StaticText2;
        static const long ID_GetInputFilePath;
        static const long ID_GetDataFolderPath;
        static const long ID_GetOutputFolderPath;
        static const long ID_InputFilePath;
        static const long ID_InputDataPath;
        static const long ID_OutputFolderPath;
        static const long ID_OutputName;
        static const long ID_UseDiffuse;
        static const long ID_UseBump;
        static const long ID_UseAlpha;
        static const long ID_ExportMaterials;
        static const long ID_CHECKBOX1;
        static const long ID_Panel1;
        static const long ID_StaticText5;
        static const long ID_NumOfThreads;
        static const long ID_Panel3;
        static const long ID_ExportTextures;
        static const long ID_TextureTga;
        static const long ID_TextureBmp;
        static const long ID_TextureTiff;
        static const long ID_TexturePng;
        static const long ID_StaticText6;
        static const long ID_CHECKBOX2;
        static const long ID_Panel2;
        static const long ID_ProgressBar;
        static const long ID_StartExport;
        static const long ID_MENUITEM1;
        static const long idMenuAbout;
        //*)

        //(*Declarations(SM2OBJFrame)
        wxStaticText* StaticText9;
        wxTextCtrl* OutputName;
        wxButton* StartExport;
        wxCheckBox* UseDiffuse;
        wxStaticText* StaticText2;
        wxStaticText* StaticText6;
        wxCheckBox* UseAlpha;
        wxTextCtrl* InputFilePath;
        wxStaticText* StaticText8;
        wxCheckBox* ExportUVs;
        wxCheckBox* UseBump;
        wxPanel* Panel1;
        wxTextCtrl* OutputFolderPath;
        wxStaticText* StaticText1;
        wxRadioButton* TextureBmp;
        wxStaticText* StaticText3;
        wxSpinCtrl* NumOfThreads;
        wxPanel* Panel3;
        wxCheckBox* SpecularHighlight;
        wxRadioButton* TexturePng;
        wxCheckBox* ExportMaterials;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxButton* GetDataFolderPath;
        wxRadioButton* TextureTga;
        wxRadioButton* TextureTiff;
        wxTextCtrl* InputDataPath;
        wxPanel* Panel2;
        wxButton* GetInputFilePath;
        wxButton* GetOutputFolderPath;
        wxStaticText* StaticText4;
        wxGauge* ProgressBar;
        wxCheckBox* ExportTextures;

        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WIDGETTESTMAIN_H
