#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//DSP_dotprod
#define NX 3

int DSP_dotprod(const short x[NX], const short y[NX])
{
    int sum = 0;
    int i;

    for (i = 0; i < NX; i++)
        sum += x[i] * y[i];

    return sum;
}

//autocor
#define N 2
#define M 4

void autcor(short ac[M], short sd[N + M])
{
    int i;
    int k;
    int sum;
    for (i = 0; i < N; i++)
    {
        sd[i] = i;
    }
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

//filter_subband_double
#define Nz 3
#define Ns 3
#define Nm 3
#define Ny 3

void filter_subband_double(double z[Nz], double s[Ns], double m[Nm])
{
    double y[Ny];
    int i, j;

    for (i = 0; i < Ny; i++)
    {
        y[i] = 0.0;
        for (j = 0; j < (Nz / Ny); j++)
        {
            y[i] += z[i + Ny * j];
        }
    }

    for (i = 0; i < Ns; i++)
    {
        s[i] = 0.0;
        for (j = 0; j < Ny; j++)
        {
            s[i] += m[Ns * i + j] * y[j];
        }
    }
}

//fir
#define M_FIR 257
#define N_FIR 32

void fir(int x[M_FIR], int y[M_FIR], int c[N_FIR])
{
    int output;

    for (int j = N_FIR - 1; j < M_FIR; j++)
    {
        output = 0;
        for (int i = 0; i < N_FIR; i++)
        {
            output += c[i] * x[j - i];
        }
        y[j] = output;
    }
}

//SVM
/*
#define D_sv 4
#define N_sv 4

void svm_predict_graph(float test_vector[D_sv], float *sum)
{
    float diff;
    float diff_extra;
    float norma;

    for (int i = 0; i < N_sv; i++)
    {

        norma = 0;

        for (int j = 0; j < D_sv; j++)
        {
            diff = test_vector[j] - sup_vectors[j][i];

            diff = diff * diff;
            norma = norma + diff;
        }

        *sum = *sum + (exp(-gamma * norma) * sv_coeff[i]);
    }
    *sum = *sum - b;
}*/

//edge detect
#define NE 128
#define K 5

void convolve2d(int input_image[NE][NE], int kernel[K][K], int output_image[NE][NE])
{
    int i;
    int j;
    int c;
    int r;
    int normal_factor;
    int sum;
    int dead_rows;
    int dead_cols;

    dead_rows = K / 2;
    dead_cols = K / 2;

    normal_factor = 0;
    for (r = 0; r < K; r++)
        for (c = 0; c < K; c++)
            normal_factor += abs(kernel[r][c]);

    if (normal_factor == 0)
        normal_factor = 1;

    for (r = 0; r < NE - K + 1; r++)
    {
        for (c = 0; c < NE - K + 1; c++)
        {
            sum = 0;
            for (i = 0; i < K; i++)
            {
                for (j = 0; j < K; j++)
                {
                    sum += input_image[r + i][c + j] * kernel[i][j];
                }
            }
            output_image[r + dead_rows][c + dead_cols] = (sum / normal_factor);
        }
    }
}

int main()
{
    const short x[NX] = {100, 200, 300};
    const short y[NX] = {300, 400, 500};
    DSP_dotprod(x, y);
    printf("DSP_dotprod finished\n");

    short ac[M] = {1, 2, 3, 4};
    short sd[N + M] = {1, 2, 3, 4, 5, 6};
    autcor(ac, sd);

    double z[Nz] = {1, 2, 3};
    double s[Ns] = {1, 2, 3};
    double m[Nm] = {1, 2, 3};
    filter_subband_double(z, s, m);
    printf("filter_subband_double finished\n");

    int input[M_FIR];
    int output[M_FIR];
    int coeff[N_FIR] = {1, 2, 4, -2, 1, 1, -3, 1, 1, 2, 4, -2, 1, 1, -3, 1, 1, 2, 4, -2, 1, 1, -3, 1, 1, 2, 4, -2, 1, 1, -3, 1};
    for (int i = 0; i < M_FIR; i++)
    {
        input[i] = i;
        output[i] = 0;
    }
    fir(input, output, coeff);
    printf("fir finished\n");
    /*
    float test_vector[18];
    float sum = 0;
    for (int i = 0; i < N_sv; i++)
    {
        sv_coeff[i] = 3;
        for (int j = 0; j < D_sv; j++)
        {
            sup_vectors[j][i] = j + 0, 01;
        }
    }
    for (int k = 0; k < D_sv; k++)
    {
        test_vector[k] = k;
    }
    svm_predict_graph(test_vector, &sum);*/

    int input_image[NE][NE];
    int output_image[NE][NE];
    int kernel[K][K];
    for (int i = 0; i < NE; i++)
        for (int j = 0; j < NE; i++)
            input_image[i][j] = rand() % 255;
    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++)
            kernel[i][j] = rand() % 255;
    convolve2d(input_image, kernel, output_image);
    printf("Edge detect finished\n");
}