/* [4x4] X [4x4] matrix multiply */

#define A_ROW 4
#define A_COL 4
#define B_ROW 4
#define B_COL 4

float a_matrix[4][4];
float b_matrix[4][4];
float c_matrix[4][4];

main()
{
  void mult();

  input_dsp(a_matrix,16,0);
  input_dsp(b_matrix,16,0);

  mult(a_matrix, b_matrix, c_matrix);

  output_dsp(c_matrix,16,0);
  output_dsp(a_matrix,16,0);
  output_dsp(b_matrix,16,0);
}

void mult(a_matrix, b_matrix, c_matrix)
float *a_matrix;		/* pointer to input matrix A (row-major) */
float *b_matrix;		/* pointer to input matrix B (row-major) */
float *c_matrix;		/* pointer to output matrix C (row-major) */
{
  int i, j, k;
  float *A, *B;
  float *a, *b;
  float sum;
  float term_a;
  float term_b;
  A = a_matrix;
  B = b_matrix;
  for (i = 0; i < A_ROW; i++) {
    for (j = 0; j < B_COL; j++) {
      a = A;
      b = B;
      sum = 0.0;
      for (k = 0; k < B_ROW; k++) {
        term_a = *a;
        term_b = *b;
        a++;
        b += B_COL;
        sum += term_a * term_b;
      }
      *c_matrix++ = sum;
      B++;
    }
    A += A_COL;
    B = b_matrix;
  }
}
