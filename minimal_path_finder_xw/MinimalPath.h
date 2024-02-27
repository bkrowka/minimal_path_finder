#pragma once

#include <wx/msgdlg.h>
#include "Matrix.h"
#include <string>
#include <fstream>
#include <set>

using namespace std;

class MinimalPath
{
	int min_path; // przechowuje wart minimalnej sciezki
	std::vector<std::vector<int>> path; // wektor, przechowuje minimalne sciezki

public:
	MinimalPath(); // konstruktor, inicjalizuje minimalna sciezke
	int calculate(Matrix& matrix); // metoda, oblicza minimalna sciezke
	int path_count; // licznik ilosæi minimalnych œcie¿ek
	int getMinPath(); // metoda, zwraca wart minimalnej sciezki
	std::vector<std::vector<int>> getPath(); // metoda, zwraca minimalna sciezke
	std::string getStrPath(int pathIndex); // metoda, zwraca minimalna sciezke w postaci ciagu znakow
	void exportPath(std::string filename); // metoda, eksportuje wynik do pliku
};