/* 32nd-order Normalized Lattice filter processing 64 points */

/*  #include "traps.h"  /*  */
#define NPOINTS 64
#define ORDER 32




float input[NPOINTS];
float output[NPOINTS];

/* the following values of coefficient and internal_state is define arbitrary */

float coefficient[NPOINTS]={
0.25, 0.51 , 0.75,-0.25,0.5, 0.75, 0.7,  0.625,
0.21, 0.22 , 0.93 , 0.81, 0.48, 0.208, 0.4 , 0.6,
0.25, 0.35, 0.875, 0.295, 0.25, 0.725,0.380, 0.295,
0.2, 0.22 , 0.73 , 0.91, 0.48, 0.28, 0.694 , 0.6,
0.25,0.5,0.75,0.525,0.5,0.75,-0.5,0.725,
0.62, 0.272 , 0.83 , 0.81, 0.48, 0.28, 0.814 ,0.56,
0.25,0.5,0.75,-0.25,0.5 ,0.75, -0.810, 0.25,
0.02, 0.252 , 0.913 , 0.81, 0.468, 0.28, 0.4 ,0.36
};

float internal_state[NPOINTS]={
0.25,0.5,0.75,-0.29,0.5,0.75,-0.3,0.422,
0.82, 0.922 , 0.63 , 0.71, 0.48, 0.218, -0.24 ,0.6,
0.92, 0.22 , 0.93 , 0.51, 0.498, 0.28, -0.84 ,0.26,
0.25,0.95, 0.75,-0.27,0.5,0.75,0.80,0.25,
0.25,0.25, 0.735, -0.25,0.5,0.75, 0.20,0.525,
0.92, 0.22 , 0.31 ,  0.81, 0.468, 0.288, -0.14 ,0.65,
0.2, 0.272 , 0.93 , 0.91, 0.485, 0.218, -0.4 ,0.6,
0.82, 0.72 , 0.63 , 0.21, 0.438, 0.928, -0.24 ,0.6
};

main()
{
  void latnrm();
 
   input_dsp(input,NPOINTS,0);                        /*new added  */
   latnrm(input, output, coefficient, internal_state);
   output_dsp(output,NPOINTS,0);                     /* new added */
 
}

void latnrm(data, outa, coefficient, internal_state)
float *data;		/* pointer to input sample array */
float *outa;		/* pointer to output sample array */
float *coefficient;	/* pointer to coefficient array */
float *internal_state;	/* pointer to internal state array */
{
  int i;
  int j;
  float *state;  /* SHOULD DECLARE GLOBALLY ;OTHERWISE RESULT IS FAULT  */
  float term_1, term_2; /* SHOULD DECLARE GLOBALLY; OTHERWISE RESULT IS 0  */
  float left,right,top; 
 
  float q_coef,k_coef;
  float *coef;  
  float bottom=0;  
  float sum;      /*  */

  for (i = 0; i < NPOINTS; i++)   /* I CHANGE VAR : NPOINTS TO ORDER --BUG IN THE
                                      PROGRAM??    */
  { 
     coef = coefficient;  /*   */
     state = internal_state;
     top = *data++;
     q_coef = *coef++;     /*  */
     state++;
     for (j = 1; j < ORDER; j++) {
      k_coef = *coef;   /*  */
      left = top;
      right = *state;
      *state++ = bottom;
      top = q_coef * left - k_coef * right;
      bottom = q_coef * right + k_coef * left; 
      q_coef = *coef++;  /*  */
     }
     *state++ = bottom;
     *state = top;
     state = internal_state;
     sum = 0.0;
     term_1 = *state++;
     term_2 = *coef++;
     for (j = 1; j <  ORDER; j++) {
       sum += term_1 * term_2;
       term_1 = *state++;
       term_2 = *coef++;
     }
     sum += term_1 * term_2;
     *outa++ = sum;
  }  
}

