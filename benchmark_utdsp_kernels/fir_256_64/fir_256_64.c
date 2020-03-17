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

  float sum;

  for (i = 0; i < 1; i++) {
    sum = 0.0;

    for (j = 0; j < NTAPS; j++) {

#ifdef GCCmod
      if (i-j < 0)
        sum += input[i-j+NTAPS] * coefficient[j];
      else
        sum += input[i-j] * coefficient[j];

#else
      sum += input[i-j] * coefficient[j];
#endif

    }
    output[i] = sum;
  }
}
