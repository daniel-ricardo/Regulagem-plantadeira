#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/clipbrd.h>
#include <wx/bmpbuttn.h>
#include <wx/sizer.h>    
#include <wx/xrc/xmlres.h>
#include <fmt/format.h>
#include <locale>

#include "mainframe_base/mainframe_base.hpp"
#include "regulagem/regulagem.hpp"
#include "calculadora_plantio.hpp"

class calculadoraRegulagem : public wxApp
{
public:
    bool OnInit() override;
};

bool calculadoraRegulagem::OnInit()
{
    /*
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load("assets/design.xrc");
    wxXmlResource::Get()->LoadAllFiles("rc");
    */
   
    mainFrame* frame = new mainFrame(NULL, wxID_ANY, "Calculadora de regulagem de plantadeira", wxDefaultPosition,
        wxSize(550, 540), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER | wxTAB_TRAVERSAL, wxFrameNameStr);

	frame->initValues();
	frame->Show(true);

    return true;
}

void mainFrame::fazerCalculoRegulagem(wxCommandEvent& event)
{
	auto* regulagem = new Regulagem();
	// Configurando regulagem conforme input do usuario
	regulagem->setCult(static_cast<std::string>(choiceCult->GetString(choiceCult->GetSelection())));
	regulagem->setFormAdb(static_cast<std::string>(inForm->GetValue()));
	regulagem->setVariSmt(static_cast<std::string>(inVari->GetValue()));
    regulagem->setEspc( static_cast<float>(inEspc->GetValue()) );
    regulagem->setTiro( static_cast<float>(inTiro->GetValue()) );
    regulagem->setGramA(calcularGramasTiro( static_cast<float>(inKgAdb->GetValue()), regulagem) );
    regulagem->setGramS(calcularGramasTiro( static_cast<float>(inKgSmt->GetValue()), regulagem) );

    // mostrando resultado
    outAdb->SetValue( fmt::format("{0:.2f}", regulagem->getGramAdb()) );
    outSmt->SetValue( fmt::format("{0:.2f}", regulagem->getGramSmt()) );
    outPrv->SetValue ( fmt::format(std::locale(""), "{0} kg de semente e {1} kg de adubo",
    	fmt::group_digits(inKgAdb->GetValue() * calcularQuilosHectare(regulagem)[0]),
        fmt::group_digits(inKgAdb->GetValue() * calcularQuilosHectare(regulagem)[1])) );
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
}

mainFrame::mainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style,
    const wxString& name) : wxFrame()
{
    if (!Create(parent, id, title, pos, size, style, name)) { return; }

    auto* panelMain = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

    auto* box_sizer = new wxBoxSizer(wxVERTICAL);

    auto* panelInsumos = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxSUNKEN_BORDER | wxCENTER);
    box_sizer->Add(panelInsumos, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_2 = new wxBoxSizer(wxHORIZONTAL);

    auto* panelTalh = new wxPanel(panelInsumos, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer_2->Add(panelTalh, wxSizerFlags(1).Center().Border(wxALL));

    auto* box_sizer_3 = new wxBoxSizer(wxVERTICAL);

    labelTalh = new wxStaticText(panelTalh, wxID_ANY, wxString::FromUTF8("Talhão:"));
    box_sizer_3->Add(labelTalh, wxSizerFlags().Center().Border(wxALL));

    inTalh = new wxTextCtrl(panelTalh, wxID_ANY, wxEmptyString);
    box_sizer_3->Add(inTalh, wxSizerFlags().Center().Border(wxALL));
    panelTalh->SetSizerAndFit(box_sizer_3);

    auto* panelCult = new wxPanel(panelInsumos, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelCult->SetToolTip("Selecione qual Cultura de Sementes vai ser plantada");
    box_sizer_2->Add(panelCult, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_4 = new wxBoxSizer(wxVERTICAL);

    labelCult = new wxStaticText(panelCult, wxID_ANY, "Cultura:");
    labelCult->SetToolTip("Selecione qual Cultura de Sementes vai ser plantada");
    box_sizer_4->Add(labelCult, wxSizerFlags().Center().Border(wxALL));

    choiceCult = new wxChoice(panelCult, wxID_ANY);
    choiceCult->Append("Aveia");
    choiceCult->Append("Cevada");
    choiceCult->Append(wxString::FromUTF8("Feijão"));
    choiceCult->Append("Milheto");
    choiceCult->Append("Milho");
    choiceCult->Append("Soja");
    choiceCult->Append("Trigo");
    choiceCult->Append("Triguilho");
    choiceCult->Append("Triticalhe");
    choiceCult->Append("Outro...");
    choiceCult->SetToolTip("Selecione qual Cultura de Sementes vai ser plantada");
    box_sizer_4->Add(choiceCult, wxSizerFlags().Center().Border(wxALL));
    panelCult->SetSizerAndFit(box_sizer_4);

    auto* panelVari = new wxPanel(panelInsumos, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer_2->Add(panelVari, wxSizerFlags(1).Center().Border(wxALL));

    auto* box_sizer_5 = new wxBoxSizer(wxVERTICAL);

    labelVari = new wxStaticText(panelVari, wxID_ANY, "Variedade:");
    box_sizer_5->Add(labelVari, wxSizerFlags().Center().Border(wxALL));

    inVari = new wxTextCtrl(panelVari, wxID_ANY, wxEmptyString);
    box_sizer_5->Add(inVari, wxSizerFlags().Center().Border(wxALL));
    panelVari->SetSizerAndFit(box_sizer_5);

    auto* panelForm = new wxPanel(panelInsumos, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer_2->Add(panelForm, wxSizerFlags(1).Center().Border(wxALL));

    auto* box_sizer_6 = new wxBoxSizer(wxVERTICAL);

    labelForm = new wxStaticText(panelForm, wxID_ANY, wxString::FromUTF8("Fórmula"));
    box_sizer_6->Add(labelForm, wxSizerFlags().Center().Border(wxALL));

    inForm = new wxTextCtrl(panelForm, wxID_ANY, wxEmptyString);
    box_sizer_6->Add(inForm, wxSizerFlags().Center().Border(wxALL));
    panelForm->SetSizerAndFit(box_sizer_6);
    panelInsumos->SetSizerAndFit(box_sizer_2);

    auto* panelConf = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxSUNKEN_BORDER | wxCENTER );
    box_sizer->Add(panelConf, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_7 = new wxBoxSizer(wxHORIZONTAL);

    auto* panelEspc = new wxPanel(panelConf, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelEspc->SetToolTip(wxString::FromUTF8("Coloque o espaçamento das linhas (em centímetros)"));
    box_sizer_7->Add(panelEspc, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_8 = new wxBoxSizer(wxVERTICAL);

    labelEspc = new wxStaticText(panelEspc, wxID_ANY, wxString::FromUTF8("Espaçamento das linhas (cm):"));
    labelEspc->SetToolTip(wxString::FromUTF8("Coloque o espaçamento das linhas (em centímetros)"));
    box_sizer_8->Add(labelEspc, wxSizerFlags().Center().Border(wxALL));

    inEspc = new wxSpinCtrlDouble(panelEspc, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxALIGN_RIGHT, 1, 1000, 0, 1);
    inEspc->SetToolTip(wxString::FromUTF8("Coloque o espaçamento das linhas (em centímetros)"));
    box_sizer_8->Add(inEspc, wxSizerFlags().Center().Border(wxALL));
    panelEspc->SetSizerAndFit(box_sizer_8);

    auto* panelTiro = new wxPanel(panelConf, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelTiro->SetToolTip(wxString::FromUTF8("Coloque o comprimento da área de regulagem em metros"));
    box_sizer_7->Add(panelTiro, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_9 = new wxBoxSizer(wxVERTICAL);

    labelTiro = new wxStaticText(panelTiro, wxID_ANY, "Tiro (m):");
    labelTiro->SetToolTip(wxString::FromUTF8("Coloque o comprimento da área de regulagem em metros"));
    box_sizer_9->Add(labelTiro, wxSizerFlags().Center().Border(wxALL));

    inTiro = new wxSpinCtrlDouble(panelTiro, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxSP_ARROW_KEYS, 1, 1000, 0, 1);
    inTiro->SetToolTip(wxString::FromUTF8("Coloque o comprimento da área de regulagem em metros"));
    box_sizer_9->Add(inTiro, wxSizerFlags().Center().Border(wxALL));
    panelTiro->SetSizerAndFit(box_sizer_9);
    panelConf->SetSizerAndFit(box_sizer_7);

    auto* panelSmt = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer->Add(panelSmt, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_10 = new wxBoxSizer(wxHORIZONTAL);

    auto* panelInSmt = new wxPanel(panelSmt, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxSUNKEN_BORDER | wxCENTER );
    panelInSmt->SetToolTip("Alvo de semente em quilos por hectare");
    box_sizer_10->Add(panelInSmt, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_11 = new wxBoxSizer(wxVERTICAL);

    tituloSmt = new wxStaticText(panelInSmt, wxID_ANY, "Semente");
    tituloSmt->SetToolTip("Alvo de semente em quilos por hectare");
    box_sizer_11->Add(tituloSmt, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_12 = new wxBoxSizer(wxHORIZONTAL);

    labelKghaSmt = new wxStaticText(panelInSmt, wxID_ANY, "Kg / Ha");
    labelKghaSmt->SetToolTip("Alvo de semente em quilos por hectare");
    box_sizer_12->Add(labelKghaSmt, wxSizerFlags().Center().Border(wxALL));

    inKgSmt = new wxSpinCtrlDouble(panelInSmt, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxSP_ARROW_KEYS, 0, 1000, 0, 1);
    inKgSmt->SetToolTip("Alvo de semente em quilos por hectare");
    box_sizer_12->Add(inKgSmt, wxSizerFlags().Center().Border(wxALL));

    box_sizer_11->Add(box_sizer_12, wxSizerFlags(1).Center().Border(wxALL));
    panelInSmt->SetSizerAndFit(box_sizer_11);

    auto* panelOutSmt = new wxPanel(panelSmt, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelOutSmt->SetToolTip(
        "A quantidade de gramas de semente por tiro que deve cair para a plantadeira estar regulada");
    box_sizer_10->Add(panelOutSmt, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_13 = new wxBoxSizer(wxVERTICAL);

    labelTituloResultadoSmt = new wxStaticText(panelOutSmt, wxID_ANY, "Gramas por tiro: (Semente)");
    box_sizer_13->Add(labelTituloResultadoSmt, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_14 = new wxBoxSizer(wxHORIZONTAL);

    outSmt = new wxTextCtrl(panelOutSmt, wxID_ANY, "0.0", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    outSmt->SetToolTip(
        "A quantidade de gramas de semente por tiro que deve cair para a plantadeira estar regulada");
    box_sizer_14->Add(outSmt, wxSizerFlags().Center().Border(wxALL));

    btnCpSmt = new wxButton(panelOutSmt, wxID_ANY, wxEmptyString);
    btnCpSmt->SetLabelMarkup("Copiar");
#if wxCHECK_VERSION(3, 1, 6)
    {
        wxVector<wxBitmap> bitmaps;
        btnCpSmt->SetBitmap(wxBitmapBundle::FromBitmaps(bitmaps));
    }
#else
    btnCpSmt->SetBitmap(wxueImage(, sizeof()));
#endif  // wxCHECK_VERSION(3, 1, 6)
    btnCpSmt->SetToolTip("Copiar gramas de semente por tiro");
    box_sizer_14->Add(btnCpSmt, wxSizerFlags().Center().Border(wxALL));

    box_sizer_13->Add(box_sizer_14, wxSizerFlags().Center().Border(wxALL));
    panelOutSmt->SetSizerAndFit(box_sizer_13);
    panelSmt->SetSizerAndFit(box_sizer_10);

    auto* panelAdb = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer->Add(panelAdb, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_15 = new wxBoxSizer(wxHORIZONTAL);

    auto* panelInAdb = new wxPanel(panelAdb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxSUNKEN_BORDER | wxCENTER );;
    panelInAdb->SetToolTip("Alvo de adubo em quilos por hectare");
    box_sizer_15->Add(panelInAdb, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_16 = new wxBoxSizer(wxVERTICAL);

    tituloAdb = new wxStaticText(panelInAdb, wxID_ANY, "Adubo");
    tituloAdb->SetToolTip("Alvo de adubo em quilos por hectare");
    box_sizer_16->Add(tituloAdb, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_17 = new wxBoxSizer(wxHORIZONTAL);

    labelKghaAdb = new wxStaticText(panelInAdb, wxID_ANY, "Kg / Ha");
    labelKghaAdb->SetToolTip("Alvo de adubo em quilos por hectare");
    box_sizer_17->Add(labelKghaAdb, wxSizerFlags().Center().Border(wxALL));

    inKgAdb = new wxSpinCtrlDouble(panelInAdb, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxSP_ARROW_KEYS, 0, 1000, 0, 1);
    inKgAdb->SetToolTip("Alvo de adubo em quilos por hectare");
    box_sizer_17->Add(inKgAdb, wxSizerFlags().Center().Border(wxALL));

    box_sizer_16->Add(box_sizer_17, wxSizerFlags().Center().Border(wxALL));
    panelInAdb->SetSizerAndFit(box_sizer_16);

    auto* panelOutAdb = new wxPanel(panelAdb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelOutAdb->SetToolTip(
        "A quantidade de gramas de adubo por tiro que deve cair para a plantadeira estar regulada");
    box_sizer_15->Add(panelOutAdb, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_18 = new wxBoxSizer(wxVERTICAL);

    labelTituloResultadoAdb = new wxStaticText(panelOutAdb, wxID_ANY, "Gramas por tiro: (Adubo)");
    labelTituloResultadoAdb->SetToolTip(
        "A quantidade de gramas de adubo por tiro que deve cair para a plantadeira estar regulada");
    box_sizer_18->Add(labelTituloResultadoAdb, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_19 = new wxBoxSizer(wxHORIZONTAL);

    outAdb = new wxTextCtrl(panelOutAdb, wxID_ANY, "0.0", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    outAdb->SetToolTip(
        "A quantidade de gramas de adubo por tiro que deve cair para a plantadeira estar regulada");
    box_sizer_19->Add(outAdb, wxSizerFlags().Center().Border(wxALL));

    btnCpAdb = new wxButton(panelOutAdb, wxID_ANY, wxEmptyString);
    btnCpAdb->SetLabelMarkup("Copiar");
#if wxCHECK_VERSION(3, 1, 6)
    {
        wxVector<wxBitmap> bitmaps;
        btnCpAdb->SetBitmap(wxBitmapBundle::FromBitmaps(bitmaps));
    }
#else
    btnCpAdb->SetBitmap(wxueImage(, sizeof()));
#endif  // wxCHECK_VERSION(3, 1, 6)
    btnCpAdb->SetToolTip("Copiar gramas de adubo por tiro");
    box_sizer_19->Add(btnCpAdb, wxSizerFlags().Center().Border(wxALL));

    box_sizer_18->Add(box_sizer_19, wxSizerFlags().Center().Border(wxALL));
    panelOutAdb->SetSizerAndFit(box_sizer_18);
    panelAdb->SetSizerAndFit(box_sizer_15);

    auto* panelPrv = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer->Add(panelPrv, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_20 = new wxBoxSizer(wxHORIZONTAL);

    auto* panelInHa = new wxPanel(panelPrv, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxSUNKEN_BORDER );
    panelInHa->SetToolTip("Quantos hectares planeja serem plantados");
    box_sizer_20->Add(panelInHa, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_21 = new wxBoxSizer(wxVERTICAL | wxCENTER );

    labelHa = new wxStaticText(panelInHa, wxID_ANY, "Hectares:");
    labelHa->SetToolTip("Quantos hectares planeja serem plantados");
    box_sizer_21->Add(labelHa, wxSizerFlags().Center().Border(wxALL));

    inHa = new wxSpinCtrlDouble(panelInHa, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxSP_ARROW_KEYS, 0, 1000, 0, 1);
    inHa->SetToolTip("Quantos hectares planeja serem plantados");
    box_sizer_21->Add(inHa, wxSizerFlags().Center().Border(wxALL));
    panelInHa->SetSizerAndFit(box_sizer_21);

    auto* panelOutPrv = new wxPanel(panelPrv, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelOutPrv->SetToolTip(wxString::FromUTF8("Gasto de insumos previsto segundo a área planejada"));
    box_sizer_20->Add(panelOutPrv, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_22 = new wxBoxSizer(wxVERTICAL);

    labelPrv = new wxStaticText(panelOutPrv, wxID_ANY, wxString::FromUTF8("Previsão:"));
    labelPrv->SetToolTip(wxString::FromUTF8("Gasto de insumos previsto segundo a área planejada"));
    box_sizer_22->Add(labelPrv, wxSizerFlags().Center().Border(wxALL));

    auto* box_sizer_23 = new wxBoxSizer(wxHORIZONTAL);

    outPrv = new wxTextCtrl(panelOutPrv, wxID_ANY, "0 kg de semente e 0 kg de adubo", wxDefaultPosition,
        wxSize(280, -1), wxTE_READONLY);
    outPrv->SetToolTip(wxString::FromUTF8("Gasto de insumos previsto segundo a área planejada"));
    box_sizer_23->Add(outPrv, wxSizerFlags().Center().Border(wxALL));

    btnCpPrv = new wxButton(panelOutPrv, wxID_ANY, wxEmptyString);
    btnCpPrv->SetLabelMarkup("Copiar");
#if wxCHECK_VERSION(3, 1, 6)
    {
        wxVector<wxBitmap> bitmaps;
        btnCpPrv->SetBitmap(wxBitmapBundle::FromBitmaps(bitmaps));
    }
#else
    btnCpPrv->SetBitmap(wxueImage(, sizeof()));
#endif  // wxCHECK_VERSION(3, 1, 6)
    btnCpPrv->SetToolTip(wxString::FromUTF8("Copiar previsão de gasto de insumos"));
    box_sizer_23->Add(btnCpPrv, wxSizerFlags().Center().Border(wxALL));

    box_sizer_22->Add(box_sizer_23, wxSizerFlags().Center().Border(wxALL));
    panelOutPrv->SetSizerAndFit(box_sizer_22);
    panelPrv->SetSizerAndFit(box_sizer_20);

    auto* panelBtnCalc = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer->Add(panelBtnCalc, wxSizerFlags().Right().Border(wxALL));

    auto* box_sizer_24 = new wxBoxSizer(wxVERTICAL);

    btnCalc = new wxButton(panelBtnCalc, wxID_ANY, wxEmptyString);
    btnCalc->SetLabelMarkup("Calcular");
#if wxCHECK_VERSION(3, 1, 6)
    {
        wxVector<wxBitmap> bitmaps;
        btnCalc->SetBitmap(wxBitmapBundle::FromBitmaps(bitmaps));
    }
#else
    btnCalc->SetBitmap(wxueImage(, sizeof()));
#endif  // wxCHECK_VERSION(3, 1, 6)
    btnCalc->SetToolTip("Calcular valores");
    box_sizer_24->Add(btnCalc, wxSizerFlags().Center().Border(wxALL));
    panelBtnCalc->SetSizerAndFit(box_sizer_24);
    panelMain->SetSizerAndFit(box_sizer);

    Centre(wxBOTH);
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
	//wxXmlResource::Get()->Unload("assets/design.xrc");
}

wxIMPLEMENT_APP(calculadoraRegulagem);

void mainFrame::initValues()
{	
	auto* regulagem = new Regulagem;

	// Valores iniciais
	regulagem->setCult(static_cast<std::string>(choiceCult->GetString(choiceCult->GetSelection())));
	regulagem->setFormAdb(static_cast<std::string>(inForm->GetValue()));
	regulagem->setVariSmt(static_cast<std::string>(inVari->GetValue()));
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
