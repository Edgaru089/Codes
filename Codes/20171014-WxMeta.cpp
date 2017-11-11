/*
DOCUMENT CODE "WxMeta.cpp"
CREATION DATE 2017-10-14
SIGNATURE CODE_20171014_WxMeta
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171014_WxMeta

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif



class MyFrame: public wxFrame {
public:

	enum {
		Id_Login,
		Id_Register
	};

	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
		: wxFrame(NULL, wxID_ANY, title, pos, size) {
		wxStaticBoxSizer* sizer = new wxStaticBoxSizer(wxVERTICAL, this, "Login");
		sizer->Add(new wxTextCtrl(this, wxID_ANY, "Please login"), 1, wxEXPAND | wxALL, 10);
		SetSizerAndFit(sizer);
	}

private:
	void OnHello(wxCommandEvent& event) {
		wxLogMessage("Hello world from wxWidgets!");
	}
	void OnExit(wxCommandEvent& event) {
		Close(true);
	}
	void OnAbout(wxCommandEvent& event) {
		wxMessageBox("This is a wxWidgets' Hello world sample",
			"About Hello World", wxOK | wxICON_INFORMATION);
	}


	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
wxEND_EVENT_TABLE()


class MyApp: public wxApp {
public:
	virtual bool OnInit() {
		MyFrame *frame = new MyFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));
		frame->Show(true);
		return true;
	}
};

wxIMPLEMENT_APP(MyApp);

#endif
