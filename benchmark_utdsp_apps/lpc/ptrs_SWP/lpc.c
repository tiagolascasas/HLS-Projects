/* This program implements a linear predictive coding (LPC) encoder.
   The general structure of the encoder is as follows:

             +---------+      +--------------+ a's +---------+
             |         |      |              |---->|         |
  s(n) ----->| Window  |--+-->| LPC Analysis | G   |  Coder  |
             |         |  |   |              |---->|         |
             +---------+  |   +--------------+     |         |
                          |                        |         |--->
                          |   +--------------+ P   |         |
                          |   |              |---->|         |
                          +-->| Pitch Estim. |v/u  |         |
                              |              |---->|         |
                              +--------------+     +---------+



*/

#include "traps.h"

#define	N	320			/* Speech samples' window size */
#define D	64			/* Decimated samples' window size */
#define P	16			/* Order of predictor filter + 1 */
#define IF	4			/* Order of the inverse filter */

#define PI	3.141592654		/* The value of pi */
#define TRUE	1
#define FALSE	0

#define max(x,y)        (((x)>(y))?(x):(y))


float window[N];			/* Buffer for storing speech samples */
float hamming[N];			/* Hamming Window */
float filtered[N]; 			/* low pass filtered speech */
float signal[N];			/* Stores windowed speech samples */
float decimated[D];			/* decimated filtered speech */
float IFout[D];				/* Inverse filter output */
float autoc[D];				/* Autocorrelation of IFout */
float alpha[P];				/* Predictor coefficients */
float autocorr[P];			/* Stores autocorrelation vector */
float temp_vect[P];			/* Temporary vector */
float coeff[IF];			/* Inverse filter coefficients */
float temp_filt[N];			/* Temporary filtered signals. */

float gain;				/* Gain of the speech signal */
float pitch;				/* Pitch of the speech signal */
int voiced;				/* Flag for voiced or unvoiced speech */

main()
{
  int i;
  int j;
  float ct1;
  float ct2;
  float ct3;
  float *h;
  float *ptr1;
  float *ptr2;

  void LPC_analysis();
  void SIFT();

  /* Initialize the Hamming window */

  ct1 = 2 * PI / N;
  ct2 = 0.54;
  ct3 = 0.46;
  h = hamming;
  j = 0;
  for (i = 0; i < N; i++) {
    *h++ = ct2 - ct3 * cos(ct1 * j);
    j++;
  }

  /* Get new speech sample */

  input_dsp(window, N, 0);

  /* Call LPC analysis routine */

  LPC_analysis();

  /* Call pitch estimation routine */

  SIFT();

  /* Send results to coder */

  output_dsp(alpha, P, 0);
  output_dsp(&gain, 1, 0);
  output_dsp(&pitch,1, 0);
  output_dsp(&voiced, 1, 1);

}

/* This function computes the linear prediction coefficients using the 
   autocorrelation method */

void LPC_analysis()
{
  float *a;
  float *b;
  float *c;
  float *d;
  float *e;
  float *f;
  float *g;
  float *i;
  float *j;
  float *k;
  float E;

  float temp_gain;
  float sum;
  float temp1;
  float temp2;
  float temp3;
 
  int x;
  int m;
  int n;
  int r;


  /* Window the signal */

  k = signal;			/* signal[m] */
  i = window;			/* window[m] */
  j = hamming;			/* hamming[m] */
  for (m = 0; m < N; m++) {
    temp1 = *i++;
    temp2 = *j++;
    *k++ = temp1 * temp2 ;	/* signal[m]=window[m]*hamming[m] */
  }

  /* Compute the autocorrelation vector */

  i = autocorr;			/* R[m] */
  x = 0;
  for (m = 0; m < P ; m++) {
    r = N - x;
    j = signal;			/* signal[n] */
    k = j + x;			/* signal[n+m] */
    sum = 0.0;			/* R[m] = 0.0 */
    for (n = 0; n < r; n++) {
      temp1 = *j++;
      temp2 = *k++;
      sum += temp1 * temp2;	/* R[m] = R[m] + signal[n] * signal[n+m] */
    }
    *i++ = sum;
    x++;
  }

  /* Solve the matrix equation by the Durbin-Levinson method */

  i = autocorr;			/* R[0] */
  E = *i++;			/* E=R[0] */

  j = alpha;			/* alpha[1] */
  j++;
  *j = (*i++) / E;		/* alpha[1]=R[1]/E */

  a = j;			/* alpha[m-1] */
  j++;				/* alpha[2] */
  b = j;			/* alpha[m] */
  c = i;			/* R[m] */
  x = 2;
  for (m = 2; m < P; m++) {
    temp1 = *a++;
    E = (1 - temp1*temp1) * E;	/* E = (1-alpha[m-1]*alpha[m-1])*E */

    d = autocorr;		/* R[m-n] */
    d += x - 1;
    e = alpha;			/* alpha[n] */
    e++;
    temp3 = *c++;		/* alpha[m] = R[m] */
    r = x;
    for (n = 1; n < r; n++) {
      temp1 = *d--;
      temp2 = *e++;
      temp3 -= temp1 * temp2;	/* alpha[m]=alpha[m]-R[m-n]*alpha[n] */
    }

    e = alpha;			/* alpha[n] */
    e++;
    f = temp_vect;		/* temp_vect[n] */
    f++;
    g = alpha;			/* alpha[m-n] */
    g += x - 1;
    temp3 = temp3 / E;
    for (n = 1; n < r; n++) {
      temp1 = *e++;
      temp2 = *g--;
      *f++ = temp1 - (temp2 * temp3);
    }

    e = alpha;			/* alpha[n] */
    e++;
    f = temp_vect;		/* temp_vect[n] */
    f++;
    for (n = 1; n < r; n++) {
      temp1 = *f++;
      *e++ = temp1;		/* alpha[n]=temp[n] */
    }

    *b++ = temp3;
    x++;
  }

  /* Compute the gain */

  temp_gain = 0.0;
  a = alpha;			/* alpha[n] */
  a++;
  b = autocorr;			/* R[n] */
  b++;
  for (n = 1; n < P; n++) {
    temp1 = *a++;
    temp2 = *b++;
    temp_gain += temp1 * temp2; 
  }

  gain = sqrt((*autocorr) - temp_gain);
    
}


/* This function implements the Simplified Inverse Filter Tracking (SIFT)
   algorithm for deciding whether a segment of speech is voiced or not,
   and for estimating the pitch of a voiced segment of speech. 
   "The SIFT Algorithm for Fundamental Frequency Estimation" by John D. Markel,
   IEEE Transactions on Audio and Electroacoustics, Vol. AU-20, No.5,
   December 1972. */

void SIFT()
{
  float a1 =  0.164352414;		/* Low pass filter coefficient */
  float a2 =  0.835647585;		/* Low pass filter coefficient */
  float a3 =  0.049970733;		/* Low pass filter coefficient */
  float a4 =  1.864166884;		/* Low pass filter coefficient */
  float a5 = -0.914137618;		/* Low pass filter coefficient */

  float *a;
  float *b;
  float *c;
  float *d;
  float *e;
  float *f;
  float *g;
  float *h;
  float *i;
  float *j;

  float denom;
  float alpha14;
  float alpha23;
  float beta14;
  float beta23;
  float est1;
  float est2;
  float est3;
  float maxVal;

  float temp1;
  float temp2;
  float temp3;
  float temp4;
  float temp5;
  float temp6;
  float temp7;

  int m;
  int n;
  int x;
  int y;
  int z;


  /* The speech signal is sampled at a rate of 10 KHz to ensure that all
     significant frequency components of voiced speech are accurately 
     represented. In order to reduce the computational requirements for 
     estimating the pitch, the speech samples need to be decimated. This
     is achieved by first passing the speech samples through an anti-aliasing
     low-pass filter which effectively limits the bandwidth of the speech
     signal to 1 KHz. The filtered samples are then downsampled at a rate of
     2 KHz. */

  /* Filter the speech samples */

  a = window; 
  b = temp_filt;
  c = temp_filt;
  d = filtered;
  e = filtered;
  f = filtered;

  temp1 = *a++;
  temp5 = a1 * temp1;
  *b++ = temp5;
  *d++ = a3 * temp5;

  temp1 = *a++;
  temp2 = *c++;
  temp3 = *e++;
  temp5 = (a1 * temp1) + (a2 * temp2);
  *b++ = temp5;
  *d++ = (a3 * temp5) + (a4 * temp3);

  for (m = 2; m < N; m++) {
    temp1 = *a++;
    temp2 = *c++;
    temp3 = *e++;
    temp4 = *f++;
    temp5 = (a1 * temp1) + (a2 * temp2);
    *b++ = temp5;
    *d++ = (a3 * temp5) + (a4 * temp3) + (a5 * temp4);
  }

  /* Decimate the speech samples */

  a = decimated;
  b = filtered;
  for (m = 0; m < D; m++) {
    temp1 = *b;
    *a++ = temp1;
    b += 5;
  }

  /* The next step is to compute the coefficients of the inverse filter.
     This is done using the autocorrelation method and the coefficients can
     typically be computed using the Durbin-Levinson method. However, since 
     the order of the filter is small (4), the coefficients can be computed
     in a simpler fashion. */

  /* Compute the autocorrelation vector */

  a = autocorr;			/* R[m] */
  x = 0;
  for (m = 0; m < 5 ; m++) {
    temp1 = 0.0;		

    b = decimated;		/* signal[n] */
    c = b + x;			/* signal[n+m] */
    y = D - x;
    for (n = 0; n < y; n++) {
      temp2 = *b++;
      temp3 = *c++;
      temp1 += temp2 * temp3;
    }
    *a++ = temp1;
    x++;
  }

  /* Compute the inverse filter coefficients */

  a = autocorr;
  temp1 = *a++;
  temp2 = *a++;
  temp3 = *a++;
  temp4 = *a++;
  temp5 = *a;
  
  denom  =(((temp2 + temp3) * (temp2 + temp3)) -
           ((temp1 + temp4) * (temp1 + temp2))) * 2.0;

  alpha14=(((temp2 + temp5) * (temp1 + temp2)) -
           ((temp2 + temp3) * (temp3 + temp4))) / denom;

  alpha23=(((temp1 + temp4) * (temp3 + temp4)) -
           ((temp2 + temp5) * (temp2 + temp3))) / denom;

  denom  =(((temp2 - temp3) * (temp2 - temp3)) -
           ((temp1 - temp4) * (temp1 - temp2))) * 2.0;

  beta14 =(((temp2 - temp5) * (temp1 - temp2)) -
           ((temp2 - temp3) * (temp3 - temp4))) / denom;

  beta23 =(((temp1 - temp4) * (temp3 - temp4)) -
           ((temp2 - temp5) * (temp2 - temp3))) / denom;

  c = coeff; 
  *c++ = alpha14 + beta14;
  *c++ = alpha23 + beta23;
  *c++ = alpha23 - beta23;
  *c   = alpha14 - beta14;


  /* Compute the output of the inverse filter */

  a = IFout;
  b = decimated;
  c = decimated;
  d = coeff;
  e = decimated;
  f = coeff;
  g = decimated;
  h = coeff;

  temp1 = *b++;
  *a++ = temp1;

  temp1 = *b++;
  temp2 = *c++;
  temp3 = *d++;

  *a++ = temp1 + temp2 * temp3;

  temp1 = *b++;
  temp2 = *c++;
  temp3 = *f++;
  temp4 = *d++;
  temp5 = *e++;

  *a++ = temp1 + temp2 * temp3 + temp4 * temp5;

  temp1 = *b++;
  temp2 = *c++;
  temp3 = *h++;
  temp4 = *e++;
  temp5 = *f++;
  temp6 = *d++;
  temp7 = *g++;

  *a++ = temp1 + temp2 * temp3 + temp4 * temp5 + temp6 * temp7;

  temp1 = *b++;
  for (m = 4; m < D; m++) {
    b = c++;
    d = coeff;
    for (n = 0; n < 3; n++) {
      temp2 = *b--;
      temp3 = *d++;
      temp1 += temp2 * temp3;
    }
    *a++ = temp1;
  }

  /* The inverse filter acts as a "prewhitening" filter which "flattens" the
     spectrum of the input by eliminating the effect of vocal tract resonances
     (formants), while retaining the fine structure due to the fundamental 
     pitch frequency. The pitch period estimates are obtained by a standard
     autocorrelation method. */

  
  /* Compute the autocorrelation of the inverse filter output */

  a = autoc;			/* R[m] */
  x = 0;
  for (m = 0; m < D ; m++) {
    temp1 = 0.0;
    b = IFout;			/* IFout[n] */
    c = b + x;			/* IFout[n+m] */
    for (n = 0; n < D - x; n++) {
      temp2 = *b++;
      temp3 = *c++;
      temp1 += temp2 * temp3;
    }
    *a++ = temp1;
    ++x;
  }

  /* Normalize the autocorrelation sequence */

  a = autoc;
  temp1 = *a;
  for (m = 0; m < D; m++) {
    temp2 = *a;
    *a++ = temp2 / temp1;
  }

  /* The pitch period estimate corresponds to the index of the largest 
     autocorrelation element other than that at index 0 */

  b = autoc;
  b++;
  c = b;
  for (m = 1; m < D; m++) {
    c++;
    if (*c > *b)
      b = c;
  }

  /* We now have a rough estimate of the pitch period. A finer estimate is 
     made through interpolation. To determine whether the segment of speech
     is voiced or not, the largest normalized autocorrelation sample is 
     compared to a threshold. The pitch is returned in KHz. */

  b++;

  temp3 = *b--;
  temp2 = *b--;
  temp1 = *b++;

  c = autoc;
  temp4 = (float) ((*b - *c) / 4);

  est1 = 0.322745 * temp1 + 0.878039 * temp2 - 0.158147 * temp3;
  est2 = 0.322745 * temp3 + 0.878039 * temp2 - 0.158147 * temp1;

  if (est1 > est2) {
    est3 = 0.637643 * temp1 + 0.636110 * temp2 - 0.212208 * temp3;
    maxVal = max(est1, max(est3, temp2));

    if (maxVal == est1) {
      pitch = (temp4 - 0.25) / 2.0;
      if (est1 >= 0.4)
        voiced = TRUE;
      else
        voiced = FALSE;
    }
    else if (maxVal == est3) {
      pitch = (temp4 - 0.50) / 2.0;
      if (est3 >= 0.4)
        voiced = TRUE;
      else
        voiced = FALSE;
    }
    else {
      pitch = temp4 / 2.0;
      if (temp2 >= 0.4)
        voiced = TRUE;
      else
        voiced = FALSE;
    }
  }
  else {
    est3 = 0.637643 * temp3 + 0.636110 * temp2 - 0.212208 * temp1;
    maxVal = max(est2, max(est3, temp2));

    if (maxVal == est2) {
      pitch = (temp4 + 0.25) / 2.0;
      if (est2 >= 0.4)
        voiced = TRUE;
      else
        voiced = FALSE;
    }
    else if (maxVal == est3) {
      pitch = (temp4 + 0.50) / 2.0;
      if (est3 >= 0.4)
        voiced = TRUE;
      else
        voiced = FALSE;
    }
    else {
      pitch = temp4 / 2.0;
      if (temp2 >= 0.4)
        voiced = TRUE;
      else
        voiced = FALSE;
    }
  }
}
