#include <stdio.h>

void example(int a[2][2], int b[2])
{
    FILE *log_file_0 = fopen("example.dot", "w+");
    if (log_file_0 == NULL)
    {
        printf("Error opening file example.dot\n");
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
    int n_sum = 0;
    int n_j = 0;
    int n_a[2][2] = {0};
    int n_b[2] = {0};
    for (int _i = 0; _i < 2; _i++)
    {
        for (int _j = 0; _j < 2; _j++)
        {
            n_a[_i][_j]++;
            fprintf(log_file_0, "\"a[%d][%d]_%d_l\" [label=\"a[%d][%d]\", att1=var, att2=inte, att3=int];\n", _i, _j, n_a[_i][_j], _i, _j);
        }
    }
    for (int _i = 0; _i < 2; _i++)
    {
        n_b[_i]++;
        fprintf(log_file_0, "\"b[%d]_%d_l\" [label=\"b[%d]\", att1=var, att2=inte, att3=int];\n", _i, n_b[_i], _i);
    }
    //---------------------
    for (int i = 0; i < 2; i++)
    {
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"0\", att1=const];\n", n_const);
        n_sum++;
        fprintf(log_file_0, "\"sum_%d\" [label=\"sum\", att1=var, att2=loc, att3=int];\n", n_sum);
        n_ne++;
        fprintf(log_file_0, "\"const%d\" -> \"sum_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_sum, n_ne, n_ne);
        //---------------------
        int sum = 0;
        for (int j = 0; j < 2; j++)
        {
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            n_ne++;
            fprintf(log_file_0, "\"a[%d][%d]_%d_l\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", i, j, n_a[i][j], n_op, n_ne, n_ne);
            n_ne++;
            fprintf(log_file_0, "\"sum_%d\" -> \"op%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_sum, n_op, n_ne, n_ne);
            n_sum++;
            fprintf(log_file_0, "\"sum_%d\" [label=\"sum\", att1=var, att2=loc, att3=int];\n", n_sum);
            n_ne++;
            fprintf(log_file_0, "\"op%d\" -> \"sum_%d\" [label=\"%d\", ord=\"%d\"];\n", n_op, n_sum, n_ne, n_ne);
            //---------------------
            sum += a[i][j];
        }
        //---------------------
        n_b[i]++;
        fprintf(log_file_0, "\"b[%d]_%d_l\" [label=\"b[%d]\", att1=var, att2=inte, att3=int];\n", i, n_b[i], i);
        n_ne++;
        fprintf(log_file_0, "\"sum_%d\" -> \"b[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_sum, i, n_b[i], n_ne, n_ne);
        //---------------------
        b[i] = sum;
    }
    fprintf(log_file_0, "}");
    fclose(log_file_0);
}

int main()
{
    int a[2][2] = {0};
    int b[2] = {0};
    example(a, b);
    return 0;
}