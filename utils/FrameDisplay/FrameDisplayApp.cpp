/***************************************************************
 * Name:      FrameDisplayApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2013-08-09
 * Copyright:  ()
 * License:
 **************************************************************/

#include "FrameDisplayApp.h"
#include "global_types.h"
#include "graph.h"
#include "framedata.h"
#include "archive.h"

//(*AppHeaders
#include "FrameDisplayMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(FrameDisplayApp);


bool FrameDisplayApp::OnInit()
{
    gr_init(640,480,"Frame");

    char buf[512];
    char path[512];
    path[0] = '.';
    path[1] = 0;
    if (argc == 2)
    {
    wxString str(argv[1]);
    sprintf(path,"%s",(const char*)str.mb_str(wxConvUTF8));
    }

    sprintf(buf,"%s/%s",path,"th105a.dat");
    arc_add_dat(buf);
    sprintf(buf,"%s/%s",path,"th105b.dat");
    arc_add_dat(buf);
    sprintf(buf,"%s/%s",path,"th105c.dat");
    arc_add_dat(buf);
    sprintf(buf,"%s/%s",path,"th123a.dat");
    arc_add_dat(buf);
    sprintf(buf,"%s/%s",path,"th123b.dat");
    arc_add_dat(buf);
    sprintf(buf,"%s/%s",path,"th123c.dat");
    arc_add_dat(buf);


    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	FrameDisplayDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)

    return wxsOK;

}
