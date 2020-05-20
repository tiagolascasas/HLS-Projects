#include <stdio.h>
int const CosBlock[8][8] = {88, 122, 115, 103, 88, 69, 47, 24, 88, 103, 47, -24, -88, -122, -115, -69, 88, 69, -47, -122, -88, 24, 115, 103, 88, 24, -115, -69, 88, 103, -47, -122, 88, -24, -115, 69, 88, -103, -47, 122, 88, -69, -47, 122, -88, -24, 115, -103, 88, -103, 47, 24, -88, 122, -115, 69, 88, -122, 115, -103, 88, -69, 47, -24};
void dct(int InIm[8][8], int TempBlock[8][8], int CosTrans[8][8], int OutIm[8][8]) {
   int i;
   int j;
   int k;
   int aux;
   for(i = 0; i < 8; i++) {
      #pragma HLS  pipeline
      for(j = 0; j < 8; j++) {
         #pragma HLS  pipeline
         aux = 0;
         for(k = 0; k < 8; k++) {
            #pragma HLS unroll factor=8
            #pragma HLS  pipeline
            aux += InIm[i][k] * CosTrans[k][j];
         }
         TempBlock[i][j] = aux;
      }
   }
   for(i = 0; i < 8; i++) {
      #pragma HLS  pipeline
      for(j = 0; j < 8; j++) {
         #pragma HLS  pipeline
         aux = 0;
         for(k = 0; k < 8; k++) {
            #pragma HLS unroll factor=8
            #pragma HLS  pipeline
            aux += TempBlock[k][j] * CosBlock[i][k];
         }
         OutIm[i][j] = aux;
      }
   }
}

int main() {
   int InIm[8][8] = {0};
   int TempBlock[8][8] = {0};
   int CosTrans[8][8] = {0};
   int OutIm[8][8] = {0};
   int i, j;
   for(i = 0; i < 8; i++) {
      for(j = 0; j < 8; j++) {
         CosTrans[j][i] = CosBlock[i][j];
         InIm[8][8] = i;
      }
   }
   dct(InIm, TempBlock, CosTrans, OutIm);
   int checksum = 0;
   for(i = 0; i < 8; i++) {
      for(i = 0; i < 8; i++) checksum += OutIm[i][j];
   }
   printf("%d\n", checksum);
   
   return 0;
}
