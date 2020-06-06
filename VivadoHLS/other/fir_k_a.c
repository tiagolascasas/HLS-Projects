#include <stdio.h>

#define N 100

void fir_k_a(int t[N], int o[N], int a[N], int m[N][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        t[i] = 0;
        for (j = 0; j < 3; j++)
            t[i] = t[i] + (a[i - j + 2] >> 2);
    }
    for (i = 0; i < N; i++)
    {
        o[i] = 0;
        for (j = 0; j < N; j++)
            o[i] = o[i] + m[i][j] * t[j];
    }
}

void fir_k_a_chigh(int o[100], int t[100], int a[100], int m[100][100])
{
#pragma HLS array_partition variable = o cyclic factor = 2 dim = 1
#pragma HLS array_partition variable = t cyclic factor = 33 dim = 1
#pragma HLS array_partition variable = a cyclic factor = 100 dim = 1
#pragma HLS array_partition variable = m cyclic factor = 33 dim = 2
    int i, j;
    for (i = 2; i < 100; i++)
    {
#pragma HLS pipeline
        t[i] = 0;
        for (j = 0; j < 3; j++)
            t[i] = t[i] + (a[i - j] >> 2);
    }
    for (i = 0; i < 100; i++)
    {
#pragma HLS pipeline
        o[i] = 0;
        for (j = 0; j < 100; j++)
            o[i] = o[i] + m[i][j] * t[j];
    }
}

int main()
{
    int t[N] = {0};
    int o[N] = {0};
    int a[N] = {0};
    int m[N][N] = {0};
    for (int i = 0; i < N; i++)
    {
        t[N] = i;
        o[N] = i;
        a[N] = i;
        for (int j = 0; j < N; j++)
            m[i][j] = i + j;
    }

    fir_k_a(t, o, a, m);

    int checksum = 0;
    for (int i = 0; i < N; i++)
        checksum += o[i];
    printf("checksum: %d\n", checksum);
    return 0;
}