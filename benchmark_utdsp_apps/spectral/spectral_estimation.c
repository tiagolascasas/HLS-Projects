/* This program calculates the power spectral estimate of an input sample of
   speech using periodogram averaging. An FFT routine is used to calculate the
   different periodograms associated with the input sample.

   The program is based on the routines and algorithms found in the book
   "C Language Algorithms for Digital Signal Processing" by P.M. Embree
   and B. Kimble.

   Copyright (c) 1992 -- Mazen A.R. Saghir -- University of Toronto */
/* Modified to use arrays - SMP */

#include "traps.h"

#define         SAMPLES         124     /* Number of input speech samples. */
#define         SLICE           64      /* Number of samples per slice. */
#define         OVLAP           60      /* Number of overlapping samples. */
#define         NUMAV           16      /* Number of slices to average. */

#define         DELTA           ((SLICE) - (OVLAP))
#define         SLICE_2         ((SLICE) * (SLICE))
#define         MAX(X, Y)       (((X) > (Y)) ? (X) : (Y))

float input_signal[SAMPLES];
float mag[SLICE];
float hamming[SLICE];
float sample_real[SLICE];
float sample_imag[SLICE];

float twiddle_real[SLICE];
float twiddle_imag[SLICE];

void fft(float real[] , float imag[]);

main()
{
  float zero;
  float factor;
  float a;
  float b;
  float c;
  int index;
  int temp1;
  int i;
  int j;


  /* Read the input samples */

  input_dsp(input_signal, SAMPLES, 0);


  /* Initialize the magnitude vector and the Hamming window coefficients. */

  zero = 0.0;

  factor = 8.0 * atan(1.0) / (SLICE - 1);

  for (i = 0; i < SLICE; ++i) {
    mag[i] = zero;
    hamming[i] = 0.54 - 0.46 * cos(factor * i);
  }


  /* Average the power spectra of NUMAV slices of the input samples. Each
     slice is composed of SLICE samples. This is the main loop. */

  for (i = 0; i < NUMAV; ++i) {


    /* Read next slice and multiply each sample by the appropriate Hamming
       coefficient. */

    index =  i * DELTA;

    for (j = 0; j < SLICE; ++j) {
      sample_real[j] = input_signal[index + j] * hamming[j] ;
      sample_imag[j] = zero;
    }


    /* Calculate the FFT of the slice. */

    fft(sample_real, sample_imag);


    /* Update the magnitude components. */


    for (j = 0; j < SLICE; ++j) {
      mag[j] = mag[j] + (((sample_real[j] * sample_real[j]) +
			  (sample_imag[j] * sample_imag[j])) / SLICE_2);
    }
  }


  /* Average and scale the magnitude components. */

  for (i = 0; i < SLICE; i++) {
    mag[i] = 10 * log10(MAX((mag[i] / NUMAV), 1.0e-14));
  }


  /* Return the average power spectrum */

  output_dsp(input_signal, SAMPLES, 0);
  output_dsp(mag, SLICE, 0);
  output_dsp(hamming, SLICE, 0);
  output_dsp(sample_real, SLICE, 0);
  output_dsp(sample_imag, SLICE, 0);
  output_dsp(twiddle_real, SLICE, 0);
  output_dsp(twiddle_imag, SLICE, 0);
}


/* This function calculates the in-place radix 2 decimation in time
   Fast Fourier Transform of a complex sequence. */

void fft(float real[] , float imag[])
{
  float u_real;
  float u_imag;
  float temp_real;
  float temp_imag;
  float arg;

  float wrecur_real;
  float wrecur_imag;
  float wtemp_real;
  float a;
  float b;
  float c;
  float d;

  int i;
  int i1;
  int j;
  int k;
  int l;
  int le;
  int offset;
  int windex;


  /* Calculate the twiddle factors recursively */

  arg = 4.0 * atan(1.0) / 32.0;

  wrecur_real = temp_real =  cos(arg);
  wrecur_imag = temp_imag = -sin(arg);


  for (j = 0; j < 31; j++) {
    twiddle_real[j] = wrecur_real;
    twiddle_imag[j] = wrecur_imag;
    wtemp_real  = (wrecur_real * temp_real) - (wrecur_imag * temp_imag);
    wrecur_imag = (wrecur_real * temp_imag) + (wrecur_imag * temp_real);
    wrecur_real = wtemp_real;
  }


  /* start fft. */

  le = 64;
  windex = 1;

  for (l = 0; l < 6; l++) {

    le = le / 2;

    /* first iteration with no multiplies. */

    offset = 2 * le;
    i1 = 64 / offset;
    for (i = 0; i < i1; i++) {
      a = real[i*offset];
      b = imag[i*offset];
      c = real[i*offset+le];
      d = imag[i*offset+le];
      real[i*offset+le] = a - c;
      imag[i*offset+le] = b - d;
      real[i*offset] = a + c;
      imag[i*offset] = b + d;
    }


    /* remaining iterations use stored twiddle factors. */
    i1 = 1;
    for (i = 1; i < le; ++i) {
      u_real = twiddle_real[i * windex - 1];
      u_imag = twiddle_imag[i * windex - 1];

      offset = 2 * le;
      for (j = 0; j < windex; ++j) {
        temp_real = real[j*offset+1] + real[j*offset+le+1];
        temp_imag = imag[j*offset+1] + imag[j*offset+le+1];
        wrecur_real = real[j*offset+1] - real[j*offset+le+1];
        wrecur_imag = imag[j*offset+1] - imag[j*offset+le+1];
        real[j*offset+le+1] = (wrecur_real * u_real) - (wrecur_imag * u_imag);
        imag[j*offset+le+1] = (wrecur_real * u_imag) + (wrecur_imag * u_real);
        real[j*offset+1] = temp_real;
        imag[j*offset+1] = temp_imag;
      }
    }
    ++i1;   /* This kind of looks wrong, shouldn't be before '}' ? */
    windex *= 2;
  }


  /* rearrange data by bit reversing. */

  j = 0;
  for (i = 0; i < 63; i++) {
    k = 32;
    while (k <= j) {
      j = j - k;
      k = k / 2;
    }
    j += k;
    if (i < j) {
      temp_real = real[j];
      temp_imag = imag[j];
      real[j] = real[i];
      imag[j] = imag[i];
      real[i] = temp_real;
      imag[i] = temp_imag;
    }
  }
}
