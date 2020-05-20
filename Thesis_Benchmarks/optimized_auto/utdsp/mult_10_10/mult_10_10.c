#include "traps.h"
/*[10x10] X [10x10] matrix multiply*/

/*Modified to use arrays - SMP*/

float a_matrix[10][10];
float b_matrix[10][10];
float c_matrix[10][10];
void mult(float a_matrix[10][10], float b_matrix[10][10], float c_matrix[10][10]);
int main() {
   input_dsp(a_matrix, 100, 0);
   input_dsp(b_matrix, 100, 0);
   mult(a_matrix, b_matrix, c_matrix);
   output_dsp(c_matrix, 100, 0);
   output_dsp(a_matrix, 100, 0);
   output_dsp(b_matrix, 100, 0);
   
   return 0;
}

void mult(float a_matrix[10][10], float b_matrix[10][10], float c_matrix[10][10]) {
   /*a_matrix:            input matrix A (row-major)*/
   /*b_matrix:            input matrix B (row-major)*/
   /*c_matrix:            output matrix C (row-major)*/
   float sum;
   for(int i = 0; i < 10; i++) {
      #pragma HLS  pipeline
      for(int j = 0; j < 10; j++) {
         #pragma HLS  pipeline
         sum = 0.0;
         for(int k = 0; k < 10; ++k) {
            #pragma HLS unroll factor=10
            #pragma HLS  pipeline
            sum += a_matrix[i][k] * b_matrix[k][j];
         }
         c_matrix[i][j] = sum;
      }
   }
}
