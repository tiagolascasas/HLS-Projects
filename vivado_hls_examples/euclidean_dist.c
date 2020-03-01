#include <math.h>
#include "rsqrt.h"

#define N 1024

float euclidean_dist(float a[N], float b[N]) {
	float dist = 0;
	for (int i = 0; i < N; i++) {
		float d = a[i] - b[i];
		dist += d * d;
	}
	return sqrtf(dist);
}
