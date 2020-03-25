/* This program squeezes 8 pieces of 4-bits data into a 32-bits storage */

#include "traps.h"  
#define NSAMPLES 2408 

void squeeze ();
int tempstorage[(NSAMPLES+7)/8];
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
          outval = (unsigned int) (*outptr & 0x0000000f);  
          squeeze ();
          Bufferstate++;
          outptr ++;  
        }

        output_dsp (tempstorage, (NSAMPLES+1)/2, 3); 
       
}


void squeeze ()

{
if (Bufferstate == 1 )
        *temptr = (outval << 28) & 0xf0000000;

else if (Bufferstate == 2)
        {buffer = (outval << 24) & 0x0f000000;
         *temptr = buffer | *temptr;
         }
else if (Bufferstate == 3)
        {buffer = (outval << 20) & 0x00f00000;
         *temptr = buffer | *temptr;
         }
else if (Bufferstate == 4) 
        {buffer = (outval << 16) & 0x000f0000;
         *temptr = buffer | *temptr;
         }
else if (Bufferstate == 5)
        {buffer = (outval << 12) & 0x0000f000;
         *temptr = buffer | *temptr;
         }
else if (Bufferstate == 6)
        {buffer = (outval << 8) & 0x00000f00;
         *temptr = buffer | *temptr;
         }
else if (Bufferstate == 7)
        {buffer = (outval << 4)  & 0x000000f0;
         *temptr = buffer | *temptr;
         }
else if (Bufferstate == 8)
        {*temptr = outval | *temptr;
         Bufferstate = 0;
         temptr++; 
	 *temptr=0;
         }
}

