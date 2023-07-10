///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

frame::frame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxFlexGridSizer* gridPrincipal;
	gridPrincipal = new wxFlexGridSizer( 1, 1, 0, 0 );
	gridPrincipal->SetFlexibleDirection( wxBOTH );
	gridPrincipal->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxGridSizer* gridMain;
	gridMain = new wxGridSizer( 5, 2, 0, 0 );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	labelCultura = new wxStaticText( m_panel1, wxID_ANY, wxT("Cultura: "), wxDefaultPosition, wxDefaultSize, 0 );
	labelCultura->Wrap( -1 );
	bSizer1->Add( labelCultura, 0, wxALIGN_CENTER|wxALL, 5 );

	wxString boxCulturasChoices[] = { wxT("Aveia"), wxT("Cevada"), wxT("Feijão"), wxT("Milheto"), wxT("Milho"), wxT("Soja"), wxT("Trigo"), wxT("Triguilho"), wxT("Triticalhe"), wxT("Outro...") };
	int boxCulturasNChoices = sizeof( boxCulturasChoices ) / sizeof( wxString );
	boxCulturas = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, boxCulturasNChoices, boxCulturasChoices, 0 );
	boxCulturas->SetSelection( 10 );
	bSizer1->Add( boxCulturas, 0, wxALIGN_CENTER|wxALL, 5 );


	m_panel1->SetSizer( bSizer1 );
	m_panel1->Layout();
	bSizer1->Fit( m_panel1 );
	gridMain->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );

	wxGridSizer* gridEspacamento;
	gridEspacamento = new wxGridSizer( 1, 2, 0, 0 );

	labelEspacamento = new wxStaticText( this, wxID_ANY, wxT("Espaçamento das linhas:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelEspacamento->Wrap( -1 );
	gridEspacamento->Add( labelEspacamento, 0, wxALIGN_CENTER|wxALL, 5 );

	inputEspacamento = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gridEspacamento->Add( inputEspacamento, 0, wxALIGN_CENTER|wxALL, 5 );


	gridMain->Add( gridEspacamento, 1, wxEXPAND|wxALL, 5 );

	wxGridSizer* gridTiro;
	gridTiro = new wxGridSizer( 1, 2, 0, 0 );

	labelTiro = new wxStaticText( this, wxID_ANY, wxT("Tiro:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelTiro->Wrap( -1 );
	gridTiro->Add( labelTiro, 0, wxALIGN_CENTER|wxALL, 5 );

	inputTiro = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gridTiro->Add( inputTiro, 0, wxALIGN_CENTER|wxALL, 5 );


	gridMain->Add( gridTiro, 1, wxEXPAND, 5 );

	wxGridSizer* gridInputSmt;
	gridInputSmt = new wxGridSizer( 2, 2, 0, 0 );

	labelTituloSmt = new wxStaticText( this, wxID_ANY, wxT("Semente"), wxDefaultPosition, wxDefaultSize, 0 );
	labelTituloSmt->Wrap( -1 );
	gridInputSmt->Add( labelTituloSmt, 0, wxALIGN_CENTER|wxALL, 5 );


	gridInputSmt->Add( 0, 0, 1, wxEXPAND, 5 );

	labelKghaSmt = new wxStaticText( this, wxID_ANY, wxT("Kg / Ha"), wxDefaultPosition, wxDefaultSize, 0 );
	labelKghaSmt->Wrap( -1 );
	gridInputSmt->Add( labelKghaSmt, 0, wxALL, 5 );

	inputKghaSmt = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gridInputSmt->Add( inputKghaSmt, 0, wxALL, 5 );


	gridMain->Add( gridInputSmt, 1, wxALIGN_CENTER|wxALL, 5 );

	wxGridSizer* gridResultadoSmt;
	gridResultadoSmt = new wxGridSizer( 2, 1, 0, 0 );

	labelTituloResultadoSmt = new wxStaticText( this, wxID_ANY, wxT("Gramas por tiro: (Semente)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelTituloResultadoSmt->Wrap( -1 );
	gridResultadoSmt->Add( labelTituloResultadoSmt, 0, wxALL, 5 );

	labelResultadoSmt = new wxStaticText( this, wxID_ANY, wxT("1234567890"), wxDefaultPosition, wxDefaultSize, 0 );
	labelResultadoSmt->Wrap( -1 );
	gridResultadoSmt->Add( labelResultadoSmt, 0, wxALL, 5 );


	gridMain->Add( gridResultadoSmt, 1, wxEXPAND, 5 );

	wxGridSizer* gridInputAdb;
	gridInputAdb = new wxGridSizer( 2, 2, 0, 0 );

	labelTituloAdb = new wxStaticText( this, wxID_ANY, wxT("Adubo"), wxDefaultPosition, wxDefaultSize, 0 );
	labelTituloAdb->Wrap( -1 );
	gridInputAdb->Add( labelTituloAdb, 0, wxALIGN_CENTER|wxALL, 5 );


	gridInputAdb->Add( 0, 0, 1, wxEXPAND, 5 );

	labelKghaAdb = new wxStaticText( this, wxID_ANY, wxT("Kg / Ha"), wxDefaultPosition, wxDefaultSize, 0 );
	labelKghaAdb->Wrap( -1 );
	gridInputAdb->Add( labelKghaAdb, 0, wxALL, 5 );

	inputKghaAdb = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gridInputAdb->Add( inputKghaAdb, 0, wxALL, 5 );


	gridMain->Add( gridInputAdb, 1, wxALIGN_CENTER|wxALL, 5 );

	wxGridSizer* gridResultadoAdb;
	gridResultadoAdb = new wxGridSizer( 2, 1, 0, 0 );

	labelTituloResultadoAdb = new wxStaticText( this, wxID_ANY, wxT("Gramas por tiro: (Adubo)"), wxDefaultPosition, wxDefaultSize, 0 );
	labelTituloResultadoAdb->Wrap( -1 );
	gridResultadoAdb->Add( labelTituloResultadoAdb, 0, wxALL, 5 );

	labelResultadoAdb = new wxStaticText( this, wxID_ANY, wxT("1234567890"), wxDefaultPosition, wxDefaultSize, 0 );
	labelResultadoAdb->Wrap( -1 );
	gridResultadoAdb->Add( labelResultadoAdb, 0, wxALL, 5 );


	gridMain->Add( gridResultadoAdb, 1, wxEXPAND, 5 );

	wxGridSizer* gridPrevisao;
	gridPrevisao = new wxGridSizer( 2, 2, 0, 0 );

	labelHectares = new wxStaticText( this, wxID_ANY, wxT("Hectares:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelHectares->Wrap( -1 );
	gridPrevisao->Add( labelHectares, 0, wxALL, 5 );

	inputHectares = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gridPrevisao->Add( inputHectares, 0, wxALL, 5 );

	labelPrevisao = new wxStaticText( this, wxID_ANY, wxT("Previsão:"), wxDefaultPosition, wxDefaultSize, 0 );
	labelPrevisao->Wrap( -1 );
	gridPrevisao->Add( labelPrevisao, 0, wxALL, 5 );

	previsão Gasto = new wxStaticText( this, wxID_ANY, wxT("01234567890"), wxDefaultPosition, wxDefaultSize, 0 );
	previsão Gasto->Wrap( -1 );
	gridPrevisao->Add( previsão Gasto, 0, wxALL, 5 );


	gridMain->Add( gridPrevisao, 1, wxEXPAND, 5 );

	btnCalcular = new wxButton( this, wxID_ANY, wxT("Calcular"), wxDefaultPosition, wxDefaultSize, 0 );
	gridMain->Add( btnCalcular, 0, wxALIGN_CENTER|wxALL, 5 );


	gridPrincipal->Add( gridMain, 1, wxEXPAND, 5 );


	this->SetSizer( gridPrincipal );
	this->Layout();

	this->Centre( wxBOTH );
}

frame::~frame()
{
}
