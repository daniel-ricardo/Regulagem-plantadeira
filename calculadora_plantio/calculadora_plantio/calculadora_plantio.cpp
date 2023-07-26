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

<<<<<<< HEAD
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
=======
void mainFrame::fazerCalculoRegulagem(wxCommandEvent& event)
{
	// TO-DO: Usar apenas uma variavel regulagem (issue #12)
	auto* regulagem = new Regulagem();
	// Configurando regulagem conforme input do usuario
	regulagem->setCult("teste");
	regulagem->setFormAdb("00-00-00");
	regulagem->setVariSmt("original");
    regulagem->setEspc( static_cast<float>(inEspc->GetValue()) );
    regulagem->setTiro( static_cast<float>(inTiro->GetValue()) );
    regulagem->setGramA(calcularGramasTiro( static_cast<float>(inKgAdb->GetValue()), regulagem) );
    regulagem->setGramS(calcularGramasTiro( static_cast<float>(inKgSmt->GetValue()), regulagem) );

	// mostrando resultado
    outAdb->SetValue( fmt::format("{0:.2f}", regulagem->getGramAdb()) );
    outSmt->SetValue( fmt::format("{0:.2f}", regulagem->getGramSmt()) );
    outPrv->SetValue ( fmt::format(std::locale(""), "{0} kg de semente e {1} kg de adubo",
		fmt::group_digits(inHa->GetValue() * calcularQuilosHectare(regulagem)[0]),
        fmt::group_digits(inHa->GetValue() * calcularQuilosHectare(regulagem)[1])) );
}

void mainFrame::copiarAduboClipboard(wxCommandEvent& event)
{
	if (wxTheClipboard->Open())
	{
		wxTheClipboard->SetData(new wxTextDataObject(outAdb->GetValue()));
		wxTheClipboard->Close();
	}
}

void mainFrame::copiarSementeClipboard(wxCommandEvent& event)
{
	if (wxTheClipboard->Open())
	{
		wxTheClipboard->SetData(new wxTextDataObject(outSmt->GetValue()));
		wxTheClipboard->Close();
	}
}

void mainFrame::copiarPrevisaoClipboard(wxCommandEvent& event)
{
	if (wxTheClipboard->Open())
	{
		wxTheClipboard->SetData(new wxTextDataObject(outPrv->GetValue()));
		wxTheClipboard->Close();
	}
>>>>>>> 633b1ce (closes #8 #12)
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
<<<<<<< HEAD
=======

mainFrame::mainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style,
	const wxString& name) : wxFrame()
{
    if (!Create(parent, id, title, pos, size, style, name)) { return; }
}


mainFrame::~mainFrame()
{
	/*
	 * Desconectar Eventos:
	 *   Botao calcular
	 *   Enter nos campos:
	 *     espacamento, tiro, kg/ha semente, kg/ha adubo e hectares
	 *   Copiar valores para area de transferencia:
	 *     Gramas por tiro de semente e adubo, e previsao de gasto
	 */
	Unbind(wxEVT_BUTTON, &mainFrame::fazerCalculoRegulagem, this, -1, -1, 0);
	Unbind(wxEVT_TEXT_ENTER, &mainFrame::fazerCalculoRegulagem, this, -1, -1, 0);
	Unbind(wxEVT_TEXT_ENTER, &mainFrame::fazerCalculoRegulagem, this, -1, -1, 0);
	Unbind(wxEVT_TEXT_ENTER, &mainFrame::fazerCalculoRegulagem, this, -1, -1, 0);
	Unbind(wxEVT_TEXT_ENTER, &mainFrame::fazerCalculoRegulagem, this, -1, -1, 0);
	Unbind(wxEVT_TEXT_ENTER, &mainFrame::fazerCalculoRegulagem, this, -1, -1, 0);
	Unbind(wxEVT_BUTTON, &mainFrame::copiarAduboClipboard, this, -1, -1, 0);
	Unbind(wxEVT_BUTTON, &mainFrame::copiarSementeClipboard, this, -1, -1, 0);
	Unbind(wxEVT_BUTTON, &mainFrame::copiarPrevisaoClipboard, this, -1, -1, 0);
	wxXmlResource::Get()->Unload("assets/design.xrc");
	wxWindow::Destroy();
}

wxIMPLEMENT_APP(calculadoraRegulagem);

void mainFrame::initFrameFromXRC()
{
	// Inicializando membros
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
	
	auto* regulagem = new Regulagem;

	// Valores iniciais
	regulagem->setCult("teste");
	regulagem->setFormAdb("00-00-00");
	regulagem->setVariSmt("original");
	regulagem->setGramA(calcularGramasTiro(static_cast<float>(inKgAdb->GetValue()), regulagem));
	regulagem->setGramS(calcularGramasTiro(static_cast<float>(inKgSmt->GetValue()), regulagem));

	// mostrando valores iniciais
	inEspc->SetValue(fmt::format("{0:.2g}", regulagem->getEspc()));
	inTiro->SetValue(fmt::format("{0:.2g}", regulagem->getTiro()));
	inKgAdb->SetValue(fmt::format("{0:.2g}", calcularQuilosHectare(regulagem)[1]));
	inKgSmt->SetValue(fmt::format("{0:.2g}", calcularQuilosHectare(regulagem)[0]));
	outAdb->SetValue(fmt::format("{0:.2f}", regulagem->getGramAdb()));
	outSmt->SetValue(fmt::format("{0:.2f}", regulagem->getGramSmt()));
	inHa->SetValue(fmt::format("{0:.2g}", 0.0));
	outPrv->SetValue(fmt::format(std::locale(""), "{0} kg de semente e {1} kg de adubo",
		fmt::group_digits(inHa->GetValue() * calcularQuilosHectare(regulagem)[0]),
		fmt::group_digits(inHa->GetValue() * calcularQuilosHectare(regulagem)[1])));

	/*
	 * Conectar Eventos:
	 *   Botao calcular
	 *   Enter nos campos:
	 *     espacamento, tiro, kg/ha semente, kg/ha adubo e hectares
	 *   Copiar valores para area de transferencia:
	 *     Gramas por tiro de semente e adubo, e previsao de gasto
	 */
	Bind(wxEVT_BUTTON, &mainFrame::fazerCalculoRegulagem, this, btnCalc->GetId(), -1, 0);
	Bind(wxEVT_TEXT_ENTER, &mainFrame::fazerCalculoRegulagem, this, inEspc->GetId(), -1, 0);
	Bind(wxEVT_TEXT_ENTER, &mainFrame::fazerCalculoRegulagem, this, inTiro->GetId(), -1, 0);
	Bind(wxEVT_TEXT_ENTER, &mainFrame::fazerCalculoRegulagem, this, inKgSmt->GetId(), -1, 0);
	Bind(wxEVT_TEXT_ENTER, &mainFrame::fazerCalculoRegulagem, this, inKgAdb->GetId(), -1, 0);
	Bind(wxEVT_TEXT_ENTER, &mainFrame::fazerCalculoRegulagem, this, inHa->GetId(), -1, 0);
	Bind(wxEVT_BUTTON, &mainFrame::copiarAduboClipboard, this, btnCpAdb->GetId(), -1, 0);
	Bind(wxEVT_BUTTON, &mainFrame::copiarSementeClipboard, this, btnCpSmt->GetId(), -1, 0);
	Bind(wxEVT_BUTTON, &mainFrame::copiarPrevisaoClipboard, this, btnCpPrv->GetId(), -1, 0);
}


>>>>>>> 633b1ce (closes #8 #12)
