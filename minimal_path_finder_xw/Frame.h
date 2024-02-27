#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>

class Frame : public wxFrame
{
    wxBoxSizer* vBoxSizer;
    wxBoxSizer* hBoxSizer;
    wxStaticText* labelFilename;
    wxStaticText* labelRows;
    wxStaticText* labelCols;
    wxStaticText* labelRange;
    wxStaticLine* line;
    void CreateControls(); // metoda, tworzy kontrolki
    void WindowLayout(); // metoda, definiuje uk³ad okna

protected:
    wxPanel* panel;
    wxBoxSizer* mainSizer;
    wxTextCtrl* textCtrlFilename;
    wxTextCtrl* textCtrlRows;
    wxTextCtrl* textCtrlCols;
    wxTextCtrl* textCtrlRange1;
    wxTextCtrl* textCtrlRange2;
    wxButton* buttonLoad;
    wxButton* buttonRand;
    wxBoxSizer* matrixSizer;
    wxGrid* grid;
    wxButton* buttonAddRow;
    wxButton* buttonDelRow;
    wxButton* buttonAddCol;
    wxButton* buttonDelCol;
    wxBoxSizer* buttonsColSizer;
    wxBoxSizer* horizontalSizer;
    wxButton* buttonCalculate;
    wxScrolledWindow* scrollWindow;
    wxBoxSizer* scrollSizer;
    wxStaticText* labelResult;
    wxButton* buttonPreviousPath;
    wxButton* buttonNextPath;
    wxBoxSizer* buttonsPathSizer;

public:
    Frame(const wxString& title); // konstruktor, tworzy okno
};


