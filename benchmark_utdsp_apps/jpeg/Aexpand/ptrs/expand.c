/* This program expands 16-bit data to 32-bit data */

#include "traps.h"
#define NSAMPLES 428

int tempsbuf[NSAMPLES/4];
int sbuf[NSAMPLES];

main () {
int one,two,three,four;
int i, j, n;
j = 0;
n = 0;

  input_dsp (tempsbuf, NSAMPLES, 3);
  for (i=0; i<NSAMPLES/4; i++)
  {
    /* expanding the upper half */
    one = *(tempsbuf+j) & 0xff000000;
    *(sbuf+n) = (one >> 24) & 0x000000ff;
   /* if ( *(sbuf+n) & 0x8000 )
	*(sbuf+n) = *(sbuf+n) | 0xffff0000;*/ n++;
    
    /* expanding the upper half */
    two = *(tempsbuf+j) & 0x00ff0000;
    *(sbuf+n) = (two >> 16) & 0x000000ff;
   /* if ( *(sbuf+n) & 0x8000 )
	*(sbuf+n) = *(sbuf+n) | 0xffff0000;*/ n++;  

    /* expanding the upper half */
    three = *(tempsbuf+j) & 0x0000ff00;
    *(sbuf+n) = (three >> 8) & 0x000000ff;
   /* if ( *(sbuf+n) & 0x8000 )
	*(sbuf+n) = *(sbuf+n) | 0xffff0000;*/ n++;

    /* expanding the lower half */
    *(sbuf+n) = *(tempsbuf+(j++)) & 0x000000ff;
    /*if ( *(sbuf+n) & 0x8000 )
	*(sbuf+n) = *(sbuf+n) | 0xffff0000;*/
    n++;
  }

  output_dsp (sbuf, NSAMPLES*4, 3);
}
 



