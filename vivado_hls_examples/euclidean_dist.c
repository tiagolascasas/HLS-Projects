#include <math.h>

#define N 1024

float euclidean_dist(float a[N], float b[N]) {
	float dist = 0;
	for (int i = 0; i < N; i++)
		dist += powf(a[i] - b[i], 2);
	dist = sqrtf(dist);
	return dist;
}
