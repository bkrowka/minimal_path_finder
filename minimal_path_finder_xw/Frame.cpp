#include "Frame.h"

Frame::Frame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	WindowLayout();
}

void Frame::CreateControls()
{
	panel = new wxPanel(this);

	labelFilename = new wxStaticText(panel, wxID_ANY, wxT("Nazwa pliku:"));
	textCtrlFilename = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	buttonLoad = new wxButton(panel, wxID_ANY, wxT("Wczytaj"));

	labelRows = new wxStaticText(panel, wxID_ANY, wxT("Liczba wierszy:"));
	textCtrlRows = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1), 0, wxTextValidator(wxFILTER_DIGITS));
	labelCols = new wxStaticText(panel, wxID_ANY, wxT("Liczba kolumn:"));
	textCtrlCols = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1), 0, wxTextValidator(wxFILTER_DIGITS));

	labelRange = new wxStaticText(panel, wxID_ANY, wxT("Zakres:"));
	textCtrlRange1 = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(50, -1));
	textCtrlRange2 = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(50, -1));
	buttonRand = new wxButton(panel, wxID_ANY, wxT("Losuj"));

	line = new wxStaticLine(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);

	grid = nullptr;
	buttonAddRow = nullptr;
	buttonDelRow = nullptr;
	buttonAddCol = nullptr;
	buttonDelCol = nullptr;
	buttonsColSizer = nullptr;
	horizontalSizer = nullptr;
	buttonCalculate = nullptr;
	scrollWindow = nullptr;
	labelResult = nullptr;
	scrollSizer = nullptr;
	buttonPreviousPath = nullptr;
	buttonNextPath = nullptr;
	buttonsPathSizer = nullptr;
}

void Frame::WindowLayout()
{
	vBoxSizer = new wxBoxSizer(wxVERTICAL);
	vBoxSizer->Add(labelFilename, 0, wxLEFT | wxTOP, 5);
	vBoxSizer->Add(textCtrlFilename, 0, wxLEFT | wxTOP, 5);
	vBoxSizer->Add(buttonLoad, 0, wxLEFT | wxTOP, 5);

	vBoxSizer->AddSpacer(100);
	vBoxSizer->Add(labelRows, 0, wxLEFT, 5);
	vBoxSizer->Add(textCtrlRows, 0, wxLEFT | wxTOP, 5);
	vBoxSizer->Add(labelCols, 0, wxLEFT | wxTOP, 5);
	vBoxSizer->Add(textCtrlCols, 0, wxLEFT | wxTOP, 5);
	vBoxSizer->Add(labelRange, 0, wxLEFT | wxTOP, 5);	
	
	hBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	hBoxSizer->Add(textCtrlRange1, 0, wxLEFT | wxTOP, 0);
	hBoxSizer->Add(textCtrlRange2, 0, wxLEFT | wxTOP, 0);	
	vBoxSizer->Add(hBoxSizer, 0, wxLEFT | wxTOP, 5);
	vBoxSizer->Add(buttonRand, 0, wxALL, 5);

	mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(vBoxSizer, 0, wxALL, 5);
	mainSizer->Add(line, 0, wxEXPAND | wxLEFT, 5);

	panel->SetSizer(mainSizer);
}