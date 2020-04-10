#include <stdlib.h>

//Fir2D
#define WIDTH_SIZE 800
#define HEIGHT_SIZE 600

const short K[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

void fir2D(unsigned char in[HEIGHT_SIZE*WIDTH_SIZE], unsigned char out[HEIGHT_SIZE*WIDTH_SIZE])
{
	int row;
	for (row = 0; row < HEIGHT_SIZE - 3 + 1; row++)
	{
		int col;
		for (col = 0; col < WIDTH_SIZE - 3 + 1; col++)
		{
			unsigned short sumval = 0;
			int wrow;
			for (wrow = 0; wrow < 3; wrow++)
			{
				int wcol;
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
#define NX 3

int DSP_dotprod(const short x[NX], const short y[NX])
{
    int i, sum = 0;

    for (int i = 0; i < NX; i++)
        sum += x[i] * y[i];

    return sum;
}

//autocor
#define N 2
#define M 4

void autcor(short ac[M], short sd[N + M])
{
    int sum;

	int i;
    for (i = 0; i < M; i++)
    {
        sum = 0;
        int k;
        for (int k = 0; k < N; k++)
        {
            sum += sd[k + M] * sd[k + M - i];
        }
        ac[i] = (sum >> 15);
    }
}
