/*

aspectdef LoopUnroll
	
	// fully unroll innermost loop
    call LoopUnrollInnermost("smooth", 0);
	
	// fully unroll innermost loop
    call LoopUnrollInnermost("smooth", 0);
    
	// unroll by 4 innermost loop
    call LoopUnrollInnermost("smooth", 4);
end

// unrooll innermost FOR type loop given the name of the function
aspectdef LoopUnrollInnermost
    input funcname, factor end
	
	select function{name==funcname}.loop end
	apply
            $loop.perform Unroll(factor);
	end
    condition
		$loop.is_innermost &&
		$loop.type=="for"
	end
end


*/


/**
 *  A smooth image kernel.
 *  Also known as a 2D FIR
 */

#include <stdio.h>
 
#define sizeX 350
#define sizeY 350
#define W 3

void smooth(int in[][sizeX], int out[][sizeX]) {
    int j, i, r, c, sum;
	int k[W][W] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
	for (j=0; j < sizeY-2; j++) {
		for (i= 0; i < sizeX-2; i++) {
			sum = 0;
			for (r=0; r < W; r++) {
				for (c = 0; c < W; c++) {
					sum += in[j+r][i+c]*k[r][c];
				}
			}
			sum = sum / 16;
			out[j+1][i+1] = sum;
		}
	}
}

int in[sizeY][sizeX];
int out[sizeY][sizeX];

/*
* a main just to execute smooth;
*/
int main() {

	int i, j;
		
	/* for now a simple inicialization */
	for (j=0; j < sizeY; j++) {
		for (i= 0; i < sizeX; i++) {
			in[j][i] = i;
		}
	}
	
	smooth(in, out);


	/* some validity checking */
	long checksum = 0;
	for (j=0; j < sizeY; j++) {
		for (i= 0; i < sizeX; i++) {
			checksum+=out[j][i];
		}
	}
	printf("checksum = %ld\n",checksum);
  	if(checksum == 21132648)
		printf("RIGHT!\n");
	else
		printf("WRONG!\n");
}

