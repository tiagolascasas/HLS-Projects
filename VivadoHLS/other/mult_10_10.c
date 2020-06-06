/* [10x10] X [10x10] matrix multiply */
/* Modified to use arrays - SMP */

#define A_ROW 10
#define A_COL 10
#define B_ROW 10
#define B_COL 10

void mult(float a_matrix[A_ROW][A_COL], float b_matrix[B_ROW][B_COL], float c_matrix[A_ROW][B_COL])
{
#pragma HLS STREAM variable=c_matrix dim=2
//#pragma HLS STREAM variable=b_matrix dim=2
//#pragma HLS STREAM variable=a_matrix dim=2
    float sum;

    for (int i = 0; i < A_ROW; i++)
    {
        for (int j = 0; j < B_COL; j++)
        {
            sum = 0.0;
            for (int k = 0; k < B_ROW; ++k)
            {
                sum += a_matrix[i][k] * b_matrix[k][j];
            }
            c_matrix[i][j] = sum;
        }
    }
}
