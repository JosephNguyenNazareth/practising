#ifndef MATRIX_ITERACTIVE_H
#define MATRIX_ITERACTIVE_H
#include "matrix.h"
template<class T>
void iteractiveMultiply(const Matrix<T>& a, const Matrix<T>& b, Matrix<T>& out) {
	unsigned int 	m = a.getRow(),
			n = a.getCol(),
			p = b.getCol();
	for (unsigned int i = 0; i < m; ++i) {
		for (unsigned int j = 0; j < p; ++j) {
			out[i][j] = 0;
			for (unsigned int k = 0; k < p; ++k) {
				out[i][j] += a[i][k] * a[k][j];
			}
		}
	}
}

#endif 
