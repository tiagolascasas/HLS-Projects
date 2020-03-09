#include "traps.h"  
#define NSAMPLES 396*4  /* NSAMPLES must be multiples of 4 */ 

void squeeze ();
int tempstorage[NSAMPLES/4];
int *temptr;
int outp[NSAMPLES];
int *outptr;
int Bufferstate=1;
int buffer;
int outval;


void main () {
        int i;

        input_dsp (outp, NSAMPLES*4, 3);

        temptr = tempstorage;
        *temptr = 0;
	outptr = outp;
 
        for (i=0; i<NSAMPLES; i++) {
          outval = (unsigned int) (*outptr & 0x000000ff);  
          squeeze ();
          Bufferstate++;
          outptr ++;  
        }

        output_dsp (tempstorage, NSAMPLES/4, 3); 
       
}


void squeeze ()

{
if (Bufferstate == 1 )
        *temptr = (outval << 24) & 0xff000000;

else if (Bufferstate == 2)
        {buffer = (outval << 16) & 0x00ff0000;
         *temptr = buffer | *temptr;
         }
else if (Bufferstate == 3)
        {buffer = (outval << 8) & 0x0000ff00;
         *temptr = buffer | *temptr;
         }
else if (Bufferstate == 4)
        {*temptr = outval | *temptr;
         Bufferstate = 0;
         temptr++; 
	 *temptr=0;
         }
}


