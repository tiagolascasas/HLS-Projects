/* 4-cascaded IIR biquad filter processing 64 points */


#define NPOINTS 64
#define NSECTIONS 4

float input[NPOINTS];
float output[NPOINTS];
float coefficient[NPOINTS];
float internal_state[NPOINTS];

main()
{
  void iir();
  int i;
  float *ptr0, *ptr1;

  ptr0=coefficient;
  ptr1=internal_state;
  for(i=0;i<NPOINTS;i++) {
    *ptr0++=1;
    *ptr1++=1;
  }
  input_dsp(input,NPOINTS,0);

  iir(input, output, coefficient, internal_state);

  output_dsp(input,NPOINTS,0);
  output_dsp(coefficient,NPOINTS,0);
  output_dsp(internal_state,NPOINTS,0);
  output_dsp(output,NPOINTS,0);
}

void iir(my_input, my_output, coefficient, internal_state)
float *my_input;	/* pointer to input sample array */
float *my_output;	/* pointer to output sample array */
float *coefficient;	/* pointer to coefficient array */
float *internal_state;	/* pointer to internal state array */
{
  int i;
  int j;
  float *coef;
  float *state;
  float state_2, state_1;
  float coef_a21, coef_a11, coef_b21, coef_b11;
  float sum;

  coef = coefficient;	  /* moved out of FOR loop below */
  state = internal_state; /* moved out of FOR loop below */

  for (i = 0; i < NPOINTS; i++) {

    sum = *my_input++;
#ifdef GCCmod
    if(my_input > &input[NPOINTS-1])
      my_input = &input[0];
#endif

    for (j = 0; j < NSECTIONS; j++) {

      state_2 = *state++;
#ifdef GCCmod
      if(state > &internal_state[NPOINTS-1])
        state = &internal_state[0];
#endif

      coef_a21 = *coef++;
#ifdef GCCmod
      if(coef > &coefficient[NPOINTS-1])
        coef = &coefficient[0];
#endif

      state_1 = *state--;
#ifdef GCCmod
      if(state < &internal_state[0])
        state = &internal_state[NPOINTS-1];
#endif

      coef_a11 = *coef++;
#ifdef GCCmod
      if(coef > &coefficient[NPOINTS-1])
        coef = &coefficient[0];
#endif

      coef_b21 = *coef++;
#ifdef GCCmod
      if(coef > &coefficient[NPOINTS-1])
        coef = &coefficient[0];
#endif

      coef_b11 = *coef++;
#ifdef GCCmod
      if(coef > &coefficient[NPOINTS-1])
        coef = &coefficient[0];
#endif
      sum -= state_2 * coef_a21;
      sum -= state_1 * coef_a11;

      *state++ = state_1;
#ifdef GCCmod
      if(state > &internal_state[NPOINTS-1])
        state = &internal_state[0];
#endif

      *state++ = sum;
#ifdef GCCmod
      if(state > &internal_state[NPOINTS-1])
        state = &internal_state[0];
#endif

      sum += state_2 * coef_b21;
      sum += state_1 * coef_b11;
    }

    *my_output++ = sum;
#ifdef GCCmod
    if(my_output > &output[NPOINTS-1])
      my_output = &output[0];
#endif
  }
}
