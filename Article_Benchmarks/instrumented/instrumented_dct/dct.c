#include <stdio.h>
#include <stdlib.h>

#define N 8

int const CosBlock[N][N] = {88, 122, 115, 103, 88, 69, 47, 24, 88, 103, 47, -24, -88, -122, -115, -69, 88, 69, -47, -122, -88, 24, 115, 103, 88, 24, -115, -69, 88, 103, -47, -122, 88, -24, -115, 69, 88, -103, -47, 122, 88, -69, -47, 122, -88, -24, 115, -103, 88, -103, 47, 24, -88, 122, -115, 69, 88, -122, 115, -103, 88, -69, 47, -24};
void dct(int InIm[N][N], int TempBlock[N][N], int CosTrans[N][N], int OutIm[N][N])
{
    FILE *log_file_0 = fopen("dct.dot", "w+");
    if (log_file_0 == NULL)
    {
        printf("Error opening file dct.dot\n");
        exit(1);
    }
    fprintf(log_file_0, "Digraph G {\n");
    //---------------------
    int n_const = 0;
    int n_temp = 0;
    int n_op = 0;
    int n_mux = 0;
    int n_ne = 0;
    int n_i = 0;
    int n_j = 0;
    int n_k = 0;
    int n_aux = 0;
    int n_InIm[N][N] = {0};
    int n_TempBlock[N][N] = {0};
    int n_CosTrans[N][N] = {0};
    int n_OutIm[N][N] = {0};
    int n_CosBlock[N][N] = {0};
    for (int _i = 0; _i < N; _i++)
    {
        for (int _j = 0; _j < N; _j++)
        {
            n_InIm[_i][_j]++;
            fprintf(log_file_0, "\"InIm[%d][%d]_%d_l\" [label=\"InIm[%d][%d]\", att1=var, att2=inte, att3=int];\n", _i, _j, n_InIm[_i][_j], _i, _j);
        }
    }
    for (int _i = 0; _i < N; _i++)
    {
        for (int _j = 0; _j < N; _j++)
        {
            n_TempBlock[_i][_j]++;
            fprintf(log_file_0, "\"TempBlock[%d][%d]_%d_l\" [label=\"TempBlock[%d][%d]\", att1=var, att2=inte, att3=int];\n", _i, _j, n_TempBlock[_i][_j], _i, _j);
        }
    }
    for (int _i = 0; _i < N; _i++)
    {
        for (int _j = 0; _j < N; _j++)
        {
            n_CosTrans[_i][_j]++;
            fprintf(log_file_0, "\"CosTrans[%d][%d]_%d_l\" [label=\"CosTrans[%d][%d]\", att1=var, att2=inte, att3=int];\n", _i, _j, n_CosTrans[_i][_j], _i, _j);
        }
    }
    for (int _i = 0; _i < N; _i++)
    {
        for (int _j = 0; _j < N; _j++)
        {
            n_CosBlock[_i][_j]++;
            fprintf(log_file_0, "\"CosBlock[%d][%d]_%d_l\" [label=\"CosBlock[%d][%d]\", att1=var, att2=inte, att3=int];\n", _i, _j, n_CosBlock[_i][_j], _i, _j);
        }
    }
    //---------------------
    //---------------------
    //---------------------
    int i, j, k, aux;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            //---------------------
            n_const++;
            fprintf(log_file_0, "\"const%d\" [label=\"0\", att1=const];\n", n_const);
            n_aux++;
            fprintf(log_file_0, "\"aux_%d\" [label=\"aux\", att1=var, att2=loc, att3=int];\n", n_aux);
            n_ne++;
            fprintf(log_file_0, "\"const%d\" -> \"aux_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_aux, n_ne, n_ne);
            //---------------------
            aux = 0;
            for (k = 0; k < N; k++)
            {
                //---------------------
                n_op++;
                fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
                n_ne++;
                fprintf(log_file_0, "\"CosTrans[%d][%d]_%d_l\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", k, j, n_CosTrans[k][j], n_op, n_ne, n_ne);
                n_ne++;
                fprintf(log_file_0, "\"InIm[%d][%d]_%d_l\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", i, k, n_InIm[i][k], n_op, n_ne, n_ne);
                n_temp++;
                fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
                n_ne++;
                fprintf(log_file_0, "\"op%d\" -> \"temp%d\" [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, n_ne, n_ne);
                n_op++;
                fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
                n_ne++;
                fprintf(log_file_0, "\"temp%d\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp, n_op, n_ne, n_ne);
                n_ne++;
                fprintf(log_file_0, "\"aux_%d\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_aux, n_op, n_ne, n_ne);
                n_aux++;
                fprintf(log_file_0, "\"aux_%d\" [label=\"aux\", att1=var, att2=loc, att3=int];\n", n_aux);
                n_ne++;
                fprintf(log_file_0, "\"op%d\" -> \"aux_%d\" [label=\"%d\", ord=\"%d\"];\n", n_op, n_aux, n_ne, n_ne);
                //---------------------
                aux += InIm[i][k] * CosTrans[k][j];
            }
            //---------------------
            n_TempBlock[i][j]++;
            fprintf(log_file_0, "\"TempBlock[%d][%d]_%d_l\" [label=\"TempBlock[%d][%d]\", att1=var, att2=inte, att3=int];\n", i, j, n_TempBlock[i][j], i, j);
            n_ne++;
            fprintf(log_file_0, "\"aux_%d\" -> \"TempBlock[%d][%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_aux, i, j, n_TempBlock[i][j], n_ne, n_ne);
            //---------------------
            TempBlock[i][j] = aux;
        }
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            //---------------------
            n_const++;
            fprintf(log_file_0, "\"const%d\" [label=\"0\", att1=const];\n", n_const);
            n_aux++;
            fprintf(log_file_0, "\"aux_%d\" [label=\"aux\", att1=var, att2=loc, att3=int];\n", n_aux);
            n_ne++;
            fprintf(log_file_0, "\"const%d\" -> \"aux_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_aux, n_ne, n_ne);
            //---------------------
            aux = 0;
            for (k = 0; k < N; k++)
            {
                //---------------------
                n_op++;
                fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
                n_ne++;
                fprintf(log_file_0, "\"CosBlock[%d][%d]_%d_l\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", i, k, n_CosBlock[i][k], n_op, n_ne, n_ne);
                n_ne++;
                fprintf(log_file_0, "\"TempBlock[%d][%d]_%d_l\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", k, j, n_TempBlock[k][j], n_op, n_ne, n_ne);
                n_temp++;
                fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
                n_ne++;
                fprintf(log_file_0, "\"op%d\" -> \"temp%d\" [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, n_ne, n_ne);
                n_op++;
                fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
                n_ne++;
                fprintf(log_file_0, "\"temp%d\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp, n_op, n_ne, n_ne);
                n_ne++;
                fprintf(log_file_0, "\"aux_%d\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_aux, n_op, n_ne, n_ne);
                n_aux++;
                fprintf(log_file_0, "\"aux_%d\" [label=\"aux\", att1=var, att2=loc, att3=int];\n", n_aux);
                n_ne++;
                fprintf(log_file_0, "\"op%d\" -> \"aux_%d\" [label=\"%d\", ord=\"%d\"];\n", n_op, n_aux, n_ne, n_ne);
                //---------------------
                aux += TempBlock[k][j] * CosBlock[i][k];
            }
            //---------------------
            n_OutIm[i][j]++;
            fprintf(log_file_0, "\"OutIm[%d][%d]_%d_l\" [label=\"OutIm[%d][%d]\", att1=var, att2=inte, att3=int];\n", i, j, n_OutIm[i][j], i, j);
            n_ne++;
            fprintf(log_file_0, "\"aux_%d\" -> \"OutIm[%d][%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_aux, i, j, n_OutIm[i][j], n_ne, n_ne);
            //---------------------
            OutIm[i][j] = aux;
        }
    fprintf(log_file_0, "}");
    fclose(log_file_0);
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
