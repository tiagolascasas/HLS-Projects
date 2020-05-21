#include <stdlib.h>

#define M 16
#define N 32

void DSP_autocor(short ac[M], short sd[N + M])
{
#pragma HLS ARRAY_PARTITION variable=sd complete dim=1
#pragma HLS STREAM variable=ac dim=1
    int i;
    int k;
    int sum;

    for (i = 0; i < M; i++)
    {
        sum = 0;
        for (k = 0; k < N; k++)
        {
#pragma HLS UNROLL factor=16
            sum += sd[k + M] * sd[k + M - i];
        }
        ac[i] = (sum >> 15);
    }
}

int main()
{
    short ac[M] = {0};
    short sd[N + M] = {0};
    for (int i = 0; i < N + M; i++)
    {
        sd[i] = i;
    }
    DSP_autocor(ac, sd);
    return 0;
}
