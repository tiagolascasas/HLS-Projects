/* 32-tap LMS adaptive FIR filter processing 64 points */

#define NPOINTS 64
#define NTAPS 32

float input[NPOINTS];
float output[NPOINTS];
float expected[NPOINTS];
float coefficients[NPOINTS]; 

float gain;

main()
{
  void lmsfir();

  input_dsp (expected,NPOINTS, 0);
  input_dsp (coefficients, NPOINTS, 0 );
  gain = 1.00;
  input_dsp (input, NPOINTS, 0);

  lmsfir(input, output, expected, coefficients, gain);

  output_dsp(input, NPOINTS, 0);
  output_dsp(coefficients, NPOINTS, 0);
  output_dsp(expected, NPOINTS, 0);
  output_dsp(output, NPOINTS, 0);
}

void lmsfir(input, output, expected, coefficient, gain)
float *input;		/* pointer to input sample array */
float *output;		/* pointer to output sample array */
float *expected;	/* pointer to expected output sample array */
float *coefficient;	/* pointer to coefficient array */
float gain;		/* adaption gain */
{
  int i;
  int j;
  float *data;
  float *coef;
#ifdef GCCmod
  float *initial;
#endif

  float *new_coef;
  float sum;
  float term1;
  float term2;
  float error;
  float adapted;
#ifdef GCCmod
  initial=input;
#endif

  for (i = 0; i < NPOINTS; i++) {
    data = input;
    coef = coefficient;
    sum = 0.0;
    for (j = 0; j < NPOINTS; j++) {
#ifdef GCCmod
      term1 = *data;
      if (data==initial)
        data=initial+(NPOINTS-1);
      else
        data--;
#else
      term1 = *data--;
#endif

      term2 = *coef++;
      sum += term1 * term2;
    }
    *output++ = sum;
    error = (*expected++ - sum) * gain;
    data = input++;
    coef = coefficient;
    new_coef = coefficient;
    adapted = term2;
    for (j = 0; j < NTAPS; j++) {
#ifdef GCCmod
      term1 = *data;
      if (data==initial)
        data=initial+(NPOINTS-1);
      else
        data--;
#else
      term1 = *data--;
#endif

      term2 = *coef++;
      adapted = term2 + (term1 * error);
      *new_coef++ = adapted;
    }
  }
}
