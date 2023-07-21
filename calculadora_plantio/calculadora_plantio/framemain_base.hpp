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
#include <wx/spinctrl.h>
#include <wx/textctrl.h>
#include "regulagem.hpp"

class frameMain : public wxFrame
{
private:

    void fazerCalculoRegulagem(wxCommandEvent& event);
    void copiarSementeClipboard(wxCommandEvent& event);
    void copiarAduboClipboard(wxCommandEvent& event);
    void copiarPrevisaoClipboard(wxCommandEvent& event);

public:

    Regulagem* regulagem;
    wxButton* btnCalcular;
    wxButton* btnCpPrev;
    wxButton* btnCpSmt;
    wxButton* btnCpAdb;
    wxChoice* boxCult;
    wxSpinCtrlDouble* inEspc;
    wxSpinCtrlDouble* inHa;
    wxSpinCtrlDouble* inKgAdb;
    wxSpinCtrlDouble* inKgSmt;
    wxSpinCtrlDouble* inTiro;
    wxStaticText* labelCult;
    wxStaticText* labelEspc;
    wxStaticText* labelHectares;
    wxStaticText* labelKghaAdb;
    wxStaticText* labelKghaSmt;
    wxStaticText* labelPrevisao;
    wxStaticText* labelTiro;
    wxStaticText* labelTituloResultadoAdb;
    wxStaticText* labelTituloResultadoSmt;
    wxTextCtrl* outAdb;
    wxTextCtrl* outSmt;
    wxTextCtrl* outHa;
    wxStaticText* tituloAdb;
    wxStaticText* tituloSmt;

    frameMain(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title =
        "Calcular Regulagem da Plantadeira", const wxPoint& pos = wxDefaultPosition, const wxSize& size =
        wxSize(550, 350), long style = wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER | wxTAB_TRAVERSAL,
        const wxString& name = wxFrameNameStr);
    ~frameMain();

};
