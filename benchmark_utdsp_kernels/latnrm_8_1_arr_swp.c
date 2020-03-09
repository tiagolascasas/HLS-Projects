/* 8rd-order Normalized Lattice filter processing 1 point */
/* Modified to use arrays - SMP */

#include "traps.h"

#define ORDER 8

float input;
float output;
float coefficient[16]={ 0.25,1.5,3.75,-2.25,0.5,0.75,-3.0,1.25,
                        0.2, 0.22 , 2.3 , 2.1, 0.48, 0.28, -2.4 ,5.6};
float internal_state[16]={ 0.25,1.5,3.75,-2.25,0.5,0.75,-3.0,1.25,
                        0.2, 0.22 , 2.3 , 2.1, 0.48, 0.28, -2.4 ,5.6};

void latnrm(float input, float *output, float coefficient[16],
                   float internal_state[16]);

main()
{

  input_dsp(&input,1,0);

  latnrm(input, &output, coefficient, internal_state);

  output_dsp(&input,1,0);
  output_dsp(coefficient,16,0);
  output_dsp(internal_state,16,0);
  output_dsp(&output,1,0);
}

void latnrm(float input, float *output, float coefficient[16],
              float internal_state[16])
/*    input:           input sample array */
/*    output:          output sample array */
/*    coefficient:     coefficient array */
/*    internal_state:  internal state array */
{
  int i;
  float left, right, top, bottom = 0.0;
  float q_coef, k_coef;
  float term_1, term_2;
  float sum;

  top = input;
  q_coef = coefficient[0];
  for (i = 0; i < ORDER; i++) {
    k_coef = coefficient[2*i];
    left = top;
    right = internal_state[i];
    internal_state[i] = bottom;
    top = q_coef * left - k_coef * right;
    bottom = q_coef * right + k_coef * left;
    q_coef = coefficient[2*i+1];
  }
  internal_state[i++] = bottom;
  internal_state[i] = top;
  sum = 0.0;
  term_1 = internal_state[1];
  term_2 = q_coef;
  for (i = 1; i < ORDER; i++) {
    sum += term_1 * term_2;
    term_1 = internal_state[i+1];
    term_2 = coefficient[i-1];
  }
  sum += term_1 * term_2;
  *output = sum;
}
