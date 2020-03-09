/* 8-tap LMS adaptive FIR filter processing 1 point */
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

main()
{
  void lmsfir();

  input_dsp (input, 16, 0);

  lmsfir(input, output, expected, coefficient, gain);

  output_dsp(input, 16, 0);
  output_dsp(coefficient, 16, 0);
  output_dsp(expected, 16, 0);
  output_dsp(output, 16, 0);
}

void lmsfir(input, output, expected, coefficient, gain)
float *input;		/* pointer to input sample array */
float *output;		/* pointer to output sample array */
float *expected;	/* pointer to expected output sample array */
float *coefficient;	/* pointer to coefficient array */
float gain;		/* adaption gain */
{
  int i;
  float *data;
  float *coef;
  float *new_coef;
  float sum;
  float term1;
  float term2;
  float error;
  float adapted;


  data = input;
  coef = coefficient;
  sum = 0.0;
  for (i = 0; i < NTAPS; i++) {
    term1 = *data++;
    term2 = *coef++;
    sum += term1 * term2;
  }
  *output = sum;
  error = (*expected - sum) * gain;
  data = input;
  coef = coefficient;
  new_coef = coefficient;
  adapted = term2;
  for (i = 0; i < NTAPS; i++) {
    term1 = *data++;
    term2 = *coef++;
    adapted = term2 + (term1 * error);
    *new_coef++ = adapted;
  }
}
