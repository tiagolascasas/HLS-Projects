#include <stdio.h>
void fir_k_a(int t[100], int o[100], int a[100], int m[100][100]) {
   #pragma HLS stream variable=m
   int i;
   int j;
   for(i = 0; i < 100; i++) {
      #pragma HLS  pipeline
      t[i] = 0;
      for(j = 0; j < 3; j++) {
         #pragma HLS unroll factor=3
         #pragma HLS  pipeline
         t[i] = t[i] + (a[i - j + 2] >> 2);
      }
   }
   for(i = 0; i < 100; i++) {
      #pragma HLS  pipeline
      o[i] = 0;
      for(j = 0; j < 100; j++) {
         #pragma HLS unroll factor=100
         #pragma HLS  pipeline
         o[i] = o[i] + m[i][j] * t[j];
      }
   }
}

int main() {
   int t[100] = {0};
   int o[100] = {0};
   int a[100] = {0};
   int m[100][100] = {0};
   for(int i = 0; i < 100; i++) {
      t[100] = i;
      o[100] = i;
      a[100] = i;
      for(int j = 0; j < 100; j++) m[i][j] = i + j;
   }
   fir_k_a(t, o, a, m);
   int checksum = 0;
   for(int i = 0; i < 100; i++) checksum += o[i];
   printf("checksum: %d\n", checksum);
   
   return 0;
}
