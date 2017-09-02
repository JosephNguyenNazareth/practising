#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cstdlib>
template <class T> class Matrix {
	unsigned int row, col;
	T **data;
	public:
	Matrix() : row(0), col(0){};
	Matrix(unsigned int userRow, unsigned int userCol)
	: row(userRow), col(userCol) {
		data = new T*[row];
		for (unsigned int index = 0; index < row; index++) {
			data[index] = new T[col];
		}
	}
	~Matrix(){
		for (int index = 0; index < row; index++){
			delete[] data[index];
			data[index] = NULL;
		}
		delete[] data;
		data = NULL;
	}
	void SetSize(unsigned int userRow, unsigned int userCol) {
		Matrix(userRow, userCol);
	}
	void SetRandomValue() {
		srand(time(NULL));
		for (int index = 0; index < row; index++) {
			for (int ikimashou = 0; ikimashou < col; ikimashou++) {
				data[index][ikimashou] = (T)(rand() % 10000 + 1)/100;
			}
		}
	}
	void Print() {
		for (int index = 0; index < row; index++) {
			for (int ikimashou = 0; ikimashou < col; ikimashou++) {
				std::cout << std::setw(10) << data[index][ikimashou];
			}
			std::cout << std::endl;
		}
	}

	friend Matrix operator*(Matrix MatB){};
	T* operator[](int i) {
		if (i < 0 || i > row) {
			throw std::out_of_range("Index out of bound");
		}
		return data[i];
	}
	T* operator[](int i) const {
		if (i < 0 || i > row) {
			throw std::out_of_range("Index out of bound");
		}
		return data[i];
	}
	unsigned int getRow() const { return this->row; }
	unsigned int getCol() const { return this->col; }
};
template<class T>
void sum(const Matrix<T>& a, const Matrix<T>& b, Matrix<T>& out) {
	if (a.getRow() != b.getRow() || a.getCol() != b.getCol()) {
		throw std::invalid_argument("Array dimensions mismatch");
	}
	for (int i = 0; i < a.getRow(); ++i) {
		for (int j = 0; j < a.getCol(); ++j) {
			out[i][j] = a[i][j] + b[i][j];
		}
	}
}
#endif
