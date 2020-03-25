/*===============================================================================
*
*       TEXAS INSTRUMENTS, INC.         
*
*       AUTOCORRELATION
*
*       Revision Date:  04/16/97
*/

/* DSP performance:
   (N/2) *M + 16 + M/4
   For N=160 and M=10;
   816 cycles or 4.08 �sec
*/

#include <stdio.h>
 //(MULTIPLE of 2)
//#include "autcor_viv.h"
#define M 16
#define N 32

short ac[M]; // --- Resulting array of autocorrelation

short sd[N+M]; // --- Input array of autocorrelation


int main() {
  int tmp;
  //void autcor(short ac[],short sd[], int N, int M) {
  int i,k,sum;
  
  FILE *f_in=fopen("autcor_in_golden.txt","w");
  FILE *f_out=fopen("autcor_out_golden.txt","w");
  for(i=0;i<N+M; i++){
	sd[i]=i;  
	fprintf(f_in,"%hu\n",sd[i]);
  }
  
  for (i = 0; i < M; i++){
    sum = 0;

    for (k = 0; k < N; k++) {
      sum += sd[k+M] * sd[k+M-i];
    }

    ac[i] = (sum >> 15);
  }
  
  for(i=0;i<M; i++){
	fprintf(f_out,"%hu\n",ac[i]);  
  }
  fclose(f_out);
  fclose(f_in);
  return 0;
}


