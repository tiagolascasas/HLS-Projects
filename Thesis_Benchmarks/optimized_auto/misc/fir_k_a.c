#include <stdio.h>
void fir_k_a(int t[100], int o[100], int a[100], int m[100][100]) {
   #pragma HLS stream variable=m
   #pragma HLS array_partition variable=t complete
   #pragma HLS array_partition variable=o complete
   #pragma HLS array_partition variable=a complete
   int i;
   int j;
   for(i = 0; i < 100; i++) {
      #pragma HLS pipeline
      t[i] = 0;
      for(j = 0; j < 3; j++) {
         #pragma HLS unroll
         t[i] = t[i] + (a[i - j + 2] >> 2);
      }
   }
   for(i = 0; i < 100; i++) {
      #pragma HLS pipeline
      o[i] = 0;
      for(j = 0; j < 100; j++) {
         #pragma HLS unroll
         o[i] = o[i] + m[i][j] * t[j];
      }
   }
}

//}
//    return 0;
//    printf("checksum: %d\n", checksum);
//        checksum += o[i];
//    for (int i = 0; i < N; i++)
//    int checksum = 0;
//
//    fir_k_a(t, o, a, m);
//
//    }
//            m[i][j] = i + j;
//        for (int j = 0; j < N; j++)
//        a[N] = i;
//        o[N] = i;
//        t[N] = i;
//    {
//    for (int i = 0; i < N; i++)
//    int m[N][N] = {0};
//    int a[N] = {0};
//    int o[N] = {0};
//    int t[N] = {0};
//{
//int main()