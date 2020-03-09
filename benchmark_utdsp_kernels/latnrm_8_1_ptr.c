/* 8rd-order Normalized Lattice filter processing 1 point */

#define ORDER 8

float input;
float output;
float coefficient[16]={ 0.25,1.5,3.75,-2.25,0.5,0.75,-3.0,1.25,
                        0.2, 0.22 , 2.3 , 2.1, 0.48, 0.28, -2.4 ,5.6};
float internal_state[16]={ 0.25,1.5,3.75,-2.25,0.5,0.75,-3.0,1.25,
                        0.2, 0.22 , 2.3 , 2.1, 0.48, 0.28, -2.4 ,5.6};


main()
{ 
   void latnrm();
   
   input_dsp(&input,1,0);
  
   latnrm(&input, &output, coefficient, internal_state);
  
   output_dsp(&input,1,0);
   output_dsp(coefficient,16,0);
   output_dsp(internal_state,16,0);
   output_dsp(&output,1,0);
 
}

void latnrm(data, outa, coefficient, internal_state)
float *data;		/* pointer to input sample array */
float *outa;		/* pointer to output sample array */
float *coefficient;	/* pointer to coefficient array */
float *internal_state;	/* pointer to internal state array */
{ 
  int i;
  float *state;
  float term_1, term_2;
  float left, right, top, bottom; 
  float q_coef, k_coef;
  float *coef;
  float sum;

  coef = coefficient;
  state = internal_state++;
  top = *data++;
  for (i = 0; i < ORDER; i++) {
    q_coef = *coef++;
    k_coef = *coef++;
    left = top;
    right = *state;
    top = q_coef * left - k_coef * right;
    bottom = q_coef * right + k_coef * left; 
    *state++ = bottom;
  }
  *state = top;

  state = internal_state;
  coef = coefficient;
  sum=0.0;     
  for (i = 0; i < ORDER; i++) {
    term_1 = *state++;
    term_2 = *coef++;
    sum += term_1 * term_2;
  }
  *outa++ = sum;     
}
