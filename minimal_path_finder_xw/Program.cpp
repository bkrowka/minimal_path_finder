#include "Program.h"

Program::Program(const wxString& title) : Frame(title), matrix(0, 0)
{
	SetClientSize(1600, 900);
	SetMinSize(wxSize(800, 600));
	SetMaxSize(wxSize(1920, 1080));
	Show(true);
	BindEventHandlers();
}

void Program::BindEventHandlers()
{
	buttonLoad->Bind(wxEVT_BUTTON, &Program::OnButtonLoadClicked, this);
	buttonRand->Bind(wxEVT_BUTTON, &Program::OnButtonRandClicked, this);
}

void Program::OnButtonLoadClicked(wxCommandEvent& evt)
{
	wxString wx_filename = textCtrlFilename->GetValue();
	filename = wx_filename.mb_str();

	matrix = dl.load(filename);
	if (matrix.getRows() == 0 || matrix.getCols() == 0)
	{
		wxMessageBox(wxT("B³¹d wczytywania macierzy"), wxT("B³¹d"), wxOK | wxICON_ERROR, this);
	}
	else
	{
		CreateGrid();
	}
}

void Program::OnButtonRandClicked(wxCommandEvent& evt)
{
	filename.clear();
	wxString wx_textCtrlRows = textCtrlRows->GetValue();
	wxString wx_textCtrlCols = textCtrlCols->GetValue();
	wxString wx_textCtrlRange1 = textCtrlRange1->GetValue();
	wxString wx_textCtrlRange2 = textCtrlRange2->GetValue();

	if (!(wx_textCtrlRows.IsEmpty() || wx_textCtrlCols.IsEmpty() || wx_textCtrlRange1.IsEmpty() || wx_textCtrlRange2.IsEmpty()))
	{
		int rows, cols, min, max;

		if (wx_textCtrlRows.ToInt(&rows) && wx_textCtrlCols.ToInt(&cols) && wx_textCtrlRange1.ToInt(&min) && wx_textCtrlRange2.ToInt(&max))
		{
			if (rows <= 100 && cols <= 100 && min >= -1000 && max <= 1000)
			{
				matrix = dl.random(rows, cols, min, max);
				if (matrix.getRows() == 0 || matrix.getCols() == 0)
				{
					wxMessageBox(wxT("B³êdne parametry losowania."), wxT("B³¹d"), wxOK | wxICON_ERROR, this);
				}
				else
				{
					CreateGrid();
				}
			}
			else
				wxMessageBox(wxT("Parametry losowania niezgodne z wymaganiami programu."), wxT("B³¹d"), wxOK | wxICON_ERROR, this);
		}
		else
		{
			wxMessageBox(wxT("B³êdne parametry losowania."), wxT("B³¹d"), wxOK | wxICON_ERROR, this);
		}
	}
	else
	{
		wxMessageBox(wxT("Wype³nij pola parametrów."), wxT("Komunikat"), wxOK | wxICON_INFORMATION, this);
	}
}

void Program::CreateGrid()
{
	if (grid) {
		ClearSpace();
	}
	grid = new wxGrid(panel, wxID_ANY);
	grid->CreateGrid(matrix.getRows(), matrix.getCols());

	for (int i = 0; i < matrix.getRows(); ++i) {
		for (int j = 0; j < matrix.getCols(); ++j) {
			wxString label = wxString::Format(wxT("%d"), j + 1);
			grid->SetColLabelValue(j, label);
			grid->SetCellValue(i, j, wxString::Format(wxT("%d"), matrix.get(i, j)));
		}
	}

	grid->AutoSize();
	grid->SetMaxSize(wxSize(1280, 720));

	buttonDelCol = new wxButton(panel, wxID_ANY, wxT("-"));
	buttonDelCol->SetMinSize(wxSize(25, 25));
	buttonDelCol->Bind(wxEVT_BUTTON, &Program::OnButtonDelColClicked, this);

	buttonAddCol = new wxButton(panel, wxID_ANY, wxT("+"));
	buttonAddCol->SetMinSize(wxSize(25, 25));
	buttonAddCol->Bind(wxEVT_BUTTON, &Program::OnButtonAddColClicked, this);

	matrixSizer = new wxBoxSizer(wxVERTICAL);

	buttonDelRow = new wxButton(panel, wxID_ANY, wxT("-"));
	buttonDelRow->SetMinSize(wxSize(25, 25));
	buttonDelRow->Bind(wxEVT_BUTTON, &Program::OnButtonDelRowClicked, this);

	buttonAddRow = new wxButton(panel, wxID_ANY, wxT("+"));
	buttonAddRow->SetMinSize(wxSize(25, 25));
	buttonAddRow->Bind(wxEVT_BUTTON, &Program::OnButtonAddRowClicked, this);

	buttonCalculate = new wxButton(panel, wxID_ANY, wxT("Oblicz"));
	buttonCalculate->Bind(wxEVT_BUTTON, &Program::OnButtonCalculateClicked, this);

	matrixSizer->Add(grid, 1, wxALL, 5);
	matrixSizer->Add(buttonDelRow, 0, wxLEFT, 5);
	matrixSizer->Add(buttonAddRow, 0, wxLEFT, 5);
	matrixSizer->AddSpacer(10);
	matrixSizer->Add(buttonCalculate, 0, wxLEFT, 5);

	buttonsColSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonsColSizer->Add(buttonDelCol, 0, wxTOP, 5);
	buttonsColSizer->Add(buttonAddCol, 0, wxTOP, 5);

	horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	horizontalSizer->Add(matrixSizer, 1, wxALL, 0);
	horizontalSizer->Add(buttonsColSizer, 0, wxALL, 5);

	mainSizer->Add(horizontalSizer, 0, wxALL, 0);

	panel->Layout();
}

void Program::ClearSpace()
{
	ClearResult();
	delete buttonCalculate;
	buttonCalculate = nullptr;
	delete buttonAddRow;
	buttonAddRow = nullptr;
	delete buttonDelRow;
	buttonDelRow = nullptr;
	delete buttonAddCol;
	buttonAddCol = nullptr;
	delete buttonDelCol;
	buttonDelCol = nullptr;
	delete grid;
	grid = nullptr;
}

void Program::ClearResult()
{
	delete buttonNextPath;
	buttonNextPath = nullptr;
	delete buttonPreviousPath;
	buttonPreviousPath = nullptr;
	delete labelResult;
	labelResult = nullptr;
	delete scrollWindow;
	scrollWindow = nullptr;
}

void Program::OnButtonDelRowClicked(wxCommandEvent& evt)
{
	if (grid->GetNumberRows() > 1) 
	{
		if (labelResult)
			ClearResult();

		grid->DeleteRows(grid->GetNumberRows() - 1);
		matrix.delRow();
	}
	grid->ForceRefresh();
	panel->Layout();
}

void Program::OnButtonAddRowClicked(wxCommandEvent& evt)
{
	if (grid->GetNumberRows() < 100)
	{
		if (labelResult)
			ClearResult();

		grid->AppendRows(1);
		matrix.addRow();
		grid->ForceRefresh();
		panel->Layout();
	}
	else
		wxMessageBox(wxT("Osi¹gniêto limit liczby wierszy."), wxT("Komunikat"), wxOK | wxICON_INFORMATION, this);
}

void Program::OnButtonAddColClicked(wxCommandEvent& evt)
{
	if (grid->GetNumberCols() < 100)
	{
		if (labelResult)
			ClearResult();

		grid->AppendCols(1);
		int col = grid->GetNumberCols() - 1;
		wxString label = wxString::Format(wxT("%d"), col + 1);
		grid->SetColLabelValue(col, label);
		grid->AutoSize();
		matrix.addCol();
		grid->ForceRefresh();
		panel->Layout();
	}
	else
		wxMessageBox(wxT("Osi¹gniêto limit liczby kolumn."), wxT("Komunikat"), wxOK | wxICON_INFORMATION, this);
}

void Program::OnButtonDelColClicked(wxCommandEvent& evt)
{
	if (grid->GetNumberCols() > 1) 
	{
		if (labelResult)
			ClearResult();
		grid->DeleteCols(grid->GetNumberCols() - 1);
		matrix.delCol();
	}
	grid->AutoSize();
	grid->ForceRefresh();
	panel->Layout();
}

void Program::OnButtonCalculateClicked(wxCommandEvent& evt)
{
	pathIndex = 0;
	if (loadFromGrid())
	{
		if (labelResult)
		{
			delete labelResult;
			labelResult = nullptr;
			delete scrollWindow;
			scrollWindow = nullptr;
			delete buttonPreviousPath;
			buttonPreviousPath = nullptr;
			delete buttonNextPath;
			buttonNextPath = nullptr;
		}

		mp.calculate(matrix);
		CreateResult();
		visualize();
		if (!filename.empty())
		{ 
			mp.exportPath(filename);
		}
		else
			mp.exportPath("random____");
	}
	else
		wxMessageBox(wxT("B³êdna zawartoœæ macierzy."), wxT("B³¹d"), wxOK | wxICON_ERROR, this);
}

bool Program::loadFromGrid()
{
	int rows, cols;
	rows = grid->GetNumberRows();
	cols = grid->GetNumberCols();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			wxString cellValue = grid->GetCellValue(i, j);

			int cellValueAsInt;
			if (cellValue.ToInt(&cellValueAsInt))
			{
				if (cellValueAsInt >= -1000 && cellValueAsInt <= 1000)
				{
					matrix.set(i, j, cellValueAsInt);
				}
				else
					return false;
			}
			else
				return false;
		}
	}
	return true;
}

void Program::CreateResult()
{
	// Tworzenie wxScrolledWindow z ustawion¹ flag¹, aby obs³ugiwaæ przewijanie pionowe
	scrollWindow = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);

	// Tworzenie wxStaticText i ustawianie tekstu
	labelResult = new wxStaticText(scrollWindow, wxID_ANY, wxT("Minimalna œcie¿ka: " + std::to_string(mp.getMinPath()) + "\nŒcie¿ka " + "(" + std::to_string(pathIndex + 1) + "/" + std::to_string(mp.path_count) + ") : \n" +  mp.getStrPath(pathIndex)));
	labelResult->Wrap(1280);

	buttonPreviousPath = new wxButton(panel, wxID_ANY, wxT("<-"));
	buttonPreviousPath->SetMinSize(wxSize(25, 25));
	buttonPreviousPath->Bind(wxEVT_BUTTON, &Program::OnButtonPreviousPathClicked, this);

	buttonNextPath = new wxButton(panel, wxID_ANY, wxT("->"));
	buttonNextPath->SetMinSize(wxSize(25, 25));
	buttonNextPath->Bind(wxEVT_BUTTON, &Program::OnButtonNextPathClicked, this);

	buttonsPathSizer = new wxBoxSizer(wxHORIZONTAL);

	// Ustawianie sizer'a dla wxScrolledWindow
	scrollSizer = new wxBoxSizer(wxVERTICAL);
	scrollSizer->Add(labelResult, 0, wxLEFT, 0);

	// Ustawianie sizer'a dla wxScrolledWindow, aby automatycznie dostosowywa³ siê do rozmiaru okna
	scrollWindow->SetSizerAndFit(scrollSizer);

	// Ustawianie minimalnych rozmiarów przewijanej zawartoœci
	scrollWindow->SetScrollbars(5, 5, 50, 50);

	// Dodawanie wxScrolledWindow do matrixSizer'a
	matrixSizer->Add(scrollWindow, 0, wxALL, 5);
	buttonsPathSizer->Add(buttonPreviousPath, 0, wxLEFT, 5);
	buttonsPathSizer->Add(buttonNextPath, 0, wxLEFT, 0);

	matrixSizer->Add(buttonsPathSizer, 0, wxALL, 0);

	// Aktualizowanie rozmieszczenia elementów
	panel->Layout();
}

void Program::OnButtonPreviousPathClicked(wxCommandEvent& evt)
{
	if (pathIndex > 0)
	{
		pathIndex -= 1;
		visualize();
		labelResult->SetLabel("Minimalna œcie¿ka: " + std::to_string(mp.getMinPath()) + "\nŒcie¿ka " + "(" + std::to_string(pathIndex + 1) + "/" + std::to_string(mp.path_count) + ") : \n" + mp.getStrPath(pathIndex));
		labelResult->Wrap(1280);
		labelResult->Refresh();
	}
}

void Program::OnButtonNextPathClicked(wxCommandEvent& evt)
{
	if (pathIndex < mp.path_count - 1)
	{
		pathIndex += 1;
		visualize();
		labelResult->SetLabel("Minimalna œcie¿ka: " + std::to_string(mp.getMinPath()) + "\nŒcie¿ka " + "(" + std::to_string(pathIndex + 1) + "/" + std::to_string(mp.path_count) + ") : \n" + mp.getStrPath(pathIndex));
		labelResult->Wrap(1280);
		labelResult->Refresh();
	}
}


void Program::visualize()
{
	std::vector<std::vector<int>> path = mp.getPath();
	if (pathIndex >= path.size()) {
		return;
	}

	wxColour white = wxColour(255, 255, 255);
	wxColour green = wxColour(0, 255, 0);

	int rows = grid->GetNumberRows();
	int cols = grid->GetNumberCols();

	grid->BeginBatch();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid->SetCellBackgroundColour(i, j, white);
		}
	}

	int col = 0;
	for (auto i : path[pathIndex]) {
		grid->SetCellBackgroundColour(i, col, green);
		col++;
	}

	grid->EndBatch();
	grid->ForceRefresh();
}