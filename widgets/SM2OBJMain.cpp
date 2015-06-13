#include "SM2OBJMain.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/dirdlg.h>

//(*InternalHeaders(SM2OBJFrame)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#undef M_PI
#include "../source/config.h"

void* runExporter(void* DATA);
static ffw::thread mainThread;
static SM2OBJFrame *FramePtr = NULL;
static void exportProgressCallback(int Value, int Range);
static void exportExitCallback(bool Success);

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(SM2OBJFrame)
const long SM2OBJFrame::ID_StaticText3 = wxNewId();
const long SM2OBJFrame::ID_StaticText7 = wxNewId();
const long SM2OBJFrame::ID_StaticText9 = wxNewId();
const long SM2OBJFrame::ID_StaticText8 = wxNewId();
const long SM2OBJFrame::ID_StaticText4 = wxNewId();
const long SM2OBJFrame::ID_StaticText1 = wxNewId();
const long SM2OBJFrame::ID_StaticText2 = wxNewId();
const long SM2OBJFrame::ID_StaticBox1 = wxNewId();
const long SM2OBJFrame::ID_StaticBox2 = wxNewId();
const long SM2OBJFrame::ID_StaticBox3 = wxNewId();
const long SM2OBJFrame::ID_StaticBox4 = wxNewId();
const long SM2OBJFrame::ID_StaticBox5 = wxNewId();
const long SM2OBJFrame::ID_SplitTiles = wxNewId();
const long SM2OBJFrame::ID_GetInputFilePath = wxNewId();
const long SM2OBJFrame::ID_GetDataFolderPath = wxNewId();
const long SM2OBJFrame::ID_GetOutputFolderPath = wxNewId();
const long SM2OBJFrame::ID_InputFilePath = wxNewId();
const long SM2OBJFrame::ID_InputDataPath = wxNewId();
const long SM2OBJFrame::ID_OutputFolderPath = wxNewId();
const long SM2OBJFrame::ID_OutputName = wxNewId();
const long SM2OBJFrame::ID_UseDiffuse = wxNewId();
const long SM2OBJFrame::ID_UseBump = wxNewId();
const long SM2OBJFrame::ID_UseAlpha = wxNewId();
const long SM2OBJFrame::ID_ExportMaterials = wxNewId();
const long SM2OBJFrame::ID_SpecularHighlight = wxNewId();
const long SM2OBJFrame::ID_StaticText5 = wxNewId();
const long SM2OBJFrame::ID_NumOfThreads = wxNewId();
const long SM2OBJFrame::ID_ExportTextures = wxNewId();
const long SM2OBJFrame::ID_TextureTga = wxNewId();
const long SM2OBJFrame::ID_TextureBmp = wxNewId();
const long SM2OBJFrame::ID_TextureTiff = wxNewId();
const long SM2OBJFrame::ID_TexturePng = wxNewId();
const long SM2OBJFrame::ID_StaticText6 = wxNewId();
const long SM2OBJFrame::ID_ExportUVs = wxNewId();
const long SM2OBJFrame::ID_ProgressBar = wxNewId();
const long SM2OBJFrame::ID_StartExport = wxNewId();
const long SM2OBJFrame::ID_MENUITEM1 = wxNewId();
const long SM2OBJFrame::idMenuAbout = wxNewId();
//*)

BEGIN_EVENT_TABLE(SM2OBJFrame,wxFrame)
    //(*EventTable(SM2OBJFrame)
    //*)
END_EVENT_TABLE()

SM2OBJFrame::SM2OBJFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(SM2OBJFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("SM2OBJ"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(535,455));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    wxFont thisFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    

    StaticText7 = new wxStaticText(this, ID_StaticText7, _("Select blueprint file"), wxPoint(8,8), wxDefaultSize, 0, _T("ID_StaticText7"));
    StaticText9 = new wxStaticText(this, ID_StaticText9, _("Select output folder"), wxPoint(8,120), wxDefaultSize, 0, _T("ID_StaticText9"));
    StaticText8 = new wxStaticText(this, ID_StaticText8, _("Select StarMade\\data folder (this folder must contains \'config\' and \'textures\' sub-folders)"), wxPoint(8,64), wxDefaultSize, 0, _T("ID_StaticText8"));
    StaticText4 = new wxStaticText(this, ID_StaticText4, _("Name of the exported OBJ:"), wxPoint(8,176), wxDefaultSize, 0, _T("ID_StaticText4"));

    StaticBox2 = new wxStaticBox(this, ID_StaticBox2, _("Materials options"), wxPoint(8,232), wxSize(168,152), 0, _T("ID_StaticBox2"));
    StaticBox5 = new wxStaticBox(this, ID_StaticBox2, _("Texture options"), wxPoint(360,232), wxSize(168,72), 0, _T("ID_StaticBox2"));
    StaticBox3 = new wxStaticBox(this, ID_StaticBox2, _("UV options"), wxPoint(184,312), wxSize(168,72), 0, _T("ID_StaticBox2"));
    StaticBox4 = new wxStaticBox(this, ID_StaticBox2, _("Texture format"), wxPoint(360,312), wxSize(168,72), 0, _T("ID_StaticBox2"));
    StaticBox1 = new wxStaticBox(this, ID_StaticBox2, _("System options"), wxPoint(184,232), wxSize(168,72), 0, _T("ID_StaticBox2"));

    GetInputFilePath = new wxButton(this, ID_GetInputFilePath, _("..."), wxPoint(496,32), wxSize(32,26), 0, wxDefaultValidator, _T("ID_GetInputFilePath"));
    GetDataFolderPath = new wxButton(this, ID_GetDataFolderPath, _("..."), wxPoint(496,88), wxSize(32,26), 0, wxDefaultValidator, _T("ID_GetDataFolderPath"));
    GetOutputFolderPath = new wxButton(this, ID_GetOutputFolderPath, _("..."), wxPoint(496,144), wxSize(32,26), 0, wxDefaultValidator, _T("ID_GetOutputFolderPath"));
    InputFilePath = new wxTextCtrl(this, ID_InputFilePath, wxEmptyString, wxPoint(8,32), wxSize(480,24), 0, wxDefaultValidator, _T("ID_InputFilePath"));
    InputDataPath = new wxTextCtrl(this, ID_InputDataPath, wxEmptyString, wxPoint(8,88), wxSize(480,24), 0, wxDefaultValidator, _T("ID_InputDataPath"));
    OutputFolderPath = new wxTextCtrl(this, ID_OutputFolderPath, wxEmptyString, wxPoint(8,144), wxSize(480,24), 0, wxDefaultValidator, _T("ID_OutputFolderPath"));
    OutputName = new wxTextCtrl(this, ID_OutputName, _("Blueprint"), wxPoint(8,200), wxSize(520,24), 0, wxDefaultValidator, _T("ID_OutputName"));

    StartExport = new wxButton(this, ID_StartExport, _("Start Exporting"), wxPoint(8,392), wxDefaultSize, 0, wxDefaultValidator, _T("ID_StartExport"));
    ProgressBar = new wxGauge(this, ID_ProgressBar, 100, wxPoint(120,392), wxSize(408,28), 0, wxDefaultValidator, _T("ID_ProgressBar"));
    ExportMaterials = new wxCheckBox(this, ID_ExportMaterials, _("Export materials"), wxPoint(16,256), wxDefaultSize, 0, wxDefaultValidator, _T("ID_ExportMaterials"));
    ExportMaterials->SetValue(true);
    UseDiffuse = new wxCheckBox(this, ID_UseDiffuse, _("Use diffuse texture"), wxPoint(16,280), wxDefaultSize, 0, wxDefaultValidator, _T("ID_UseDiffuse"));
    UseDiffuse->SetValue(true);
    UseBump = new wxCheckBox(this, ID_UseBump, _("Use bump texture"), wxPoint(16,304), wxDefaultSize, 0, wxDefaultValidator, _T("ID_UseBump"));
    UseBump->SetValue(true);
    UseAlpha = new wxCheckBox(this, ID_UseAlpha, _("Use alpha texture"), wxPoint(16,328), wxDefaultSize, 0, wxDefaultValidator, _T("ID_UseAlpha"));
    UseAlpha->SetValue(true);
    SpecularHighlight = new wxCheckBox(this, ID_SpecularHighlight, _("Specular highlight"), wxPoint(16,352), wxDefaultSize, 0, wxDefaultValidator, _T("ID_SpecularHighlight"));
    SpecularHighlight->SetValue(true);
    ExportTextures = new wxCheckBox(this, ID_ExportTextures, _("Export textures"), wxPoint(368,256), wxDefaultSize, 0, wxDefaultValidator, _T("ID_ExportTextures"));
    ExportTextures->SetValue(false);
    SplitTiles = new wxCheckBox(this, ID_SplitTiles, _("Split tiles"), wxPoint(192,360), wxDefaultSize, 0, wxDefaultValidator, _T("ID_SplitTiles"));
    SplitTiles->SetValue(true);
    StaticText5 = new wxStaticText(this, ID_StaticText5, _("Thread count:"), wxPoint(192,256), wxDefaultSize, 0, _T("ID_StaticText5"));
    NumOfThreads = new wxSpinCtrl(this, ID_NumOfThreads, _T("1"), wxPoint(280,256), wxSize(64,21), 0, 1, 16, 1, _T("ID_NumOfThreads"));
    NumOfThreads->SetValue(_T("1"));
    TextureTga = new wxRadioButton(this, ID_TextureTga, _("TGA"), wxPoint(368,336), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TextureTga"));
    TexturePng = new wxRadioButton(this, ID_TexturePng, _("PNG"), wxPoint(448,336), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TexturePng"));
    TexturePng->SetValue(true);
    TextureBmp = new wxRadioButton(this, ID_TextureBmp, _("BMP"), wxPoint(368,360), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TextureBmp"));
    TextureTiff = new wxRadioButton(this, ID_TextureTiff, _("TIFF"), wxPoint(448,360), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TextureTiff"));
    ExportUVs = new wxCheckBox(this, ID_ExportUVs, _("Export UVs"), wxPoint(192,336), wxDefaultSize, 0, wxDefaultValidator, _T("ID_ExportUVs"));
    ExportUVs->SetValue(true);

    /*UseDiffuse = new wxCheckBox(Panel1, ID_UseDiffuse, _("Use diffuse texture"), wxPoint(8,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_UseDiffuse"));
    UseDiffuse->SetValue(true);
    UseBump = new wxCheckBox(Panel1, ID_UseBump, _("Use bump texture"), wxPoint(8,56), wxDefaultSize, 0, wxDefaultValidator, _T("ID_UseBump"));
    UseBump->SetValue(true);
    UseAlpha = new wxCheckBox(Panel1, ID_UseAlpha, _("Use alpha texture"), wxPoint(8,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_UseAlpha"));
    UseAlpha->SetValue(true);
    ExportMaterials = new wxCheckBox(Panel1, ID_ExportMaterials, _("Export materials"), wxPoint(8,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_ExportMaterials"));
    ExportMaterials->SetValue(true);
    SpecularHighlight = new wxCheckBox(Panel1, ID_CHECKBOX1, _("Specular highlight"), wxPoint(8,104), wxDefaultSize, 0, wxDefaultValidator, _T("ID_SpecularHighlight"));
    SpecularHighlight->SetValue(true);
    StaticText5 = new wxStaticText(Panel3, ID_StaticText5, _("Thread count:"), wxPoint(8,8), wxDefaultSize, 0, _T("ID_StaticText5"));
    NumOfThreads = new wxSpinCtrl(Panel3, ID_NumOfThreads, _T("1"), wxPoint(96,8), wxSize(64,21), 0, 1, 16, 1, _T("ID_NumOfThreads"));
    NumOfThreads->SetValue(_T("1"));
    ExportTextures = new wxCheckBox(Panel2, ID_ExportTextures, _("Export textures"), wxPoint(8,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_ExportTextures"));
    ExportTextures->SetValue(false);
    TextureTga = new wxRadioButton(Panel2, ID_TextureTga, _("TGA"), wxPoint(8,64), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TextureTga"));
    TextureBmp = new wxRadioButton(Panel2, ID_TextureBmp, _("BMP"), wxPoint(8,88), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TextureBmp"));
    TextureTiff = new wxRadioButton(Panel2, ID_TextureTiff, _("TIFF"), wxPoint(96,88), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TextureTiff"));
    TexturePng = new wxRadioButton(Panel2, ID_TexturePng, _("PNG"), wxPoint(96,64), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TexturePng"));
    TexturePng->SetValue(true);
    StaticText6 = new wxStaticText(Panel2, ID_StaticText6, _("Texture format:"), wxPoint(8,40), wxDefaultSize, 0, _T("ID_StaticText6"));
    ExportUVs = new wxCheckBox(Panel2, ID_CHECKBOX2, _("Export UVs"), wxPoint(8,112), wxDefaultSize, 0, wxDefaultValidator, _T("ID_ExportUVs"));
    ExportUVs->SetValue(true);
    ProgressBar = new wxGauge(this, ID_ProgressBar, 100, wxPoint(120,400), wxSize(408,28), 0, wxDefaultValidator, _T("ID_ProgressBar"));
    StartExport = new wxButton(this, ID_StartExport, _("Start Exporting"), wxPoint(8,400), wxDefaultSize, 0, wxDefaultValidator, _T("ID_StartExport"));*/


    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);

    Connect(ID_StartExport,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SM2OBJFrame::OnStartExportClick);
    Connect(ID_GetInputFilePath,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SM2OBJFrame::OnGetInputFilePathClick);
    Connect(ID_GetDataFolderPath,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SM2OBJFrame::OnGetDataFolderPathClick);
    Connect(ID_GetOutputFolderPath,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SM2OBJFrame::OnGetOutputFolderPathClick);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SM2OBJFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SM2OBJFrame::OnAbout);
    //*)
}

SM2OBJFrame::~SM2OBJFrame(){
    //(*Destroy(SM2OBJFrame)
    //*)
}

void SM2OBJFrame::OnQuit(wxCommandEvent& event){
    Close();
}

void SM2OBJFrame::OnAbout(wxCommandEvent& event){
    wxString msg = "StarMade blueprint to OBJ version 1.2";
    wxMessageBox(msg, _("Welcome!"));
}

void exportProgressCallback(int Value, int Range){
    if(FramePtr == NULL)return;
    FramePtr->ProgressBar->SetValue(Value);
    FramePtr->ProgressBar->SetRange(Range);
}

void exportExitCallback(bool Success){
    if(FramePtr == NULL)return;

    if(FramePtr != NULL){
        FramePtr->StartExport->Enable();
    }
    if(Success)wxMessageBox( wxT("Export complete!"), wxT("Hurray!"), wxICON_INFORMATION);
    else wxMessageBox( wxT("Something went wrong. Check console output!"), wxT("Ouch!"), wxICON_ERROR);
}

void SM2OBJFrame::OnStartExportClick(wxSpinEvent& event){
    if(TextureBmp->GetValue()){
        imageSaver = &ffw::saveBMP;
        imageExtension = "bmp";
    } else if(TexturePng->GetValue()){
        imageSaver = &ffw::savePNG;
        imageExtension = "png";
    } else if(TextureTga->GetValue()){
        imageSaver = &ffw::saveTGA;
        imageExtension = "tga";
    } else if(TextureTiff->GetValue()){
        imageSaver = &ffw::saveTIFF;
        imageExtension = "tiff";
    }

    textureExport = ExportTextures->GetValue();
    materialExport = ExportMaterials->GetValue();
    threadsCount = NumOfThreads->GetValue();
    filePath = InputFilePath->GetValue();
    fileOutputFolder = OutputFolderPath->GetValue();
    fileName = OutputName->GetValue();
    starMadeDataFolder = InputDataPath->GetValue();

    exportDiffuse = UseDiffuse->GetValue();
    exportBump = UseBump->GetValue();
    exportAlpha = UseAlpha->GetValue();

    exportProgressFunc = &exportProgressCallback;
    exportExitFunc = &exportExitCallback;

    useSpecularHighlight = SpecularHighlight->GetValue();
    uvsExport = ExportUVs->GetValue();
    textureSplit = SplitTiles->GetValue();

    FramePtr = this;
    StartExport->Disable();
    mainThread.bindFunction(&runExporter);
    mainThread.start(NULL);
}

void SM2OBJFrame::OnGetDataFolderPathClick(wxSpinEvent& event){
    wxDirDialog dialog(this, wxT("Select StarMade data folder"), wxT(""), wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, wxT("Select folder"));
    if(dialog.ShowModal() == wxID_OK){
         InputDataPath->SetValue(dialog.GetPath());
    }
}

void SM2OBJFrame::OnGetInputFilePathClick(wxSpinEvent& event){
    wxFileDialog openFileDialog(this, _("Select blueprint file"), "", "", "SMD2 files (*.smd2)|*.smd2", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(openFileDialog.ShowModal() == wxID_CANCEL) return;

    InputFilePath->SetValue(openFileDialog.GetPath());
}

void SM2OBJFrame::OnGetOutputFolderPathClick(wxSpinEvent& event){
    wxDirDialog dialog(this, wxT("Select output folder"), wxT(""), wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, wxT("Select folder"));
    if(dialog.ShowModal() == wxID_OK){
         OutputFolderPath->SetValue(dialog.GetPath());
    }
}
