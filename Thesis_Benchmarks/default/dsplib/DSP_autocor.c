#include <stdlib.h>

#define M 16
#define N 32

int DSP_autocor(short ac[M], short sd[N + M])
{
    int i;
    int k;
    int sum;

    for (i = 0; i < M; i++)
    {
        sum = 0;
        for (k = 0; k < N; k++)
        {
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