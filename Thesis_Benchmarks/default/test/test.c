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
            if (bazz > bizz)
            	aa = 1;
            aa += 2;
        }
    }
    int fi = 3, fa = 98;
}

void if1(int in0, int in1, int in2)
{
	int x = 1;
    if (in0 < in1)
    {
        if (in0 < in2)
            x = 2;
        else
            x = 3;
    }
    else
    {
        if (in1 < in2)
            x = 4;
        else
            x = 5;
    }
}

int if2(int counter, int fragments[], int size, int pixels[])
{
    // initilize the z-buffer in rendering first triangle for an image
    static int z_buffer[300][300];
    if (counter == 0)
    {
        for (int i = 0; i < 300; i++)
        {
            for (int j = 0; j < 300; j++)
            {
                z_buffer[i][j] = 255;
            }
        }
    }
    int x = 0;
    for (int i = 0; i < 300; i++)
    	 x += 1;	
}

int main()
{
    test();
    constFolding();
    unwrapDecls();
    return 0;
}