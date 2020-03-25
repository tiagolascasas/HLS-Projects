/* testc - Test adpcm coder */

#include "adpcm.h"
#include <stdio.h>

struct adpcm_state state;

#define NSAMPLES 2407 

char	abuf[(NSAMPLES/2)+1];
short	sbuf[NSAMPLES];

main() {
    int n;
    int Remainder;

    while(1) {
	n = read(0, sbuf, NSAMPLES*2);
	if ( n < 0 ) {
	    perror("input file");
	    exit(1);
	}
	if ( n == 0 ) break;
	adpcm_coder(sbuf, abuf, n/2, &state);

        /* check EOF and then write to abuf */
        Remainder = (2*NSAMPLES)%4;
        if (Remainder == 2)
	    write(1, abuf, (n/4)+1);
        if (Remainder == 0)
	    write(1, abuf, (n/4));
    }
    fprintf(stderr, "Final valprev=%d, index=%d\n",
	    state.valprev, state.index);
    exit(0);
}
