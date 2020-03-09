/* This program enhances a 256-gray-level, 128x128 pixel image by applying
   global histogram equalization.

   This program is based on the routines and algorithms found in the book
   "C Language Algorithms for Disgital Signal Processing" by P. M. Embree
   and B. Kimble.

   Copyright (c) 1992 -- Mazen A.R. Saghir -- University of Toronto */

#include "traps.h"

#define		N	128
#define 	L	256

int image[N][N];
int histogram[L];
int gray_level_mapping[L];

main()
{
  float cdf;
  float pixels;
  int *image_ptr;
  int *h;
  int *m;
  int v;
  int g;
  int i;
  float b2;
  int b3;
  int ii;

  /* Get the original image */

  input_dsp(image, N*N, 1);

  /* Initialize the histogram array. */

  h = histogram;
  for (i = 0; i < L; i++)
    *h++ = 0;

  /* Compute the image's histogram */

  image_ptr = image[0];
  h = histogram;
  for (i = 0; i < N * N; i++) {
    g = *image_ptr++;
    v = *(h + g);
    v++;
    *(h + g) = v;
  }


  /* Compute the mapping from the old to the new gray levels */

  h = histogram;
  m = gray_level_mapping;
  cdf = 0.0;
  pixels = (float) (N * N);
  v = *h++;
  for (i = 1; i < L; i++) {
    cdf += ((float)(v)) / pixels;
    *m++ = (int)(255.0 * cdf);
    v = *h++;
  }
  cdf += ((float)(v)) / pixels;
  *m++ = (int)(255.0 * cdf);

  /* Map the old gray levels in the original image to the new gray levels. */

  m = gray_level_mapping;
  image_ptr = image[0];
  for (i = 0; i < N * N; i++) {
    g = *image_ptr;
    v = *(m + g);
    *image_ptr++ = v;
  }

  /* Return the histogram equalized image. */

  output_dsp(image, N*N, 1);
  output_dsp(histogram, L, 1);
  output_dsp(gray_level_mapping, L, 1);
}
