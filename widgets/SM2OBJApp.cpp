#include "SM2OBJApp.h"

//(*AppHeaders
#include "SM2OBJMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(SM2OBJApp);

bool SM2OBJApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	SM2OBJFrame* Frame = new SM2OBJFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
