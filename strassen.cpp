#include <iostream>
#include <time.h>
using namespace std;
template<class t>
void nhanmatranvuong(t **a, t **b, t **c, int n)
{
	t sum = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int k = 0; k < n; ++k)
		{
			for (int j = 0; j < n; ++j)
			{
				sum += a[i][j] * b[j][k];
			}
			c[i][k] = sum;
			sum = 0;
		}
	}
}
template<class t>
void sinhmatranvuong(t **&a, int n)
{
	a = new t*[n];
	for (int i = 0; i < n; ++i)
	{
		a[i] = new t[n];
	}
}
template<class t>
void huymatranvuong(t **&a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		delete a[i];
	}
	a = NULL;
}
template <class t>
void congmatranvuong(t **a, t **b, t**c, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}
template <class t>
void trumatranvuong(t **a, t **b, t**c, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			c[i][j] = a[i][j] - b[i][j];
		}
	}
}
template <class t>
void strassen(t **a, t **b, t **&c, int n)
{
	if (n == 2)
	{
		nhanmatran<t>(a, b, c, n, n, n, n);
	}
	else
	{
		t **a11, **a12, **a21, **a22, **b11, **b12, **b21, **b22, **c11, **c12, **c21, **c22;
		t **m1, **m2, **m3, **m4, **m5, **m6, **m7;
		t **temp1, **temp2;
		sinhmatranvuong<t>(a11,n);
		sinhmatranvuong<t>(a12, n);
		sinhmatranvuong<t>(a21, n);
		sinhmatranvuong<t>(a22, n);
		sinhmatranvuong<t>(b11, n);
		sinhmatranvuong<t>(b12, n);
		sinhmatranvuong<t>(b21, n);
		sinhmatranvuong<t>(b22, n);
		sinhmatranvuong<t>(m1, n);
		sinhmatranvuong<t>(m2, n);
		sinhmatranvuong<t>(m3, n);
		sinhmatranvuong<t>(m4, n);
		sinhmatranvuong<t>(m5, n);
		sinhmatranvuong<t>(m6, n);
		sinhmatranvuong<t>(m7, n);
		sinhmatranvuong<t>(temp1, n);
		sinhmatranvuong<t>(temp2, n);
		sinhmatranvuong<t>(c11, n);
		sinhmatranvuong<t>(c12, n);
		sinhmatranvuong<t>(c21, n);
		sinhmatranvuong<t>(c22, n);
		for (int i = 0; i < n / 2; ++i)
		{
			for (int j = 0; j < n / 2; ++j)
			{
				a11[i][j] = a[i][j];
				a12[i][j] = a[i][j + n / 2];
				a21[i][j] = a[i + n / 2][j];
				a22[i][j] = a[i + n / 2][j + n / 2];
				b11[i][j] = b[i][j];
				b12[i][j] = b[i][j + n / 2];
				b21[i][j] = b[i + n / 2][j];
				b22[i][j] = b[i + n / 2][j + n / 2];
			}
		}
		//m1=(a11+a22)*(b11+b22);
		congmatranvuong<t>(a11, a22, temp1,n / 2);
		congmatranvuong<t>(b11, b22, temp2,n / 2);
		strassen(temp1, temp2, m1, n / 2);
		//m2=(a21+a22)*b11;
		congmatranvuong<t>(a21, a22, temp1,n / 2);
		strassen(temp1, b11, m2, n / 2);
		//m3=a11*(b12-b22);
		trumatranvuong<t>(b12, b22, temp2,n / 2);
		strassen(a11, temp2, m3, n / 2);
		//m4=a22*(b21-b11)
		trumatranvuong<t>(b21, b11, temp2,n / 2);
		strassen(a22, temp2, m4, n / 2);
		//m5=(a11+a12)*b22;
		congmatranvuong<t>(a11, a12, temp1,n / 2);
		strassen(temp1, b22, m5, n / 2);
		//m6=(a21-a11)*(b11+b12);
		trumatranvuong<t>(a21, a11, temp1,n / 2);
		congmatranvuong<t>(b11, b12, temp2, n / 2);
		strassen(temp1, temp2, m6, n / 2);
		//m7=(a12-a22)*(b21+b22)
		trumatranvuong<t>(a12, a22, temp1,n / 2);
		congmatranvuong<t>(b21, b22, temp2,n / 2);
		strassen(temp1, temp2, m7, n / 2);
		//c11=m1+m4-m5+m7;
		congmatranvuong<t>(m1, m4, temp1,n / 2);
		trumatranvuong<t>(m7, m5, temp2,n / 2);
		congmatranvuong<t>(temp1, temp2, c11,n / 2);
		//c12=m3+m5;
		congmatranvuong<t>(m3, m5, c12,n / 2);
		//c21=m2+m4;
		congmatranvuong<t>(m2, m4, c21,n / 2);
		//c22=m1-m2+m3+m6
		trumatranvuong<t>(m1, m2, temp1,n / 2);
		congmatranvuong<t>(m3, m6, temp2, n / 2);
		congmatranvuong<t>(temp1, temp2, c22,n/2);
		for (int i = 0; i < n / 2; ++i)
		{
			for (int j = 0; j < n / 2; ++j)
			{
				c[i][j] = c11[i][j];
				c[i][j + n / 2] = c12[i][j];
				c[i + n / 2][j] = c21[i][j];
				c[i + n / 2][j + n / 2] = c22[i][j];
			}
		}
		huymatranvuong<t>(c11, n / 2);
		huymatranvuong<t>(c12, n / 2);
		huymatranvuong<t>(c21, n / 2);
		huymatranvuong<t>(c22, n / 2);
		huymatranvuong<t>(a11, n / 2);
		huymatranvuong<t>(a12, n / 2);
		huymatranvuong<t>(a21, n / 2);
		huymatranvuong<t>(a22, n / 2);
		huymatranvuong<t>(b11, n / 2);
		huymatranvuong<t>(b12, n / 2);
		huymatranvuong<t>(b21, n / 2);
		huymatranvuong<t>(b22, n / 2);
		huymatranvuong<t>(temp1, n / 2);
		huymatranvuong<t>(temp2, n / 2);
		huymatranvuong<t>(m1, n / 2);
		huymatranvuong<t>(m2, n / 2);
		huymatranvuong<t>(m3, n / 2);
		huymatranvuong<t>(m4, n / 2);
	}
}
void randomint(int **a, int r, int c)
{
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			a[i][j] = rand() % 10 -5;
		}
	}
}
template <class T>
void xuatmatran(T** a, int r, int c)
{
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}
int main()
{
	srand(time(NULL));
	int **a, **b, **c, **d,n;
	cout << " Nhap so n = "; cin >> n;
	sinhmatranvuong(a, n); sinhmatranvuong(b, n); sinhmatranvuong(c, n), sinhmatranvuong(d, n);
	randomint(a, n, n);
	randomint(b, n, n);
	xuatmatran(a, n, n);
	xuatmatran(b, n, n);
	nhanmatranvuong(a, b, c, n);
	strassen(a, b, d, n);
	xuatmatran(c, n, n);
	xuatmatran(d, n, n);
	huymatranvuong(a, n); huymatranvuong(b, n); huymatranvuong(c, n); huymatranvuong(d, n);
	return 0;
}