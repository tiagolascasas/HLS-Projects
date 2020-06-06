#include "traps.h"
/*32nd-order Normalized Lattice filter processing 64 points*/

/*Modified to use arrays - SMP*/

float input[64];
float output[64];
/*the following values of coefficient and internal_state is define arbitrary*/

float coefficient[64] = {0.25, 0.51, 0.75, -0.25, 0.5, 0.75, 0.7, 0.625, 0.21, 0.22, 0.93, 0.81, 0.48, 0.208, 0.4, 0.6, 0.25, 0.35, 0.875, 0.295, 0.25, 0.725, 0.380, 0.295, 0.2, 0.22, 0.73, 0.91, 0.48, 0.28, 0.694, 0.6, 0.25, 0.5, 0.75, 0.525, 0.5, 0.75, -0.5, 0.725, 0.62, 0.272, 0.83, 0.81, 0.48, 0.28, 0.814, 0.56, 0.25, 0.5, 0.75, -0.25, 0.5, 0.75, -0.810, 0.25, 0.02, 0.252, 0.913, 0.81, 0.468, 0.28, 0.4, 0.36};
float internal_state[64] = {0.25, 0.5, 0.75, -0.29, 0.5, 0.75, -0.3, 0.422, 0.82, 0.922, 0.63, 0.71, 0.48, 0.218, -0.24, 0.6, 0.92, 0.22, 0.93, 0.51, 0.498, 0.28, -0.84, 0.26, 0.25, 0.95, 0.75, -0.27, 0.5, 0.75, 0.80, 0.25, 0.25, 0.25, 0.735, -0.25, 0.5, 0.75, 0.20, 0.525, 0.92, 0.22, 0.31, 0.81, 0.468, 0.288, -0.14, 0.65, 0.2, 0.272, 0.93, 0.91, 0.485, 0.218, -0.4, 0.6, 0.82, 0.72, 0.63, 0.21, 0.438, 0.928, -0.24, 0.6};
void latnrm(float data[64], float outa[64], float coefficient[64], float internal_state[64]);
int main() {
   input_dsp(input, 64, 0);
   /*new added*/
   latnrm(input, output, coefficient, internal_state);
   output_dsp(output, 64, 0);
   /*new added*/
}

void latnrm(float data[64], float outa[64], float coefficient[64], float internal_state[64]) {
   #pragma HLS stream variable=data
   #pragma HLS array_partition variable=outa complete
   #pragma HLS array_partition variable=coefficient complete
   #pragma HLS array_partition variable=internal_state complete
   /*data:            input sample array*/
   /*outa:            output sample array*/
   /*coefficient:     coefficient array*/
   /*internal_state:  internal state array*/
   int i;
   int j;
   float left;
   float right;
   float top;
   float bottom = 0;
   float sum;
   /**/
   for(i = 0; i < 64; i++) {
      #pragma HLS pipeline
      top = data[i];
      for(j = 1; j < 32; j++) {
         #pragma HLS unroll
         left = top;
         right = internal_state[j];
         internal_state[j] = bottom;
         top = coefficient[j - 1] * left - coefficient[j] * right;
         bottom = coefficient[j - 1] * right + coefficient[j] * left;
      }
      internal_state[32] = bottom;
      internal_state[33] = top;
      sum = 0.0;
      for(j = 0; j < 32; j++) {
         #pragma HLS unroll
         sum += internal_state[j] * coefficient[j + 32];
      }
      outa[i] = sum;
   }
}
