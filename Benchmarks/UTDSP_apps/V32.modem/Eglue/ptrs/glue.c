#include "traps.h"

int inarray[2];
int outarray[1];

void expand ();

void main ()
{
int x;

while (1){
  x=input_dsp (inarray, 2, 2);
  if (x != 2) break;
  expand (inarray,outarray);
}

}
 

void expand (int *inptr,int *outarray) 
{
  int value;
  int *outptr;
 
  outptr=outarray;
    value = *inptr++;
    *outptr = (value << 7*4) & 0xf0000000; 

    value = *inptr ;
    *outptr = *outptr | ((value << 6*4) & 0x0f000000); 
  output_dsp (outptr, 1, 3);
}
