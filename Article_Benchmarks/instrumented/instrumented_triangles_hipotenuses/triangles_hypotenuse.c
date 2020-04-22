/*

Example to present:
- profiling;
- substitution of an algorithm in order to accelerate the application

From:
MicroBlaze System Performance Tuning
By: Richard Griffith and Felix Pang
Xilinx, White Paper: EDK
WP348 (v1.1) August 30, 2008
*/

#include <math.h>
#include <stdio.h>

#define NUMBER_OF_TRIANGLES 10000 //300

unsigned int square(unsigned int);
void calc_hypotenuse(unsigned int first_array[], unsigned int second_array[], unsigned int hypotenuse_array[]);
unsigned int int_sqrt(unsigned int value);

void print_hypotenuse(unsigned int first_array[], unsigned int second_array[], unsigned int hypotenuse_array[]);

int main(void)
{

    unsigned int x = 0;
    unsigned int triangle_side_a[NUMBER_OF_TRIANGLES];
    unsigned int triangle_side_b[NUMBER_OF_TRIANGLES];
    unsigned int hypotenuse[NUMBER_OF_TRIANGLES];

    for (x = 0; x < NUMBER_OF_TRIANGLES; x++)
    {
        triangle_side_a[x] = (x * 2) + 5;
        while (triangle_side_a[x] > 50000)
        {
            triangle_side_a[x] -= 1000;
        }
    }

    for (x = 0; x < NUMBER_OF_TRIANGLES; x++)
    {
        triangle_side_b[x] = ((x + 3) * 3) + 3;
        while (triangle_side_b[x] > 50000)
        {
            triangle_side_b[x] -= 787;
        }
    }

    calc_hypotenuse(triangle_side_a, triangle_side_b, hypotenuse);

    print_hypotenuse(triangle_side_a, triangle_side_b, hypotenuse);

    return 0;
}

void calc_hypotenuse(unsigned int first_array[NUMBER_OF_TRIANGLES], unsigned int second_array[NUMBER_OF_TRIANGLES], unsigned int hypotenuse_array[NUMBER_OF_TRIANGLES])
{
    //---------------------
    FILE *f = fopen("triangles_hypotenuse.dot", "w");
    int n_const = 0;
    int n_temp = 0;
    int ne = 0;
    int n_op = 0;

    int n_first_array[NUMBER_OF_TRIANGLES] = {0};
    int n_second_array[NUMBER_OF_TRIANGLES] = {0};
    int n_hypotenuse_array[NUMBER_OF_TRIANGLES] = {0};
    fprintf(f, "Digraph G{\n");
    for (int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        n_first_array[i]++;
        fprintf(f, "\"first_array[%d]_%d_l\" [label=\"first_array[%d]\", att1=var, att2=inte, att3=float ];\n", i, n_first_array[i], i);
        n_second_array[i]++;
        fprintf(f, "\"second_array[%d]_%d_l\" [label=\"second_array[%d]\", att1=var, att2=inte, att3=float ];\n", i, n_second_array[i], i);
    }
    //---------------------
    for (int x = 0; x < NUMBER_OF_TRIANGLES; x++)
    {
        //---------------------
        n_op++;
        fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
        n_temp++;
        fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
        ne++;
        fprintf(f, "\"first_array[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\", mod=\"square(\"];\n", x, n_first_array[x], n_op, ne, ne);
        ne++;
        fprintf(f, "\"second_array[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\", mod=\"square(\"];\n", x, n_second_array[x], n_op, ne, ne);
        ne++;
        fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

        n_hypotenuse_array[x]++;
        fprintf(f, "\"hypotenuse_array[%d]_%d\" [label=\"hypotenuse_array[%d]\", att1=var, att2=inte, att3=float ];\n", x, n_hypotenuse_array[x], x);
        ne++;
        fprintf(f, "temp%d->\"hypotenuse_array[%d]_%d\" [label=\"%d\", ord=\"%d\", mod=\"sqrt(\"];\n", n_temp, x, n_hypotenuse_array[x], ne);
        //---------------------
        hypotenuse_array[x] = sqrt(square(first_array[x]) + square(second_array[x]));
    }
    //---------------------
    fprintf(f, "}\n");
    fclose(f);
    //---------------------
}

unsigned int square(unsigned int value)
{
    return value * value;
}

void print_hypotenuse(unsigned int first_array[], unsigned int second_array[], unsigned int hypotenuse_array[])
{
    unsigned int x = 0;
    for (x = 0; x < NUMBER_OF_TRIANGLES; x++)
    {
        printf("(X = %d, Y = %d)", first_array[x], second_array[x]);
        printf(" Hipotenuse = %d\n", hypotenuse_array[x]);
    }
}

#define UPPERBITS(value) (value >> 30)
unsigned int int_sqrt(unsigned int value)
{
    unsigned int i;
    unsigned int a = 0, b = 0, c = 0;

    for (i = 0; i < (32 >> 1); i++)
    {
        c <<= 2;
        c += UPPERBITS(value);
        value <<= 2;
        a <<= 1;
        b = (a << 1) | 1;
        if (c >= b)
        {
            c -= b;
            a++;
        }
    }
    return a;
}
