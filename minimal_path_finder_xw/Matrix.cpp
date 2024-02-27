#include "Matrix.h"

Matrix::Matrix(int rows, int cols) : data(rows, std::vector<int>(cols)) {}

void Matrix::set(int row, int col, int value) 
{
    data[row][col] = value;
}

void Matrix::addRow()
{
    data.push_back(std::vector<int>(getCols()));
}

void Matrix::addCol()
{
    for (auto& row : data) {
        row.push_back(0);
    }
}

void Matrix::delRow()
{
    if (!data.empty()) {
        data.pop_back();
    }
}

void Matrix::delCol()
{
    for (auto& row : data) {
        if (!row.empty()) {
            row.pop_back();
        }
    }
}

int Matrix::get(int row, int col) const
{
    return data[row][col];
}

std::size_t Matrix::getRows() const
{
    return data.size();
}

std::size_t Matrix::getCols() const
{
    return data[0].size();
}