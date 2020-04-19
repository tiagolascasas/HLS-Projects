/* [10x10] X [10x10] matrix multiply */
/* Modified to use arrays - SMP */

#include <stdio.h>
#include "traps.h"

#define ROW 10
#define COL 10

float a_matrix[ROW][COL];
float b_matrix[ROW][COL];
float c_matrix[ROW][COL];

void mult(float a_matrix[ROW][COL], float b_matrix[ROW][COL],
          float c_matrix[ROW][COL]);

int main()
{

    input_dsp(a_matrix, ROW * COL, 0);
    input_dsp(b_matrix, ROW * COL, 0);

    mult(a_matrix, b_matrix, c_matrix);

    output_dsp(c_matrix, ROW * COL, 0);
    output_dsp(a_matrix, ROW * COL, 0);
    output_dsp(b_matrix, ROW * COL, 0);
    return 0;
}

void mult(float a_matrix[ROW][COL], float b_matrix[ROW][COL],
          float c_matrix[ROW][COL])
/*    a_matrix:            input matrix A (row-major) */
/*    b_matrix:            input matrix B (row-major) */
/*    c_matrix:            output matrix C (row-major) */
{
    //---------------------
    FILE *f = fopen("mmult_10_10.dot", "w");
    int n_const = 0;
    int n_temp = 0;
    int n_sum = 0;
    int ne = 0;
    int n_op = 0;
    int n_a_matrix[ROW][COL] = {0};
    int n_b_matrix[ROW][COL] = {0};
    int n_c_matrix[ROW][COL] = {0};
    fprintf(f, "Digraph G{\n");
    //---------------------

    float sum;

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            //---------------------
            n_const++;
            fprintf(f, "const%d [label=\"0.0\", att1=const];\n", n_const);
            fprintf(f, "\"sum_%d\" [label=sum, att1=var, att2=loc, att3=float ];\n", n_sum + 1);
            ne++;
            fprintf(f, "const%d->\"sum_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_sum + 1, ne, ne);
            n_sum++;
            //---------------------
            sum = 0.0;
            for (int k = 0; k < ROW; ++k)
            {
                //---------------------
                // a_matrix[i][k]
                n_a_matrix[i][k]++;
                fprintf(f, "\"a_matrix[%d][%d]_%d_l\" [label=\"a_matrix[%d][%d]\", att1=var, att2=inte, att3=float ];\n", i, k, n_a_matrix[i][k], i, k);
                // b_matrix[k][j]
                n_b_matrix[i][k]++;
                fprintf(f, "\"b_matrix[%d][%d]_%d_l\" [label=\"b_matrix[%d][%d]\", att1=var, att2=inte, att3=float ];\n", k, j, n_b_matrix[k][j], k, j);
                // *
                n_op++;
                fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
                // temp res of *
                n_temp++;
                fprintf(f, "temp%d [label=\"temp_l44_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
                // edges of *
                ne++;
                fprintf(f, "\"a_matrix[%d][%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", i, k, n_a_matrix[i][k], n_op, ne, ne);
                ne++;
                fprintf(f, "\"b_matrix[%d][%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", k, j, n_b_matrix[k][j], n_op, ne, ne);
                ne++;
                fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);
                // temp res of +
                fprintf(f,"temp%d [label=\"temp_l44_i%d\", att1=var, att2=loc, att3=float ];\n",n_temp,n_temp);
                // sum
                fprintf(f,"\"sum_%d\" [label=sum, att1=var, att2=loc, att3=float ];\n",n_sum);
                // +
                n_op++;
                fprintf(f,"op%d [label=\"+\", att1=op ];\n",n_op);
                // sum
                fprintf(f,"\"sum_%d\" [label=sum, att1=var, att2=loc, att3=int ];\n",n_sum+1);
                // edges of +
                ne++;		   
                fprintf(f,"temp%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n",n_temp,n_op,ne,ne);
                ne++;
                fprintf(f,"\"sum_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n",n_sum,n_op,ne,ne);
                ne++;
                fprintf(f,"op%d->\"sum_%d\" [label=\"%d\", ord=\"%d\"];\n",n_op,n_sum+1,ne,ne);
                n_sum++;
                //---------------------
                sum += a_matrix[i][k] * b_matrix[k][j];
            }
            //---------------------
            // c_matrix[i][j]
            n_c_matrix[i][j]++;
            fprintf(f, "\"c_matrix[%d][%d]_%d_l\" [label=\"c_matrix[%d][%d]\", att1=var, att2=inte, att3=float ];\n", i, j, n_c_matrix[i][j], i, j);
            // edge
            ne++;
            fprintf(f,"sum_%d->\"c_matrix[%d][%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n",n_sum,i,j,n_c_matrix[i][j],ne,ne);
            
            //---------------------
            c_matrix[i][j] = sum;
        }
    }

    //---------------------
    fprintf(f, "}\n");
    fclose(f);
    //---------------------
}
