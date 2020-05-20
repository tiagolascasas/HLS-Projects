#include "stdio.h"
#include "math.h"
/**

Code for a Kalman filter
Code version of a benchmark used for evaluating the XPP-VC compiler and the XPP architecture
Jo�o M.P. Cardoso, 2002
@PACT XPP Technologies, Munich, Germany

Version v1,
Jo�o M.P. Cardoso, May 2020

*/
//#include "xpuports.h"
/**
Kalman filter
*/
void kalman(int Y[16], int A[256], int K[256], int G[256], int V[4]) {
   int i;
   int j;
   int index;
   int temp;
   int X[16];
   /*Initializing state Vector X*/
   for(i = 0; i < 16; i++) {
      #pragma HLS  pipeline
      X[i] = 0;
   }
   /*Initializing state Vector Y*/
   for(i = 12; i < 16; i++) {
      #pragma HLS  pipeline
      Y[i] = 0;
   }
   /*-- Computing state Vector X*/
   for(i = 0; i < 16; i++) {
      #pragma HLS  pipeline
      temp = 0;
      for(j = 0; j < 16; j++) {
         #pragma HLS unroll factor=16
         #pragma HLS  pipeline
         index = i * 16 + j;
         temp += (A[index] * X[j] + K[index] * Y[j]);
      }
      X[i] = temp;
   }
   /*-- Computing output Vector V*/
   // it only uses 4x16 elements of G
   for(i = 0; i < 4; i++) {
      #pragma HLS  pipeline
      temp = 0;
      for(j = 0; j < 16; j++) {
         #pragma HLS unroll factor=16
         #pragma HLS  pipeline
         index = i * 16 + j;
         temp += (G[index] * X[j]);
      }
      V[i] = (temp * Y[i + 1]);
   }
}

int main() {
   int i, j, tmp, index;
   int A[256];
   int K[256];
   int Y[16];
   int G[256];
   int V[4];
   /*read data stream from port 1*/
   for(i = 0; i < 12; i++) {
      //getstream(1, &tmp);
      tmp = i * j;
      Y[i] = tmp;
   }
   /*initialize for now:*/
   for(i = 0; i < 16; i++) {
      for(j = 0; j < 16; j++) {
         index = i * 16 + j;
         G[index] = 2 * (i + j);
         K[index] = i + j;
         A[index] = i - j;
      }
   }
   kalman(Y, A, K, G, V);
   /*-- Output Vector V*/
   /*write data stream to output*/
   // for now just calculate a checksum
   int checksum = 0;
   for(i = 0; i < 4; i++) {
      //putstream(4, V[i]);
      checksum += abs(V[i]);
   }
   printf("checksum = %d\n", checksum);
   if(checksum == -410206000) printf("RIGHT!\n");
   else printf("WRONG!\n");
}
