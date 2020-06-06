#include <math.h>

#define NUMBER_OF_TRIANGLES 10000 //300

unsigned int square(unsigned int value)
{
    return value * value;
}

void calc_hypotenuse(unsigned int first_array[NUMBER_OF_TRIANGLES], unsigned int second_array[NUMBER_OF_TRIANGLES], unsigned int hypotenuse_array[NUMBER_OF_TRIANGLES])
{
#pragma HLS STREAM variable=second_array dim=1
#pragma HLS STREAM variable=first_array dim=1
    for (int x = 0; x < NUMBER_OF_TRIANGLES; x++)
    {
#pragma HLS UNROLL factor=4
        hypotenuse_array[x] = sqrt(square(first_array[x]) + square(second_array[x]));
    }
}


