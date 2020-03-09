/* This program squeezes 8 pieces of 4-bits data into a 32-bits storage */

#include "traps.h"  
#define NSAMPLES 2408  

void squeeze ();
int tempstorage[(NSAMPLES+1)/2];
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
          outval = (unsigned int) (*outptr & 0x0000ffff);  
          squeeze ();
          Bufferstate++;
          outptr ++;  
        }

        output_dsp (tempstorage, ((NSAMPLES+1)/2)*4, 3); 
       
}


void squeeze ()

{
if (Bufferstate == 1 )
        {buffer = (outval << 16) & 0xffff0000;
         *temptr = buffer | *temptr;
         }
else if (Bufferstate == 2)
        {*temptr = outval | *temptr;
         Bufferstate = 0;
         temptr++; 
	 *temptr=0;
         }
}

