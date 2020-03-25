#include "traps.h"

int inarray[1];
int outarray[1];

void expand ();

void main ()
{
int x;

while (1){
  x=input_dsp (inarray, 1, 3);
  if (!x) break;
  expand (inarray,outarray);
}

}
 

void expand (int *inptr,int *outarray) 
{
  int value;
  int *outptr;
 
  outptr=outarray;
    value = *inptr & 0xf0000000;
    *outptr = (value >> 7*4) & 0x0000000f; 
  output_dsp (outptr, 1, 2);

    value = *inptr & 0x0f000000;
    *outptr = (value >> 6*4) & 0x0000000f; 
  output_dsp (outptr, 1, 2);


}
 
