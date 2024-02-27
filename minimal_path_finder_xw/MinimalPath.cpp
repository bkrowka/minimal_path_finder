#include "MinimalPath.h"

using namespace std;

MinimalPath::MinimalPath() { min_path = INT_MAX; path_count = 0;}

int MinimalPath::calculate(Matrix& matrix)
{
    size_t rows = matrix.getRows(), cols = matrix.getCols();
    vector<vector<int>> mp(rows, vector<int>(cols, INT_MAX));
    vector<vector<vector<int>>> prev(rows, vector<vector<int>>(cols));

    // Przepisanie wartosci z macierzy wejsciowej do pierwszej kolumny macierzy pomocniczej
    for (int i = 0; i < rows; i++) 
    {
        mp[i][0] = matrix.get(i, 0);
    }

    // Obliczanie wartoœci minimalnej œcie¿ki dla ka¿dej komorki macierzy wejsciowej i zapisywanie w macierzy pomocniczej
    for (size_t j = 1; j < cols; j++) 
    {
        for (size_t i = 0; i < rows; i++) 
        {
            vector<int> prev_row(3);
            prev_row[0] = (i == 0) ? mp[rows - 1][j - 1] : mp[i - 1][j - 1];
            prev_row[1] = mp[i][j - 1];
            prev_row[2] = (i == rows - 1) ? mp[0][j - 1] : mp[i + 1][j - 1];
            mp[i][j] = matrix.get(i, j) + *min_element(prev_row.begin(), prev_row.end());

            // Odnajdywanie i zapisywanie indeksow poprzednich wierszy dla minimalnej œcie¿ki do komorki
            for (int k = -1; k <= 1; k++) 
            {
                int prev_index = (i + k + rows) % rows;
                if (mp[prev_index][j - 1] + matrix.get(i, j) == mp[i][j]) 
                {
                    prev[i][j].push_back(prev_index);
                }
            }
        }
    }

    // Odnajdywanie wartosci minimalnej sciezki w ostatniej kolumnie
    min_path = mp[0][cols - 1];
    size_t last_row = 0;
    for (int i = 1; i < rows; i++) 
    {
        if (mp[i][cols - 1] < min_path) 
        {
            min_path = mp[i][cols - 1];
            last_row = i;
        }
    }

    // Odtwarzanie wszystkich minimalnych œcie¿ek
    set<vector<int>> unique_paths; // zbior przechowujacy unkialne sciezki
    path_count = 0;
    for (int i = 0; i < rows; i++)  // iteracja przez wszystkie wiersze
    {
        if (mp[i][cols - 1] == min_path) // znalezienie wiersza ostatnie kolumny zawierajacego minimalna wartosc sciezki
        {
            vector<vector<int>> paths = { {i} }; // wektor zawierajacy jedna sciezke zaczynajaca sie od i
            for (int j = cols - 1; j > 0; j--) // iteracja przez wszystkie kolumny od ostatniej
            {
                vector<vector<int>> new_paths; // tymczasowy wektor przechowujacy nowe sciezki dla kolejnej kolumny
                for (auto& p : paths) // iteruje przez istniejace sciezki w biezacej kolumnie (p przyjmuje rzad paths)
                {
                    for (auto& prev_index : prev[p.back()][j]) // iteruje przez poprzednie wiersze dla bie¿¹cego elementu œcie¿kiprev ([p.back()][j] - wektor poprzednich elementów)
                    {
                        vector<int> new_path = p; // tworzy now¹ œcie¿kê na podstawie istniej¹cej œcie¿ki
                        new_path.push_back(prev_index); // dodaje do nowej œcie¿ki aktualny poprzedni indeks
                        new_paths.push_back(new_path); // dodaje now¹ œcie¿kê do wektora tymczasowego
                    }
                }
                paths = new_paths; // aktualizacja
            }
            for (auto& p : paths) 
            {
                reverse(p.begin(), p.end()); // odwrocenie kolejnosci sciezki (sciezki byly budowane od konca)
                unique_paths.insert(p); // dodaje sciezke do listy bez duplikatow
            }
        }
    }

    path = vector<vector<int>>(unique_paths.begin(), unique_paths.end());
    path_count = path.size();

    return min_path;
}

int MinimalPath::getMinPath()
{
    return min_path;
}

vector<std::vector<int>> MinimalPath::getPath()
{
    return path;
}

string MinimalPath::getStrPath(int pathIndex)
{
    string str_path;
    if (pathIndex < 0 || pathIndex >= path_count) {
        return "Nieprawid³owy indeks œcie¿ki.";
    }
    for (auto i : path[pathIndex]) {
        str_path += to_string(i + 1) + " "; // +1 aby wyœwietliæ numery od 1 do n zamiast od 0 do n-1
    }
    return str_path;
}



void MinimalPath::exportPath(std::string filename)
{
    filename = filename.substr(0, filename.length() - 4);
    std::ofstream file(filename + "_min_path.txt");
    if (!file.is_open()) {
        return;
    }

    file << "Minimalna sciezka: " << min_path << "\n";
    for (int p = 0; p < path_count; p++) {
        file << "Sciezka " << p + 1 << ": ";
        for (auto i : path[p]) {
            file << i + 1 << " "; // +1 aby wyœwietliæ numery od 1 do n zamiast od 0 do n-1
        }
        file << "\n";
    }

    file.close();
}