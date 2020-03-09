#include "traps.h"

/* Intel ADPCM step variation table */
static int indexTable[16] = {
    -1, -1, -1, -1, 2, 4, 6, 8,
    -1, -1, -1, -1, 2, 4, 6, 8,
};

static int stepsizeTable[89] = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17,
    19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
    50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
    130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
    337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
    876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
    2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
    5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
    15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
};

#define NSAMPLES 2407 
/*
  Note: Number of samples is set at 2407 for "bark.pcm"
*/
int sbuf[NSAMPLES];

void main()
  {
  int count;		/* loop counter */
  int *inp;		/* Input buffer pointer */
  int *outp;		/* output buffer pointer */
  int sign;		/* Current adpcm sign bit */
  int delta;		/* Current adpcm output value */
  int step;		/* Stepsize */
  int valprev;		/* virtual previous output value */
  int vpdiff;		/* Current change to valprev */
  int index;		/* Current step change index */
  int inputbuffer;	/* place to keep next 4-bit value */

  input_dsp  (sbuf, NSAMPLES, 1);

  outp = sbuf;
  inp  = sbuf;

  valprev = 1;
  index = 1;
  step = 8;

  for (count=0; count < NSAMPLES; count++)
    {

    /* Step 1 - get the delta value and compute next index */
    delta = *inp++;

    /* Step 2 - Find new index value (for later) */
    index += indexTable[delta];
    if ( index < 0 ) index = 0;
    if ( index > 88 ) index = 88;

    /* Step 3 - Separate sign and magnitude */
    sign = delta & 8;
    delta = delta & 7;

    /* Step 4 - update output value */
    vpdiff = (delta*step) >> 2;

    if ( sign )
      valprev -= vpdiff;
    else
      valprev += vpdiff;

    /* Step 5 - clamp output value */
    if ( valprev > 32767 )
      valprev = 32767;
    else if ( valprev < -32768 )
      valprev = -32768;

    /* Step 6 - Update step value */
    step = stepsizeTable[index];

    /* Step 7 - Output value */
    *outp++ = valprev;
    }

  output_dsp (sbuf, NSAMPLES, 1); 

  }
