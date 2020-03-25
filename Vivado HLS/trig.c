#include <math.h>

#define N 1024

float sine_sum(float coef[N], float weight[N], float x) {
	float sum = 0;
	for (int i = 0; i < N; i++)
		sum = weight[i] * sinf(coef[i] * x);
	return sum;
}

float cosine_sum(float coef[N], float weight[N], float x) {
	float sum = 0;
	for (int i = 0; i < N; i++)
		sum = weight[i] * cosf(coef[i] * x);
	return sum;
}
