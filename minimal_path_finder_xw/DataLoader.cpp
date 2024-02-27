#include "DataLoader.h"

Matrix DataLoader::load(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		return Matrix(0, 0);
	}

    int rows, cols;
    file >> rows >> cols;

    if (rows <= 100 && rows > 0  && cols <= 100 && cols > 0)
    {
        Matrix matrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int value;
                if (file >> value)
                {
                    if (value <= 1000 && value >= -1000)
                    {
                        matrix.set(i, j, value);
                    }
                    else
                        return Matrix(0, 0);
                }
                else
                    return Matrix(0, 0);
            }
        }
        std::string other;
        if (file >> other) {
            return Matrix(0, 0);
        }
        file.close();
        return matrix;
    }
    else
        return Matrix(0, 0);
}

Matrix DataLoader::random(int rows, int cols, int min, int max)
{
    if (rows > 0 && cols > 0 && min <= max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);

        Matrix matrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                matrix.set(i, j, dis(gen));
            }
        }
        return matrix;
    }
    else
        return Matrix(0,0);
}