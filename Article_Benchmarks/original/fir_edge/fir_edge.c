#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define LENGTH 600
#define SIZE WIDTH *LENGTH

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

int K[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

void fir_edge(int p1[SIZE], int p2[SIZE], int in[SIZE]);

void fir(int p1[SIZE], int p2[SIZE], int in[SIZE])
{
    for (int i = 0; i < SIZE; i++)
        in[i] = i;

    for (int row = 0; row <= LENGTH - 3; row++)
    {
        for (int col = 0; col <= WIDTH - 3; col++)
        {
            int sumval = 0;

            for (int wrow = 0; wrow < 3; wrow++)
            {
                for (int wcol = 0; wcol < 3; wcol++)
                {
                    sumval += in[(row + wrow) * WIDTH + col + wcol] * K[wrow * 3 + wcol];
                }
            }
            sumval = sumval >> 4;
            p1[row * WIDTH + col] = sumval;
        }
    }
}

void edge(int p1[SIZE], int p2[SIZE])
{
    for (int v = 0; v <= LENGTH - 3; v++)
    {
        for (int h = 0; h <= WIDTH - 3; h++)
        {
            int htmp = (p1[(v + 2) * WIDTH + h] - p1[v * WIDTH + h]) +
                       (p1[(v + 2) * WIDTH + h + 2] - p1[v * WIDTH + h + 2]) +
                       2 * (p1[(v + 2) * WIDTH + h + 1] - p1[v * WIDTH + h + 1]);

            htmp = (htmp < 0) ? -htmp : htmp;

            int vtmp = (p1[v * WIDTH + h + 2] - p1[v * WIDTH + h]) +
                       (p1[(v + 2) * WIDTH + h + 2] - p1[(v + 2) * WIDTH + h]) +
                       2 * (p1[(v + 1) * WIDTH + h + 2] - p1[(v + 1) * WIDTH + h]);

            vtmp = (vtmp < 0) ? -vtmp : vtmp;

            int sum = htmp + vtmp;

            sum = (sum > 255) ? 255 : sum;

            p2[(v + 1) * WIDTH + h + 1] = sum;
        }
    }
}

int main(void)
{
    int in[SIZE] = {0};
    int p1[SIZE] = {0};
    int p2[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        in[i] = rand() % __INT_MAX__;
        p1[i] = rand() % __INT_MAX__;
        p2[i] = rand() % __INT_MAX__;
    }

    fir(p1, p1, in);
    edge(p1, p2);

    for (int i = 0; i < SIZE; i++)
    {
        in[i] = rand() % __INT_MAX__;
        p1[i] = rand() % __INT_MAX__;
        p2[i] = rand() % __INT_MAX__;
    }

    fir_edge(p1, p2, in);

    return 0;
}

void fir_edge(int p1[SIZE], int p2[SIZE], int in[SIZE])
{
    for (int i = 0; i < SIZE; i++)
        in[i] = i;

    for (int row = 0; row <= LENGTH - 3; row++)
    {
        for (int col = 0; col <= WIDTH - 3; col++)
        {
            int sumval = 0;

            for (int wrow = 0; wrow < 3; wrow++)
            {
                for (int wcol = 0; wcol < 3; wcol++)
                {
                    sumval += in[(row + wrow) * WIDTH + col + wcol] * K[wrow * 3 + wcol];
                }
            }
            sumval = sumval >> 4;
            p1[row * WIDTH + col] = sumval;
        }
    }

    for (int v = 0; v <= LENGTH - 3; v++)
    {
        for (int h = 0; h <= WIDTH - 3; h++)
        {
            int htmp = (p1[(v + 2) * WIDTH + h] - p1[v * WIDTH + h]) +
                       (p1[(v + 2) * WIDTH + h + 2] - p1[v * WIDTH + h + 2]) +
                       2 * (p1[(v + 2) * WIDTH + h + 1] - p1[v * WIDTH + h + 1]);

            htmp = (htmp < 0) ? -htmp : htmp;

            int vtmp = (p1[v * WIDTH + h + 2] - p1[v * WIDTH + h]) +
                       (p1[(v + 2) * WIDTH + h + 2] - p1[(v + 2) * WIDTH + h]) +
                       2 * (p1[(v + 1) * WIDTH + h + 2] - p1[(v + 1) * WIDTH + h]);

            vtmp = (vtmp < 0) ? -vtmp : vtmp;

            int sum = htmp + vtmp;

            sum = (sum > 255) ? 255 : sum;

            p2[(v + 1) * WIDTH + h + 1] = sum;
        }
    }
}