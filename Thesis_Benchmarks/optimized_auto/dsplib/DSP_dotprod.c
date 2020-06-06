#include <stdlib.h>
int DSP_dotprod(short x[100], short y[100]) {
   #pragma HLS stream variable=x
   #pragma HLS stream variable=y
   int sum = 0;
   for(int i = 0; i < 100; i++) {
      #pragma HLS unroll
      sum += x[i] * y[i];
   }
   
   return sum;
}

int main() {
   short x[100] = {0};
   short y[100] = {0};
   for(int i = 0; i < 100; i++) {
      x[i] = i;
      y[i] = i;
   }
   int res = DSP_dotprod(x, y);
   printf("res: %d\n", res);
   
   return 0;
}
