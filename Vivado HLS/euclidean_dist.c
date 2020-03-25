#include <math.h>
#include "rsqrt.h"

#define N 1024

float euclidean_dist_32(float a[N], float b[N]) {
	float dist = 0;
	for (int i = 0; i < N; i++) {
		dist += pow(a[i] - b[i], 2);
	}
	return rsqrt32(dist);
}

double euclidean_dist_64(double a[N], double b[N]) {
	double dist = 0;
	for (int i = 0; i < N; i++) {
		dist += pow(a[i] - b[i], 2);
	}
	return rsqrt64(dist);
}
