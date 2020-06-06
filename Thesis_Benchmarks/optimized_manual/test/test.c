void constFolding()
{
    int x = 1 + 2 + 3;
    int y = 1 / 2 * 3;
    float z = 1.34f + 8.5f;
    float w = 1.4f + 1;
    float t = 15 + 123.123f;

    for (int i = 0; i < 10 + 1; i++)
    {
        x += 2;
    }
}

void unwrapDecls()
{
    int x, y, z = 1000, k[100], a[55][66], p[14] = {0};
    for (int i = 0; i < 10 + 1; i++)
    {
    		int aa = 2, bb = 3;
		x += 2;
        	for (int j = 0; j < 10; j++) 
        	{
        		int bazz = 4, bizz = 5;
        		aa += 2;
        	}
    }
    int fi = 3, fa = 98;
}

void exprBalance(int a[100], int b[100]) {
#pragma HLS EXPRESSION_BALANCE
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	for (int i = 0; i < 100; i++) {
		a[i] += b[i] * (x1 + a[i] * x2 + b[i]) / x1;
	}
}

int main()
{
    test();
    constFolding();
    unwrapDecls();
    return 0;
}
