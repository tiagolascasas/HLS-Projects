#include <stdio.h>
#include <stdint.h>
#include <math.h>

float fast_fabs(float a) {
    unsigned int p2 = * (unsigned int *) &a; 
    p2 = p2 & 0X7FFFFFFF;
    return * (float *) &p2;
}

float fast_symmetrical(float a) {
    unsigned int p2 = * (unsigned int *) &a; 
    p2 = p2 ^ (1 << 31);  // p2 ^ 0X80000000
    return * (float *) &p2;
}

float rsqrt32(float number) {
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

double rsqrt64(double number) {
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
    printf("fabs\n");
    float a = -1.345f;
    float aa = fast_fabs(a);
    printf("%f -> %f\n", a, aa);
    float b = 1.345f;
    float bb = fast_fabs(b);
    printf("%f -> %f\n", b, bb);

    printf("symmetrical\n");
    float c = 2.450f;
    float cc = fast_symmetrical(c);
    printf("%f -> %f\n", c, cc);
    float d = -2.450f;
    float dd = fast_symmetrical(dd);
    printf("%f -> %f\n", d, dd);

    printf("sqrt float\n");
    float e = 1256.45f;
    float e1 = sqrtf(e);
    float e2 = e * rsqrt32(e);
    printf("%f -> %f | %f\n", e, e1, e2);

    printf("sqrt double\n");
    double f = 1256.45;
    double f1 = sqrt(f);
    double f2 = f * rsqrt64(f);
    printf("%f -> %f | %f\n", f, f1, f2);

    return 0;
}