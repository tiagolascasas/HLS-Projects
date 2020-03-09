/* 8rd-order Normalized Lattice filter processing 1 point */

#include "traps.h"

#define ORDER 8

float input;
float output;
float coefficient[16]={ 0.25,1.5,3.75,-2.25,0.5,0.75,-3.0,1.25,
                        0.2, 0.22 , 2.3 , 2.1, 0.48, 0.28, -2.4 ,5.6};
float internal_state[16]={ 0.25,1.5,3.75,-2.25,0.5,0.75,-3.0,1.25,
                        0.2, 0.22 , 2.3 , 2.1, 0.48, 0.28, -2.4 ,5.6};


void latnrm(float data, float *outa, float *coefficient, float *internal_state);

main()
{ 
   
   input_dsp(&input,1,0);
  
   latnrm(input, &output, coefficient, internal_state);
  
   output_dsp(&input,1,0);
   output_dsp(coefficient,16,0);
   output_dsp(internal_state,16,0);
   output_dsp(&output,1,0);
 
}

void latnrm(float data, float *outa, float *coefficient, float *internal_state)
/* float data;		pointer to input sample array */
/* float *outa;		pointer to output sample array */
/* float *coefficient;	pointer to coefficient array */
/* float *internal_state;	pointer to internal state array */
{ 
  int i;

  /* Following statement must be here; otherwise, an error message occur:
            * Couldn't find label in the data label list. 
     Also, I assign bottom=0 , otherwise, if one type gcc latnrm_8_1.c ,
     it will generate the wrong answer.
  */
  float *state;          /*must be here ; otherwise other wrong answer  */  
  float q_coef, k_coef;  /*must be here; otherwise other wrong answer   */ 
  float term_1, term_2;  /*  must ; otherwise  output.corinna=0 */
  float left, right, top, bottom=0; 
  float sum;                              /*ok to delcare as local variable   */ 
  float *save_coef = coefficient;
   
  state = internal_state++;
  top = data;
  q_coef = *coefficient;
  for (i = 0; i < ORDER; i++) {
    k_coef = *coefficient++;
    left = top;
    right = *state;
    *state++ = bottom;
    top = q_coef * left - k_coef * right;
    bottom = q_coef * right + k_coef * left; 
    q_coef = *coefficient++;
  }
  *state++ = bottom;
  *state = top;
  state = internal_state;
  sum=0.0;     
  term_1 = *state++;
  term_2 = q_coef;
  coefficient = save_coef;
  for (i = 1; i < ORDER; i++) {
    sum += term_1 * term_2;
    term_1 = *state++;
    term_2 = *coefficient++;
 
  }
  sum += term_1 * term_2;
  *outa = sum;     
  
}
