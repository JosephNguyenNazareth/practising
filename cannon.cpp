// Ham dich trai xoay vong dong thu i trong matran a k lan;
template<class t>
void rotateleftarray(t *a, int n, int k)
{
	while (k-->0)
	{
		t temp = a[0];
		for (int i = 0; i < n-1; ++i)
		{
			a[i] = a[i + 1];
		}
		a[n - 1] = temp;
	}
}
// Ham dich len xoay vong cot thu c trong ma tran a k lan;
template<class t>
void rotateupcollum(t **a, int c, int k,int n)
{
	while (k-->0)
	{
		t temp = a[0][c];
		for (int i = 0; i < n-1; ++i)
		{
			a[i][c] = a[i + 1][c];
		}
		a[n - 1][c] = temp;
	}
}
template <class t>
void meshmultiplicationmatrix(t **a, t **b, t **c, int n)
{
	// Khoi tao ma tran ket qua phuc vu cho viec cong don ket qua ;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			c[i][j] = 0;
		}
	}
	// Xoay vong hang thu i cua ma tran a sang trai i lan;
	for (int i = 0; i < n; ++i)
	{
		rotateleftarray(a[i], n, i);
	}
	// Xoay vong cot thu j cua ma tran b len tren j lan;
	for (int j = 0; j < n; ++j)
	{
		rotateupcollum(b, j, j, n);
	}
	// Lap n lan de tinh ket qua c[i][j]=a[i][j]*b[i][j] sau do cong don lai 
	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j=0; j < n; ++j)
			{
				c[i][j] += a[i][j] * b[i][j];
			}
		}
		// ung voi moi lan lap:
		// Xoay vong n hang cua ma tran a sang trai 1 lan;
		for (int i = 0; i < n; ++i)
		{
			rotateleftarray(a[i], n, 1);
		}
		// Xoay vong n cot cua ma tran b len tren 1 lan;
		for (int j = 0; j < n; ++j)
		{
			rotateupcollum(b, j, 1, n);
		}
	}
}