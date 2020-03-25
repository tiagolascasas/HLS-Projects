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
/* Modified to use arrays - SMP */

//#include "traps.h"
#include <stdlib.h> 
#include <stdio.h> 

#define         K       3
#define         N       64
#define         T       127

int image_buffer1[N][N];
int image_buffer2[N][N];
int image_buffer3[N][N];
int filter[K][K];
void convolve2d(int input_image[N][N], int kernel[K][K], int output_image[N][N]);
void result( int kernel[K][K], int input_image[N][N], int output_image[N][N]);
void main()
{
  int temp1;
  int temp2;
  int temp3;
  int i;
  int j;


  /* Read input image. */

  //input_dsp(image_buffer1, N*N, 1);

  /* Initialize image_buffer2 and image_buffer3 */

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; ++j) {
	   image_buffer1[i][j] = i*5;
       image_buffer2[i][j] = 0;
       image_buffer3[i][j] = 0;
     }
  }


/* Set the values of the filter matrix to a Gaussian kernel.
   This is used as a low-pass filter which blurs the image so as to
   de-emphasize the response of some isolated points to the edge
   detection (Sobel) kernels. */

  filter[0][0] = 1;
  filter[0][1] = 2;
  filter[0][2] = 1;
  filter[1][0] = 2;
  filter[1][1] = 4;
 filter[1][2] = 2;
  filter[2][0] = 1;
  filter[2][1] = 2;
  filter[2][2] = 1;

  /* Perform the Gaussian convolution. */

  convolve2d(image_buffer1, filter, image_buffer3);
  printf("Convolve\n");

 result(filter, image_buffer1 , image_buffer2);
 printf("Post Graph\n");
 int corr=1;
   for (i = 0; i < N; i++) {
    for (j = 0; j < N; ++j) {
		if(image_buffer2[i][j]!=image_buffer3[i][j])
			corr=0;
     }
  }
  
  if(corr==1){
	  printf("Correct");
  } else
	printf("Error");
}


/* This function convolves the input image by the kernel and stores the result
   in the output image. */

void convolve2d(int input_image[N][N], int kernel[K][K], int output_image[N][N])
{
	
  FILE *f=fopen("edge_detect.dot","w");
  fprintf(f,"Digraph G{\n");
  
  int i;
  int j;
  int c;
  int r;
  int normal_factor;
 
  int sum;
  int dead_rows;
  int dead_cols;
  
   int n_normal_factor=0;
   int n_temp=0;
   int n_const=0;
   int n_sum=0;
   int ne=0;
   int n_K=0;
   int n_op=0;
   int n_input_image[N][N]={0};
   int n_kernel[K][K]={0};
   int n_output_image[N][N]={0};
  /* Set the number of dead rows and columns. These represent the band of rows
     and columns around the edge of the image whose pixels must be formed from
     less than a full kernel-sized compliment of input image pixels. No output
     values for these dead rows and columns since  they would tend to have less
     than full amplitude values and would exhibit a "washed-out" look known as
     convolution edge effects. */

  dead_rows = K / 2;
  
	n_const++;
	fprintf(f,"\"const%d\" [label=\"2\", att1=const];\n",n_const);
	fprintf(f,"\"K_%d\" [label=\"K\", att1=var, att2=loc, att3=short ];\n",n_K);
	n_op++;
	fprintf(f,"\"op%d\" [label=\"div\", att1=op ];\n",n_op);	
	fprintf(f,"\"dead_rows_%d\" [label=\"dead_rows\", att1=var, att2=loc, att3=int ];\n",1);	
	
	ne++;
	fprintf(f,"\"K_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n",n_K,n_op,ne,ne);
	ne++;
	fprintf(f,"\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n",n_const,n_op,ne,ne);
	ne++;
	fprintf(f,"op%d->\"dead_rows_%d\" [label=\"%d\", ord=\"%d\"];\n",n_op,1,ne,ne);
		
  dead_cols = K / 2;
	
	n_const++;
	fprintf(f,"\"const%d\" [label=\"2\", att1=const];\n",n_const);
	fprintf(f,"\"K_%d\" [label=\"K\", att1=var, att2=loc, att3=short ];\n",n_K);
	n_op++;
	fprintf(f,"\"op%d\" [label=\"div\", att1=op ];\n",n_op);	
	fprintf(f,"\"dead_cols_%d\" [label=\"dead_cols\", att1=var, att2=loc, att3=int ];\n",1);	
	
	ne++;
	fprintf(f,"\"K_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n",n_K,n_op,ne,ne);
	ne++;
	fprintf(f,"\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n",n_const,n_op,ne,ne);
	ne++;
	fprintf(f,"op%d->\"dead_cols_%d\" [label=\"%d\", ord=\"%d\"];\n",n_op,1,ne,ne);
  /* Calculate the normalization factor of the kernel matrix. */

  normal_factor = 0;
  
    n_const++;
	fprintf(f,"const%d [label=\"0\", att1=const];\n",n_const);
	fprintf(f,"\"normal_factor_%d\" [label=\"normal_factor\", att1=var, att2=loc, att3=int ];\n",n_normal_factor+1);
	ne++;
	fprintf(f,"const%d->\"normal_factor_%d\" [label=\"%d\", ord=\"%d\"];\n",n_const,n_normal_factor+1,ne,ne);
	n_normal_factor++;
	 
  for (r = 0; r < K; r++) {
    for (c = 0; c < K; c++) {
      normal_factor += abs(kernel[r][c]);
	  
	  	fprintf(f,"\"kernel[%d][%d]_%d\" [label=\"kernel[%d][%d]\", att1=var, att2=inte, att3=int ];\n" ,r,c, n_kernel[r][c] ,r,c);//nc-5
		fprintf(f,"\"normal_factor_%d\" [label=\"normal_factor\", att1=var, att2=loc, att3=int ];\n" ,n_normal_factor);//nc-5
		n_op++;
		fprintf(f,"op%d [label=\"+\", att1=op];\n",n_op);//nc-3
		
		fprintf(f,"normal_factor_%d [label=\"normal_factor\", att1=var, att2=loc, att3=int ];\n",n_normal_factor+1);//nc-2
		   
		ne++;
		fprintf(f,"\"normal_factor_%d\" ->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n",n_normal_factor,n_op,ne,ne);
		ne++;
		fprintf(f,"\"kernel[%d][%d]_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\",mod=\"abs(\" ];\n",r,c, n_kernel[r][c],n_op,ne,ne);
		ne++;
		fprintf(f,"op%d->normal_factor_%d [label=\"%d\", ord=\"%d\"];\n",n_op,n_normal_factor+1,ne,ne);
		n_normal_factor++; 
	
		
    }
  }

  if (normal_factor == 0){
    normal_factor = 1;
	n_const++;
	fprintf(f,"const%d [label=\"1\", att1=const];\n",n_const);
	fprintf(f,"\"normal_factor_%d\" [label=\"normal_factor\", att1=var, att2=loc, att3=int ];\n",n_normal_factor+1);
	ne++;
	fprintf(f,"const%d->\"normal_factor_%d\" [label=\"%d\", ord=\"%d\"];\n",n_const,n_normal_factor+1,ne,ne);
	n_normal_factor++;	
  }

  /* Convolve the input image with the kernel. */
  for (r = 0; r < N - K + 1; r++) {
    for (c = 0; c < N - K + 1; c++) {
      sum = 0;
	  
	 n_const++;
	 fprintf(f,"const%d [label=\"0\", att1=const];\n",n_const);
	 fprintf(f,"\"sum_%d\" [label=\"sum\", att1=var, att2=loc, att3=int ];\n",n_sum+1);
	 ne++;
	 fprintf(f,"const%d->\"sum_%d\" [label=\"%d\", ord=\"%d\"];\n",n_const,n_sum+1,ne,ne);
	 n_sum++;
	 
      for (i = 0; i < K; i++) {
        for (j = 0; j < K; j++) {
          sum += input_image[r+i][c+j] * kernel[i][j];
		  
		fprintf(f,"\"input_image[%d][%d]_%d\" [label=\"input_image[%d][%d]\", att1=var, att2=inte, att3=int ];\n" ,r+i,c+j, n_input_image[r+i][c+j] ,r+i,c+j);//nc-5
		fprintf(f,"\"kernel[%d][%d]_%d\" [label=\"kernel[%d][%d]\", att1=var, att2=inte, att3=int ];\n" ,i,j, n_kernel[i][j] ,i,j);//nc-5
		n_op++;
		fprintf(f,"op%d [label=\"*\", att1=op];\n",n_op);//nc-3
		n_temp++;
		fprintf(f,"temp%d [label=\"temp_l258_i%d\", att1=var, att2=loc, att3=int ];\n",n_temp,n_temp);//nc-2
		   
		ne++;
		fprintf(f,"\"input_image[%d][%d]_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n",r+i,c+j, n_input_image[r+i][c+j],n_op,ne,ne);
		ne++;
		fprintf(f,"\"kernel[%d][%d]_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n",i,j, n_kernel[i][j],n_op,ne,ne);
		ne++;
		fprintf(f,"op%d->temp%d [label=\"%d\", ord=\"%d\"];\n",n_op,n_temp,ne,ne);
		   
		fprintf(f,"temp%d [label=\"temp_l258_i%d\", att1=var, att2=loc, att3=int ];\n",n_temp,n_temp);//nc-2
		fprintf(f,"\"sum_%d\" [label=sum, att1=var, att2=loc, att3=int ];\n",n_sum);
		n_op++;
		fprintf(f,"op%d [label=\"+\", att1=op ];\n",n_op);//nc-1
		fprintf(f,"\"sum_%d\" [label=sum, att1=var, att2=loc, att3=int ];\n",n_sum+1);
		   
		ne++;		   
		fprintf(f,"temp%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n",n_temp,n_op,ne,ne);
		ne++;
		fprintf(f,"\"sum_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n",n_sum,n_op,ne,ne);
		ne++;
		fprintf(f,"op%d->\"sum_%d\" [label=\"%d\", ord=\"%d\"];\n",n_op,n_sum+1,ne,ne);
	    n_sum++;
		
        }
      }
      output_image[r+dead_rows][c+dead_cols] = (sum / normal_factor);
	  
	  	fprintf(f,"\"sum_%d\" [label=sum, att1=var, att2=loc, att3=int ];\n",n_sum);
		//n_const++;
	    //fprintf(f,"const%d [label=\"16\", att1=const];\n",n_const);
		fprintf(f,"\"normal_factor_%d\" [label=\"normal_factor\", att1=var, att2=loc, att3=int ];\n" ,n_normal_factor);//nc-5
		n_op++;
		fprintf(f,"op%d [label=\"div\", att1=op];\n",n_op);//nc-3
		
		fprintf(f,"\"output_image[%d][%d]_%d\" [label=\"output_image[%d][%d]\", att1=var, att2=inte, att3=int ];\n",r+dead_rows,c+dead_cols,n_output_image[r+dead_rows][c+dead_cols]+1,r+dead_rows,c+dead_cols);//nc-2
		   
		ne++;
		fprintf(f,"\"sum_%d\" ->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n",n_sum,n_op,ne,ne);
		ne++;
		fprintf(f,"\"normal_factor_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n",n_normal_factor,n_op,ne,ne);
		//fprintf(f,"const%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n",n_const,n_op,ne,ne);
		ne++;
		fprintf(f,"op%d->\"output_image[%d][%d]_%d\" [label=\"%d\", ord=\"%d\"];\n",n_op,r+dead_rows,c+dead_cols,n_output_image[r+dead_rows][c+dead_cols]+1,ne,ne);
		n_output_image[r+dead_rows][c+dead_cols]++; 
    }
  }
  
  	
	fprintf(f,"}\n");	
	fclose(f);
}

//Func created from graph [First implementatiom]// Step by step description of process
// Step 1: create function header

void result( int kernel[K][K], int input_image[N][N], int output_image[N][N]){
// Step 2: Initialize local variables
int normal_factor_w0;
int sum_w1;
int normal_factor;
int temp_l258_i9;
int sum;
int sum_w2;
int temp_l258_i8;
int sum_w3;
int temp_l258_i7;
int sum_w4;
int temp_l258_i6;
int sum_w5;
int temp_l258_i5;
int sum_w6;
int temp_l258_i4;
int sum_w7;
int temp_l258_i3;
int sum_w8;
int temp_l258_i2;
int sum_w9;
int temp_l258_i1;
int sum_w10;
int normal_factor_w11;
int normal_factor_w12;
int normal_factor_w13;
int normal_factor_w14;
int normal_factor_w15;
int normal_factor_w16;
int normal_factor_w17;
int normal_factor_w18;
// Initialization done




// Step 3: write code by level
// Currently we write attributions and  simple operations between two variabels


normal_factor_w18=0;

normal_factor_w17=normal_factor_w18 + kernel[0][0];

normal_factor_w16=normal_factor_w17 + kernel[0][1];

normal_factor_w15=normal_factor_w16 + kernel[0][2];

normal_factor_w14=normal_factor_w15 + kernel[1][0];

normal_factor_w13=normal_factor_w14 + kernel[1][1];

normal_factor_w12=normal_factor_w13 + kernel[1][2];

normal_factor_w11=normal_factor_w12 + kernel[2][0];

normal_factor_w0=normal_factor_w11 + kernel[2][1];

normal_factor=normal_factor_w0 + kernel[2][2];


 // CreatingLoop
// starting Loop
for( int i =0; i < 14; i=i+1){
#pragma HLS pipeline


// Currently we write attributions and  simple operations between two variabels and unrolling with directive
// Start of Level 0:
// Start of Level 1:
// Start of Level 2:

 // CreatingLoop
// starting Loop
for( int j =0; j < 14; j=j+1){
#pragma HLS pipeline


// Currently we write attributions and  simple operations between two variabels and unrolling with directive
// Start of Level 0:
// Start of Level 1:
// Start of Level 2:
temp_l258_i9=input_image[i+2][j+2] * kernel[2][2];
temp_l258_i8=input_image[i+2][j+1] * kernel[2][1];
temp_l258_i7=input_image[i+2][j] * kernel[2][0];
temp_l258_i6=input_image[i+1][j+2] * kernel[1][2];
temp_l258_i5=input_image[i+1][j+1] * kernel[1][1];
temp_l258_i4=input_image[i+1][j] * kernel[1][0];
temp_l258_i3=input_image[i][j+2] * kernel[0][2];
temp_l258_i2=input_image[i][j+1] * kernel[0][1];
temp_l258_i1=input_image[i][j] * kernel[0][0];
sum_w10=0;
// Start of Level 3:
sum_w9=sum_w10 + temp_l258_i1;
// Start of Level 4:
sum_w8=sum_w9 + temp_l258_i2;
// Start of Level 5:
sum_w7=sum_w8 + temp_l258_i3;
// Start of Level 6:
sum_w6=sum_w7 + temp_l258_i4;
// Start of Level 7:
sum_w5=sum_w6 + temp_l258_i5;
// Start of Level 8:
sum_w4=sum_w5 + temp_l258_i6;
// Start of Level 9:
sum_w3=sum_w4 + temp_l258_i7;
// Start of Level 10:
sum_w2=sum_w3 + temp_l258_i8;
// Start of Level 11:
sum_w1=sum_w2 + temp_l258_i9;
// Start of Level 12:
output_image[i+1][j+1]=sum_w1 / normal_factor;
// Start of Level 13:
// Start of Level 14:
}
// Start of Level 3:
}
}


