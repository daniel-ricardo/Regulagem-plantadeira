#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>
#include "regulagem.hpp"

class mainFrame : public wxFrame
{
<<<<<<< HEAD
protected:

=======
private:

    void fazerCalculoRegulagem(wxCommandEvent& event);
    void copiarSementeClipboard(wxCommandEvent& event);
    void copiarAduboClipboard(wxCommandEvent& event);
    void copiarPrevisaoClipboard(wxCommandEvent& event);

protected:
>>>>>>> 633b1ce (closes #8 #12)
    Regulagem* regulagem;

    wxButton* btnCalc;
    wxButton* btnCpAdb;
    wxButton* btnCpPrv;
    wxButton* btnCpSmt;
    wxChoice* boxCult;
    wxPanel* panelAdb;
    wxPanel* panelBtnCalc;
    wxPanel* panelCult;
    wxPanel* panelEspc;
    wxPanel* panelGeral;
    wxPanel* panelInAdb;
    wxPanel* panelInHa;
    wxPanel* panelInSmt;
    wxPanel* panelMain;
    wxPanel* panelOutAdb;
    wxPanel* panelOutPrv;
    wxPanel* panelOutSmt;
    wxPanel* panelPrv;
    wxPanel* panelSmt;
    wxPanel* panelTiro;
    wxSpinCtrlDouble* inEspc;
    wxSpinCtrlDouble* inHa;
    wxSpinCtrlDouble* inKgAdb;
    wxSpinCtrlDouble* inKgSmt;
    wxSpinCtrlDouble* inTiro;
    wxStaticText* labelCult;
    wxStaticText* labelEspc;
    wxStaticText* labelHa;
    wxStaticText* labelKghaAdb;
    wxStaticText* labelKghaSmt;
    wxStaticText* labelPrv;
    wxStaticText* labelTiro;
    wxStaticText* labelTituloResultadoAdb;
    wxStaticText* labelTituloResultadoSmt;
    wxStaticText* tituloAdb;
    wxStaticText* tituloSmt;
    wxTextCtrl* outAdb;
    wxTextCtrl* outPrv;
    wxTextCtrl* outSmt;

public:
    mainFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title =
        "Calculadora de regulagem de plantadeira", const wxPoint& pos = wxDefaultPosition, const wxSize& size =
        wxSize(500, 300), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL,
        const wxString& name = wxFrameNameStr);
    ~mainFrame();
    void initFrameFromXRC();
};
