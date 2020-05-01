#include <stdio.h>
#include <stdlib.h>

#define NR1 (8)
#define NC1 (4)
#define NC2 (8)

void DSPF_sp_mat_mul_cplx_cn(float x1[2 * NR1 * NC1], int r1, int c1, float x2[2 * NC1 * NC2], int c2, float y[2 * NR1 * NC2])
{
    float real, imag;
    int i, j, k;

    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            real = 0;
            imag = 0;

            for (k = 0; k < c1; k++)
            {
                real += (x1[i * 2 * c1 + 2 * k] * x2[k * 2 * c2 + 2 * j] - x1[i * 2 * c1 + 2 * k + 1] * x2[k * 2 * c2 + 2 * j + 1]);
                imag += (x1[i * 2 * c1 + 2 * k] * x2[k * 2 * c2 + 2 * j + 1] + x1[i * 2 * c1 + 2 * k + 1] * x2[k * 2 * c2 + 2 * j]);
            }
            y[i * 2 * c2 + 2 * j] = real;
            y[i * 2 * c2 + 2 * j + 1] = imag;
        }
    }
}

int main()
{
    float ptr_y_cn[2 * NR1 * NC2] = {0};
    for (int i = 0; i < 2 * NR1 * NC2; i++)
        ptr_y_cn[i] = rand();

    float ptr_x1[2 * NR1 * NC1] = {0};
    for (int i = 0; i < 2 * NR1 * NC1; i++)
        ptr_x1[i] = rand();

    float ptr_x2[2 * NC1 * NC2] = {0};
    for (int i = 0; i < 2 * NC1 * NC2; i++)
        ptr_x2[i] = rand();

    DSPF_sp_mat_mul_cplx_cn(ptr_x1, NR1, NC1, ptr_x2, NC2, ptr_y_cn);

    return 0;
}