#include <math.h>

#define N 256

float foo(float x[N]) {
	//float is a 32-bit floating point type

	float n1 = 0;

	for (int i = 0; i < N; i++) {
		n1 += cosf(x[i]);
		n1 += powf(x[i], 1.5f);
		n1 += log10f(x[i]);
	}
	return n1;
}
