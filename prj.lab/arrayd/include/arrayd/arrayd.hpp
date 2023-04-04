#pragma once

#ifndef ARRAYD_ARRAYD_HPP_20230330
#define ARRAYD_ARRAYD_HPP_20230330

#include <iosfwd>
#include <cstdint>
using namespace std;

class ArrayD {

public:
	ArrayD();
	explicit ArrayD(ptrdiff_t ssize);
	ArrayD(const ArrayD& other);
	~ArrayD();

	ArrayD& operator=(const ArrayD& rhs);
	double& operator[](const ptrdiff_t i);
	const double& operator[](const ptrdiff_t i) const;

	ptrdiff_t ssize() const noexcept;

	void insert(const ptrdiff_t i, const double value);

	void resize(const ptrdiff_t new_size);

	void remove(const ptrdiff_t i);

	static const char separator{ ',' };

private:
	// Указатель на димнамический массив
	double* coords; 

	ptrdiff_t size; 

	ptrdiff_t capacity;
};
#endif
