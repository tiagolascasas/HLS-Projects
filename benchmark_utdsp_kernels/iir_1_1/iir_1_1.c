/* IIR biquad filter processing 1 point */
/* Modified to use arrays - SMP */

#include "traps.h"

float input;
float output;
float coefficient[4] = {1.0, 1.0, 1.0, 1.0};
float internal_state[4] = {1.0, 1.0, 1.0, 1.0};

void iir(float input[], float output[], float coefficient[],
          float internal_state[]);

main()
{
  int i;

  input_dsp(&input,1,0);

  iir(&input, &output, coefficient, internal_state);

  output_dsp(&input,1,0);
  output_dsp(coefficient,4,0);
  output_dsp(internal_state,4,0);
  output_dsp(&output,1,0);
}

void iir(float input[], float output[], float coefficient[],
          float internal_state[])
/*  input:           input sample array */
/*  output:          output sample array */
/*  coefficient:     coefficient array */
/*  internal_state:  internal state array */
{
  float state_2;
  float state_1;
  float sum;

  sum = input[0];
  state_2 = internal_state[0];
  state_1 = internal_state[1];
  sum -= state_2 * coefficient[0] + state_1 * coefficient[1];
  internal_state[0] = state_1;
  internal_state[1] = sum;
  sum += state_2 * coefficient[2] + state_1 * coefficient[3];
  output[0] = sum;
}
