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
  float temp;

  void LPC_analysis();
  void SIFT();

  /* Initialize the Hamming window */

  ct1 = 2 * PI / N;
  ct2 = 0.54;
  ct3 = 0.46;

  temp = ct2 - ct3 * cos(0);
  for (i = 1; i < N; ++i) {
    hamming[i-1] = temp;
    temp = ct2 - ct3 * cos(ct1 * i);
  }
  hamming[N-1] = temp;

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
  float E;

  float temp;
  float sum;
  float temp3;

  int m;
  int n;
  int r;


  /* Window the signal */

  temp3 = window[0]*hamming[0];
  for (m = 1; m < N; ++m) {
    signal[m-1] = temp3;
    temp3=window[m]*hamming[m];
  }
  signal[N-1] = temp3;

  /* Compute the autocorrelation vector */

  for (m = 0; m < P ; ++m) {
    r = N - m;
    sum = 0;
    temp3 = signal[0] * signal[m];                  /* R[m] = 0.0 */
    for (n = 1; n < r; ++n) {
      sum += temp3;
      temp3 = signal[n] * signal[n+m];
    }
    sum += temp3;
    autocorr[m] = sum;
  }

  /* Solve the matrix equation by the Durbin-Levinson method */

  E = autocorr[0];                       /* E=R[0] */

  alpha[1] = autocorr[1]/E;

  for (m = 2; m < P; ++m) {
    E = (1 - alpha[m-1] * alpha[m-1]) * E;

    temp3 = autocorr[m];
    temp = autocorr[m-1] * alpha[1];
    for (n = 2; n < m; ++n) {
      temp3 -= temp;
      temp = autocorr[m-n] * alpha[n];
    }
    temp3 -= temp;
    temp3 = temp3 / E;
    temp = alpha[1] - (alpha[m-1] * temp3);
    for (n = 2; n < m; ++n) {
      temp_vect[n-1] = temp;
      temp = alpha[n] - (alpha[m-n] * temp3);
    }
    temp_vect[m-1] = temp;

    temp = temp_vect[1];
    for (n = 2; n < m; ++n) {
      alpha[n-1]=temp;
      temp=temp_vect[n];
    }
    alpha[m-1] = temp;

    alpha[m] = temp3;
  }

  /* Compute the gain */
  temp = 0.0;
  temp3 = alpha[1] * autocorr[1];
  for (n = 2; n < P; ++n) {
    temp += temp3;
    temp3 = alpha[n] * autocorr[n];
  }
  temp += temp3;

  gain = sqrt((autocorr[0]) - temp);

}


/* This function implements the Simplified Inverse Filter Tracking (SIFT)
   algorithm for deciding whether a segment of speech is voiced or not,
   and for estimating the pitch of a voiced segment of speech. 
   "The SIFT Algorithm for Fundamental Frequency Estimation" by John D. Markel,
   IEEE Transactions on Audio and Electroacoustics, Vol. AU-20, No.5,
   December 1972. */

void SIFT()
{

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

  int m,ib;
  int n;


  /* The speech signal is sampled at a rate of 10 KHz to ensure that all
     significant frequency components of voiced speech are accurately 
     represented. In order to reduce the computational requirements for 
     estimating the pitch, the speech samples need to be decimated. This
     is achieved by first passing the speech samples through an anti-aliasing
     low-pass filter which effectively limits the bandwidth of the speech
     signal to 1 KHz. The filtered samples are then downsampled at a rate of
     2 KHz. */

  /* Filter the speech samples */
  /* change from here */

  temp1 = 0.164352414 * window[0];
  temp_filt[0] = temp1;
  temp3 = 0.049970733 * temp1;
  filtered[0] = temp3;
  temp2 = (0.164352414 * window[1]) + (0.835647585 * temp1);
  temp_filt[1] = temp2;
  filtered[1] = (0.049970733 * temp2) + (1.864166884 * temp3);

  temp1 = (0.164352414 * window[2]) + (0.835647585 * temp_filt[1]);
  temp2 = (0.049970733 * temp_filt[1]) + (1.864166884 * filtered[1]) +
             (-0.914137618 * filtered[0]);
  for (m = 3; m < N; ++m) {
    temp_filt[m-1] = temp1;
    filtered[m-1] = temp2;
    temp1 = (0.164352414 * window[m]) + (0.835647585 * temp_filt[m-1]);
    temp2 = (0.049970733 * temp_filt[m-1]) + (1.864166884 * filtered[m-1]) +
      (-0.914137618 * filtered[m-2]);
  }
  temp_filt[N-1] = temp1;
  filtered[N-1] = temp2;

  /* Decimate the speech samples */
  /* last change from here */

  temp1 = filtered[0];
  for (m = 1; m < D; ++m) {   /* was m < D + 1 - looks wrong */
    decimated[m-1] = temp1;
    temp1 = filtered[m*5];  /* was m*6 here - is wrong */
  }
  decimated[D-1] = temp1;


  /* The next step is to compute the coefficients of the inverse filter.
     This is done using the autocorrelation method and the coefficients can
     typically be computed using the Durbin-Levinson method. However, since
     the order of the filter is small (4), the coefficients can be computed
     in a simpler fashion. */

  /* Compute the autocorrelation vector */

  for (m = 0; m < 5 ; ++m) {
    temp1 = 0.0;

    temp2 = decimated[0] * decimated[m];
    for (n = 1; n < D - m; ++n) {
      temp1 += temp2;
      temp2 = decimated[n] * decimated[n+m];
    }
    temp1 += temp2;
    autocorr[m] = temp1;
  }

  /* Compute the inverse filter coefficients */

  temp1 = autocorr[0];
  temp2 = autocorr[1];
  temp3 = autocorr[2];
  temp4 = autocorr[3];
  temp5 = autocorr[4];

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

  temp1 = alpha14 + beta14;
  temp2 = alpha23 + beta23;
  temp3 = alpha23 - beta23;
  temp4 = alpha14 - beta14;

  coeff[0] = temp1;
  coeff[1] = temp2;
  coeff[2] = temp3;
  coeff[3] = temp4;

  /* Compute the output of the inverse filter */



  IFout[0] = decimated[0];

  IFout[1] = decimated[1] + decimated[0]  * temp1 ;

  IFout[2] = decimated[2] + decimated[1] * temp1 + decimated[0] * temp2;

  IFout[3] = decimated[3] + decimated[2] * temp1 + decimated[1] * temp2 +
                          decimated[0] * temp3;


  temp1 = decimated[4];
  for (m = 4; m < D; m++) {
    temp2 = decimated[m-1] * coeff[0]; 
    for (n = 1; n < 3; n++) {
      temp1 += temp2;
      temp2 = decimated[m-1-n] * coeff[n];   /* was + here - looks wrong */
    }
    temp1 += temp2;
    IFout[m] = temp1;
  }



  /* The inverse filter acts as a "prewhitening" filter which "flattens" the
     spectrum of the input by eliminating the effect of vocal tract resonances
     (formants), while retaining the fine structure due to the fundamental 
     pitch frequency. The pitch period estimates are obtained by a standard
     autocorrelation method. */

  
  /* Compute the autocorrelation of the inverse filter output */

  for (m = 0; m < D ; m++) {
    temp1 = 0.0;
    temp2 = IFout[0] * IFout[m];
    for (n = 1; n < D - m; n++) {
      temp1 += temp2;
      temp2 = IFout[n] * IFout[n+m];
    }
    temp1 += temp2;
    autoc[m] = temp1;
  }


  /* Normalize the autocorrelation sequence */
  temp1 = autoc[0];
  temp2 = temp1;
  for (m = 1; m < D; ++m) {
    autoc[m-1] = temp2 / temp1;
    temp2 = autoc[m];
  }
  autoc[D-1] = temp2 / temp1;

  /* The pitch period estimate corresponds to the index of the largest 
     autocorrelation element other than that at index 0 */

  ib = 1;
  temp1 = autoc[2];
  temp2 = autoc[1];
  for (m = 3; m < D; ++m) {
    if (temp1 > temp2)
      ib = m - 1;
    temp1 = autoc[m];
    temp2 = autoc[ib];
  }
  if (temp1 > temp2)
    ib = D - 1;

  /* We now have a rough estimate of the pitch period. A finer estimate is
     made through interpolation. To determine whether the segment of speech
     is voiced or not, the largest normalized autocorrelation sample is
     compared to a threshold. The pitch is returned in KHz. */


  temp3 = autoc[ib+1];
  temp2 = autoc[ib];
  temp1 = autoc[ib-1];

  temp4 = (float) ((autoc[ib] - autoc[0]) / 4);



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
