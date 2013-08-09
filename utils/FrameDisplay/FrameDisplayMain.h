/***************************************************************
 * Name:      FrameDisplayMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2013-08-09
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef FRAMEDISPLAYMAIN_H
#define FRAMEDISPLAYMAIN_H

#include "global_types.h"
#include "graph.h"
#include "framedata.h"

//(*Headers(FrameDisplayDialog)
#include <wx/dialog.h>
#include <wx/treectrl.h>
//*)

class FrameDisplayDialog: public wxDialog
{
    public:

        FrameDisplayDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~FrameDisplayDialog();

        char_graph marisa;
        char_graph alice;
        char_graph cirno;

    private:

        void AddChar(char_graph *graph, wxTreeItemId &root);

        //(*Handlers(FrameDisplayDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTreeCtrl1BeginDrag(wxTreeEvent& event);
        void OnTreeCtrl1SelectionChanged(wxTreeEvent& event);
        //*)

        //(*Identifiers(FrameDisplayDialog)
        static const long ID_TREECTRL1;
        //*)

        //(*Declarations(FrameDisplayDialog)
        wxTreeCtrl* TreeCtrl1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // FRAMEDISPLAYMAIN_H
