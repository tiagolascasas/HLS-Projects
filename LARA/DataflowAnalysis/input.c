#include <stdlib.h>

//Fir2D
#define WIDTH_SIZE 800
#define HEIGHT_SIZE 600

const short K[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

void fir2D(unsigned char in[HEIGHT_SIZE*WIDTH_SIZE], unsigned char out[HEIGHT_SIZE*WIDTH_SIZE])
{
    for (int row = 0; row < 598; row++)
    {
        for (int col = 0; col < 798; col++)
        {
            unsigned short sumval = 0;
            for (int wrow = 0; wrow < 3; wrow++)
            {
                for (int wcol = 0; wcol < 3; wcol++)
                {
                    sumval += (unsigned short)in[(row + wrow) * WIDTH_SIZE + (col + wcol)] * (unsigned short)K[wrow * 3 + wcol];
                }
            }
            sumval = sumval / 16;
            out[row * WIDTH_SIZE + col] = (unsigned char)sumval;
        }
    }
}

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

//autocor
#define N 2
#define M 4

void autcor(short ac[M], short sd[N + M])
{
    int sum;

    for (int i = 0; i < M; i++)
    {
        sum = 0;
        for (int k = 0; k < N; k++)
        {
            sum += sd[k + M] * sd[k + M - i];
        }
        ac[i] = (sum >> 15);
    }
}

int foo() {
	int x = 2;
	int y = 4;
	x = x + y;
	y = y + y + y;
	y = y * x;
	for (int i = 0; i < 10; i++)
		x += y;
	return x;
}
