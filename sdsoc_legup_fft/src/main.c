#include <stdio.h>
#include <stdlib.h>

#ifdef __SDSCC__
#include "sds_lib.h"
#else 
#define sds_alloc(x)(malloc(x))
#define sds_free(x)(free(x))
#endif

#include "fft.h"

int main() {
	short i, Real[Input_Size], Imag[Input_Size], New_Real[Input_Size],
			New_Imag[Input_Size];
	volatile short input_temp;
	int sum = 0;

	// Set input, each input value consists of a Real and imaginary part
	for (i = 0; i < Input_Size; i++) {
		input_temp = 0;
		Imag[i] = input_temp;
		input_temp = 10 * i;
		Real[i] = input_temp;
	}

	fft(Real, Imag, New_Real, New_Imag);

//  for (i=0; i<Input_Size; i++)
//    printf ("%d\t\t%d\n", New_Real[i], New_Imag[i]);

	for (i = 0; i < Input_Size; i++) {
		sum += abs(New_Real[i]);
		sum += abs(New_Imag[i]);
	}

	printf("Result: %d\n", sum);
	if (sum == 87100) {
		printf("RESULT: PASS\n");
	} else {
		printf("RESULT: FAIL\n");
	}

	return sum;
}
