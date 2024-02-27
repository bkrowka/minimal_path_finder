#pragma once

#include <vector>

class Matrix
{
	std::vector<std::vector<int>> data; // wektor, przechowuje dane

public:
	Matrix(int rows, int cols); // konstruktor, tworzy macierz
	void set(int row, int col, int value); // metoda, ustawia wart komorki
	void addRow(); // metoda, dodaje wiersz
	void addCol();  // metoda, dodaje kolumne
	void delRow(); // metoda, usuwa wiersz
	void delCol(); // metoda, usuwa kolumne
	int get(int row, int col) const; // metoda, pobiera wart komorki
	std::size_t getRows() const; // metoda, zwraca liczbe wierszy
	std::size_t getCols() const; // metoda, zwraca liczbe kolumn
};

