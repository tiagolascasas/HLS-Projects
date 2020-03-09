/* This program expands 16-bit data to 32-bit data */

#include "traps.h"
#define NSAMPLES 2408 

int tempsbuf[NSAMPLES/2];
int sbuf[NSAMPLES];

main () {
int left;
int i, j, n;
j = 0;
n = 0;

  input_dsp (tempsbuf, NSAMPLES*2, 3);
  for (i=0; i<NSAMPLES/2; i++)
  {
    /* expanding the upper half */
    left = *(tempsbuf+j) & 0xffff0000;
    *(sbuf+n) = (left >> 16) & 0x0000ffff;
    if ( *(sbuf+n) & 0x8000 )
	*(sbuf+n) = *(sbuf+n) | 0xffff0000;
    n++;

    /* expanding the lower half */
    *(sbuf+n) = *(tempsbuf+(j++)) & 0x0000ffff;
    if ( *(sbuf+n) & 0x8000 )
	*(sbuf+n) = *(sbuf+n) | 0xffff0000;
    n++;
  }

  output_dsp (sbuf, NSAMPLES*4, 3);
}
 


