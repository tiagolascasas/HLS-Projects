void filter_subband(double z[512], double s[32], double m[1024]) {
   #pragma HLS array_partition variable=z cyclic factor=5
   #pragma HLS array_partition variable=s complete
   #pragma HLS array_partition variable=m cyclic factor=10
   int j;
   int i;
   double y[64];
   for(i = 0; i < 64; i++) {
      #pragma HLS pipeline
      y[i] = 0.0;
      for(j = 0; j < 8; j++) {
         #pragma HLS unroll
         y[i] += z[i + 64 * j];
      }
   }
   for(i = 0; i < 32; i++) {
      #pragma HLS pipeline
      s[i] = 0.0;
      for(j = 0; j < 64; j++) {
         #pragma HLS unroll
         s[i] += m[32 * i + j] * y[j];
      }
   }
}

int main() {
   double z[512] = {0};
   double s[32] = {0};
   double m[1024] = {0};
   filter_subband(z, s, m);
   
   return 0;
}
