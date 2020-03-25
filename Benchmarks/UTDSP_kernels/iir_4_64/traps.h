/* This header file contains the declarations for the trap handlers */

/* type = 0 ---> floating point
          1 ---> signed integer
          2 ---> unsigned integer
*/

#include <math.h>

extern int input_dsp();			/* input_dsp  (dest,   words, type) */
extern void output_dsp();		/* output_dsp (source, words, type) */
/*
extern int abs();
extern float fabs();
extern float fmod();
extern float asin();
extern float acos();
extern float ceil();
extern float cos();
extern float exp();
extern float floor();
extern float log();
extern float log10();
extern float sin();
extern float sqrt();
extern float pow();
extern float tan();
extern float atan();

*/