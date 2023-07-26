#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/clipbrd.h>
#include <wx/bmpbuttn.h>
#include <wx/sizer.h>	
#include <wx/xrc/xmlres.h>
#include <fmt/format.h>
#include <locale>

#include "framemain_base.hpp"
#include "regulagem.hpp"

class calculadoraRegulagem : public wxApp
{
public:
    bool OnInit() override;
};

bool calculadoraRegulagem::OnInit()
{
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load("assets/design.xrc");
    wxXmlResource::Get()->LoadAllFiles("rc");

	mainFrame* frame = new mainFrame(NULL, wxID_ANY, "Calculadora de regulagem de plantadeira", wxDefaultPosition,
        wxSize(470, 500), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER | wxTAB_TRAVERSAL, wxFrameNameStr);

	frame->initFrameFromXRC();
	frame->Show(true);

    return true;
}

mainFrame::mainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style,
	const wxString& name) : wxFrame()
{
    if (!Create(parent, id, title, pos, size, style, name)) { return; }
}

mainFrame::~mainFrame() {
	wxXmlResource::Get()->Unload("assets/design.xrc");
	wxWindow::Destroy();
}

wxIMPLEMENT_APP(calculadoraRegulagem);

void mainFrame::initFrameFromXRC()
{

	wxXmlResource::Get()->LoadFrame(this, NULL, "mainFrame");
	panelMain = XRCCTRL(*this, "panelMain", wxPanel);
	panelGeral = XRCCTRL(*this, "panelGeral", wxPanel);
	panelCult = XRCCTRL(*this, "panelCult", wxPanel);
	labelCult = XRCCTRL(*this, "labelCult", wxStaticText);
	boxCult = XRCCTRL(*this, "boxCult", wxChoice);
	panelEspc = XRCCTRL(*this, "panelEspc", wxPanel);
	labelEspc = XRCCTRL(*this, "labelEspc", wxStaticText);
	inEspc = XRCCTRL(*this, "inEspc", wxSpinCtrlDouble);
	panelTiro = XRCCTRL(*this, "panelTiro", wxPanel);
	labelTiro = XRCCTRL(*this, "labelTiro", wxStaticText);
	inTiro = XRCCTRL(*this, "inTiro", wxSpinCtrlDouble);
	panelSmt = XRCCTRL(*this, "panelSmt", wxPanel);
	panelInSmt = XRCCTRL(*this, "panelInSmt", wxPanel);
	tituloSmt = XRCCTRL(*this, "tituloSmt", wxStaticText);
	labelKghaSmt = XRCCTRL(*this, "labelKghaSmt", wxStaticText);
	inKgSmt = XRCCTRL(*this, "inKgSmt", wxSpinCtrlDouble);
	panelOutSmt = XRCCTRL(*this, "panelOutSmt", wxPanel);
	labelTituloResultadoSmt = XRCCTRL(*this, "labelTituloResultadoSmt", wxStaticText);
	outSmt = XRCCTRL(*this, "outSmt", wxTextCtrl);
	btnCpSmt = XRCCTRL(*this, "btnCpSmt", wxButton);
	panelAdb = XRCCTRL(*this, "panelAdb", wxPanel);
	panelInAdb = XRCCTRL(*this, "panelInAdb", wxPanel);
	tituloAdb = XRCCTRL(*this, "tituloAdb", wxStaticText);
	labelKghaAdb = XRCCTRL(*this, "labelKghaAdb", wxStaticText);
	inKgAdb = XRCCTRL(*this, "inKgAdb", wxSpinCtrlDouble);
	panelOutAdb = XRCCTRL(*this, "panelOutAdb", wxPanel);
	labelTituloResultadoAdb = XRCCTRL(*this, "labelTituloResultadoAdb", wxStaticText);
	outAdb = XRCCTRL(*this, "outAdb", wxTextCtrl);
	btnCpAdb = XRCCTRL(*this, "btnCpAdb", wxButton);
	panelPrv = XRCCTRL(*this, "panelPrv", wxPanel);
	panelInHa = XRCCTRL(*this, "panelInHa", wxPanel);
	labelHa = XRCCTRL(*this, "labelHa", wxStaticText);
	inHa = XRCCTRL(*this, "inHa", wxSpinCtrlDouble);
	panelOutPrv = XRCCTRL(*this, "panelOutPrv", wxPanel);
	labelPrv = XRCCTRL(*this, "labelPrv", wxStaticText);
	outPrv = XRCCTRL(*this, "outPrv", wxTextCtrl);
	btnCpPrv = XRCCTRL(*this, "btnCpPrv", wxButton);
	panelBtnCalc = XRCCTRL(*this, "panelBtnCalc", wxPanel);
	btnCalc = XRCCTRL(*this, "btnCalc", wxButton);
}

/*
 * Estrutura de paineis e sizers:
 * (cada wxPanel tem um wxBoxSizer diretamente abaixo na estrutura.
 * para simplificar essa representacao, foram colocados na mesma linha)
 *
 * + wxFrame frameMain,
 *     + wxPanel panelMain, wxBoxSizer boxMain (Vertical)
 *         + wxPanel panelGeral, wxBoxSizer boxGeral (Horizontal)
 *		       + wxPanel panelCult, wxBoxSizer panelSzCult (Vertical)
 *		       + wxPanel panelEspc, wxBoxSizer boxEspc (Vertical)
 *			   + wxPanel panelTiro, wxBoxSizer boxTiro (Vertical)
 *	       + wxPanel panelSmt, wxBoxSizer boxSmt (Horizontal)
 *			   + wxPanel panelInSmt, wxBoxSizer boxInSmt (Vertical)
 *                 + wxBoxSizer boxInKgSmt (Horizontal)
 *			   + wxPanel panelOutSmt, wxBoxSizer boxOutSmt (Vertical)
 *			       + wxBoxSizer boxOutSmt2 (Horizontal)
 *         + wxPanel panelAdb, wxBoxSizer boxAdb (Horizontal)
 *             + wxPanel panelInAdb, wxBoxSizer boxInAdb (Vertical)
 *                 + wxBoxSizer boxInKgAdb (Horizontal)
 *             + wxPanel panelOutAdb, wxBoxSizer boxOutAdb (Vertical)
 *			       + wxBoxSizer boxOutAdb2 (Horizontal)
 *         + wxPanel panelPrv, wxBoxSizer boxHa (Horizontal)
 *             + wxPanel panelInHa, wxBoxSizer boxInHa (Vertical)
 *             + wxPanel panelOutPrv, wxBoxSizer panelOutPrv (Vertical)
 *			       + wxBoxSizer boxOutPrv2 (Horizontal)
 *         + wxPanel panelBtnCalc, wxBoxSizer boxBtnCalc (Vertical)
 */
