/*
   Corinna G. Lee
   6 Jun 94: Modified for GNU C version of DSP programs:
 	1. "float" data type converted into "double" data type
	    so that math library functions can be used
	2. add data_type=3 to read/write binary data
   13 Jun 94: Make file pointers static variables to allow multiple calls
	to same I/O routine.  Note: files are not explicitly closed.

   Mark G. Stoodley
   17 Apr 96: caused input_dsp to return an integer that is non-zero if data
		was read from the file
*/

#include <stdio.h>
#include <stdlib.h>

FILE	*input_fp=NULL,*output_fp=NULL;

int input_dsp (dest, words, data_type)
void *dest;
int  words;
int  data_type;
{
  int success;
  int		i;
  double	*float_ptr;
  int		*int_ptr;
  unsigned	*unsigned_ptr;

  if (input_fp==NULL && (input_fp = fopen ("input.dsp", "r")) == NULL) {
    printf ("** Error: cannot open input.dsp.\n");
    exit(1);
  }

  if (words <= 0) {
    printf ("** Error: trying to read a negative or zero number of words.\n");
    exit (1);
  }

  switch (data_type) {
    case 0:
      float_ptr = (double *) dest;
      for (i = 0; i < words; i++)
        success = fscanf (input_fp, "%lf", &float_ptr[i]);
      break;
    case 1:
      int_ptr = (int *) dest;
      for (i = 0; i < words; i++)
        success = fscanf (input_fp, "%d", &int_ptr[i]);
      break;
    case 2:
      unsigned_ptr = (unsigned *) dest;
      for (i = 0; i < words; i++)
        success = fscanf (input_fp, "%u", &unsigned_ptr[i]);
      break;
    case 3:
      success = fread( (char *) dest, 1, words, input_fp);
      break;
    default:
      printf ("** Error: trying to use an undefined data type. \n");
      exit(1);
      break;
  }

  return success;
}


void output_dsp (src, words, data_type)
void *src;
int  words;
int  data_type;
{
  int i;
  double *float_ptr;
  int *int_ptr;
  unsigned *unsigned_ptr;

  if (output_fp==NULL && (output_fp = fopen ("output.dsp", "w")) == NULL) {
    printf ("** Error: cannot open output.dsp.\n");
    exit(1);
  }

  if (words <= 0) {
    printf ("** Error: trying to write a negative or zero number of words.\n");
    exit (1);
  }

  switch (data_type) {
    case 0:
      float_ptr = (double *) src;
      for (i = 0; i < words; i++)
        fprintf (output_fp, "%lf\n", float_ptr[i]);
      break;
    case 1:
      int_ptr = (int *) src;
      for (i = 0; i < words; i++)
        fprintf (output_fp, "%d\n", int_ptr[i]);
      break;
    case 2:
      unsigned_ptr = (unsigned *) src;
      for (i = 0; i < words; i++)
        fprintf (output_fp, "%u\n", unsigned_ptr[i]);
      break;
    case 3:
      fwrite( (char *) src, 1, words, output_fp);
      break;
    default:
      printf ("** Error: trying to use an undefined data type. \n");
      exit(1);
      break;
  }

}
