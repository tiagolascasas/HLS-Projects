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

main()
{
  float cdf,b2;
  float pixels;
  int i,j,ii,b3;

  /* Get the original image */

  input_dsp(image, N*N, 1);

  /* Initialize the histogram array. */

  for (i = 0; i < L; i++)
    histogram[i] = 0;

  /* Compute the image's histogram */


  for (i = 0; i < N; i++) {
    for (j = 0; j < N; ++j) {
      histogram[image[i][j]] += 1;
    }
  }

  /* Compute the mapping from the old to the new gray levels */

  cdf = 0.0;
  pixels = (float) (N * N);
  b3 = histogram[0];
  for (i = 1; i < L; i++) {
    cdf += ((float)(b3)) / pixels;
    gray_level_mapping[i-1] = (int)(255.0 * cdf);
    b3 = histogram[i];
  }
  cdf += ((float)(b3)) / pixels;
  gray_level_mapping[L-1] = (int)(255.0 * cdf);

  /* Map the old gray levels in the original image to the new gray levels. */

  for (i = 0; i < N; i++) {
    ii = image[i][0];
    for (j = 1; j < N; ++j) {
        image[i][j-1] = gray_level_mapping[ii];
	ii = image[i][j];
    }
    image[i][N-1] = gray_level_mapping[ii];
  }

  /* Return the histogram equalized image. */

  output_dsp(image, N*N, 1);
  output_dsp(histogram, L, 1);
  output_dsp(gray_level_mapping, L, 1);
}


