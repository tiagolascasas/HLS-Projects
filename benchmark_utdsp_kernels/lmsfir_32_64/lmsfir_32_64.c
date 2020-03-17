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
  float error;
  float adapted;

  for (i = 0; i < NPOINTS; ++i) {

    sum = 0.0;

    for (j = 0; j < NPOINTS; j++) {
#ifdef GCCmod
      if (i-j < 0)
        sum +=input[i-j+NPOINTS] * coefficient[j];
      else
        sum +=input[i-j] * coefficient[j];

#else
      sum +=input[i-j] * coefficient[j];
#endif
    }

    output[i] = sum;

    error = (expected[i] - sum) * gain;

    for (j = 0; j < NTAPS-1; j++) {
#ifdef GCCmod
      if (i-j < 0)
        coefficient[j] = coefficient[j] + (input[i-j+NPOINTS] * error);
      else
        coefficient[j] = coefficient[j] + (input[i-j] * error);

#else
      coefficient[j] = coefficient[j] + (input[i-j] * error);
#endif
    }

#ifdef GCCmod
    if (i < NTAPS+1)
      coefficient[NTAPS-1] = coefficient[NTAPS-2] + input[i-NTAPS+1+NPOINTS] *
									error;
    else
      coefficient[NTAPS-1] = coefficient[NTAPS-2] + input[i-NTAPS+1] * error;

#else
    coefficient[NTAPS-1] = coefficient[NTAPS-2] + input[i-NTAPS+1] * error;
#endif

  }
}
