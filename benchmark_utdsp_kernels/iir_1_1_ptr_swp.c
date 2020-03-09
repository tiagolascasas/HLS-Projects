/* IIR biquad filter processing 1 point */

#include "traps.h"

float input;
float output;
float coefficient[4];
float internal_state[4];

main()
{
  void iir();
  int i;
  float *ptr0, *ptr1;

  ptr0=coefficient;
  ptr1=internal_state;
  for(i=0;i<4;i++)
    {
    *ptr0++=1;
    *ptr1++=1;
    }
  input_dsp(&input,1,0);

  iir(&input, &output, coefficient, internal_state); 

  output_dsp(&input,1,0);
  output_dsp(coefficient,4,0);
  output_dsp(internal_state,4,0);
  output_dsp(&output,1,0);
}

void iir(input, output, coefficient, internal_state)
float *input;		/* pointer to input sample array */
float *output;		/* pointer to output sample array */
float *coefficient;	/* pointer to coefficient array */
float *internal_state;	/* pointer to internal state array */
{
  float state_2;
  float state_1;
  float sum;
  sum = *input;
  state_2 = *internal_state++;
  state_1 = *internal_state--;
  sum -= state_2 * *coefficient++;
  sum -= state_1 * *coefficient++;
  *internal_state++ = state_1;
  *internal_state++ = sum;
  sum += state_2 * *coefficient++;
  sum += state_1 * *coefficient;
  *output = sum;
}
