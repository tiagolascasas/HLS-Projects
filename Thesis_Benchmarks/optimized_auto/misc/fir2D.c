#include <stdlib.h>
// Display resolutions: https://en.wikipedia.org/wiki/Display_resolution

short const K[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
void fir2D(unsigned char in[480000], unsigned char out[480000]) {
   #pragma HLS array_partition variable=in cyclic factor=1024
   #pragma HLS array_partition variable=out cyclic factor=1024
   for(int row = 0; row < 598; row++) {
      for(int col = 0; col < 798; col++) {
         #pragma HLS pipeline
         unsigned short sumval = 0;
         for(int wrow = 0; wrow < 3; wrow++) {
            #pragma HLS unroll
            #pragma HLS pipeline
            for(int wcol = 0; wcol < 3; wcol++) {
               #pragma HLS unroll
               sumval += (unsigned short) in[(row + wrow) * 800 + (col + wcol)] * (unsigned short) K[wrow * 3 + wcol];
            }
         }
         sumval = sumval / 16;
         out[row * 800 + col] = (unsigned char) sumval;
      }
   }
}

int main() {
   unsigned char image[480000];
   for(int i = 0; i < 600 * 800; i++) image[i] = (unsigned char) (rand() % 255);
   unsigned char smooth_image[480000];
   fir2D(image, smooth_image);
   
   return 0;
}
