#ifndef MATRIX_DIVIDE_AND_CONQUER_H
#define MATRIX_DIVIDE_AND_CONQUER_H

#include "matrix.h"
#include "matrix-iteractive.h"
#define ARRAY_SIZE 1024

/* --- DIVIDE AND CONQUER (MATRIX MULTPLICATION) ---
This algorithm works only for square matrices whose dimensions are powers of two. It's complexity is O(n^3). */
template<class T>
void divideAndConquer(const Matrix<T>& a, const Matrix<T>& b, Matrix<T>& out, unsigned int n) {
	if (n <= 2) {
		iteractiveMultiply(a, b, out);
	} else {
		// halve the size
		unsigned int newN = n / 2;
		// subdivide the matrix
		Matrix<T> a11(newN, newN), a12(newN, newN),
			a21(newN, newN), a22(newN, newN),
			b11(newN, newN), b12(newN, newN),
			b21(newN, newN), b22(newN, newN);
		for (unsigned int i = 0; i < newN; ++i) {
			for (unsigned int j = 0; j < newN; ++j) {
				a11[i][j] = a[i][j];
				a12[i][j] = a[i][j + newN];
				a21[i][j] = a[i + newN][j];
				a22[i][j] = a[i + newN][j + newN];
				
				b11[i][j] = b[i][j];
				b12[i][j] = b[i][j + newN];
				b21[i][j] = b[i + newN][j];
				b22[i][j] = b[i + newN][j + newN];
			}
		}
		// result matrices
		Matrix<T> c11(newN, newN),
			c12(newN, newN),
			c21(newN, newN),
			c22(newN, newN);
		// divide and conquer
		Matrix<T> resultA(newN, newN),
			resultB(newN, newN);
		divideAndConquer(a11, b11, resultA, newN);
		divideAndConquer(a12, b21, resultB, newN);
		sum(resultA, resultB, c11); // a11*b11 + a12*b21
		divideAndConquer(a11, b12, resultA, newN);
		divideAndConquer(a12, b22, resultB, newN);
		sum(resultA, resultB, c12); // a11*b12 + a12*b22
		divideAndConquer(a21, b11, resultA, newN);
		divideAndConquer(a22, b21, resultB, newN);
		sum(resultA, resultB, c21); // a21*b11 + a22*b21
		divideAndConquer(a21, b12, resultA, newN);
		divideAndConquer(a22, b22, resultB, newN);
		sum(resultA, resultB, c22); // a21*b12 + a22*b22;
		// putting everything back together
		for (unsigned int i = 0; i < newN; ++i) {
			for (unsigned int j = 0; j < newN; ++j) {
				out[i][j] = c11[i][j];
				out[i][j + newN] = c12[i][j];
				out[i + newN][j] = c21[i][j];
				out[i + newN][j + newN] = c22[i][j];
			}
		}
	}
}

#endif
