//#include <math.h>

#define N 1024

//Lara: should convert pow -> d * d and sqrt -> rsqrt32 
float dist32(float x1[N], float x2[N]) {
    float count = 0;
    for (int i = 0; i < N; i++)
        count += pow(x1[i] - x2[i], 2);
    return sqrt(count) + sqrt(count);
}

//Lara: should convert sqrt -> rsqrt64
double dist64(double x1[N], double x2[N]) {
    double count = 0;
    for (int i = 0; i < N; i++)
        count += pow(x1[i] - x2[i], 7);
    return sqrt(count);
}

//Lara: should convert sin -> sinf
float sum_sin(float coef[N], float weight[N], float x) {
    float sum = 0;
    for (int i = 0; i < N; i++)
        sum += weight[N] * sin(weight[N] * x);
    return sum;
}

//Lara: should convert cos -> cosf
float sum_cos(float coef[N], float weight[N], float x) {
    float sum = 0;
    for (int i = 0; i < N; i++)
        sum += weight[N] * cos(weight[N] * x);
    return sum;
}

//Lara: should convert all to float
float test_all_double(float x, float y) {
    float z = 0;
    z += acos(x);
    z += asin(x);
    z += atan(x);
    z += atan2(x, y);
    z += cos(x);
    z += cosh(x);
    z += sin(x);
    z += sinh(x);
    z += tanh(x);
    z += exp(x);
    //z += frexp(x, 4);
    z += ldexp(x, 4);
    z += log(x);
    z += log10(x);
    //z += modf(x, 4);
    z += pow(x, y);
    z += sqrt(x);
    z += ceil(x);
    z += fabs(x);
    z += floor(x);
    z += fmod(x, y);
    return x;
}

//Lara: should not convert to float
float test_all_float(float x, float y) {
    float z = 0;
    z += acosf(x);
    z += asinf(x);
    z += atanf(x);
    z += atan2f(x, y);
    z += cosf(x);
    z += coshf(x);
    z += sinf(x);
    z += sinhf(x);
    z += tanhf(x);
    z += expf(x);
    //z += frexpf(x, 4);
    z += ldexpf(x, 4);
    z += logf(x);
    z += log10f(x);
    //z += modff(x, 4);
    z += powf(x, y);
    z += sqrtf(x);
    z += ceilf(x);
    z += fabsf(x);
    z += floorf(x);
    z += fmodf(x, y);
    return x;
}