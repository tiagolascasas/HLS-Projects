#include <stdio.h>
#include <stdlib.h>

#define N 100

void fir_k_a(int t[N], int o[N], int a[N], int m[N][N])
{
    FILE *log_file_0 = fopen("fir_k_a.dot", "w+");
    if (log_file_0 == NULL)
    {
        printf("Error opening file fir_k_a.dot\n");
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
    int n_t[N] = {0};
    int n_o[N] = {0};
    int n_a[N] = {0};
    int n_m[N][N] = {0};
    for (int _i = 0; _i < N; _i++)
    {
        n_t[_i]++;
        fprintf(log_file_0, "\"t[%d]_%d_l\" [label=\"t[%d]\", att1=var, att2=inte, att3=int];\n", _i, n_t[_i], _i);
    }
    for (int _i = 0; _i < N; _i++)
    {
        n_o[_i]++;
        fprintf(log_file_0, "\"o[%d]_%d_l\" [label=\"o[%d]\", att1=var, att2=inte, att3=int];\n", _i, n_o[_i], _i);
    }
    for (int _i = 0; _i < N; _i++)
    {
        n_a[_i]++;
        fprintf(log_file_0, "\"a[%d]_%d_l\" [label=\"a[%d]\", att1=var, att2=inte, att3=int];\n", _i, n_a[_i], _i);
    }
    for (int _i = 0; _i < N; _i++)
    {
        for (int _j = 0; _j < N; _j++)
        {
            n_m[_i][_j]++;
            fprintf(log_file_0, "\"m[%d][%d]_%d_l\" [label=\"m[%d][%d]\", att1=var, att2=inte, att3=int];\n", _i, _j, n_m[_i][_j], _i, _j);
        }
    }
    //---------------------
    //---------------------
    //---------------------
    //---------------------
    //---------------------
    int i, j;
    for (i = 0; i < N; i++)
    {
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"0\", att1=const];\n", n_const);
        n_t[i]++;
        fprintf(log_file_0, "\"t[%d]_%d_l\" [label=\"t[%d]\", att1=var, att2=inte, att3=int];\n", i, n_t[i], i);
        n_ne++;
        fprintf(log_file_0, "\"const%d\" -> \"t[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_const, i, n_t[i], n_ne, n_ne);
        //---------------------
        t[i] = 0;
        for (j = 0; j < 3; j++)
        {
            //---------------------
            n_const++;
            fprintf(log_file_0, "\"const%d\" [label=\"2\", att1=const];\n", n_const);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
            n_ne++;
            fprintf(log_file_0, "\"const%d\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, n_ne, n_ne);
            n_ne++;
            fprintf(log_file_0, "\"a[%d]_%d_l\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", i - j + 2, n_a[i - j + 2], n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=int];\n", n_temp, n_temp);
            n_ne++;
            fprintf(log_file_0, "\"op%d\" -> \"temp%d\" [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            n_ne++;
            fprintf(log_file_0, "\"temp%d\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp, n_op, n_ne, n_ne);
            n_ne++;
            fprintf(log_file_0, "\"t[%d]_%d_l\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", i, n_t[i], n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=int];\n", n_temp, n_temp);
            n_ne++;
            fprintf(log_file_0, "\"op%d\" -> \"temp%d\" [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, n_ne, n_ne);
            n_t[i]++;
            fprintf(log_file_0, "\"t[%d]_%d_l\" [label=\"t[%d]\", att1=var, att2=inte, att3=int];\n", i, n_t[i], i);
            n_ne++;
            fprintf(log_file_0, "\"temp%d\" -> \"t[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_temp, i, n_t[i], n_ne, n_ne);
            //---------------------
            t[i] = t[i] + (a[i - j + 2] >> 2);
        }
    }
    for (i = 0; i < N; i++)
    {
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"0\", att1=const];\n", n_const);
        n_o[i]++;
        fprintf(log_file_0, "\"o[%d]_%d_l\" [label=\"o[%d]\", att1=var, att2=inte, att3=int];\n", i, n_o[i], i);
        n_ne++;
        fprintf(log_file_0, "\"const%d\" -> \"o[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_const, i, n_o[i], n_ne, n_ne);
        //---------------------
        o[i] = 0;
        for (j = 0; j < N; j++)
        {
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            n_ne++;
            fprintf(log_file_0, "\"t[%d]_%d_l\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", j, n_t[j], n_op, n_ne, n_ne);
            n_ne++;
            fprintf(log_file_0, "\"m[%d][%d]_%d_l\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", i, j, n_m[i][j], n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=int];\n", n_temp, n_temp);
            n_ne++;
            fprintf(log_file_0, "\"op%d\" -> \"temp%d\" [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            n_ne++;
            fprintf(log_file_0, "\"temp%d\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp, n_op, n_ne, n_ne);
            n_ne++;
            fprintf(log_file_0, "\"o[%d]_%d_l\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", i, n_o[i], n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=int];\n", n_temp, n_temp);
            n_ne++;
            fprintf(log_file_0, "\"op%d\" -> \"temp%d\" [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, n_ne, n_ne);
            n_o[i]++;
            fprintf(log_file_0, "\"o[%d]_%d_l\" [label=\"o[%d]\", att1=var, att2=inte, att3=int];\n", i, n_o[i], i);
            n_ne++;
            fprintf(log_file_0, "\"temp%d\" -> \"o[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_temp, i, n_o[i], n_ne, n_ne);
            //---------------------
            o[i] = o[i] + m[i][j] * t[j];
        }
    }
    fprintf(log_file_0, "}");
    fclose(log_file_0);
}

int main()
{
    int t[N] = {0};
    int o[N] = {0};
    int a[N] = {0};
    int m[N][N] = {0};
    for (int i = 0; i < N; i++)
    {
        t[N] = 123;
        o[N] = 345;
        a[N] = 233;
        for (int j = 0; j < N; j++)
            m[i][j] = 127 + 129;
    }
    fir_k_a(t, o, a, m);
    int checksum = 0;
    for (int i = 0; i < N; i++)
        checksum += o[i];
    printf("checksum: %d\n", checksum);

    return 0;
}
