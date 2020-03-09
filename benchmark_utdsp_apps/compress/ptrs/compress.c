/* This program uses the discrete cosine transform to compress a 128 x 128 
   pixel image by a factor of 4:1 while preserving its information content.
   Block encoding is used with a block size of 8 x 8.

   This program is based on the routines and algorithms found in the book
   "C Language Algorithms for Digital Signal Processing" By P. M. Embree 
   and B. Kimble.

   Copyright (c) 1992 -- Mazen A.R. Saghir -- University of Toronto  */


#include "traps.h"

#define         ROUND(f)        (((f)<0.0) ? (int)((f)-0.5) : (int)((f)+0.5))
#define         N               128
#define         B               8
#define         P               1024

int image[N][N];                /* 2D array that stores the original image. */
int outer_block[B][B];          /* 2D array that stores an image block. */
float cos1[B][B];               /* 2D array that stores cosine coefficients. */
float cos2[B][B];               /* 2D array that is the transpose of cos1. */
float temp2d[B][B];             /* Temporary 2D array. */
int result[P];                  /* Result array */


main()
{
  float factor1;
  float factor2;
  float temp_cos;
  float *tp1;
  float *tp2;
  float *temp1;
  float *temp2;
  int *image_ptr;
  int *ptr1;
  int *ptr2;
  int *ptr3;
  int image_offset;
  int *offset1;
  int *offset2;
  int a;
  int b;
  int c;
  int d;
  int i;
  int j;
  int k;
  int l;
  int m;
  int n;

  void dct();
  int pack2in8();
  int pack4in32();


  /* Initialize the cosine matrices. "cos2" is the transpose of "cos1" */

  factor1 = 2.0 * atan(1.0) / B;
  tp1 = (float *)cos1;
  temp2 = (float *)cos2;
  factor2 = 0.0;
  for (i = 0; i < B; i++) {
    tp2 = temp2;
    k = 0;
    for (j = 0; j < B; j++) {
      temp_cos = cos(factor2 * (k + 1));
      temp_cos = temp_cos / B;
      *tp1++ = temp_cos; 
      *tp2 = temp_cos;
      tp2 += B;
      k += 2;
    }
    temp2++;
    factor2 += factor1;
  }

  /* Read the image */

  input_dsp(image, N*N, 1);

  /* Each image is assumed to have a resolution of 128 x 128, with 256 gray
     levels. Since each block is 8 x 8, 256 iterations are needed to compress
     the image. This is the main loop. */

  image_ptr = (int *)image;
  ptr3 = result;
  for (m = 0; m < 16; m++) {
    image_offset = 0;
    for(n = 0; n < 16; n++) {

      /* Read next image block. */

      ptr1 = image_ptr;
      ptr1 += image_offset;
      ptr2 = (int *)outer_block;
      for (k = 0; k < B; k++) {
	offset1 = ptr1;
	offset2 = ptr2;
	for (l = 0; l < B; l++) {
	  a = *offset1++;
	  *offset2++ = a;
	}
	ptr2 += B;
	ptr1 += N;
      }

      image_offset += B;


      /* Find its DCT */

      dct(outer_block);
   
      /* Select coefficients, scale, and pack */

      ptr1 = (int *)outer_block;

      a = *(ptr1); 
      b = *(ptr1 + 1); 
      i = *(ptr1 + 2) / 3;
      j = *(ptr1 + 3) / 3;
      c = pack2in8(i,j);
      i = *(ptr1 + 4) / 2;
      j = *(ptr1 + 5) / 2;
      d = pack2in8(i,j);
      *ptr3++ = pack4in32(a,b,c,d);

      i = *(ptr1 + 6);
      j = *(ptr1 + 7);
      a = pack2in8(i,j);
      ptr1 += B;
      b = *(ptr1);
      c = *(ptr1 + 1);
      i = *(ptr1 + 2) / 2;
      j = *(ptr1 + 3);
      d = pack2in8(i,j);
      *ptr3++ = pack4in32(a,b,c,d);

      i = *(ptr1 + 4);
      j = *(ptr1 + 5);
      a = pack2in8(i,j);
      ptr1 += B;
      i = *(ptr1) / 3;
      j = *(ptr1 + 1) / 2;
      b = pack2in8(i,j);
      i = *(ptr1 + 2) / 2;
      j = *(ptr1 + 3);
      c = pack2in8(i,j);
      ptr1 += B;
      i = *(ptr1) / 3;
      j = *(ptr1 + 1);
      d = pack2in8(i,j);
      *ptr3++ = pack4in32(a,b,c,d);

      i = *(ptr1 + 2);
      j = *(ptr1 + 3);
      a = pack2in8(i,j);
      ptr1 += B;
      i = *(ptr1) / 2;
      j = *(ptr1 + 1);
      b = pack2in8(i,j);
      ptr1 += B;
      i = *(ptr1) / 2;
      j = *(ptr1 + 1);
      c = pack2in8(i,j);
      ptr1 += B;
      i = *ptr1;
      ptr1 += B;
      j = *ptr1;
      d = pack2in8(i,j);
      *ptr3++ = pack4in32(a,b,c,d);
    }
    
    image_ptr += (B * N);
  }
  /* Store processed block */
    

  output_dsp(result, P, 1);	/* Result array */
  output_dsp(outer_block, B*B, 1);/* 2D array that stores an image block. */
  output_dsp(temp2d, B*B, 0);	/* Temporary 2D array. */
  output_dsp(cos1, B*B, 0);	/* 2D array that stores cosine coefficients. */
  output_dsp(cos2, B*B, 0);	/* 2D array that is the transpose of cos1. */
  output_dsp(image, N*N, 1);	/* 2D array that stores the original image. */
}




/* This function calculates the discrete cosine transform of an image block.
   The result is returned in the same matrix as the original block. */

void dct(block)
int *block;
{
  float *tp2;
  float *tp3;
  float *temp2;
  float *temp3;
  int *tp1;
  int *temp1;
  int i;
  int j;
  int k;
  int v1;
  float sum;
  float term_a;
  float term_b;
  float v2;
  float v3;

  float b1;
  float b2;
  int b3;
  int ii;

  /* Multiply the input image block with the cos2 matrix; store the result 
     in the temporary matrix "temp2d". */

  tp1 = block;
  tp3 = (float *)temp2d;
  for (i = 0; i < B; i++) {
    temp2 = (float *)cos2;
    temp3 = tp3;
    for (j = 0; j < B; j++) {
      tp2 = temp2;
      temp1 = tp1;
      sum = 0.0;
      for (k = 0; k < B; k++) {
        v1 = *temp1++;
        v2 = *tp2;
        tp2 += B;
	sum += v2 * v1;
      }
      *temp3++ = sum;
      temp2++;
    }
    tp1 += B;
    tp3 += B;
  }
  
  /* Multiply the cosine matrix by the temporary matrix; store the 
     result back in the original matrix.  */

  tp1 = block;
  tp3 = (float *)cos1;
  for (i = 0; i < B; i++) {
    temp1 = tp1;
    temp2 = (float *)temp2d;
    for (j = 0; j < B; j++) {
      tp2 = temp2;
      temp3 = tp3;
      sum = 0.0;
      for (k = 0; k < B; k++) {
        v2 = *temp3++;
        v3 = *tp2;
        tp2 += B;
	sum += v2 * v3 ;
      }
      *temp1++ = ROUND(sum); 
      temp2++;
    }
    tp3 += B;
    tp1 += B;
  }
}


int pack2in8(a,b)
int a;
int b;
{
  /* limit to signed 4 bits */

  if (a > 7) 
    a = 7;
  else if (a < -8)
    a = -8;

  if (b > 7) 
    b = 7;
  else if (b < -8)
    b = -8;

  return((a << 4) | (b & 15));
}

int pack4in32(a,b,c,d)
int a;
int b;
int c;
int d;
{
  /* limit to signed 8 bits */
  
  if (a > 127)
    a = 127;
  else if (a < -128)
    a = -128;

  if (b > 127)
    b = 127;
  else if (b < -128)
    b = -128;

  if (c > 127)
    c = 127;
  else if (c < -128)
    c = -128;

  if (d > 127)
    d = 127;
  else if (d < -128)
    d = -128;

  return((a << 24) | (b << 16) | (c << 8) | (d & 255));
}




