#include <iostream>
#include <ctime>
#include <cstdlib>
#include "matrix-iteractive.h"
#include "matrix-divide-and-conquer.h"

using namespace std;


// One test case for now
#define TEST_CASES 1

int main() {
	// gonna make two arrays just in case we need different dimensions for each matrix
	cout << "--- MATRIX MULTIPLICATION ALGORITHMS ---" << endl;
	// The following test cases could be replaced by the invocations of a single function whose arguments contain a function pointer
	cout << "\t+ Iteractive method" << endl;
	for (int i = 0; i < TEST_CASES; ++i) {	
		// For now all matrices will have their dimensions as 1000
		Matrix<int> a(1000, 1000),
			b(1000, 1000),
			c(1000, 1000);
		a.SetRandomValue();
		b.SetRandomValue();
		clock_t start = clock();
		iteractiveMultiply(a, b, c);
		clock_t end = clock();
		double timeElapsed = (end - start) / CLOCKS_PER_SEC;
		cout << "\t\t+ Test case " << i << ": " << timeElapsed << endl;
	}
	cout << "\t+ Divide and Conquer" << endl;
	for (int i = 0; i < TEST_CASES; ++i) {
		Matrix<int> a(1000, 1000),
			b(1000, 1000),
			c(1000, 1000);
		a.SetRandomValue();
		b.SetRandomValue();
		clock_t start = clock();
		divideAndConquer(a, b, c, 1000);
		clock_t end = clock();
		double timeElapsed = (end - start) / CLOCKS_PER_SEC;
		cout << "\t\t+ Test case " << i << ": " << timeElapsed << endl;
	}
}
