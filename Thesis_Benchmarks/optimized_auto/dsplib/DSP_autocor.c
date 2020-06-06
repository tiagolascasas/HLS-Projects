#include <stdlib.h>
int DSP_autocor(short ac[16], short sd[48]) {
   #pragma HLS array_partition variable=ac complete
   #pragma HLS array_partition variable=sd complete
   int i;
   int k;
   int sum;
   for(i = 0; i < 16; i++) {
      #pragma HLS pipeline
      sum = 0;
      for(k = 0; k < 32; k++) {
         #pragma HLS unroll
         sum += sd[k + 16] * sd[k + 16 - i];
      }
      ac[i] = (sum >> 15);
   }
}

int main() {
   short ac[16] = {0};
   short sd[48] = {0};
   for(int i = 0; i < 32 + 16; i++) {
      sd[i] = i;
   }
   DSP_autocor(ac, sd);
   
   return 0;
}
