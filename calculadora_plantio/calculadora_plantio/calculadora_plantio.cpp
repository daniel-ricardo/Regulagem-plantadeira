#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/clipbrd.h>
#include <wx/bmpbuttn.h>
#include <fmt/format.h>
#include <locale>

#include "framemain_base.hpp"
#include "regulagem.hpp"

class calculadoraRegulagem : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(calculadoraRegulagem);

bool calculadoraRegulagem::OnInit()
{
    frameMain* frame = new frameMain(NULL, wxID_ANY, "Calcular Regulagem da Plantadeira", wxDefaultPosition,
        wxSize(470, 450), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER | wxTAB_TRAVERSAL, wxFrameNameStr);
    frame->Show(true);

    // TO-DO: Usar apenas uma variavel regulagem (issue #12)
    auto* regulagem = new Regulagem();

    // Valores iniciais
    regulagem->setCult("teste");
    regulagem->setFormAdb("00-00-00");
    regulagem->setVariSmt("original");
    regulagem->setGramA(calcularGramasTiro(static_cast<float>(frame->inKgAdb->GetValue()), regulagem));
    regulagem->setGramS(calcularGramasTiro(static_cast<float>(frame->inKgSmt->GetValue()), regulagem));

    // mostrando valores iniciais
    frame->inEspc->  SetValue( fmt::format("{0:.2g}", regulagem->getEspc()) );
    frame->inTiro->  SetValue( fmt::format("{0:.2g}", regulagem->getTiro()) );
    frame->inKgAdb-> SetValue( fmt::format("{0:.2g}", calcularQuilosHectare(regulagem)[1]) );
    frame->inKgSmt-> SetValue( fmt::format("{0:.2g}", calcularQuilosHectare(regulagem)[0]) );
    frame->outAdb->  SetValue( fmt::format("{0:.2f}", regulagem->getGramAdb()) );
    frame->outSmt->  SetValue( fmt::format("{0:.2f}", regulagem->getGramSmt()) );
    frame->inHa->    SetValue( fmt::format("{0:.2g}", 0.0) );
    frame->outPrv->   SetValue( fmt::format(std::locale(""), "{0} kg de semente e {1} kg de adubo",
        fmt::group_digits(frame->inHa->GetValue() * calcularQuilosHectare(regulagem)[0]),
        fmt::group_digits(frame->inHa->GetValue() * calcularQuilosHectare(regulagem)[1])) );
    return true;
}

void frameMain::fazerCalculoRegulagem(wxCommandEvent& event)
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

void frameMain::copiarAduboClipboard(wxCommandEvent& event)
{
    if (wxTheClipboard->Open())
    {
        wxTheClipboard->SetData(new wxTextDataObject(outAdb->GetValue()));
        wxTheClipboard->Close();
    }
}

void frameMain::copiarSementeClipboard(wxCommandEvent& event)
{
    if (wxTheClipboard->Open())
    {
        wxTheClipboard->SetData(new wxTextDataObject(outSmt->GetValue()));
        wxTheClipboard->Close();
    }
}

void frameMain::copiarPrevisaoClipboard(wxCommandEvent& event)
{
    if (wxTheClipboard->Open())
    {
        wxTheClipboard->SetData(new wxTextDataObject(outPrv->GetValue()));
        wxTheClipboard->Close();
    }
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
 *             + wxPanel panelOutPrv, wxBoxSizer boxOutHa (Vertical)
 *			       + wxBoxSizer boxOutPrv2 (Horizontal)
 *         + wxPanel panelBtnCalc, wxBoxSizer boxBtnCalc (Vertical)
 */

frameMain::frameMain(wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxFrame()
{
    if (!Create(parent, id, title, pos, size, style, name)) { return; }

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

    inEspc = new wxSpinCtrlDouble(panelEspc, wxID_ANY, "0.0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxTE_PROCESS_ENTER, 1.0, 1000.0, 0, 1.0, L"wxSpinCtrlDouble");
    boxEspc->Add(inEspc, wxSizerFlags().Center().Border(wxALL));
    panelEspc->SetSizerAndFit(boxEspc);

    // input tiro

    auto* panelTiro = new wxPanel(panelGeral, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxGeral->Add(panelTiro, wxSizerFlags().Center().Border(wxALL));

    auto* boxTiro = new wxBoxSizer(wxVERTICAL);

    labelTiro = new wxStaticText(panelTiro, wxID_ANY, "Tiro (m):");
    boxTiro->Add(labelTiro, wxSizerFlags().Center().Border(wxALL));

    inTiro = new wxSpinCtrlDouble(panelTiro, wxID_ANY, "0.0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxTE_PROCESS_ENTER, 1.0, 1000.0, 0, 1.0, L"wxSpinCtrlDouble");
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

    inKgSmt = new wxSpinCtrlDouble(panelInSmt, wxID_ANY, "0.0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxTE_PROCESS_ENTER, 0.0, 1000.0, 0, 1.0, L"wxSpinCtrlDouble");
    boxInKgSmt->Add(inKgSmt, wxSizerFlags().Border(wxALL));

    boxInSmt->Add(boxInKgSmt, wxSizerFlags().Border(wxALL));
    panelInSmt->SetSizerAndFit(boxInSmt);

    // output sementes

    auto* panelOutSmt = new wxPanel(panelSmt, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxSmt->Add(panelOutSmt, wxSizerFlags().Center().Border(wxALL));

    auto* boxOutSmt = new wxBoxSizer(wxVERTICAL);

    labelTituloResultadoSmt = new wxStaticText(panelOutSmt, wxID_ANY, "Gramas por tiro: (Semente)");
    boxOutSmt->Add(labelTituloResultadoSmt, wxSizerFlags().Border(wxALL));

    auto* boxOutSmt2 = new wxBoxSizer(wxHORIZONTAL);
    outSmt = new wxTextCtrl(panelOutSmt, wxID_ANY, "0.0", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    boxOutSmt2->Add(outSmt, wxSizerFlags().Right().Border(wxALL));
    btnCpSmt = new wxButton(panelOutSmt, wxID_ANY, "Copiar");
    boxOutSmt2->Add(btnCpSmt, wxSizerFlags().Right().Border(wxALL));

    boxOutSmt->Add(boxOutSmt2, wxSizerFlags().Right().Border(wxALL));

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

    inKgAdb = new wxSpinCtrlDouble(panelInAdb, wxID_ANY, "0.0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxTE_PROCESS_ENTER, 0.0, 1000.0, 0, 1.0, L"wxSpinCtrlDouble");
    boxInKgAdb->Add(inKgAdb, wxSizerFlags().Border(wxALL));

    boxInAdb->Add(boxInKgAdb, wxSizerFlags().Border(wxALL));
    panelInAdb->SetSizerAndFit(boxInAdb);

    // output adubo

    auto* panelOutAdb = new wxPanel(panelAdb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxAdb->Add(panelOutAdb, wxSizerFlags().Border(wxALL));

    auto* boxOutAdb = new wxBoxSizer(wxVERTICAL);

    labelTituloResultadoAdb = new wxStaticText(panelOutAdb, wxID_ANY, "Gramas por tiro: (Adubo)");
    boxOutAdb->Add(labelTituloResultadoAdb, wxSizerFlags().Border(wxALL));

    auto* boxOutAdb2 = new wxBoxSizer(wxHORIZONTAL);
    outAdb = new wxTextCtrl(panelOutAdb, wxID_ANY, "0.0", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    boxOutAdb2->Add(outAdb, wxSizerFlags().Right().Border(wxALL));
    btnCpAdb = new wxButton(panelOutAdb, wxID_ANY, "Copiar");
    boxOutAdb2->Add(btnCpAdb, wxSizerFlags().Right().Border(wxALL));

    boxOutAdb->Add(boxOutAdb2, wxSizerFlags().Right().Border(wxALL));

    panelOutAdb->SetSizerAndFit(boxOutAdb);
    panelAdb->SetSizerAndFit(boxAdb);

    // Painel Hectares e previsao de gasto total

    auto* panelPrv = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxMain->Add(panelPrv, wxSizerFlags().Center().Border(wxALL));

    auto* boxHa = new wxBoxSizer(wxHORIZONTAL);

    // input hectares

    auto* panelInHa = new wxPanel(panelPrv, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxSUNKEN_BORDER);
    boxHa->Add(panelInHa, wxSizerFlags().Border(wxALL));

    auto* boxInHa = new wxBoxSizer(wxVERTICAL);

    labelHectares = new wxStaticText(panelInHa, wxID_ANY, "Hectares:");
    boxInHa->Add(labelHectares, wxSizerFlags().Center().Border(wxALL));

    inHa = new wxSpinCtrlDouble(panelInHa, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxTE_PROCESS_ENTER, 0.0, 1000.0, 0.0, 1.0, L"wxSpinCtrlDouble");
    boxInHa->Add(inHa, wxSizerFlags().Border(wxALL));
    panelInHa->SetSizerAndFit(boxInHa);

    // output previsao

    auto* panelOutPrv = new wxPanel(panelPrv, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    boxHa->Add(panelOutPrv, wxSizerFlags().Border(wxALL));

    auto* boxOutPrv = new wxBoxSizer(wxVERTICAL);

    /// Palavra "Previsao:" codificada em utf8 por causa do acento
    labelPrevisao = new wxStaticText(panelOutPrv, wxID_ANY, wxString::FromUTF8("\x50\x72\x65\x76\x69\x73\xc3\xa3\x6f\x3a"));
    boxOutPrv->Add(labelPrevisao, wxSizerFlags().Center().Border(wxALL));

    auto* boxOutPrv2 = new wxBoxSizer(wxHORIZONTAL);
    outPrv = new wxTextCtrl(panelOutPrv, wxID_ANY, (fmt::format("{0} kg de semente e {1} kg de adubo", 0, 0)), wxDefaultPosition, wxSize(230, -1), wxTE_READONLY);
    boxOutPrv2->Add(outPrv, wxSizerFlags().Border(wxALL));
    btnCpPrev = new wxButton(panelOutPrv, wxID_ANY, "Copiar");
    boxOutPrv2->Add(btnCpPrev, wxSizerFlags().Border(wxALL));

    boxOutPrv->Add(boxOutPrv2, wxSizerFlags().Right().Border(wxALL));

    panelOutPrv->SetSizerAndFit(boxOutPrv);
    panelPrv->SetSizerAndFit(boxHa);

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
     *   Enter nos campos:
     *     espacamento, tiro, kg/ha semente, kg/ha adubo e hectares
     *   Copiar valores para area de transferencia:
     *     Gramas por tiro de semente e adubo, e previsao de gasto
     */
    Bind(wxEVT_BUTTON, &frameMain::fazerCalculoRegulagem, this, btnCalcular->GetId(), -1, 0);
    Bind(wxEVT_TEXT_ENTER, &frameMain::fazerCalculoRegulagem, this, inEspc->GetId(), -1, 0);
    Bind(wxEVT_TEXT_ENTER, &frameMain::fazerCalculoRegulagem, this, inTiro->GetId(), -1, 0);
    Bind(wxEVT_TEXT_ENTER, &frameMain::fazerCalculoRegulagem, this, inKgSmt->GetId(), -1, 0);
    Bind(wxEVT_TEXT_ENTER, &frameMain::fazerCalculoRegulagem, this, inKgAdb->GetId(), -1, 0);
    Bind(wxEVT_TEXT_ENTER, &frameMain::fazerCalculoRegulagem, this, inHa->GetId(), -1, 0);
    Bind(wxEVT_BUTTON, &frameMain::copiarAduboClipboard, this, btnCpAdb->GetId(), -1, 0);
    Bind(wxEVT_BUTTON, &frameMain::copiarSementeClipboard, this, btnCpSmt->GetId(), -1, 0);
    Bind(wxEVT_BUTTON, &frameMain::copiarPrevisaoClipboard, this, btnCpPrev->GetId(), -1, 0);
}

frameMain::~frameMain()
{
    /*
     * Desconectar Eventos:
     *   Botao calcular
     *   Enter nos campos:
     *     espacamento, tiro, kg/ha semente, kg/ha adubo e hectares
     *   Copiar valores para area de transferencia:
     *     Gramas por tiro de semente e adubo, e previsao de gasto
     */
    Unbind(wxEVT_BUTTON,&frameMain::fazerCalculoRegulagem, this, -1, -1, 0);
    Unbind(wxEVT_TEXT_ENTER,&frameMain::fazerCalculoRegulagem, this, -1, -1, 0);
    Unbind(wxEVT_TEXT_ENTER,&frameMain::fazerCalculoRegulagem, this, -1, -1, 0);
    Unbind(wxEVT_TEXT_ENTER,&frameMain::fazerCalculoRegulagem, this, -1, -1, 0);
    Unbind(wxEVT_TEXT_ENTER,&frameMain::fazerCalculoRegulagem, this, -1, -1, 0);
    Unbind(wxEVT_TEXT_ENTER,&frameMain::fazerCalculoRegulagem, this, -1, -1, 0);
    Unbind(wxEVT_BUTTON, &frameMain::copiarAduboClipboard, this, -1, -1, 0);
    Unbind(wxEVT_BUTTON, &frameMain::copiarSementeClipboard, this, -1, -1, 0);
    Unbind(wxEVT_BUTTON, &frameMain::copiarPrevisaoClipboard, this, -1, -1, 0);
}
