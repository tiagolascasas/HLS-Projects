/* This program implements an adaptive differential pulse coded modulation
   encoder that adheres to the CCITT G.172 standard for 32 Kbits/s ADPCM
   speech coding.

   Copyright (C) 1992 -- Mazen A.R. Saghir -- University of Toronto */
/* Modified to use arrays - SMP */

#include "traps.h"

#define         N       256

int   input[N];                         /* 8-bit u-law encoded input signals. */
int   output[N];                        /* 4-bit ADPCM output signals. */

/* Look-up-tables */

float lut1[8] = {-0.98, 0.62, 1.38, 1.91, 2.34, 2.72, 3.12, 0.00};
float lut2[8] = {-1000000.00, 0.031, 1.05, 1.66, 2.13, 2.52, 2.91, 3.32};
float lut3[8] = {-0.75, 1.13, 2.56, 4.00, 7.00, 12.38, 22.19, 70.13};
float lut4[8] = { 0.00, 0.00, 0.00, 1.00, 1.00, 1.00, 3.00, 7.00};

/* pole coefficients */
float coeff_a[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

/* zero coefficients */
float coeff_b[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

/* inverse quantized difference signals */
float quant_diff_sig[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

/* reconstructed signals */
float recon_sig[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

/* temporary signals */
float p_sig[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

main()
{
  void call_adpcm();

  /* Get input samples */
  input_dsp(input, N, 1);

  call_adpcm();

  /* store processed results */
  output_dsp(input, N, 1);
  output_dsp(output, N, 1);

  output_dsp(lut1, 8, 0);
  output_dsp(lut2, 8, 0);
  output_dsp(lut3, 8, 0);
  output_dsp(lut4, 8, 0);
  output_dsp(coeff_a, 8, 0);
  output_dsp(coeff_b, 8, 0);
  output_dsp(quant_diff_sig, 8, 0);
  output_dsp(recon_sig, 8, 0);
  output_dsp(p_sig, 8, 0);

}


void call_adpcm()
{
  int   lin_sig;                /* 12-bit linear PCM encoded signal */
  int   adpcm_sig;              /* output ADPCM signal */
  int   tone_detect_sig;        /* tone detect signal */
  int   tone_trans_detect_sig;  /* tone transition signal */
  int    i;                     /* index */
  int    c;                     /* counter */
  int    arrayIndex;

  float quant_diff_signal;      /* current quantized difference signal */
  float p_signal;               /* current temorary signal */
  float recon_signal;           /* current reconstructed signal */
  float diff_sig;               /* difference signal */
  float diff_log_sig;           /* log 2 of the difference signal */
  float diff_log_norm_sig;      /* normalized log diff. signal */
  float quant_diff_log_norm_sig;/* inverse quant. norm. log diff. sig.*/
  float quant_diff_log_sig;     /* inverse quant. log. diff. signal */
  float estim_zero_sig;         /* output of the zeros filter */
  float estim_sig;              /* estimate signal */
  float fast_scale_fact;        /* fast scale factor */
  float slow_scale_fact;        /* slow scale factor */
  float scale_fact;             /* scale factor */
  float short_term_av;          /* short term average */
  float long_term_av;           /* long term average */
  float unlim_speed_cont_param; /* unlimited speed control parameter */
  float speed_cont_param;       /* speed control parameter */
  float temp1;                  /* temporary */
  float temp2;                  /* temporary */
  float temp3;                  /* temporary */
  float temp4;                  /* temporary */
  float temp5;                  /* temporary */
  float temp6;                  /* temporary */

  /* Initialize variables */

  fast_scale_fact = 0.0;
  slow_scale_fact = 0.0;
  short_term_av   = 0.0;
  long_term_av    = 0.0;
  unlim_speed_cont_param = 0.0;


  for (c = 0; c < N; c++) {

    /* Compute signal estimate */

    estim_zero_sig = 0.0;

    for (i = 0; i < 6 ; i++) {
#ifdef GCCmod
      if ( i-c+1 < 0 )
        arrayIndex = (((i-c+1) % 8) + 8) % 8;
      else
#endif
        arrayIndex = i-c+1;
    estim_zero_sig += quant_diff_sig[arrayIndex] * coeff_b[i];
    }
    estim_sig = estim_zero_sig;

#ifdef GCCmod
    if ( 1-c < 0)
      arrayIndex = (((1-c) % 8) + 8) % 8;
    else 
#endif
      arrayIndex = 1-c;
    estim_sig += coeff_a[0] * recon_sig[arrayIndex];

#ifdef GCCmod
    if ( 2-c < 0)
      arrayIndex = (((2-c) % 8) + 8) % 8;
    else 
#endif
      arrayIndex = 2-c;
    estim_sig += coeff_a[1] * recon_sig[arrayIndex];

    /* Limit speed control parameter */

    if  (unlim_speed_cont_param > 1.0)
      speed_cont_param = 1.0;
    else
      speed_cont_param = unlim_speed_cont_param;


    /* Compute scale factor */

    scale_fact = (speed_cont_param * fast_scale_fact) +
                 ((1.0 - speed_cont_param) * slow_scale_fact);


    /* Convert u-law PCM to linear PCM */

    if (input[c] < 128)
      lin_sig = (input[c] * 16) + 8;
    else
      lin_sig = ((input[c] - 128) * 16) + 8;

    /* Compute difference signal */

    diff_sig = lin_sig - estim_sig;

    /* Quantize difference signal */

    diff_log_sig = log10(fabs(diff_sig)) / log10(2.0);
    diff_log_norm_sig = diff_log_sig - scale_fact;

    for (i = 0; diff_log_norm_sig >= lut1[i]; i++) {
      if ( i >= 7)
        break;
    }
    adpcm_sig = i;

    if (diff_sig < 0)
      adpcm_sig += 8;


    /* Output ADPCM word */

    output[c] = adpcm_sig;

    /* Inverse quantize the ADPCM signal */

    if (adpcm_sig >= 8)
      adpcm_sig -= 8;

    quant_diff_log_norm_sig = lut2[adpcm_sig];
    quant_diff_log_sig = quant_diff_log_norm_sig + scale_fact;
    quant_diff_signal = pow(2.0, quant_diff_log_sig);

    if (diff_sig < 0)
      quant_diff_signal  = -(quant_diff_signal);

    /* Compute pole coefficient a2 */

    p_signal = quant_diff_signal + estim_zero_sig;

    if (p_signal > 0.0)
      temp1 =  1.0;
    else if (p_signal == 0.0)
      temp1 =  0.0;
    else
      temp1 = -1.0;

#ifdef GCCmod
    if ( 1-c < 0)
      arrayIndex = (((1-c) % 8) + 8) % 8;
    else 
#endif
      arrayIndex = 1-c;
    if (p_sig[arrayIndex] >= 0.0)
      temp2 =  temp1;
    else
      temp2 = -temp1;

#ifdef GCCmod
    if ( 2-c < 0)
      arrayIndex = (((2-c) % 8) + 8) % 8;
    else 
#endif
      arrayIndex = 2-c;
    if (p_sig[arrayIndex] >= 0.0)
      temp3 =  temp1;
    else
      temp3 = -temp1;

    if (fabs(coeff_a[0]) <= 0.5)
      temp4 = 4 * (coeff_a[0]) * temp2;
    else if (coeff_a[0] > 0.5)
      temp4 =  temp2;
    else
      temp4 = -temp2;

    temp6 = (0.9921875) * (coeff_a[1]) + (7.8125e-3) * (temp3 - temp4);

    if (temp6 > 0.75)
      temp6 =  0.75;
    else if (temp6 < -0.75)
      temp6 = -0.75;


    /* Compute fast scale factor */

    fast_scale_fact = ((0.96875) * scale_fact) + ((3.125e-2) * lut3[adpcm_sig]);

    if (fast_scale_fact > 10.00)
      fast_scale_fact = 10.00;
    else if (fast_scale_fact < 1.06)
      fast_scale_fact = 1.06;


    /* Compute slow scale factor */

    slow_scale_fact = ((0.984375)  * slow_scale_fact) +
                      ((1.5625e-2) * fast_scale_fact);


    /* Tone transition detection */

    tone_trans_detect_sig = 0;
    if (temp6 < -0.71875) 
      if (fabs(quant_diff_signal) > (24.0 * pow(2.0, slow_scale_fact)) )
          tone_trans_detect_sig = 1;


    /* Compute reconstructed signal */

    recon_signal = estim_sig + quant_diff_signal;


    /* Predictor adaptation */

    if (tone_trans_detect_sig == 1) {
      for (i = 0; i < 2; ++i)
      {
        coeff_a[i] = 0.0;
      }
      for (i = 0; i < 6; ++i)
      {
        coeff_b[i] = 0.0;
      }

    }
    else {

      /* Compute a1 */

      temp2 = ((0.99609375) * coeff_a[0]) + ((1.171875e-2) * temp2);

      temp5 = 0.9375 - temp6;
      if (temp2 > temp5)
        temp2 = temp5;
      else if (temp2 < -temp5)
        temp2 = -temp5;


      /* Update pole (a) coefficients */

      coeff_a[0] = temp2;
      coeff_a[1] = temp6;

      /* Update zero (b) coefficients */

      if (quant_diff_signal > 0.0)
        temp1 =  1.0;
      else if (quant_diff_signal == 0.0)
        temp1 =  0.0;
      else
        temp1 = -1.0;


      temp5 = 0.99609375;
      temp2 = 7.8125e-3;
      for (i = 0; i < 6; i++) {
#ifdef GCCmod
        if ( i-c+1 < 0 )
          arrayIndex = (((i-c+1) % 8) + 8) % 8;
        else
#endif
          arrayIndex = i-c+1;
        if (quant_diff_sig[arrayIndex] >= 0.0)
          temp4 = temp1;
        else
          temp4 = -temp1;
        coeff_b[i] = (temp5 * coeff_b[i]) + (temp2 * temp4);
      }
    }


    /* Tone detection */

    if (tone_trans_detect_sig == 1)
      tone_detect_sig = 0;
    else {
      if (temp6 < -0.71875)
        tone_detect_sig = 1;
      else
        tone_detect_sig = 0;
    }


    /* Speed control parameter adaptation */

    temp1 = lut4[adpcm_sig];

    short_term_av = (0.96875)   * short_term_av + (3.125e-2)  * temp1;
    long_term_av  = (0.9921875) * long_term_av  + (7.8125e-3) * temp1;

    if (fabs(short_term_av - long_term_av) >= (0.125 * long_term_av))
      unlim_speed_cont_param = (0.9375) * unlim_speed_cont_param + 0.125;

    if (scale_fact < 3.0)
      unlim_speed_cont_param = (0.9375) * unlim_speed_cont_param + 0.125;

    if (tone_detect_sig == 1) 
      unlim_speed_cont_param = (0.9375) * unlim_speed_cont_param + 0.125;
    else if (tone_trans_detect_sig == 1)
      unlim_speed_cont_param = 1.0;
    else
      unlim_speed_cont_param = (0.9375) * unlim_speed_cont_param;


    /* Update delay line values and pointers */

#ifdef GCCmod
        if ( -c < 0 )
          arrayIndex = ((-c % 8) + 8) % 8;
        else
#endif
          arrayIndex = -c;
    quant_diff_sig[arrayIndex] = quant_diff_signal;
    p_sig[arrayIndex] = p_signal;
    recon_sig[arrayIndex] = recon_signal;

  }
}
