//DSP_dotprod
#define NX 100

int DSP_dotprod(short x[NX], const short y[NX])
{
    int sum = 0;

    for (int i = 0; i < NX; i++) {
        sum += x[i] * y[i];
        x[i] = 2;
    }

    return sum;
}