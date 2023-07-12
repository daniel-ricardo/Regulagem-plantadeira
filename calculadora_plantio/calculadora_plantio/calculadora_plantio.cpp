#include <wx/wx.h>
#include <wx/wxprec.h>
#include <format>

#include "framemain_base.hpp"
#include "regulagem.hpp"
#include "tools.hpp"

class calculadoraRegulagem : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(calculadoraRegulagem);

bool calculadoraRegulagem::OnInit()
{
    frameMain* frame = new frameMain(NULL, wxID_ANY, "Calcular Regulagem da Plantadeira", wxDefaultPosition,
        wxSize(470, 430), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER | wxTAB_TRAVERSAL, wxFrameNameStr);
    frame->Show(true);
    return true;
}

void frameMain::OnCalcularClick(wxCommandEvent& event)
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
    outAdb->SetValue( pontuarMilhares(regulagem->getGramAdb()) );
    outSmt->SetValue( pontuarMilhares(regulagem->getGramSmt()) );
    outHa->SetValue( pontuarMilhares(static_cast<float>(inHa->GetValue()) * calcularQuilosHectare(regulagem)[0]) + " kg de semente e " +
        pontuarMilhares(static_cast<float>(inHa->GetValue()) * calcularQuilosHectare(regulagem)[1]) + " kg de adubo." );
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
 *         + wxPanel panelAdb, wxBoxSizer boxAdb (Horizontal)
 *             + wxPanel panelInAdb, wxBoxSizer boxInAdb (Vertical)
 *                 + wxBoxSizer boxInKgAdb (Horizontal)
 *             + wxPanel panelOutAdb, wxBoxSizer boxOutAdb (Vertical)
 *         + wxPanel panelHa, wxBoxSizer boxHa (Horizontal)
 *             + wxPanel panelInHa, wxBoxSizer boxInHa (Vertical)
 *             + wxPanel panelOutHa, wxBoxSizer boxOutHa (Vertical)
 *         + wxPanel panelBtnCalc, wxBoxSizer boxBtnCalc (Vertical)
 */

frameMain::frameMain(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxFrame()
{
    if (!Create(parent, id, title, pos, size, style, name)) { return; }
    
    auto* regulagem = new Regulagem();

    // Definicoes painel principal

    auto* panelMain = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

    auto* boxMain = new wxBoxSizer(wxVERTICAL);

    // Painel informacoes gerais ( cultura, espacamento e tiro )

    auto* panelGeral = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxSUNKEN_BORDER);
    boxMain->Add(panelGeral, wxSizerFlags().Center().Border(wxALL));

    auto* boxGeral = new wxBoxSizer(wxHORIZONTAL);

    // input cultura

    auto* panelCult = new wxPanel(panelGeral, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxGeral->Add(panelCult, wxSizerFlags().Center().Border(wxALL));

    auto* panelSzCult = new wxBoxSizer(wxVERTICAL);

    labelCult = new wxStaticText(panelCult, wxID_ANY, "Cultura:");
    panelSzCult->Add(labelCult, wxSizerFlags().Center().Border(wxALL));

    boxCult = new wxChoice(panelCult, wxID_ANY);
    boxCult->Append("Aveia");
    boxCult->Append("Cevada");
    /// Palavra "Feijao" codificada em utf8 por causa do acento
    boxCult->Append(wxString::FromUTF8("\x46\x65\x69\x6a\xc3\xa3\x6f"));
    boxCult->Append("Milheto");
    boxCult->Append("Milho");
    boxCult->Append("Soja");
    boxCult->Append("Trigo");
    boxCult->Append("Triguilho");
    boxCult->Append("Triticalhe");
    boxCult->Append("Outro...");
    panelSzCult->Add(boxCult, wxSizerFlags().Center().Border(wxALL));
    panelCult->SetSizerAndFit(panelSzCult);

    // input espacamento

    auto* panelEspc = new wxPanel(panelGeral, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxGeral->Add(panelEspc, wxSizerFlags().Center().Border(wxALL));

    auto* boxEspc = new wxBoxSizer(wxVERTICAL);

    /// Frase "Espacamento das linhas (cm):" codificada em utf8 por causa do cedilha
    labelEspc = new wxStaticText(panelEspc, wxID_ANY, wxString::FromUTF8("\x45\x73\x70\x61\xc3\xa7\x61\x6d\x65\x6e\x74\x6f\x20\x64\x61\x73\x20\x6c\x69\x6e\x68\x61\x73\x20\x28\x63\x6d\x29\x3a"));
    boxEspc->Add(labelEspc, wxSizerFlags().Center().Border(wxALL));

    inEspc = new wxSpinCtrlDouble(panelEspc, wxID_ANY, std::to_string(regulagem->getEspc()), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0.0, 1000.0, regulagem->getEspc(), 1.0, L"wxSpinCtrlDouble");
    boxEspc->Add(inEspc, wxSizerFlags().Center().Border(wxALL));
    panelEspc->SetSizerAndFit(boxEspc);

    // input tiro

    auto* panelTiro = new wxPanel(panelGeral, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxGeral->Add(panelTiro, wxSizerFlags().Center().Border(wxALL));

    auto* boxTiro = new wxBoxSizer(wxVERTICAL);

    labelTiro = new wxStaticText(panelTiro, wxID_ANY, "Tiro (m):");
    boxTiro->Add(labelTiro, wxSizerFlags().Center().Border(wxALL));

    inTiro = new wxSpinCtrlDouble(panelTiro, wxID_ANY, std::to_string(regulagem->getTiro()), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0.0, 1000.0, regulagem->getTiro(), 1.0, L"wxSpinCtrlDouble");
    boxTiro->Add(inTiro, wxSizerFlags().Center().Border(wxALL));
    panelTiro->SetSizerAndFit(boxTiro);
    panelGeral->SetSizerAndFit(boxGeral);

    // Painel Sementes

    auto* panelSmt = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxMain->Add(panelSmt, wxSizerFlags().Center().Border(wxALL));

    auto* boxSmt = new wxBoxSizer(wxHORIZONTAL);

    // input sementes

    auto* panelInSmt = new wxPanel(panelSmt, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxSUNKEN_BORDER);
    boxSmt->Add(panelInSmt, wxSizerFlags().Expand().Border(wxALL));

    auto* boxInSmt = new wxBoxSizer(wxVERTICAL);

    tituloSmt = new wxStaticText(panelInSmt, wxID_ANY, "Semente");
    boxInSmt->Add(tituloSmt, wxSizerFlags().Center().Border(wxALL));

    auto* boxInKgSmt = new wxBoxSizer(wxHORIZONTAL);

    labelKghaSmt = new wxStaticText(panelInSmt, wxID_ANY, "Kg / Ha");
    boxInKgSmt->Add(labelKghaSmt, wxSizerFlags().Border(wxALL));

    inKgSmt = new wxSpinCtrlDouble(panelInSmt, wxID_ANY, std::to_string(regulagem->getGramSmt()), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0.0, 1000.0, regulagem->getGramSmt(), 1.0, L"wxSpinCtrlDouble");
    boxInKgSmt->Add(inKgSmt, wxSizerFlags().Border(wxALL));

    boxInSmt->Add(boxInKgSmt, wxSizerFlags().Border(wxALL));
    panelInSmt->SetSizerAndFit(boxInSmt);

    // output sementes

    auto* panelOutSmt = new wxPanel(panelSmt, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxSmt->Add(panelOutSmt, wxSizerFlags().Center().Border(wxALL));

    auto* boxOutSmt = new wxBoxSizer(wxVERTICAL);

    labelTituloResultadoSmt = new wxStaticText(panelOutSmt, wxID_ANY, "Gramas por tiro: (Semente)");
    boxOutSmt->Add(labelTituloResultadoSmt, wxSizerFlags().Border(wxALL));

    outSmt = new wxTextCtrl(panelOutSmt, wxID_ANY, std::format( "{:.2f}", static_cast<float>(calcularQuilosHectare(regulagem)[0])), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    boxOutSmt->Add(outSmt, wxSizerFlags().Right().Border(wxALL));

    panelOutSmt->SetSizerAndFit(boxOutSmt);
    panelSmt->SetSizerAndFit(boxSmt);

    // Painel Adubo

    auto* panelAdb = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxMain->Add(panelAdb, wxSizerFlags().Center().Border(wxALL));

    auto* boxAdb = new wxBoxSizer(wxHORIZONTAL);

    // input adubo

    auto* panelInAdb = new wxPanel(panelAdb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxSUNKEN_BORDER);
    boxAdb->Add(panelInAdb, wxSizerFlags().Border(wxALL));

    auto* boxInAdb = new wxBoxSizer(wxVERTICAL);

    tituloAdb = new wxStaticText(panelInAdb, wxID_ANY, "Adubo");
    boxInAdb->Add(tituloAdb, wxSizerFlags().Center().Border(wxALL));

    auto* boxInKgAdb = new wxBoxSizer(wxHORIZONTAL);

    labelKghaAdb = new wxStaticText(panelInAdb, wxID_ANY, "Kg / Ha");
    boxInKgAdb->Add(labelKghaAdb, wxSizerFlags().Border(wxALL));

    inKgAdb = new wxSpinCtrlDouble(panelInAdb, wxID_ANY, std::to_string(regulagem->getGramAdb()), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0.0, 1000.0, regulagem->getGramAdb(), 1.0, L"wxSpinCtrlDouble");
    boxInKgAdb->Add(inKgAdb, wxSizerFlags().Border(wxALL));

    boxInAdb->Add(boxInKgAdb, wxSizerFlags().Border(wxALL));
    panelInAdb->SetSizerAndFit(boxInAdb);

    // output adubo

    auto* panelOutAdb = new wxPanel(panelAdb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxAdb->Add(panelOutAdb, wxSizerFlags().Border(wxALL));

    auto* boxOutAdb = new wxBoxSizer(wxVERTICAL);

    labelTituloResultadoAdb = new wxStaticText(panelOutAdb, wxID_ANY, "Gramas por tiro: (Adubo)");
    boxOutAdb->Add(labelTituloResultadoAdb, wxSizerFlags().Border(wxALL));

    outAdb = new wxTextCtrl(panelOutAdb, wxID_ANY, std::format( "{:.2f}", static_cast<float>(calcularQuilosHectare(regulagem)[1])) , wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    boxOutAdb->Add(outAdb, wxSizerFlags().Right().Border(wxALL));
    panelOutAdb->SetSizerAndFit(boxOutAdb);
    panelAdb->SetSizerAndFit(boxAdb);

    // Painel Hectares e previsao de gasto total

    auto* panelHa = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxMain->Add(panelHa, wxSizerFlags().Center().Border(wxALL));

    auto* boxHa = new wxBoxSizer(wxHORIZONTAL);

    // input hectares

    auto* panelInHa = new wxPanel(panelHa, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxSUNKEN_BORDER);
    boxHa->Add(panelInHa, wxSizerFlags().Border(wxALL));

    auto* boxInHa = new wxBoxSizer(wxVERTICAL);

    labelHectares = new wxStaticText(panelInHa, wxID_ANY, "Hectares:");
    boxInHa->Add(labelHectares, wxSizerFlags().Center().Border(wxALL));

    inHa = new wxSpinCtrlDouble(panelInHa, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0.0, 1000.0, 0.0, 1.0, L"wxSpinCtrlDouble");
    boxInHa->Add(inHa, wxSizerFlags().Border(wxALL));
    panelInHa->SetSizerAndFit(boxInHa);

    // output previsao

    auto* panelOutHa = new wxPanel(panelHa, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxHa->Add(panelOutHa, wxSizerFlags().Border(wxALL));

    auto* boxOutHa = new wxBoxSizer(wxVERTICAL);

    /// Palavra "Previsao:" codificada em utf8 por causa do acento
    labelPrevisao = new wxStaticText(panelOutHa, wxID_ANY, wxString::FromUTF8("\x50\x72\x65\x76\x69\x73\xc3\xa3\x6f\x3a"));
    boxOutHa->Add(labelPrevisao, wxSizerFlags().Center().Border(wxALL));

    outHa = new wxTextCtrl(panelOutHa, wxID_ANY, std::format("{:.2f} kg de semente e {:.2f} kg de adubo.", 0.0, 0.0), wxDefaultPosition, wxSize(300, -1), wxTE_READONLY);
    boxOutHa->Add(outHa, wxSizerFlags().Border(wxALL));
    panelOutHa->SetSizerAndFit(boxOutHa);
    panelHa->SetSizerAndFit(boxHa);

    // Painel Botao calcular

    auto* panelBtnCalc = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxMain->Add(panelBtnCalc, wxSizerFlags().Right().Bottom().Border(wxALL));

    auto* boxBtnCalc = new wxBoxSizer(wxVERTICAL);

    btnCalcular = new wxButton(panelBtnCalc, wxID_ANY, "Calcular");
    boxBtnCalc->Add(btnCalcular, wxSizerFlags().Center().Right().Border(wxALL));
    panelBtnCalc->SetSizerAndFit(boxBtnCalc);
    panelMain->SetSizerAndFit(boxMain);

    Centre(wxBOTH);

    /*
     * Conectar Eventos:
     *   Botao calcular
     */

    btnCalcular->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(frameMain::OnCalcularClick), NULL, this);
}

frameMain::~frameMain()
{
    /*
     * Desconectar Eventos:
     *   Botao calcular
     */
    delete regulagem;
    btnCalcular->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(frameMain::OnCalcularClick), NULL, this);

}

