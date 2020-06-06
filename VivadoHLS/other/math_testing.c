#include <math.h>
#include "fast_math.h"

#define FAST

void make_positive(float a[1024]) {
	for (int i = 0; i < 1024; i++) {
#ifdef FAST
		a[i] = fast_fabs32(a[i]);
#else
		a[i] = fabsf(a[i]);
#endif
	}
}

void make_symmetrical(float a[1024]) {
	for (int i = 0; i < 1024; i++) {
#ifdef FAST
		a[i] = fast_symmetrical32(a[i]);
#else
		a[i] = -1 * a[i];
#endif
	}
}
