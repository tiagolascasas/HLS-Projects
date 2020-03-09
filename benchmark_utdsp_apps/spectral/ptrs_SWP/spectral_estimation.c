/* This program calculates the power spectral estimate of an input sample of
   speech using periodogram averaging. An FFT routine is used to calculate the
   different periodograms associated with the input sample.

   The program is based on the routines and algorithms found in the book
   "C Language Algorithms for Digital Signal Processing" by P.M. Embree
   and B. Kimble.

   Copyright (c) 1992 -- Mazen A.R. Saghir -- University of Toronto */

#include "traps.h"

#define		SAMPLES		124	/* Number of input speech samples. */
#define		SLICE		64	/* Number of samples per slice. */
#define		OVLAP		60	/* Number of overlapping samples. */ 
#define		NUMAV		16	/* Number of slices to average. */

#define		DELTA		((SLICE) - (OVLAP))
#define 	SLICE_2		((SLICE) * (SLICE))
#define 	MAX(X, Y)	(((X) > (Y)) ? (X) : (Y))

float input_signal[SAMPLES];
float mag[SLICE];
float hamming[SLICE];
float sample_real[SLICE];
float sample_imag[SLICE];

float twiddle_real[SLICE];
float twiddle_imag[SLICE];

main()
{
  float *mag_ptr;
  float	*ham_ptr;
  float *signal_ptr;
  float *real_ptr;
  float *imag_ptr;
  float zero;
  float factor;
  float a;
  float b;
  float c;
  int index;
  int temp1;
  int i;
  int j;

  void fft();


  /* Read the input samples */
  
  input_dsp(input_signal, SAMPLES, 0);

  /* Initialize the magnitude vector and the Hamming window coefficients. */

  zero = 0.0;

  mag_ptr = mag;
  ham_ptr = hamming;
  temp1 = 0;
  factor = 8.0 * atan(1.0) / (SLICE - 1);

  for (i = 0; i < SLICE; i++) {
    *mag_ptr++ = zero;
    *ham_ptr++ = 0.54 - 0.46 * cos(factor * temp1);
    temp1++;
  }


  /* Average the power spectra of NUMAV slices of the input samples. Each
     slice is composed of SLICE samples. This is the main loop. */

  temp1 = 0;
  for (i = 0; i < NUMAV; i++) {


    /* Read next slice and multiply each sample by the appropriate Hamming
       coefficient. */

    index =  temp1 * DELTA;
    signal_ptr = input_signal + index;
    real_ptr = sample_real;
    imag_ptr = sample_imag;
    ham_ptr = hamming;

    a = *signal_ptr++;
    b = *ham_ptr++;
    for (j = 1; j < SLICE; j++) {
      *real_ptr++ = a * b ;
      a = *signal_ptr++;
      b = *ham_ptr++;
      *imag_ptr++ = zero;  
    }
    *real_ptr++ = a * b ;
    *imag_ptr++ = zero;  


    /* Calculate the FFT of the slice. */

    fft(sample_real, sample_imag);


    /* Update the magnitude components. */

    mag_ptr = mag;
    real_ptr = sample_real;
    imag_ptr = sample_imag;

    a = *real_ptr++;
    b = *imag_ptr++;
    c = *mag_ptr;

    for (j = 1; j < SLICE; j++) {
      *mag_ptr++ = c + (((a * a) + (b * b)) / SLICE_2);
      a = *real_ptr++;
      b = *imag_ptr++;
      c = *mag_ptr;
    }
    *mag_ptr = c + (((a * a) + (b * b)) / SLICE_2);
    temp1++;
  }

  
  /* Average and scale the magnitude components. */

  mag_ptr = mag;

  for (i = 0; i < SLICE; i++) {
    a = *mag_ptr;
    a = 10 * log10(MAX((a / NUMAV), 1.0e-14));
    *mag_ptr++ = a;
  }

  
  /* Return the average power spectrum */

  output_dsp(input_signal, SAMPLES, 0);
  output_dsp(mag, SLICE, 0);		/* average power spectrum */
  output_dsp(hamming, SLICE, 0);
  output_dsp(sample_real, SLICE, 0);
  output_dsp(sample_imag, SLICE, 0);
  output_dsp(twiddle_real, SLICE, 0);
  output_dsp(twiddle_imag, SLICE, 0);
}


/* This function calculates the in-place radix 2 decimation in time
   Fast Fourier Transform of a complex sequence. */

void fft(real, imag)
float *real;
float *imag;
{

  float *xi_real;
  float *xi_imag;
  float *xip_real;
  float *xip_imag;
  float *xj_real;
  float *xj_imag;
  float *wptr_real;
  float *wptr_imag;
  
  float u_real;
  float u_imag;
  float temp_real;
  float temp_imag;
  float tm_real;
  float tm_imag;
  float arg;
  float w_real;
  float w_imag;
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

  wrecur_real = w_real =  cos(arg);
  wrecur_imag = w_imag = -sin(arg);

  xj_real = twiddle_real;
  xj_imag = twiddle_imag;

  for (j = 1; j < 32; j++) {
    *xj_real++ = wrecur_real;
    *xj_imag++ = wrecur_imag;
    wtemp_real  = (wrecur_real * w_real) - (wrecur_imag * w_imag);
    wrecur_imag = (wrecur_real * w_imag) + (wrecur_imag * w_real);
    wrecur_real = wtemp_real;
  }


  /* start fft. */

  le = 64;
  windex = 1;

  for (l = 0; l < 6; l++) {

    le = le / 2;

    /* first iteration with no multiplies. */

    xi_real = real;
    xi_imag = imag;
    xip_real = xi_real + le;
    xip_imag = xi_imag + le;
    offset = 2 * le;
    i1 = 64 / offset;
    for (i = 0; i < i1; i++) {
      a = *xi_real;
      b = *xi_imag;
      c = *xip_real;
      d = *xip_imag;
      temp_real = a + c;
      temp_imag = b + d;
      *xip_real = a - c;
      *xip_imag = b - d;
      *xi_real = temp_real;
      *xi_imag = temp_imag;
      xi_real += offset;
      xi_imag += offset;
      xip_real += offset; 
      xip_imag += offset;
    }

  
    /* remaining iterations use stored twiddle factors. */

    wptr_real = twiddle_real + (windex - 1);
    wptr_imag = twiddle_imag + (windex - 1);

    i1 = 1;
    for (i = 1; i < le; i++) {
      u_real = *wptr_real;
      u_imag = *wptr_imag;
      
/*
      *xi_real = i;
*/
      xi_real = real + i1;
      xi_imag = imag + i1;
      xip_real = xi_real + le;
      xip_imag = xi_imag + le;
      offset = 2 * le;
      for (j = 0; j < windex; j++) {
        a = *xi_real;
        b = *xi_imag;
        c = *xip_real;
        d = *xip_imag;
        temp_real = a + c;
        temp_imag = b + d;
        tm_real = a - c;
        tm_imag = b - d;
        *xip_real = (tm_real * u_real) - (tm_imag * u_imag);
        *xip_imag = (tm_real * u_imag) + (tm_imag * u_real);
        *xi_real = temp_real;
        *xi_imag = temp_imag;
        xi_real += offset;
        xi_imag += offset;
        xip_real += offset; 
        xip_imag += offset;
      }
      wptr_real += windex;
      wptr_imag += windex;
    }
    i1++;
    windex *= 2;
  }


  /* rearrange data by bit reversing. */

  j = 0;
  i1 = 0;
  for (i = 0; i < 63; i++) {
    k = 32;
    while (k <= j) {
      j = j - k;
      k = k / 2;
    }
    j += k;
    if (i1 < j) {
      xi_real = real + i1;
      xi_imag = imag + i1;
      xj_real = real + j;
      xj_imag = imag + j;
      temp_real = *xj_real;
      temp_imag = *xj_imag;
      *xj_real = *xi_real;
      *xj_imag = *xi_imag;
      *xi_real = temp_real;
      *xi_imag = temp_imag;
    }
    i1++;
  }

}
