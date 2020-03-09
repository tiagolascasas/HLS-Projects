/* 8-tap LMS adaptive FIR filter processing 1 point */
/* Modified to use arrays - SMP */

#include "traps.h"

#define NTAPS 8

float input[16];
float output[16];
float expected[16]=
{0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25};

float coefficient[16]=
{0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25,
0.25, 1.50, 3.75, -2.25, 0.50, 0.75, -3.00, 1.25};
float gain;

void lmsfir(float input[], float output[], float expected[],
              float coefficient[], float gain);

main()
{

  input_dsp (input, 16, 0);

  lmsfir(input, output, expected, coefficient, gain);

  output_dsp(input, 16, 0);
  output_dsp(coefficient, 16, 0);
  output_dsp(expected, 16, 0);
  output_dsp(output, 16, 0);
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
  float sum;
  float term1;
  float term2;
  float error;
  float adapted, old_adapted;


  sum = 0.0;
  term1 = input[0];
  term2 = coefficient[0];
  for (i = 1; i < NTAPS; ++i) {
    sum += term1 * term2;
    term1 = input[i];
    term2 = coefficient[i];

  }
  sum += term1 * term2;
  output[0] = sum;
  error = (expected[0] - sum) * gain;
  term1 = input[0];
  term2 = coefficient[0];
  for (i = 1; i < NTAPS; ++i) {
    adapted = term2 + (term1 * error);
    coefficient[i-1] = adapted;
    term1 = input[i];
    term2 = coefficient[i];
  }
  coefficient[NTAPS-1] = coefficient[NTAPS-2] + input[NTAPS-1] * error;
}
