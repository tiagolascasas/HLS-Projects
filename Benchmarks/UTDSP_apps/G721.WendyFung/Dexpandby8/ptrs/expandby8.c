#include "traps.h"
#define N 2408 

int inarray[(N+7)/8];
int outarray[N];

void expand ();

void main ()
{
  input_dsp (inarray, (N+1)/2, 3);
  expand (inarray, (N+7)/8, outarray);
  output_dsp (outarray, N*4, 3);
}
 

void expand (int *inptr, int n, int *outptr)
{
  int i;
  int value;

  for (i=0; i<n; i++)
  {
    value = *inptr & 0xf0000000;
    *outptr++ = (value >> 7*4) & 0x0000000f; 

    value = *inptr & 0x0f000000;
    *outptr++ = (value >> 6*4) & 0x0000000f; 

    value = *inptr & 0x00f00000;
    *outptr++ = (value >> 5*4) & 0x0000000f; 

    value = *inptr & 0x000f0000;
    *outptr++ = (value >> 4*4) & 0x0000000f; 

    value = *inptr & 0x0000f000;
    *outptr++ = (value >> 3*4) & 0x0000000f; 

    value = *inptr & 0x00000f00;
    *outptr++ = (value >> 2*4) & 0x0000000f; 

    value = *inptr & 0x000000f0;
    *outptr++ = (value >> 1*4) & 0x0000000f; 

    value = *inptr & 0x0000000f;
    *outptr++ =  (*inptr & 0x0000000f);

    inptr++;
  }
}
 
