/***************************************************************
 * Name:      FrameDisplayMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2013-08-09
 * Copyright:  ()
 * License:
 **************************************************************/

#include "FrameDisplayMain.h"
#include "FrameDisplayApp.h"
#include "global_types.h"
#include "graph.h"
#include "framedata.h"
#include <wx/msgdlg.h>

class chr_frm_data : public wxTreeItemData
{
public:
    seq *sq;
    int32_t sub;
    int32_t frame;
};


//(*InternalHeaders(FrameDisplayDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)

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

//(*IdInit(FrameDisplayDialog)
const long FrameDisplayDialog::ID_TREECTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(FrameDisplayDialog,wxDialog)
    //(*EventTable(FrameDisplayDialog)
    //*)
END_EVENT_TABLE()


pthread_mutex_t mutex1;
char_sprite *spr;

void FrameDisplayDialog::AddChar(char_graph *graph, wxTreeItemId &root)
{
    wxString itm;
    for (mapseq::iterator sqit = graph->seqs.begin(); sqit != graph->seqs.end(); sqit++)
    {
        itm.Printf(wxT("seq %d"),sqit->first);
        wxTreeItemId sqq = TreeCtrl1->AppendItem(root, itm);
        seq *sq = sqit->second;
        for(int32_t ss=0; ss < sq->subseqs.size(); ss++)
        {
            itm.Printf(wxT("subseq %d"),ss);
            wxTreeItemId subsq = TreeCtrl1->AppendItem(sqq, itm);
            for(int32_t fr=0; fr < sq->subseqs[ss].frames.size(); fr++)
            {
                itm.Printf(wxT("Frame %d"),fr);

                chr_frm_data *dat = new chr_frm_data;
                dat->frame = fr;
                dat->sub = ss;
                dat->sq = sq;

                TreeCtrl1->AppendItem(subsq, itm,-1,-1,dat);

            }

        }
//        wxTreeCtrlBase.AppendItem()
    }
}

FrameDisplayDialog::FrameDisplayDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(FrameDisplayDialog)
    Create(parent, id, _("FrameDisplay"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("id"));
    SetClientSize(wxSize(247,420));
    Move(wxPoint(-1,-1));
    TreeCtrl1 = new wxTreeCtrl(this, ID_TREECTRL1, wxPoint(8,8), wxSize(232,408), wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));

    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_BEGIN_DRAG,(wxObjectEventFunction)&FrameDisplayDialog::OnTreeCtrl1BeginDrag);
    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&FrameDisplayDialog::OnTreeCtrl1SelectionChanged);
    //*)

    spr = new char_sprite;

    marisa.load_dat("marisa",0);
    alice.load_dat("alice",0);
    cirno.load_dat("chirno",0);

    wxString itm;
    itm.Printf(wxT("%s"),_("Characters"));

    wxTreeItemId root = TreeCtrl1->AddRoot(itm);
    wxTreeItemId chroot;

    itm.Printf(wxT("%s"),_("marisa"));
    chroot = TreeCtrl1->AppendItem(root,itm);
    AddChar(&marisa, chroot);

    itm.Printf(wxT("%s"),_("alice"));
    chroot = TreeCtrl1->AppendItem(root,itm);
    AddChar(&alice, chroot);

    itm.Printf(wxT("%s"),_("cirno"));
    chroot = TreeCtrl1->AppendItem(root,itm);
    AddChar(&cirno, chroot);

    gr_clear(0,0,0);
    gr_flip();
//    printf("%d\n",);
}

FrameDisplayDialog::~FrameDisplayDialog()
{
    //(*Destroy(FrameDisplayDialog)
    //*)
}

void FrameDisplayDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void FrameDisplayDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void FrameDisplayDialog::OnTreeCtrl1BeginDrag(wxTreeEvent& event)
{

}

void FrameDisplayDialog::OnTreeCtrl1SelectionChanged(wxTreeEvent& event)
{
    chr_frm_data *data = (chr_frm_data *)TreeCtrl1->GetItemData(event.GetItem());

    if (data)
    {
        spr->set_seq(data->sq);
        spr->set_subseq(data->sub);
        spr->set_frame(data->frame);
        gr_clear(0,0,0);
        spr->setXY(300,-300);
        spr->draw(0);
        gr_flip();

    }
}
