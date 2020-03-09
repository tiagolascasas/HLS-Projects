/* 4-cascaded IIR biquad filter processing 64 points */
/* Modified to use arrays & software pipelining - SMP */

#include "traps.h"

#define NPOINTS 64
#define NSECTIONS 4

float input[NPOINTS];
float output[NPOINTS];
float coefficient[NSECTIONS][NSECTIONS][NSECTIONS];
float internal_state[8][NSECTIONS][2];

void iir(float input[NPOINTS], float output[NPOINTS],
	 float coefficient[NSECTIONS][NSECTIONS][NSECTIONS],
         float internal_state[8][NSECTIONS][2]);

main()
{
  int i;

  float *pcoef = coefficient[0][0];
  float *pint = internal_state[0][0];

  for(i=0;i<NPOINTS;i++)
  {
    pcoef[i]=1;
    pint[i]=1;
  }
  input_dsp(input,NPOINTS,0);

  iir(input, output, coefficient, internal_state);

  output_dsp(input,NPOINTS,0);
  output_dsp(coefficient,NPOINTS,0);
  output_dsp(internal_state,NPOINTS,0);
  output_dsp(output,NPOINTS,0);
}

void iir(float input[NPOINTS], float output[NPOINTS],
	 float coefficient[NSECTIONS][NSECTIONS][NSECTIONS],
	 float internal_state[8][NSECTIONS][2])
/* input:           input sample array */
/* output:          output sample array */
/* coefficient:     coefficient array */
/* internal_state:  internal state array */
{
  int i, imod8, imodNSECTIONS;
  int j;

  float state_2, state_1;
  float coef_a21, coef_a11, coef_b21, coef_b11;
  float sum;

  for (i = 0; i < NPOINTS; ++i) {

    sum = input[i];

#ifdef GCCmod
    imod8 = i % 8;
    imodNSECTIONS = i % NSECTIONS;

    state_2 = internal_state[imod8][0][0];
    state_1 = internal_state[imod8][0][1];

    coef_a21 = coefficient[imodNSECTIONS][0][0];
    coef_a11 = coefficient[imodNSECTIONS][0][1];
    coef_b21 = coefficient[imodNSECTIONS][0][2];
    coef_b11 = coefficient[imodNSECTIONS][0][3];
#else
    state_2 = internal_state[i][0][0];
    state_1 = internal_state[i][0][1];

    coef_a21 = coefficient[i][0][0];
    coef_a11 = coefficient[i][0][1];
    coef_b21 = coefficient[i][0][2];
    coef_b11 = coefficient[i][0][3];
#endif

    for (j = 1; j < NSECTIONS ; ++j) {

      sum -= state_2 * coef_a21 + state_1 * coef_a11;

#ifdef GCCmod
      internal_state[imod8][j-1][0] = state_1;
      internal_state[imod8][j-1][1] = sum;

      sum += state_2 * coef_b21 + state_1 * coef_b11;

      state_2 = internal_state[imod8][j][0];
      state_1 = internal_state[imod8][j][1];

      coef_a21 = coefficient[imodNSECTIONS][j][0];
      coef_a11 = coefficient[imodNSECTIONS][j][1];
      coef_b21 = coefficient[imodNSECTIONS][j][2];
      coef_b11 = coefficient[imodNSECTIONS][j][3];

#else

      internal_state[i][j-1][0] = state_1;
      internal_state[i][j-1][1] = sum;

      sum += state_2 * coef_b21 + state_1 * coef_b11;

      state_2 = internal_state[i][j][0];
      state_1 = internal_state[i][j][1];

      coef_a21 = coefficient[i][j][0];
      coef_a11 = coefficient[i][j][1];
      coef_b21 = coefficient[i][j][2];
      coef_b11 = coefficient[i][j][3];
#endif

    }

    sum -= state_2 * coef_a21 + state_1 * coef_a11;
    
#ifdef GCCmod
    internal_state[imod8][NSECTIONS-1][0] = state_1;
    internal_state[imod8][NSECTIONS-1][1] = sum;
#else
    internal_state[i][NSECTIONS-1][0] = state_1;
    internal_state[i][NSECTIONS-1][1] = sum;
#endif
    
    sum += state_2 * coef_b21 + state_1 * coef_b11;

    output[i] = sum;

  }
}
