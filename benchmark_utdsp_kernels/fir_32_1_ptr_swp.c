/* 32-tap FIR filter processing 1 point */

#include "traps.h"

#define NTAPS 32

float input[NTAPS];
float output[NTAPS];
float coefficients[NTAPS] = {0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25};


main()
{
  void fir();

  input_dsp (input, NTAPS, 0);

  fir(input, output, coefficients);

  output_dsp (input, NTAPS, 0);
  output_dsp (coefficients, NTAPS, 0);
  output_dsp (output, NTAPS, 0);
}

void fir(input, output, coefficient)
float *input;		/* pointer to input sample array */
float *output;		/* pointer to output sample array */
float *coefficient;	/* pointer to coefficient array */
{
  int i;
  float sum;
  float term1;
  float term2;

  sum = 0.0;
  term1 = *input++;
  term2 = *coefficient++;
  for (i = 1; i < NTAPS; i++) {
    sum += term1 * term2;
    term1 = *input++;
    term2 = *coefficient++;
  }
  sum += term1 * term2;
  *output++ = sum;
}
