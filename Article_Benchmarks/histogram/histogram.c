/* This program enhances a 256-gray-level, 128x128 pixel image by applying
   global histogram equalization.

   This program is based on the routines and algorithms found in the book
   "C Language Algorithms for Disgital Signal Processing" by P. M. Embree
   and B. Kimble.

   Copyright (c) 1992 -- Mazen A.R. Saghir -- University of Toronto */
/* Modified to use arrays - SMP */

#include "traps.h"

#define         N       128
#define         L       256

int image[N][N];
int histogram[L];
int gray_level_mapping[L];

void hist() {
  float cdf;
  float b2;
  float pixels;

  /* Initialize the histogram array. */

  for (int i = 0; i < L; i++)
    histogram[i] = 0;

  /* Compute the image's histogram */


   for (int i = 0; i < N; i++) {
     for (int j = 0; j < N; ++j) {
       histogram[image[i][j]] += 1;
     }
   }

  /* Compute the mapping from the old to the new gray levels */

  cdf = 0.0;
  pixels = (float) (N * N);
  for (int i = 0; i < L; i++) {
    cdf += ((float)(histogram[i])) / pixels;
    gray_level_mapping[i] = (int)(255.0 * cdf);
  }

  /* Map the old gray levels in the original image to the new gray levels. */

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; ++j) {
        image[i][j] = gray_level_mapping[image[i][j]];
    }
  }
}

int main()
{
  /* Get the original image */

  input_dsp(image, N*N, 1);

  hist();

  /* Return the histogram equalized image. */

  output_dsp(image, N*N, 1);
  output_dsp(histogram, L, 1);
  output_dsp(gray_level_mapping, L, 1);
}


