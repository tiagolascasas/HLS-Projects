/* 256-tap FIR filter processing 64 points */
/* Modified to use arrays - SMP */

#include "traps.h"

#define NPOINTS 64
#define NTAPS 256

float input[NTAPS];
float coefficients[NTAPS];
float output[NPOINTS];

void fir(float input[], float output[], float coefficient[]);

main()
{
  input_dsp (coefficients, NTAPS, 0);
  input_dsp (input, NTAPS, 0);

  fir(input, output, coefficients);

  output_dsp (input, NTAPS, 0);
  output_dsp (coefficients, NTAPS, 0);
  output_dsp (output, NPOINTS, 0);

}

void fir(float input[], float output[], float coefficient[])
/*     input:          input sample array */
/*     output:         output sample array */
/*     coefficient:    coefficient array */
{
  int i;
  int j;

  float sum, term1, term2;

  for (i = 0; i < NPOINTS; i++) {
    sum = 0.0;
    
    term1 = input[i];
    term2 = coefficient[0];

    for (j = 1; j < NTAPS; j++) {
      sum += term1 * term2;

#ifdef GCCmod
      if (i-j < 0)
        term1 = input[i-j+NTAPS];
      else
        term1 = input[i-j];

#else
      term1 = input[i-j];
#endif

      term2 = coefficient[j];
    }

    sum += term1 * term2;
    output[i] = sum;
  }
}
