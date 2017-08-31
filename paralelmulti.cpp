template<class t>
void paralelmulti(t **a, t **b, t** c, int n)
{
	if (n == 2)
	{
		nhanmatranvuong<t>(a, b, c, n);
	}
	else
	{
		t **a11, **a12, **a21, **a22;
		t **b11, **b12, **b21, **b22;
		t **c11, **c12, **c21, **c22;
		t **d11, **d12, **d21, **d22;
		sinhmatranvuong(a11, n); sinhmatranvuong(a12, n);
		sinhmatranvuong(a21, n); sinhmatranvuong(a22, n);
		sinhmatranvuong(b11, n); sinhmatranvuong(b12, n);
		sinhmatranvuong(b21, n); sinhmatranvuong(b22, n);
		sinhmatranvuong(c11, n); sinhmatranvuong(c12, n);
		sinhmatranvuong(c21, n); sinhmatranvuong(c22, n);
		sinhmatranvuong(d11, n); sinhmatranvuong(d12, n);
		sinhmatranvuong(d21, n); sinhmatranvuong(d22, n);
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
		paralelmulti(a11, b11, c11, n / 2);
		paralelmulti(a11, b12, c12, n / 2);
		paralelmulti(a21, b11, c21, n / 2);
		paralelmulti(a21, b12, c22, n / 2);
		paralelmulti(a12, b21, d11, n / 2);
		paralelmulti(a12, b22, d12, n / 2);
		paralelmulti(a22, b21, d21, n / 2);
		paralelmulti(a22, b22, d22, n / 2);
		congmatranvuong(c11, d11, n / 2);
		congmatranvuong(c12, d12, n / 2);
		congmatranvuong(c21, d21, n / 2);
		congmatranvuong(c22, d22, n / 2);
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
		huymatranvuong(c11, n / 2);
		huymatranvuong(c12, n / 2);
		huymatranvuong(c21, n / 2);
		huymatranvuong(c22, n / 2);
		huymatranvuong(d11, n / 2);
		huymatranvuong(d12, n / 2);
		huymatranvuong(d21, n / 2);
		huymatranvuong(d22, n / 2);
		huymatranvuong(a11, n / 2);
		huymatranvuong(a12, n / 2);
		huymatranvuong(a21, n / 2);
		huymatranvuong(a22, n / 2);
		huymatranvuong(b11, n / 2);
		huymatranvuong(b12, n / 2);
		huymatranvuong(b21, n / 2);
		huymatranvuong(b22, n / 2);
	}
}