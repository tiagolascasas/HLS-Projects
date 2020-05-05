#include <stdio.h>
#include <stdlib.h>
/**
*  A smooth image kernel.
*  Also known as a 2D FIR
*/
#define WIDTH 350
#define HEIGHT 350

int k[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

void smooth(int in[WIDTH][HEIGHT], int out[WIDTH][HEIGHT])
{
    FILE *log_file_0 = fopen("smooth.dot", "w+");
    if (log_file_0 == NULL)
    {
        printf("Error opening file smooth.dot\n");
        exit(1);
    }
    fprintf(log_file_0, "Digraph G {\n");
    //---------------------
    int n_const = 0;
    int n_temp = 0;
    int n_op = 0;
    int n_mux = 0;
    int ne = 0;
    int n_j = 0;
    int n_i = 0;
    int n_r = 0;
    int n_c = 0;
    int n_sum = 0;
    int n_k[3][3] = {0};
    int n_in[WIDTH][HEIGHT] = {0};
    int n_out[WIDTH][HEIGHT] = {0};
    for (int _i = 0; _i < 3; _i++)
    {
        for (int _j = 0; _j < 3; _j++)
        {
            n_k[_i][_j]++;
            fprintf(log_file_0, "\"k[%d][%d]_%d_l\" [label=\"k[%d][%d]\", att1=var, att2=inte, att3=int ];\n", _i, _j, n_k[_i][_j], _i, _j);
        }
    }
    for (int _i = 0; _i < WIDTH; _i++)
    {
        for (int _j = 0; _j < HEIGHT; _j++)
        {
            n_in[_i][_j]++;
            fprintf(log_file_0, "\"in[%d][%d]_%d_l\" [label=\"in[%d][%d]\", att1=var, att2=inte, att3=int ];\n", _i, _j, n_in[_i][_j], _i, _j);
        }
    }
    //---------------------
    //---------------------
    //---------------------
    int j, i, r, c, sum;
    //---------------------
    //---------------------
    for (j = 0; j < WIDTH - 2; j++)
    {
        for (i = 0; i < HEIGHT - 2; i++)
        {
            //---------------------
            n_const++;
            fprintf(log_file_0, "const%d [label=\"0\", att1=const];\n", n_const);
            n_sum++;
            fprintf(log_file_0, "\"sum_%d\" [label=sum, att1=var, att2=loc, att3=int ];\n", n_sum);
            ne++;
            fprintf(log_file_0, "const%d->\"sum_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_sum, ne, ne);
            //---------------------
            sum = 0;
            for (r = 0; r < 3; r++)
            {
                for (c = 0; c < 3; c++)
                {
                    //---------------------
                    n_op++;
                    fprintf(log_file_0, "op%d [label=\"*\", att1=op];\n", n_op);
                    n_temp++;
                    fprintf(log_file_0, "temp%d [label=\"temp%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
                    ne++;
                    fprintf(log_file_0, "\"in[%d][%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", j + r, i + c, n_in[j + r][i + c], n_op, ne, ne);
                    ne++;
                    fprintf(log_file_0, "\"k[%d][%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", r, c, n_k[r][c], n_op, ne, ne);
                    ne++;
                    fprintf(log_file_0, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

                    n_op++;
                    fprintf(log_file_0, "op%d [label=\"+\", att1=op];\n", n_op);
                    ne++;
                    fprintf(log_file_0, "temp%d->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp, n_op, ne, ne);
                    ne++;
                    fprintf(log_file_0, "sum_%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_sum, n_op, ne, ne);
                    n_sum++;
                    fprintf(log_file_0, "\"sum_%d\" [label=sum, att1=var, att2=loc, att3=int ];\n", n_sum);
                    ne++;
                    fprintf(log_file_0, "op%d->sum_%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_sum, ne, ne);
                    //---------------------
                    sum += in[j + r][i + c] * k[r][c];
                }
            }
            //---------------------
            n_op++;
            fprintf(log_file_0, "op%d [label=\"/\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "sum_%d->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_sum, n_op, ne, ne);
            n_const++;
            fprintf(log_file_0, "const%d [label=\"16\", att1=const];\n", n_const);
            ne++;
            fprintf(log_file_0, "const%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);
            n_sum++;
            fprintf(log_file_0, "\"sum_%d\" [label=sum, att1=var, att2=loc, att3=int ];\n", n_sum);
            ne++;
            fprintf(log_file_0, "op%d->sum_%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_sum, ne, ne);
            //---------------------
            sum = sum / 16;
            //---------------------
            n_out[j + 1][i + 1]++;
            fprintf(log_file_0, "\"out[%d][%d]_%d_l\" [label=\"out[%d][%d]\", att1=var, att2=inte, att3=int ];\n", j + 1, i + 1, n_out[j + 1][i + 1], j + 1, i + 1);
            ne++;
            fprintf(log_file_0, "sum_%d->\"out[%d][%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_sum, j + 1, i + 1, n_out[j + 1][i + 1], ne, ne);
            //---------------------
            out[j + 1][i + 1] = sum;
        }
    }
    //---------------------
    fprintf(log_file_0, "}\n");
    //---------------------
    fclose(log_file_0);
}

int in[WIDTH][HEIGHT];
int out[WIDTH][HEIGHT];
/*
* a main just to execute smooth;
*/
int main()
{
    int i, j;
    /*for now a simple inicialization*/
    for (j = 0; j < WIDTH; j++)
    {
        for (i = 0; i < HEIGHT; i++)
        {
            in[j][i] = i;
        }
    }
    smooth(in, out);
    /*some validity checking*/
    long checksum = 0;
    for (j = 0; j < WIDTH; j++)
    {
        for (i = 0; i < HEIGHT; i++)
        {
            checksum += out[j][i];
        }
    }
    printf("checksum = %ld\n", checksum);
    if (checksum == 21132648)
        printf("RIGHT!\n");
    else
        printf("WRONG!\n");
}
