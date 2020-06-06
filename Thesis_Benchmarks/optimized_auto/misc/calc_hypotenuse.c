#include <math.h>
#include <stdio.h>
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
unsigned int square(unsigned int);
void calc_hypotenuse(unsigned int first_array[10000], unsigned int second_array[10000], unsigned int hypotenuse_array[10000]);
unsigned int int_sqrt(unsigned int value);
void print_hypotenuse(unsigned int first_array[10000], unsigned int second_array[10000], unsigned int hypotenuse_array[10000]);
int main() {
   unsigned int x = 0;
   unsigned int triangle_side_a[10000];
   unsigned int triangle_side_b[10000];
   unsigned int hypotenuse[10000];
   for(x = 0; x < 10000; x++) {
      triangle_side_a[x] = (x * 2) + 5;
      while(triangle_side_a[x] > 50000) {
         triangle_side_a[x] -= 1000;
      }
   }
   for(x = 0; x < 10000; x++) {
      triangle_side_b[x] = ((x + 3) * 3) + 3;
      while(triangle_side_b[x] > 50000) {
         triangle_side_b[x] -= 787;
      }
   }
   calc_hypotenuse(triangle_side_a, triangle_side_b, hypotenuse);
   print_hypotenuse(triangle_side_a, triangle_side_b, hypotenuse);
   
   return 0;
}

void calc_hypotenuse(unsigned int first_array[10000], unsigned int second_array[10000], unsigned int hypotenuse_array[10000]) {
   #pragma HLS stream variable=first_array
   #pragma HLS stream variable=second_array
   #pragma HLS array_partition variable=hypotenuse_array cyclic factor=97
   for(int x = 0; x < 10000; x++) {
      #pragma HLS unroll
      hypotenuse_array[x] = sqrt(square(first_array[x]) + square(second_array[x]));
   }
}

unsigned int square(unsigned int value) {
   #pragma HLS inline
   
   return value * value;
}

void print_hypotenuse(unsigned int first_array[10000], unsigned int second_array[10000], unsigned int hypotenuse_array[10000]) {
   unsigned int x = 0;
   for(x = 0; x < 10000; x++) {
      printf("(X = %d, Y = %d)", first_array[x], second_array[x]);
      printf(" Hipotenuse = %d\n", hypotenuse_array[x]);
   }
}

unsigned int int_sqrt(unsigned int value) {
   unsigned int i;
   unsigned int a = 0, b = 0, c = 0;
   for(i = 0; i < (32 >> 1); i++) {
      c <<= 2;
      c += (value >> 30);
      value <<= 2;
      a <<= 1;
      b = (a << 1) | 1;
      if(c >= b) {
         c -= b;
         a++;
      }
   }
   
   return a;
}
