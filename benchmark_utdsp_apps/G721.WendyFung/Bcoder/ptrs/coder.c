#include "traps.h"

void adpcm_coder();

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
int StateValprev=1;
int StateIndex=1;

void main()
  {
  input_dsp  (sbuf, NSAMPLES*4, 3); 
  adpcm_coder(sbuf, sbuf, NSAMPLES, &StateValprev, &StateIndex); 
  output_dsp (sbuf, NSAMPLES*4, 3); 
  }

void adpcm_coder(int *indata, int *outdata, int len, int *state_valprev, int *state_index)
{
    int count;
    int *inp;			/* Input buffer pointer */
    int *outp;			/* output buffer pointer */
    int val;			/* Current input sample value */
    int sign;			/* Current adpcm sign bit */
    int step;			/* Stepsize */
    int delta;			/* Current adpcm output value */
    int valprev;		/* virtual previous output value */
    int vpdiff;			/* Current change to valprev */
    int index;			/* Current step change index */

    outp = outdata;
    inp  = (int*)indata;

    valprev = 1;   /* *state_valprev; */
    index   = 1;   /* *state_index;   */
    step    = stepsizeTable[index];  

    for (count=0; len>=count; count++)
    {
	val = *inp++;

	/* Step 1 - compute difference with previous value */
	delta =val - valprev;
	if (delta < 0) 
	  {
	  sign = 8;
	  delta = (-delta);
	  }
	else
	  sign = 0;

	/* Step 2 - Divide and clamp */
	delta <<= 2;
	delta  /= step;
	if ( delta > 7 ) 
	  delta = 7;
	vpdiff   = delta*step;
	vpdiff >>= 2;

	/* Step 3 - Update previous value */
	if ( sign )
	  valprev -= vpdiff;
	else
	  valprev += vpdiff;

	/* Step 4 - Clamp previous value to 16 bits */
	if ( valprev > 32767 )
	  valprev = 32767;
	if ( valprev < -32768 )
	  valprev = -32768;

	/* Step 5 - Assemble value, update index and step values */
	delta |= sign;
	
	index += indexTable[delta];
	if ( index < 0 ) 
	  index = 0;
	if ( index > 88 ) 
	  index = 88;
	step = stepsizeTable[index];

	/* Step 6 - Output value */
	*outp++ = delta; 

    }

    *state_valprev = (int)valprev;
    *state_index   = (int)index;

}

