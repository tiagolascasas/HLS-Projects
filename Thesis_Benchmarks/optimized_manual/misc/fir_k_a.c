#include <stdio.h>

#define N 100

void fir_k_a(int t[N], int o[N], int a[N], int m[N][N])
{
    int i;
    int j;

    for (i = 0; i < N; i++)
    {
    	t[i] = 0;
        for (j = 0; j < 3; j++)
			#pragma HLS UNROLL
			t[i] = t[i] + (a[i - j + 2] >> 2);
    }
    for (i = 0; i < N; i++)
    {
        o[i] = 0;
        for (j = 0; j < N; j++)
			#pragma HLS UNROLL
			o[i] = o[i] + m[i][j] * t[j];
    }
}

int main()
{
    int t[N] = {0};
    int o[N] = {0};
    int a[N] = {0};
    int m[N][N] = {0};
    int i, j;
    for (i = 0; i < N; i++)
    {
        t[N] = i;
        o[N] = i;
        a[N] = i;
        for (j = 0; j < N; j++)
            m[i][j] = i + j;
    }

    fir_k_a(t, o, a, m);

    int checksum = 0;
    for (i = 0; i < N; i++)
        checksum += o[i];
    printf("checksum: %d\n", checksum);
    return 0;
}
