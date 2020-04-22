/* This program enhances a 256-gray-level, 128x128 pixel image by applying
   global histogram equalization.

   This program is based on the routines and algorithms found in the book
   "C Language Algorithms for Disgital Signal Processing" by P. M. Embree
   and B. Kimble.

   Copyright (c) 1992 -- Mazen A.R. Saghir -- University of Toronto */
/* Modified to use arrays - SMP */

#include <stdio.h>
#include "traps.h"

#define N 128
#define L 256

void hist(int image[N][N], int histogram[L], int gray_level_mapping[L])
{
    //---------------------
    FILE *f = fopen("histogram.dot", "w");
    int n_const = 0;
    int n_temp = 0;
    int ne = 0;
    int n_op = 0;

    int n_cdf = 0;
    int n_b2 = 0;
    int n_pixels = 0;

    int n_image[N][N] = {0};
    int n_histogram[L] = {0};
    int n_gray_level_mapping[L] = {0};
    fprintf(f, "Digraph G{\n");
    for (int i = 0; i < L; i++)
    {
        n_histogram[i]++;
        fprintf(f, "\"histogram[%d]_%d_l\" [label=\"histogram[%d]\", att1=var, att2=inte, att3=float ];\n", i, n_histogram[i], i);
        n_gray_level_mapping[i]++;
        fprintf(f, "\"gray_level_mapping[%d]_%d_l\" [label=\"gray_level_mapping[%d]\", att1=var, att2=inte, att3=float ];\n", i, n_gray_level_mapping[i], i);
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            n_image[i][j]++;
            fprintf(f, "\"n_image[%d][%d]_%d_l\" [label=\"data_imag[%d][%d]\", att1=var, att2=inte, att3=float ];\n", i, j, n_image[i][j], i, j);
        }
    }
    //---------------------
    float cdf;
    float b2;
    float pixels;

    /* Compute the image's histogram */

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; ++j)
        {
            //---------------------
            n_const++;
            fprintf(f, "const%d [label=\"1\", att1=const];\n", n_const);
            n_op++;
            fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(f, "\"const%d\"->\"op%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_op, ne, ne);
            ne++;
            fprintf(f, "\"histogram[%d]_%d_l\"->\"op%d\" [label=\"%d\", ord=\"%d\"];\n", image[i][j], n_histogram[image[i][j]], n_op, ne, ne);
            n_histogram[image[i][j]]++;
            fprintf(f, "\"histogram[%d]_%d_l\" [label=\"histogram[%d]\", att1=var, att2=inte, att3=float ];\n", image[i][j], n_histogram[image[i][j]], image[i][j]);
            ne++;
            fprintf(f, "\"op%d\"->\"histogram[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_op, image[i][j], n_histogram[image[i][j]], ne, ne);
            //---------------------
            histogram[image[i][j]] += 1;
        }
    }

    /* Compute the mapping from the old to the new gray levels */

    //---------------------
    n_const++;
    fprintf(f, "const%d [label=\"0.0\", att1=const];\n", n_const);
    n_cdf++;
    fprintf(f, "cdf_%d [label=\"cdf\", att1=var, att2=loc, att3=float];\n", n_cdf);
    ne++;
    fprintf(f, "\"const%d\"->\"cdf_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_cdf, ne, ne);
    //---------------------
    cdf = 0.0;

    //---------------------
    n_const++;
    fprintf(f, "const%d [label=\"%d\", att1=const];\n", n_const, N * N);
    n_pixels++;
    fprintf(f, "pixels_%d [label=\"pixels\", att1=var, att2=loc, att3=float];\n", n_pixels);
    ne++;
    fprintf(f, "\"const%d\"->\"pixels_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_pixels, ne, ne);
    //---------------------
    pixels = (float)(N * N);

    for (int i = 0; i < L; i++)
    {
        //---------------------
        n_op++;
        fprintf(f, "op%d [label=\"/\", att1=op];\n", n_op);
        ne++;
        fprintf(f, "\"histogram[%d]_%d_l\"->\"op%d\" [label=\"%d\", ord=\"%d\"];\n", i, n_histogram[i], n_op, ne, ne);
        ne++;
        fprintf(f, "\"pixels_%d\"->\"op%d\" [label=\"%d\", ord=\"%d\"];\n", n_pixels, n_op, ne, ne);
        n_temp++;
        fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
        ne++;
        fprintf(f, "\"op%d\"->\"temp_%d\" [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);
        n_op++;
        fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(f, "\"temp_%d\"->\"op%d\" [label=\"%d\", ord=\"%d\"];\n", n_temp, n_op, ne, ne);
        ne++;
        fprintf(f, "\"cdf_%d\"->\"op%d\" [label=\"%d\", ord=\"%d\"];\n", n_cdf, n_op, ne, ne);
        n_cdf++;
        fprintf(f, "\"cdf_%d\" [label=\"cdf\", att1=var, att2=loc, att3=float ];\n", n_cdf);
        ne++;
        fprintf(f, "\"op%d\"->\"cdf_%d\" [label=\"%d\", ord=\"%d\"];\n", n_op, n_cdf, ne, ne);
        //---------------------
        cdf += ((float)(histogram[i])) / pixels;

        //---------------------
        n_op++;
        fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
        n_const++;
        fprintf(f, "const%d [label=\"%.1f\", att1=const];\n", n_const, 255.0f);
        ne++;
        fprintf(f, "\"cdf_%d\"->\"op%d\" [label=\"%d\", ord=\"%d\"];\n", n_cdf, n_op, ne, ne);
        ne++;
        fprintf(f, "\"const_%d\"->\"op%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_op, ne, ne);
        n_temp++;
        fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
        ne++;
        fprintf(f, "\"op%d\"->\"temp_%d\" [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);
        n_gray_level_mapping[i]++;
        fprintf(f, "\"gray_level_mapping[%d]_%d_l\" [label=\"gray_level_mapping[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_gray_level_mapping[i], i);
        ne++;
        fprintf(f, "\"temp%d\"->\"gray_level_mapping[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_temp, i, n_gray_level_mapping[i], ne, ne);
        //---------------------
        gray_level_mapping[i] = (int)(255.0 * cdf);
    }

    /* Map the old gray levels in the original image to the new gray levels. */

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; ++j)
        {
            //---------------------
            n_image[i][j]++;
            fprintf(f, "\"image[%d][%d]_%d_l\" [label=\"image[%d][%d]\", att1=var, att2=inte, att3=int ];\n", i, j, n_image[i][j], i, j);
            ne++;
            fprintf(f, "\"gray_level_mapping[%d]_%d_l\"->\"image[%d][%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", image[i][j], n_gray_level_mapping[image[i][j]], i, j, n_image[i][j], ne, ne);
            //---------------------
            image[i][j] = gray_level_mapping[image[i][j]];
        }
    }
    //---------------------
    fprintf(f, "}\n");
    fclose(f);
    //---------------------
}

int main()
{
    /* Get the original image */
    int image[N][N] = {0};
    int histogram[L] = {0};
    int gray_level_mapping[L] = {0};

    input_dsp(image, N * N, 1);

    hist(image, histogram, gray_level_mapping);

    /* Return the histogram equalized image. */

    output_dsp(image, N * N, 1);
    output_dsp(histogram, L, 1);
    output_dsp(gray_level_mapping, L, 1);
}
