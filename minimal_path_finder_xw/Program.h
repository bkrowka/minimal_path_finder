#pragma once

#include "Frame.h"
#include "DataLoader.h"
#include "MinimalPath.h"

class Program : public Frame
{
	void BindEventHandlers(); // metoda, wiaze obsluge zdarzen
	void OnButtonLoadClicked(wxCommandEvent& evt); // metoda, obsluguje zdarzenia po kliknieciu przycisku wczytywania
	void OnButtonRandClicked(wxCommandEvent& evt); // metoda, obsluguje zdarzenia po kliknieciu przycisku losowania
	std::string filename; // przechowuje nazwe pliku
	DataLoader dl; // instancja do wczytywania danych
	Matrix matrix; // instancja do przechowywania macierzy
	MinimalPath mp; // instancja do obliczen
	void CreateGrid(); // metoda,tworzy siatke macierzy
	void ClearSpace(); // metoda, czysci przestrzen robocza
	void ClearResult(); // metoda, czysci przestrzen wyniku
	void OnButtonDelRowClicked(wxCommandEvent& evt); // metoda, usuwa wiersz
	void OnButtonAddRowClicked(wxCommandEvent& evt); // metoda, dodaje wiersz
	void OnButtonAddColClicked(wxCommandEvent& evt); // metoda, dodaje kolumne
	void OnButtonDelColClicked(wxCommandEvent& evt); // metoda, usuwa kolumne
	void OnButtonCalculateClicked(wxCommandEvent& evt);  // metoda, obsluguje zdarzenia po kliknieciu przycisku "Oblicz"
	bool loadFromGrid(); // metoda, wczytuje dane z siatki
	int pathIndex; // numer œcie¿ki
	void CreateResult(); // metoda, tworzy okno do wyswietlania wyniku
	void OnButtonPreviousPathClicked(wxCommandEvent& evt); // metoda, obsluguje zdarzenia po kliknieciu przycisku "<-"
	void OnButtonNextPathClicked(wxCommandEvent& evt); // metoda, obsluguje zdarzenia po kliknieciu przycisku "->"
	void visualize(); // metoda, wizualizuje sciezke na macierzy
	
public:
	Program(const wxString& title); // konstruktor, inicjalizuje glowne okno aplikacji
};

