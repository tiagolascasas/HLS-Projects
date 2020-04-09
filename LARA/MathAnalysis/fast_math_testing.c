#include <stdio.h>

inline float fast_fabs(float a) {
    unsigned int p2 = * (unsigned int *) &a; 
    p2 = p2 & 0X7FFFFFFF;
    return * (float *) &p2;
}

inline float fast_negate(float a) {
    unsigned int p2 = * (unsigned int *) &a; 
    p2 = p2 ^ (1 << 31);  // p2 ^ 0X80000000
    return * (float *) &p2;
}

inline float rsqrt32(float number) {
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

inline double rsqrt64(double number) {
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

int main() {
    float a = -1.345f;
    float aa = fast_fabs_condensed(a);
    printf("%f\n", aa);
    float b = -1.345f;
    float bb = fast_fabs_condensed(b);
    printf("%f\n", bb);

    float c = 2.450f;
    float cc = fast_negate(c);
    printf("%f\n", cc);
    float d = -2.450f;
    float dd = fast_negate(dd);
    printf("%f\n", dd);

    return 0;
}