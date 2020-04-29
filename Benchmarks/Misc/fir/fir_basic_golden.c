#include "fir_basic.h"

void fir_b_golden(int x[M], int y[M], int c[N])
{
    int output;
    for (int j = N - 1; j < M; j++)
    {
        output = 0;
        // Loop 2:
        for (int i = 0; i < N; i++)
        {
            output += c[i] * x[j - i];
        }

        y[j] = output;
    }
}
