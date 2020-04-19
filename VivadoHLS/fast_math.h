#pragma once
#include <stdint.h>

static inline float fast_fabs32(float number) {
    unsigned int p2 = * (unsigned int *) &number; 
    p2 = p2 & 0X7FFFFFFF;
    return * (float *) &p2;
}

static inline float fast_symmetrical32(float number) {
    unsigned int p2 = * (unsigned int *) &number; 
    p2 = p2 ^ (1 << 31);  // p2 ^ 0X80000000
    return * (float *) &p2;
}

static inline float fast_inv_sqrt32(float number) {
	uint32_t i;
	float x2, y;
	x2 = number * 0.5F;
	y = number;
	i = * (uint32_t *) &y;
	i = 0x5f375a86 - (i >> 1);
	y = *(float *) &i;
	y = y * (1.5F - (x2 * y * y));
	return y;
}

static inline double fast_inv_sqrt64(double number) {
	uint64_t i;
	double x2, y;
	x2 = number * 0.5;
	y = number;
	i = * (uint64_t *) &y;
	i = 0x5fe6eb50c7b537a9 - (i >> 1);
	y = * (double *) &i;
	y = y * (1.5 - (x2 * y * y));
	return y;
}