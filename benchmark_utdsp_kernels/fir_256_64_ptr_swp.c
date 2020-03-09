/* 256-tap FIR filter processing 64 points */

#define NPOINTS 64
#define NTAPS 256

float input[NTAPS];
float coefficients[NTAPS]; 
float output[NPOINTS];

main()
{
  void fir();

  input_dsp (coefficients, NTAPS, 0);
  input_dsp (input, NTAPS, 0);

  fir(input, output, coefficients);

  output_dsp (input, NTAPS, 0);
  output_dsp (coefficients, NTAPS, 0);
  output_dsp (output, NPOINTS, 0);
}

void fir(input, output, coefficient)
float *input;		/* pointer to input sample array */
float *output;		/* pointer to output sample array */
float *coefficient;	/* pointer to coefficient array */
{
  int i;
  int j;
  float *data;
  float *coef;
#ifdef GCCmod
  float *initial;
#endif
  float sum;
  float term1;
  float term2;
#ifdef GCCmod
  initial=input;
#endif
  for (i = 0; i < NPOINTS; i++) {
    data = input++;
    coef = coefficient;
    sum = 0.0;
#ifdef GCCmod
    term1 = *data;
    if (data==initial)
       data=initial+(NTAPS-1);
    else
       data--;
#else
    term1 = *data--;
#endif
    term2 = *coef++;
    for (j = 1; j < NTAPS; j++) {
      sum += term1 * term2;
#ifdef GCCmod
      term1 = *data;
      if (data==initial)
        data=initial+(NTAPS-1);
      else
        data--;
#else
      term1 = *data--;
#endif
      term2 = *coef++;
    }
    sum += term1 * term2;
    *output++ = sum;
  }
}
