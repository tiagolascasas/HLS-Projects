/* [4x4] X [4x4] matrix multiply */
/* Modified to use arrays - SMP */

#include "traps.h"

#define A_ROW 4
#define A_COL 4
#define B_ROW 4
#define B_COL 4

float a_matrix[4][4];
float b_matrix[4][4];
float c_matrix[4][4];

void mult(float a_matrix[A_ROW][A_COL], float b_matrix[B_ROW][B_COL],
          float c_matrix[A_ROW][B_COL]);

main()
{

    input_dsp(a_matrix, 16, 0);
    input_dsp(b_matrix, 16, 0);

    mult(a_matrix, b_matrix, c_matrix);

    output_dsp(c_matrix, 16, 0);
    output_dsp(a_matrix, 16, 0);
    output_dsp(b_matrix, 16, 0);
}

void mult(float a_matrix[A_ROW][A_COL], float b_matrix[B_ROW][B_COL],
          float c_matrix[A_ROW][B_COL])
/*    a_matrix:            input matrix A (row-major) */
/*    b_matrix:            input matrix B (row-major) */
/*    c_matrix:            output matrix C (row-major) */
{
    int i, j, k;

    float sum;

    for (i = 0; i < A_ROW; i++)
    {
        for (j = 0; j < B_COL; j++)
        {
            sum = 0.0;
            for (k = 0; k < B_ROW; ++k)
            {
                sum += a_matrix[i][k] * b_matrix[k][j];
            }
            c_matrix[i][j] = sum;
        }
    }
}
