#include <stdlib.h>

#define N 100

int DSP_dotprod(short x[N], short y[N])
{
//#pragma HLS STREAM variable=y dim=1
//#pragma HLS STREAM variable=x dim=1
#pragma HLS INTERFACE axis port=x
#pragma HLS INTERFACE axis port=y
    int sum = 0;

    for (int i = 0; i < N; i++)

#pragma HLS UNROLL
sum += x[i] * y[i];

    return sum;
}

int main()
{
    short x[N] = {0};
    short y[N] = {0};
    for (int i = 0; i < N; i++)
    {
        x[i] = i;
        y[i] = i;
    }
    int res = DSP_dotprod(x, y);
    printf("res: %d\n", res);
    return 0;
}
