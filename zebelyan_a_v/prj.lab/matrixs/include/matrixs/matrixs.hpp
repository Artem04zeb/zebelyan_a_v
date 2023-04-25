#pragma once

#ifndef MATRIXS_MATRIXS_HPP_20230403
#define MATRIXS_MATRIXS_HPP_20230403

#include <iosfwd>
#include <tuple>

using namespace std;


class MatrixS {
public:
	MatrixS();
	MatrixS(const int n, const int m);
	~MatrixS();

	/**
	 * \return количество строк в матрице (m)
	 */
	int nRows();

	/**
	 * \return количество столбцов в матрице (n)
	 */
	int nCols();

	/**
	 *  Возвращает элемент матрицы под индексами {i, j}
	 */
	int& at(int i, int j);

	/**
	 * \return текущий размер матрицы {m, n}
	 */
	tuple<int, int> ssize();

	/**
	 * \brief Изменение размера матрицы
	*/
	void resize(int columns_new, int rows_new);

	/**
	 *  Проверяет входные данные
	 */
	bool check_size(int rows, int columns);

private:
	int columns = 0;
	int rows = 0;
	int* dina = nullptr;
	int* dina2 = nullptr;
};

#endif 
