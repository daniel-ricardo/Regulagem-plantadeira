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
        wxSize(470, 500), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER | wxTAB_TRAVERSAL, wxFrameNameStr);

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
    	fmt::group_digits(*ha * calcularQuilosHectare(regulagem)[0]),
        fmt::group_digits(*ha * calcularQuilosHectare(regulagem)[1])) );
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

    auto* panelInsumos = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer->Add(panelInsumos, wxSizerFlags().Border(wxALL));

    auto* box_sizer_2 = new wxBoxSizer(wxHORIZONTAL);

    auto* panelTalh = new wxPanel(panelInsumos, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer_2->Add(panelTalh, wxSizerFlags(1).Border(wxALL));

    auto* box_sizer_3 = new wxBoxSizer(wxVERTICAL);

    labelTalh = new wxStaticText(panelTalh, wxID_ANY, wxString::FromUTF8("Talh�o:"));
    box_sizer_3->Add(labelTalh, wxSizerFlags().Border(wxALL));

    inTalh = new wxTextCtrl(panelTalh, wxID_ANY, wxEmptyString);
    box_sizer_3->Add(inTalh, wxSizerFlags().Border(wxALL));
    panelTalh->SetSizerAndFit(box_sizer_3);

    auto* panelCult = new wxPanel(panelInsumos, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelCult->SetToolTip("Selecione qual Cultura de Sementes vai ser plantada");
    box_sizer_2->Add(panelCult, wxSizerFlags().Border(wxALL));

    auto* box_sizer_4 = new wxBoxSizer(wxVERTICAL);

    labelCult = new wxStaticText(panelCult, wxID_ANY, "Cultura:");
    labelCult->SetToolTip("Selecione qual Cultura de Sementes vai ser plantada");
    box_sizer_4->Add(labelCult, wxSizerFlags().Border(wxALL));

    choiceCult = new wxChoice(panelCult, wxID_ANY);
    choiceCult->Append("Aveia");
    choiceCult->Append("Cevada");
    choiceCult->Append(wxString::FromUTF8("Feij�o"));
    choiceCult->Append("Milheto");
    choiceCult->Append("Milho");
    choiceCult->Append("Soja");
    choiceCult->Append("Trigo");
    choiceCult->Append("Triguilho");
    choiceCult->Append("Triticalhe");
    choiceCult->Append("Outro...");
    choiceCult->SetToolTip("Selecione qual Cultura de Sementes vai ser plantada");
    box_sizer_4->Add(choiceCult, wxSizerFlags().Border(wxALL));
    panelCult->SetSizerAndFit(box_sizer_4);

    auto* panelVari = new wxPanel(panelInsumos, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer_2->Add(panelVari, wxSizerFlags(1).Border(wxALL));

    auto* box_sizer_5 = new wxBoxSizer(wxVERTICAL);

    labelVari = new wxStaticText(panelVari, wxID_ANY, "Variedade:");
    box_sizer_5->Add(labelVari, wxSizerFlags().Border(wxALL));

    inVari = new wxTextCtrl(panelVari, wxID_ANY, wxEmptyString);
    box_sizer_5->Add(inVari, wxSizerFlags().Border(wxALL));
    panelVari->SetSizerAndFit(box_sizer_5);

    auto* panelForm = new wxPanel(panelInsumos, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer_2->Add(panelForm, wxSizerFlags(1).Border(wxALL));

    auto* box_sizer_6 = new wxBoxSizer(wxVERTICAL);

    labelForm = new wxStaticText(panelForm, wxID_ANY, wxString::FromUTF8("F�rmula"));
    box_sizer_6->Add(labelForm, wxSizerFlags().Border(wxALL));

    inForm = new wxTextCtrl(panelForm, wxID_ANY, wxEmptyString);
    box_sizer_6->Add(inForm, wxSizerFlags().Border(wxALL));
    panelForm->SetSizerAndFit(box_sizer_6);
    panelInsumos->SetSizerAndFit(box_sizer_2);

    auto* panelConf = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer->Add(panelConf, wxSizerFlags().Border(wxALL));

    auto* box_sizer_7 = new wxBoxSizer(wxHORIZONTAL);

    auto* panelEspc = new wxPanel(panelConf, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelEspc->SetToolTip(wxString::FromUTF8("Coloque o espa�amento das linhas (em cent�metros)"));
    box_sizer_7->Add(panelEspc, wxSizerFlags().Border(wxALL));

    auto* box_sizer_8 = new wxBoxSizer(wxVERTICAL);

    labelEspc = new wxStaticText(panelEspc, wxID_ANY, wxString::FromUTF8("Espa�amento das linhas (cm):"));
    labelEspc->SetToolTip(wxString::FromUTF8("Coloque o espa�amento das linhas (em cent�metros)"));
    box_sizer_8->Add(labelEspc, wxSizerFlags().Border(wxALL));

    inEspc = new wxSpinCtrlDouble(panelEspc, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxALIGN_RIGHT, 1, 1000, 0, 1);
    inEspc->SetToolTip(wxString::FromUTF8("Coloque o espa�amento das linhas (em cent�metros)"));
    box_sizer_8->Add(inEspc, wxSizerFlags().Border(wxALL));
    panelEspc->SetSizerAndFit(box_sizer_8);

    auto* panelTiro = new wxPanel(panelConf, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelTiro->SetToolTip(wxString::FromUTF8("Coloque o comprimento da �rea de regulagem em metros"));
    box_sizer_7->Add(panelTiro, wxSizerFlags().Border(wxALL));

    auto* box_sizer_9 = new wxBoxSizer(wxVERTICAL);

    labelTiro = new wxStaticText(panelTiro, wxID_ANY, "Tiro (m):");
    labelTiro->SetToolTip(wxString::FromUTF8("Coloque o comprimento da �rea de regulagem em metros"));
    box_sizer_9->Add(labelTiro, wxSizerFlags().Border(wxALL));

    inTiro = new wxSpinCtrlDouble(panelTiro, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxSP_ARROW_KEYS, 1, 1000, 0, 1);
    inTiro->SetToolTip(wxString::FromUTF8("Coloque o comprimento da �rea de regulagem em metros"));
    box_sizer_9->Add(inTiro, wxSizerFlags().Border(wxALL));
    panelTiro->SetSizerAndFit(box_sizer_9);
    panelConf->SetSizerAndFit(box_sizer_7);

    auto* panelSmt = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer->Add(panelSmt, wxSizerFlags().Border(wxALL));

    auto* box_sizer_10 = new wxBoxSizer(wxHORIZONTAL);

    auto* panelInSmt = new wxPanel(panelSmt, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelInSmt->SetToolTip("Alvo de semente em quilos por hectare");
    box_sizer_10->Add(panelInSmt, wxSizerFlags().Border(wxALL));

    auto* box_sizer_11 = new wxBoxSizer(wxVERTICAL);

    tituloSmt = new wxStaticText(panelInSmt, wxID_ANY, "Semente");
    tituloSmt->SetToolTip("Alvo de semente em quilos por hectare");
    box_sizer_11->Add(tituloSmt, wxSizerFlags().Border(wxALL));

    auto* box_sizer_12 = new wxBoxSizer(wxHORIZONTAL);

    labelKghaSmt = new wxStaticText(panelInSmt, wxID_ANY, "Kg / Ha");
    labelKghaSmt->SetToolTip("Alvo de semente em quilos por hectare");
    box_sizer_12->Add(labelKghaSmt, wxSizerFlags().Border(wxALL));

    inKgSmt = new wxSpinCtrlDouble(panelInSmt, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxSP_ARROW_KEYS, 0, 1000, 0, 1);
    inKgSmt->SetToolTip("Alvo de semente em quilos por hectare");
    box_sizer_12->Add(inKgSmt, wxSizerFlags().Border(wxALL));

    box_sizer_11->Add(box_sizer_12, wxSizerFlags(1).Border(wxALL));
    panelInSmt->SetSizerAndFit(box_sizer_11);

    auto* panelOutSmt = new wxPanel(panelSmt, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelOutSmt->SetToolTip(
        "A quantidade de gramas de semente por tiro que deve cair para a plantadeira estar regulada");
    box_sizer_10->Add(panelOutSmt, wxSizerFlags().Border(wxALL));

    auto* box_sizer_13 = new wxBoxSizer(wxVERTICAL);

    labelTituloResultadoSmt = new wxStaticText(panelOutSmt, wxID_ANY, "Gramas por tiro: (Semente)");
    box_sizer_13->Add(labelTituloResultadoSmt, wxSizerFlags().Border(wxALL));

    auto* box_sizer_14 = new wxBoxSizer(wxHORIZONTAL);

    outSmt = new wxTextCtrl(panelOutSmt, wxID_ANY, "0.0", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    outSmt->SetToolTip(
        "A quantidade de gramas de semente por tiro que deve cair para a plantadeira estar regulada");
    box_sizer_14->Add(outSmt, wxSizerFlags().Border(wxALL));

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
    box_sizer_14->Add(btnCpSmt, wxSizerFlags().Border(wxALL));

    box_sizer_13->Add(box_sizer_14, wxSizerFlags().Border(wxALL));
    panelOutSmt->SetSizerAndFit(box_sizer_13);
    panelSmt->SetSizerAndFit(box_sizer_10);

    auto* panelAdb = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer->Add(panelAdb, wxSizerFlags().Border(wxALL));

    auto* box_sizer_15 = new wxBoxSizer(wxHORIZONTAL);

    auto* panelInAdb = new wxPanel(panelAdb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelInAdb->SetToolTip("Alvo de adubo em quilos por hectare");
    box_sizer_15->Add(panelInAdb, wxSizerFlags().Border(wxALL));

    auto* box_sizer_16 = new wxBoxSizer(wxVERTICAL);

    tituloAdb = new wxStaticText(panelInAdb, wxID_ANY, "Adubo");
    tituloAdb->SetToolTip("Alvo de adubo em quilos por hectare");
    box_sizer_16->Add(tituloAdb, wxSizerFlags().Border(wxALL));

    auto* box_sizer_17 = new wxBoxSizer(wxHORIZONTAL);

    labelKghaAdb = new wxStaticText(panelInAdb, wxID_ANY, "Kg / Ha");
    labelKghaAdb->SetToolTip("Alvo de adubo em quilos por hectare");
    box_sizer_17->Add(labelKghaAdb, wxSizerFlags().Border(wxALL));

    inKgAdb = new wxSpinCtrlDouble(panelInAdb, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxSP_ARROW_KEYS, 0, 1000, 0, 1);
    inKgAdb->SetToolTip("Alvo de adubo em quilos por hectare");
    box_sizer_17->Add(inKgAdb, wxSizerFlags().Border(wxALL));

    box_sizer_16->Add(box_sizer_17, wxSizerFlags().Border(wxALL));
    panelInAdb->SetSizerAndFit(box_sizer_16);

    auto* panelOutAdb = new wxPanel(panelAdb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelOutAdb->SetToolTip(
        "A quantidade de gramas de adubo por tiro que deve cair para a plantadeira estar regulada");
    box_sizer_15->Add(panelOutAdb, wxSizerFlags().Border(wxALL));

    auto* box_sizer_18 = new wxBoxSizer(wxVERTICAL);

    labelTituloResultadoAdb = new wxStaticText(panelOutAdb, wxID_ANY, "Gramas por tiro: (Adubo)");
    labelTituloResultadoAdb->SetToolTip(
        "A quantidade de gramas de adubo por tiro que deve cair para a plantadeira estar regulada");
    box_sizer_18->Add(labelTituloResultadoAdb, wxSizerFlags().Border(wxALL));

    auto* box_sizer_19 = new wxBoxSizer(wxHORIZONTAL);

    outAdb = new wxTextCtrl(panelOutAdb, wxID_ANY, "0.0", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    outAdb->SetToolTip(
        "A quantidade de gramas de adubo por tiro que deve cair para a plantadeira estar regulada");
    box_sizer_19->Add(outAdb, wxSizerFlags().Border(wxALL));

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
    box_sizer_19->Add(btnCpAdb, wxSizerFlags().Border(wxALL));

    box_sizer_18->Add(box_sizer_19, wxSizerFlags().Border(wxALL));
    panelOutAdb->SetSizerAndFit(box_sizer_18);
    panelAdb->SetSizerAndFit(box_sizer_15);

    auto* panelPrv = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer->Add(panelPrv, wxSizerFlags().Border(wxALL));

    auto* box_sizer_20 = new wxBoxSizer(wxHORIZONTAL);

    auto* panelInHa = new wxPanel(panelPrv, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelInHa->SetToolTip("Quantos hectares planeja serem plantados");
    box_sizer_20->Add(panelInHa, wxSizerFlags().Border(wxALL));

    auto* box_sizer_21 = new wxBoxSizer(wxVERTICAL);

    labelHa = new wxStaticText(panelInHa, wxID_ANY, "Hectares:");
    labelHa->SetToolTip("Quantos hectares planeja serem plantados");
    box_sizer_21->Add(labelHa, wxSizerFlags().Border(wxALL));

    inHa = new wxSpinCtrlDouble(panelInHa, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxSP_ARROW_KEYS, 0, 1000, 0, 1);
    inHa->SetToolTip("Quantos hectares planeja serem plantados");
    box_sizer_21->Add(inHa, wxSizerFlags().Border(wxALL));
    panelInHa->SetSizerAndFit(box_sizer_21);

    auto* panelOutPrv = new wxPanel(panelPrv, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelOutPrv->SetToolTip(wxString::FromUTF8("Gasto de insumos previsto segundo a �rea planejada"));
    box_sizer_20->Add(panelOutPrv, wxSizerFlags().Border(wxALL));

    auto* box_sizer_22 = new wxBoxSizer(wxVERTICAL);

    labelPrv = new wxStaticText(panelOutPrv, wxID_ANY, wxString::FromUTF8("Previs�o:"));
    labelPrv->SetToolTip(wxString::FromUTF8("Gasto de insumos previsto segundo a �rea planejada"));
    box_sizer_22->Add(labelPrv, wxSizerFlags().Border(wxALL));

    auto* box_sizer_23 = new wxBoxSizer(wxHORIZONTAL);

    outPrv = new wxTextCtrl(panelOutPrv, wxID_ANY, "0 kg de semente e 0 kg de adubo", wxDefaultPosition,
        wxSize(280, -1), wxTE_READONLY);
    outPrv->SetToolTip(wxString::FromUTF8("Gasto de insumos previsto segundo a �rea planejada"));
    box_sizer_23->Add(outPrv, wxSizerFlags().Border(wxALL));

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
    btnCpPrv->SetToolTip(wxString::FromUTF8("Copiar previs�o de gasto de insumos"));
    box_sizer_23->Add(btnCpPrv, wxSizerFlags().Border(wxALL));

    box_sizer_22->Add(box_sizer_23, wxSizerFlags().Border(wxALL));
    panelOutPrv->SetSizerAndFit(box_sizer_22);
    panelPrv->SetSizerAndFit(box_sizer_20);

    auto* panelBtnCalc = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    box_sizer->Add(panelBtnCalc, wxSizerFlags().Border(wxALL));

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
    box_sizer_24->Add(btnCalc, wxSizerFlags().Border(wxALL));
    panelBtnCalc->SetSizerAndFit(box_sizer_24);
    panelMain->SetSizerAndFit(box_sizer);


    Centre(wxBOTH);
}

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

