#pragma once

#include "Matrix.h"
#include <string>
#include <fstream>
#include <random>

class DataLoader
{
public:
	Matrix load(const std::string& filename); // metoda, wczytuje dane z pliku
	Matrix random(int rows, int cols, int min, int max); // metoda, losuje dane na podstawie podanych parametrow
};