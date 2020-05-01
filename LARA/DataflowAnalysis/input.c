#include <stdlib.h>

//Helper functions
float g1 = 2;
float g2 = 4;
int g3 = 123;

int foo(int x) {
	return x + x / x;
}

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

//misc_dsp_dotprod
#define NX 100

int DSP_dotprod(short x[NX], const short y[NX])
{
    int sum = 0;

    for (int i = 0; i < NX; i++) {
        sum += x[i] * y[i];
    }

    return sum;
}

//misc_autocor
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

//misc_triangles_hypotenuse
#define NUMBER_OF_TRIANGLES 100000

int square(int x) {
	return x * x;
}

void calc_hypotenuse(unsigned int first_array[NUMBER_OF_TRIANGLES], unsigned int second_array[NUMBER_OF_TRIANGLES], unsigned int hypotenuse_array[NUMBER_OF_TRIANGLES]) {
      for(unsigned int x=0; x<NUMBER_OF_TRIANGLES; x++) {
              hypotenuse_array[x] = sqrt(square(first_array[x]) +  square(second_array[x]));
     }
}

//misc_fir
void fir(int x[M],int  y[M], int c[N])
{
	int output;
	for(int j=N-1; j<M; j++) {
		output=0;
		// Loop 2:
		for(int i=0; i<N; i++) {
			output+=c[i]*x[j-i];
		}
	
		y[j] = output;
	}
}
