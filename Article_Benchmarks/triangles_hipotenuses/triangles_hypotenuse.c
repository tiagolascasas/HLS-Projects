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

int main(void) {

     unsigned int x = 0;
     unsigned int triangle_side_a[NUMBER_OF_TRIANGLES];
     unsigned int triangle_side_b[NUMBER_OF_TRIANGLES];
     unsigned int hypotenuse[NUMBER_OF_TRIANGLES];

     for(x=0; x<NUMBER_OF_TRIANGLES; x++) {
              triangle_side_a[x] = (x*2)+5;
              while(triangle_side_a[x] > 50000) {
                 triangle_side_a[x] -= 1000;
              }
     }

     for(x=0; x<NUMBER_OF_TRIANGLES; x++) {
              triangle_side_b[x] = ((x+3)*3)+3;
              while(triangle_side_b[x] > 50000) {
                 triangle_side_b[x] -= 787;
              }
     }

     calc_hypotenuse(triangle_side_a, triangle_side_b, hypotenuse);


     print_hypotenuse(triangle_side_a, triangle_side_b, hypotenuse);

     return 0;
}

void calc_hypotenuse(unsigned int first_array[], unsigned int second_array[], unsigned int hypotenuse_array[]) {
      for(int x=0; x<NUMBER_OF_TRIANGLES; x++) {
              hypotenuse_array[x] = sqrt(square(first_array[x]) +  square(second_array[x]));
     }
}

unsigned int square(unsigned int value) {
  return value*value;
}

void print_hypotenuse(unsigned int first_array[], unsigned int second_array[], unsigned int hypotenuse_array[]) {
      unsigned int x = 0;
      for(x=0; x<NUMBER_OF_TRIANGLES; x++) {
              printf("(X = %d, Y = %d)", first_array[x], second_array[x]);
              printf(" Hipotenuse = %d\n", hypotenuse_array[x]);
     }
}


#define UPPERBITS(value) (value>>30)
unsigned int int_sqrt (unsigned int value)
{
         unsigned int i;
         unsigned int a = 0, b = 0, c = 0;

         for (i=0; i < (32 >> 1); i++)
         {
          c<<= 2;
          c += UPPERBITS(value);
          value <<= 2;
          a <<= 1;
          b = (a<<1) | 1;
          if (c >= b)
          {
           c -= b;
           a++;
           }
           }
           return a;
}
