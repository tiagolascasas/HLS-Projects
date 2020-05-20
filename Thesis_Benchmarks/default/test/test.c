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

int main()
{
    test();
    constFolding();
    unwrapDecls();
    return 0;
}