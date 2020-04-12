#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "fast_math.h"

int main() {
    printf("fabs\n");
    float a = -1.345f;
    float aa = fast_fabs32(a);
    printf("%f -> %f\n", a, aa);
    float b = 1.345f;
    float bb = fast_fabs32(b);
    printf("%f -> %f\n", b, bb);

    printf("symmetrical\n");
    float c = 2.450f;
    float cc = fast_symmetrical32(c);
    printf("%f -> %f\n", c, cc);
    float d = -2.450f;
    float dd = fast_symmetrical32(dd);
    printf("%f -> %f\n", d, dd);

    printf("sqrt float\n");
    float e = 1256.45f;
    float e1 = sqrtf(e);
    float e2 = e * fast_inv_sqrt32(e);
    printf("%f -> %f | %f\n", e, e1, e2);

    printf("sqrt double\n");
    double f = 1256.45;
    double f1 = sqrt(f);
    double f2 = f * fast_inv_sqrt64(f);
    printf("%f -> %f | %f\n", f, f1, f2);

    return 0;
}