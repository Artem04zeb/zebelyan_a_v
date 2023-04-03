#include <iostream>
#include "../include/matrixs/matrixs.hpp"


MatrixS::MatrixS() = default;

MatrixS::MatrixS(const int n, const int m) :rows(m), columns(n) {
	if (check_size(rows, columns)) dina = new int[rows * columns] {0};
	else throw invalid_argument("Invalid input data: m <= 0 или n <= 0");

}

MatrixS::~MatrixS() {
	delete[] dina;
};

int MatrixS::nRows() { return rows; }

int nCols() { return columns; }

tuple<int, int> MatrixS::ssize() { return make_tuple(columns, rows); }

int& MatrixS::at(int i, int j) {
	if (!(check_size(i, j) && i <= rows && j <= columns)) throw invalid_argument("i вне диапазона [0, m) или j вне диапазона [0, n)");
	return dina[(i - 1) * columns + j - 1];
}

void MatrixS::resize(int columns_new, int rows_new) {
	dina2 = new int[rows_new * columns_new] {0};
	if (columns_new <= columns && rows_new > rows)
	{
		for (int i = 0; i < rows; i++) // 2
		{
			for (int j = 0; j < columns_new; j++) // 2
			{
				dina2[i * columns_new + j] = dina[i * columns + j];
			}
		}
		rows = rows_new;
		columns = columns_new;
	}
	if (columns_new > columns && rows_new <= rows) {
		for (int i = 0; i < rows_new; i++) // 2
		{
			for (int j = 0; j < columns; j++) // 2
			{
				dina2[i * columns_new + j] = dina[i * columns + j];
			}
		}
		rows = rows_new;
		columns = columns_new;
	}
	if (columns_new > columns && rows_new > rows) {
		for (int i = 0; i < rows; i++) // 2
		{
			for (int j = 0; j < columns; j++) // 2
			{
				dina2[i * columns_new + j] = dina[i * columns + j];
			}
		}
		rows = rows_new;
		columns = columns_new;
	}
	if (columns_new < columns && rows_new < rows) {
		for (int i = 0; i < rows_new; i++) // 2
		{
			for (int j = 0; j < columns_new; j++) // 2
			{
				dina2[i * columns_new + j] = dina[i * columns + j];
			}
		}
		rows = rows_new;
		columns = columns_new;
	}

	delete[] dina;
	dina = dina2;
	delete[] dina2;
}

bool MatrixS::check_size(int rows, int columns)
{
	if (columns <= 0 || rows <= 0) return false;
	else return true;
}
