/* 32-tap LMS adaptive FIR filter processing 64 points */
/* Modified to use arrays - SMP */

#include "traps.h"

#define NPOINTS 64
#define NTAPS 32

float input[NPOINTS];
float output[NPOINTS];
float expected[NPOINTS];
float coefficients[NPOINTS];

float gain;

void lmsfir(float input[], float output[], float expected[],
               float coefficient[], float gain);

main()
{

  input_dsp (expected,NPOINTS, 0);
  input_dsp (coefficients, NPOINTS, 0 );
  gain = 1.00;
  input_dsp (input, NPOINTS, 0);

  lmsfir(input, output, expected, coefficients, gain);

  output_dsp(input, NPOINTS, 0);
  output_dsp(coefficients, NPOINTS, 0);
  output_dsp(expected, NPOINTS, 0);
  output_dsp (&output, NPOINTS, 0);
}

void lmsfir(float input[], float output[], float expected[],
               float coefficient[], float gain)
/* input:            input sample array */
/* output:           output sample array */
/* expected:         expected output sample array */
/* coefficient:      coefficient array */
/* gain:             adaption gain */
{
  int i;
  int j;

  float sum;
  float term1;
  float term2;
  float error;
  float adapted;

  for (i = 0; i < NPOINTS; ++i) {

    sum = 0.0;

    term1 = input[i];

    term2 = coefficient[0];
    for (j = 1; j < NPOINTS; j++) {
      sum += term1 * term2;

#ifdef GCCmod
      if (i-j < 0)
        term1 = input[i-j+NPOINTS];
      else
        term1 = input[i-j];

#else
      term1 = input[i-j];
#endif

      term2 = coefficient[j];
    }
    sum += term1 * term2;
    output[i] = sum;

    error = (expected[i] - sum) * gain;

    term1 = input[i];

    term2 = coefficient[0];
    adapted = term2;
    for (j = 1; j < NTAPS; j++) {
      adapted = term2 + (term1 * error);
      coefficient[j-1] = adapted;

#ifdef GCCmod
      if (i-j < 0)
        term1 = input[i-j];
      else
        term1 = input[i-j];

#else
      term1 = input[i-j];
#endif

      term2 = coefficient[j];
    }
    adapted += term1 * error;
    coefficient[j-1] = adapted;
  }
}
