#pragma once

#ifndef ARRAYD_ARRAYD_HPP_20230330
#define ARRAYD_ARRAYD_HPP_20230330

#include <iosfwd>
#include <cstdint>

class ArrayD {

public:
	ArrayD();
	explicit ArrayD(std::ptrdiff_t ssize);
	ArrayD(const ArrayD& other);
	~ArrayD();

	ArrayD& operator=(const ArrayD& rhs);
	double& operator[](const std::ptrdiff_t i);
	const double& operator[](const std::ptrdiff_t i) const;

	std::ptrdiff_t ssize() const noexcept;
	
	void insert(const std::ptrdiff_t i, const double value);

	void resize(const std::ptrdiff_t new_size);

	void remove(const std::ptrdiff_t i);

	static const char separator{ ',' };

private:
	// Указатель на димнамический массив
	double* coords; 

	std::ptrdiff_t size;

	std::ptrdiff_t capacity;
};
#endif
