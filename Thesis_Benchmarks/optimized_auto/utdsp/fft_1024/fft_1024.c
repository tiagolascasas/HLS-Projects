#include "traps.h"
/*1024-point complex FFT (radix-2, in-place, decimation-in-time)*/

/*Modified to use arrays - SMP*/

float data_real[1024];
float data_imag[1024];
float coef_real[1024];
float coef_imag[1024];
void fft(float data_real[1024], float data_imag[1024], float coef_real[1024], float coef_imag[1024]);
int main() {
   input_dsp(data_real, 1024, 0);
   for(int i = 0; i < 1024; i++) {
      /*was 256 - not ok?*/
      data_imag[i] = 1;
      coef_real[i] = 1;
      coef_imag[i] = 1;
   }
   fft(data_real, data_imag, coef_real, coef_imag);
   output_dsp(data_real, 1024, 0);
   output_dsp(data_imag, 1024, 0);
   output_dsp(coef_real, 1024, 0);
   output_dsp(coef_imag, 1024, 0);
}

void fft(float data_real[1024], float data_imag[1024], float coef_real[1024], float coef_imag[1024]) {
   #pragma HLS array_partition variable=data_real cyclic factor=10
   #pragma HLS array_partition variable=data_imag cyclic factor=10
   #pragma HLS array_partition variable=coef_real cyclic factor=10
   #pragma HLS array_partition variable=coef_imag cyclic factor=10
   /*data_real:         real data points*/
   /*data_imag:         imaginary data points*/
   /*coef_real:         real coefficient points*/
   /*coef_imag:         imaginary coefficient points*/
   float temp_real;
   float temp_imag;
   float Wr;
   float Wi;
   int groupsPerStage = 1;
   int buttersPerGroup = 512;
   for(int i = 0; i < 10; ++i) {
      #pragma MAX_ITER 1
      for(int j = 0; j < groupsPerStage; ++j) {
         #pragma HLS unroll
         #pragma HLS pipeline
         Wr = coef_real[(1 << i) - 1 + j];
         Wi = coef_imag[(1 << i) - 1 + j];
         #pragma MAX_ITER 512
         for(int k = 0; k < buttersPerGroup; ++k) {
            #pragma HLS unroll
            temp_real = Wr * data_real[2 * j * buttersPerGroup + buttersPerGroup + k] - Wi * data_imag[2 * j * buttersPerGroup + buttersPerGroup + k];
            temp_imag = Wi * data_real[2 * j * buttersPerGroup + buttersPerGroup + k] + Wr * data_imag[2 * j * buttersPerGroup + buttersPerGroup + k];
            data_real[2 * j * buttersPerGroup + buttersPerGroup + k] = data_real[2 * j * buttersPerGroup + k] - temp_real;
            data_real[2 * j * buttersPerGroup + k] += temp_real;
            data_imag[2 * j * buttersPerGroup + buttersPerGroup + k] = data_imag[2 * j * buttersPerGroup + k] - temp_imag;
            data_imag[2 * j * buttersPerGroup + k] += temp_imag;
         }
      }
      groupsPerStage <<= 1;
      buttersPerGroup >>= 1;
   }
}
