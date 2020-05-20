void DSPF_sp_mat_mul_cplx_cn(float x1[64], float x2[64], float y[128]) {
   float real;
   float imag;
   int i;
   int j;
   int k;
   for(i = 0; i < 8; i++) {
      #pragma HLS  pipeline
      for(j = 0; j < 8; j++) {
         #pragma HLS  pipeline
         real = 0;
         imag = 0;
         for(k = 0; k < 4; k++) {
            #pragma HLS unroll factor=4
            #pragma HLS  pipeline
            real += (x1[i * 2 * 4 + 2 * k] * x2[k * 2 * 8 + 2 * j] - x1[i * 2 * 4 + 2 * k + 1] * x2[k * 2 * 8 + 2 * j + 1]);
            imag += (x1[i * 2 * 4 + 2 * k] * x2[k * 2 * 8 + 2 * j + 1] + x1[i * 2 * 4 + 2 * k + 1] * x2[k * 2 * 8 + 2 * j]);
         }
         y[i * 2 * 8 + 2 * j] = real;
         y[i * 2 * 8 + 2 * j + 1] = imag;
      }
   }
}

int main() {
   float ptr_x1[64] = {0};
   for(int i = 0; i < 2 * 8 * 4; i++) ptr_x1[i] = rand();
   float ptr_x2[64] = {0};
   for(int i = 0; i < 2 * 4 * 8; i++) ptr_x2[i] = rand();
   float ptr_y_cn[128] = {0};
   for(int i = 0; i < 2 * 8 * 8; i++) ptr_y_cn[i] = rand();
   DSPF_sp_mat_mul_cplx_cn(ptr_x1, ptr_x2, ptr_y_cn);
   
   return 0;
}
