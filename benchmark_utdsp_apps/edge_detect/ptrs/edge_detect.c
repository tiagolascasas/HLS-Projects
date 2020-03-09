/* This program detects the edges in a 256 gray-level 128 x 128 pixel image.
   The program relies on a 2D-convolution routine to convolve the image with
   kernels (Sobel operators) that expose horizontal and vertical edge 
   information.

   The following is a block diagram of the steps performed in edge detection,


            +---------+       +----------+
   Input    |Smoothing|       |Horizontal|-------+
   Image -->| Filter  |---+-->| Gradient |       |	
            +---------+   |   +----------+  +----x-----+   +---------+  Binary
                          |                 | Gradient |   |  Apply  |  Edge
                          |                 | Combining|-->|Threshold|->Detected
                          |   +----------+  +----x-----+   +----x----+  Output
                          |   | Vertical |       |              |
                          +-->| Gradient |-------+              |
                              +----------+                   Threshold		
							       Value


    This program is based on the routines and algorithms found in the book
    "C Language Algorithms for Digital Signal Processing" by P.M. Embree
    and B. Kimble.

    Copyright (c) 1992 -- Mazen A.R. Saghir -- University of Toronto */

#include "traps.h"

#define 	K	3
#define 	N	128
#define 	T	127

int image_buffer1[N][N];
int image_buffer2[N][N];
int image_buffer3[N][N];
int filter[K][K];

main()
{
  int *matrix_ptr1;
  int *matrix_ptr2;
  int *matrix_ptr3;
  int *filter_ptr;
  int temp1;
  int temp2;
  int temp3;
  int v1;
  int v2;
  int v3;
  int i;
  int j;

  void convolve2d();

  /* Read input image. */

  input_dsp(image_buffer1, N*N, 1);

/* Set the values of the filter matrix to a Gaussian kernel. 
   This is used as a low-pass filter which blurs the image so as to
   de-emphasize the response of some isolated points to the edge
   detection (Sobel) kernels. */

  filter_ptr = (int *)filter;
  *filter_ptr++ = 1;
  *filter_ptr++ = 2;
  *filter_ptr++ = 1;
  *filter_ptr++ = 2;
  *filter_ptr++ = 4;
  *filter_ptr++ = 2;
  *filter_ptr++ = 1;
  *filter_ptr++ = 2;
  *filter_ptr   = 1;

  /* Perform the Gaussian convolution. */

  convolve2d(image_buffer1, filter, image_buffer3);

  /* Set the values of the filter matrix to the vertical Sobel operator. */

  filter_ptr = (int *)filter;
  *filter_ptr++ =  1;
  *filter_ptr++ =  0;
  *filter_ptr++ = -1;
  *filter_ptr++ =  2;
  *filter_ptr++ =  0;
  *filter_ptr++ = -2;
  *filter_ptr++ =  1;
  *filter_ptr++ =  0;
  *filter_ptr   = -1;

  /* Convolve the smoothed matrix with the vertical Sobel kernel. */

  convolve2d(image_buffer3, filter, image_buffer1);

  /* Set the values of the filter matrix to the horizontal Sobel operator. */

  filter_ptr = (int *)filter;
  *filter_ptr++ =  1;
  *filter_ptr++ =  2;
  *filter_ptr++ =  1;
  *filter_ptr++ =  0;
  *filter_ptr++ =  0;
  *filter_ptr++ =  0;
  *filter_ptr++ = -1;
  *filter_ptr++ = -2;
  *filter_ptr   = -1;

  /* Convolve the smoothed matrix with the horizontal Sobel kernel. */

  convolve2d(image_buffer3, filter, image_buffer2);

  /* Take the larger of the magnitudes of the horizontal and vertical 
     matrices. Form a binary image by comparing to a threshold and 
     storing one of two values. */

  matrix_ptr1 = (int *)image_buffer1;
  matrix_ptr2 = (int *)image_buffer2;
  matrix_ptr3 = (int *)image_buffer3;
  for (i = 0; i < N * N; i++) {
    v1 = *matrix_ptr1++;
    v2 = *matrix_ptr2++;
    temp1 = abs(v1);
    temp2 = abs(v2);
    temp3 = (temp1 > temp2) ? temp1 : temp2;
    *matrix_ptr3++ = (temp3 > T) ? 255 : 0;
  }

  /* Store binary image. */

  output_dsp(image_buffer3, N*N, 1);
  output_dsp(image_buffer1, N*N, 1);
  output_dsp(image_buffer2, N*N, 1);
  output_dsp(filter, K*K, 1);
}


/* This function convolves the input image by the kernel and stores the result
   in the output image. */

void convolve2d(input_image, kernel, output_image)
int *input_image;
int *kernel;
int *output_image;
{
  int *kernel_ptr;
  int *input_image_ptr;
  int *output_image_ptr;
  int *kernel_offset;
  int *input_image_offset;
  int *output_image_offset;
  int i;
  int j;
  int c;
  int r;
  int row;
  int col;
  int normal_factor;
  int sum;
  int temp1;
  int temp2;
  int dead_rows;
  int dead_cols;

  /* Set the number of dead rows and columns. These represent the band of rows
     and columns around the edge of the image whose pixels must be formed from
     less than a full kernel-sized compliment of input image pixels. No output
     values for these dead rows and columns since  they would tend to have less
     than full amplitude values and would exhibit a "washed-out" look known as
     convolution edge effects. */

  dead_rows = K / 2;
  dead_cols = K / 2;

  /* Calculate the normalization factor of the kernel matrix. */

  normal_factor = 0;
  kernel_ptr = kernel;
  for (r = 0; r < K; r++) {
    kernel_offset = kernel_ptr;
    for (c = 0; c < K; c++) {
      temp1 = *kernel_offset++;
      normal_factor += abs(temp1);
    }
    kernel_ptr += K;
  }

  if (normal_factor == 0)
    normal_factor = 1;

  /* Convolve the input image with the kernel. */

  row = 0;
  output_image_ptr = output_image;
  output_image_ptr += (N * dead_rows);
  for (r = 0; r < N - K + 1; r++) {
    output_image_offset = output_image_ptr;
    output_image_offset += dead_cols;
    col = 0;
    for (c = 0; c < N - K + 1; c++) {
      input_image_ptr = input_image;
      input_image_ptr += (N * row);
      kernel_ptr = kernel;
      sum = 0;
      for (i = 0; i < K; i++) {
        input_image_offset = input_image_ptr;
        input_image_offset += col;
        kernel_offset = kernel_ptr;
        for (j = 0; j < K; j++) {
          temp1 = *input_image_offset++;
          temp2 = *kernel_offset++;
          sum += temp1 * temp2;
        }
        kernel_ptr += K;
        input_image_ptr += N;
      }
      *output_image_offset++ = (sum / normal_factor);
      col++;
    }
    output_image_ptr += N;
    row++;
  }
}
