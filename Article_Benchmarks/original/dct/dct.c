#include <stdio.h>

#define N 8
#define M N *N

const int CosBlock[8][8] = {88, 122, 115, 103, 88, 69, 47, 24,
                            88, 103, 47, -24, -88, -122, -115, -69,
                            88, 69, -47, -122, -88, 24, 115, 103,
                            88, 24, -115, -69, 88, 103, -47, -122,
                            88, -24, -115, 69, 88, -103, -47, 122,
                            88, -69, -47, 122, -88, -24, 115, -103,
                            88, -103, 47, 24, -88, 122, -115, 69,
                            88, -122, 115, -103, 88, -69, 47, -24};

void dct(
    int InIm[N][N],
    int TempBlock[N][N],
    int CosTrans[N][N],
    int OutIm[N][N])
{
    int i, j, k, aux;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            aux = 0;
            for (k = 0; k < N; k++)
                aux += InIm[i][k] * CosTrans[k][j];
            TempBlock[i][j] = aux;
        }

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            aux = 0;
            for (k = 0; k < N; k++)
                aux += TempBlock[k][j] * CosBlock[i][k];
            OutIm[i][j] = aux;
        }
}

int main()
{
    int InIm[N][N] = {0};
    int TempBlock[N][N] = {0};
    int CosTrans[N][N] = {0};
    int OutIm[N][N] = {0};
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            CosTrans[j][i] = CosBlock[i][j];
            InIm[N][N] = i;
        }
    }

    dct(InIm, TempBlock, CosTrans, OutIm);

    int checksum = 0;
    for (i = 0; i < N; i++)
    {
        for (i = 0; i < N; i++)
            checksum += OutIm[i][j];
    }
    printf("%d\n", checksum);

    return 0;
}
