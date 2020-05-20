#include <stdlib.h>
#include <math.h>

//Helper functions
float g1 = 2;
float g2 = 4;
int g3 = 123;

int foo(int x)
{
    int a = 0;
    for (int i = 0; i < 32; i++) {
    	int b = 0;
    	for (int j = 0; j < 16; j++) {
    		int c = a + b;
    		int d = c;
    		for (int k = 0; k < 8; k++) {
    			int e = 15;
    		}
    	}
    }
}

int bar(int x)
{
	int a = 1;
	int b = 2;
	int c = a + b;
	return c / a;
}

int funTest(int x[32], int y[16]) 
{
	int n1 = 500;
	int n2 = 200;
	n2 = foo(n1);
	for (int i = 0; i < 32; i++) 
	{
		int z = 0;
		z = bar(n2);
		for (int j = 0; j < 16; j++) 
		{
			int n3 = foo(n1);
			int n4 = bar(n2);
			int n5 = sqrt(n1);
			y[j] = n4; 
		}
	}
	return n1;
}

//dct
const int CosBlock[8][8] = {88, 122, 115, 103, 88, 69, 47, 24,
                            88, 103, 47, -24, -88, -122, -115, -69,
                            88, 69, -47, -122, -88, 24, 115, 103,
                            88, 24, -115, -69, 88, 103, -47, -122,
                            88, -24, -115, 69, 88, -103, -47, 122,
                            88, -69, -47, 122, -88, -24, 115, -103,
                            88, -103, 47, 24, -88, 122, -115, 69,
                            88, -122, 115, -103, 88, -69, 47, -24};

void dct(
    int InIm[8][8],
    int TempBlock[8][8],
    int CosTrans[8][8],
    int OutIm[8][8])
{
    int i;// = 0;
    int j = 0;
    int k;// = 0;
    int aux = 0;

    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
        {
            aux = 0;
            for (k = 0; k < 8; k++)
                aux += InIm[i][k] * CosTrans[k][j];
            TempBlock[i][j] = aux;
        }

    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
        {
            aux = 0;
            for (k = 0; k < 8; k++)
                aux += TempBlock[k][j] * CosBlock[i][k];
            OutIm[i][j] = aux;
        }
}

//Kalman
void kalman(int Y[16], int A[16 * 16], int K[16 * 16], int G[16 * 16], int V[4])
{
    int i, j, index, temp;
    int X[16];

    /* Initializing state Vector X */
    for (i = 0; i < 16; i++)
    {
        X[i] = 0;
    }

    /* Initializing state Vector Y */
    for (i = 12; i < 16; i++)
    {
        Y[i] = 0;
    }

    /* -- Computing state Vector X */
    for (i = 0; i < 16; i++)
    {
        temp = 0;
        for (j = 0; j < 16; j++)
        {
            index = i * 16 + j;
            temp += (A[index] * X[j] + K[index] * Y[j]);
        }
        X[i] = temp;
    }

    /* -- Computing output Vector V */
    // it only uses 4x16 elements of G
    for (i = 0; i < 4; i++)
    {
        temp = 0;
        for (j = 0; j < 16; j++)
        {
            index = i * 16 + j;
            temp += (G[index] * X[j]);
        }
        V[i] = (temp * Y[i + 1]);
    }
}

//Fir2D
#define WIDTH_SIZE 800
#define HEIGHT_SIZE 600

const short K[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
void fir2D(unsigned char in[HEIGHT_SIZE * WIDTH_SIZE], unsigned char out[HEIGHT_SIZE * WIDTH_SIZE])
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

    for (int i = 0; i < NX; i++)
    {
        sum += x[i] * y[i];
        sum = x[i] * y[i];
        sum = sum + x[i] * y[i];
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

int square(int x)
{
    return x * x;
}

void calc_hypotenuse(unsigned int first_array[NUMBER_OF_TRIANGLES], unsigned int second_array[NUMBER_OF_TRIANGLES], unsigned int hypotenuse_array[NUMBER_OF_TRIANGLES])
{
    for (unsigned int x = 0; x < NUMBER_OF_TRIANGLES; x++)
    {
        hypotenuse_array[x] = sqrt(square(first_array[x]) + square(second_array[x]));
    }
}

//gcd
int gcd(int n1, int n2) {  
    while (n1 != n2) {  
        if (n1 > n2) {
            n1 = n1 - n2;
        }      
        else {    
            n2 = n2 - n1;
        }      
    }  
    return n1;  
}  

//misc_fir
void fir(int x[M], int y[M], int c[N])
{
    int output;
    for (int j = N - 1; j < M; j++)
    {
        output = 0;
        for (int i = 0; i < N; i++)
        {
            output += c[i] * x[j - i];
        }

        y[j] = output;
    }
}

//utdsp_latnrm_32_64
#define NPOINTS 64
#define ORDER 32

/* the following values of coefficient and internal_state is define arbitrary */

float coefficient[NPOINTS] = {0.25, 0.51, 0.75, -0.25, 0.5, 0.75, 0.7, 0.625,
                              0.21, 0.22, 0.93, 0.81, 0.48, 0.208, 0.4, 0.6, 0.25, 0.35, 0.875, 0.295,
                              0.25, 0.725, 0.380, 0.295, 0.2, 0.22, 0.73, 0.91, 0.48, 0.28, 0.694,
                              0.6, 0.25, 0.5, 0.75, 0.525, 0.5, 0.75, -0.5, 0.725, 0.62, 0.272, 0.83,
                              0.81, 0.48, 0.28, 0.814, 0.56, 0.25, 0.5, 0.75, -0.25, 0.5, 0.75,
                              -0.810, 0.25, 0.02, 0.252, 0.913, 0.81, 0.468, 0.28, 0.4, 0.36};

float internal_state[NPOINTS] = {0.25, 0.5, 0.75, -0.29, 0.5, 0.75, -0.3,
                                 0.422, 0.82, 0.922, 0.63, 0.71, 0.48, 0.218, -0.24, 0.6, 0.92, 0.22,
                                 0.93, 0.51, 0.498, 0.28, -0.84, 0.26, 0.25, 0.95, 0.75, -0.27, 0.5,
                                 0.75, 0.80, 0.25, 0.25, 0.25, 0.735, -0.25, 0.5, 0.75, 0.20, 0.525,
                                 0.92, 0.22, 0.31, 0.81, 0.468, 0.288, -0.14, 0.65, 0.2, 0.272, 0.93,
                                 0.91, 0.485, 0.218, -0.4, 0.6, 0.82, 0.72, 0.63, 0.21, 0.438, 0.928,
                                 -0.24, 0.6};

void latnrm(float data[NPOINTS], float outa[NPOINTS],
            float coefficient[NPOINTS], float internal_state[NPOINTS])
{
    int i;
    int j;

    float left, right, top;
    float bottom = 0;
    float sum;
    for (i = 0; i < NPOINTS; i++)
    {
        top = data[i];
        for (j = 1; j < ORDER; j++)
        {
            left = top;
            right = internal_state[j];
            internal_state[j] = bottom;
            top = coefficient[j - 1] * left - coefficient[j] * right;
            bottom = coefficient[j - 1] * right + coefficient[j] * left;
        }
        internal_state[ORDER] = bottom;
        internal_state[ORDER + 1] = top;
        sum = 0.0;
        for (j = 0; j < ORDER; j++)
        {
            sum += internal_state[j] * coefficient[j + ORDER];
        }
        outa[i] = sum;
    }
}
