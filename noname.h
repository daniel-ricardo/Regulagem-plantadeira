///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

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
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class frame
///////////////////////////////////////////////////////////////////////////////
class frame : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel1;
		wxStaticText* labelCultura;
		wxChoice* boxCulturas;
		wxStaticText* labelEspacamento;
		wxTextCtrl* inputEspacamento;
		wxStaticText* labelTiro;
		wxTextCtrl* inputTiro;
		wxStaticText* labelTituloSmt;
		wxStaticText* labelKghaSmt;
		wxTextCtrl* inputKghaSmt;
		wxStaticText* labelTituloResultadoSmt;
		wxStaticText* labelResultadoSmt;
		wxStaticText* labelTituloAdb;
		wxStaticText* labelKghaAdb;
		wxTextCtrl* inputKghaAdb;
		wxStaticText* labelTituloResultadoAdb;
		wxStaticText* labelResultadoAdb;
		wxStaticText* labelHectares;
		wxTextCtrl* inputHectares;
		wxStaticText* labelPrevisao;
		wxStaticText* previsão Gasto;
		wxButton* btnCalcular;

	public:

		frame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Calcular Regulagem da Plantadeira"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 550,350 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~frame();

};

