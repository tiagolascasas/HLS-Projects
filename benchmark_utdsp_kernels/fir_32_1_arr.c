/* 32-tap FIR filter processing 1 point */
/* Modified to use arrays - SMP */

#include "traps.h"

#define NTAPS 32

float input[NTAPS];
float output[NTAPS];
float coefficients[NTAPS] = {0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25};

void fir(float input[], float output[], float coefficient[]);

main()
{

  input_dsp (input, NTAPS, 0);

  fir(input, output, coefficients);

  output_dsp (input, NTAPS, 0);
  output_dsp (coefficients, NTAPS, 0);
  output_dsp (output, NTAPS, 0);
}

void fir(float input[], float output[], float coefficient[])
/*   input :           input sample array */
/*   output:           output sample array */
/*   coefficient:      coefficient array */
{
  int i;
  float sum;
  sum = 0.0;

  for (i = 0; i < NTAPS; ++i) {
    sum += input[i] * coefficient[i];
  }
  output[0] = sum;
}
