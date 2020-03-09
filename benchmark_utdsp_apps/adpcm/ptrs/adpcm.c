/* This program implements an adaptive differential pulse coded modulation
   encoder that adheres to the CCITT G.172 standard for 32 Kbits/s ADPCM
   speech coding.

   Copyright (C) 1992 -- Mazen A.R. Saghir -- University of Toronto */

#include <stdio.h>
#include "traps.h"

#define 	N	256

int   input[N];				/* 8-bit u-law encoded input signals. */
int   output[N];			/* 4-bit ADPCM output signals. */

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
  int *input_sig;		/* pointer to input signal */
  int *output_sig;		/* pointer to output signal */

  float *p1;			/* temporary pointer */
  float *p2;			/* temporary pointer */
  float *p3;			/* temporary pointer */
  float *qds;			/* ptr to inverse quantized difference signal */
  float *qds_old;		/* ptr to old inverse quant. diff. signal */
  float *rs;			/* ptr to reconstructed signal */
  float *rs_old;		/* ptr to old reconstructed signal */
  float *ps;			/* ptr to temporary signal */
  float *ps_old;		/* ptr to old temporary signal */

  int   lin_sig;		/* 12-bit linear PCM encoded signal */
  int   adpcm_sig;		/* output ADPCM signal */
  int   tone_detect_sig;	/* tone detect signal */
  int   tone_trans_detect_sig;	/* tone transition signal */
  int    i;			/* index */
  int    c;			/* counter */

  float quant_diff_signal; 	/* current quantized difference signal */
  float p_signal;		/* current temorary signal */
  float recon_signal;		/* current reconstructed signal */
  float diff_sig;		/* difference signal */
  float diff_log_sig;		/* log 2 of the difference signal */
  float diff_log_norm_sig;	/* normalized log diff. signal */
  float quant_diff_log_norm_sig;/* inverse quant. norm. log diff. sig.*/
  float quant_diff_log_sig;	/* inverse quant. log. diff. signal */
  float estim_zero_sig;		/* output of the zeros filter */
  float estim_sig;		/* estimate signal */
  float fast_scale_fact;	/* fast scale factor */
  float slow_scale_fact;	/* slow scale factor */
  float scale_fact;		/* scale factor */
  float short_term_av;		/* short term average */
  float long_term_av;		/* long term average */
  float unlim_speed_cont_param;	/* unlimited speed control parameter */
  float speed_cont_param;	/* speed control parameter */
  float temp1;			/* temporary */
  float temp2;			/* temporary */
  float temp3;			/* temporary */
  float temp4;			/* temporary */
  float temp5;			/* temporary */
  float temp6;			/* temporary */
  float temp7;			/* temporary */
  float temp8;			/* temporary */

  /* Initialize variables */

  qds = quant_diff_sig;
  qds_old = qds + 1;
  rs = recon_sig;
  rs_old = rs + 1;
  ps = p_sig; 
  ps_old = ps + 1;
  fast_scale_fact = 0.0;
  slow_scale_fact = 0.0;
  short_term_av   = 0.0;
  long_term_av    = 0.0;
  unlim_speed_cont_param = 0.0;

  input_sig = input;
  output_sig = output;

  for (c = 0; c < N; c++) {

    /* Compute signal estimate */

    estim_zero_sig = 0.0;
    p1 = qds_old;
    p2 = coeff_b;

    for (i = 0; i < 6 ; i++) {
      temp1 = *p1++;
#ifdef GCCmod
      if(p1 > &quant_diff_sig[7])
        p1 = &quant_diff_sig[0];
#endif

      temp2 = *p2++;
#ifdef GCCmod
      if(p2 > &coeff_b[7])
        p2 = &coeff_b[0];
#endif

      estim_zero_sig += temp1 * temp2;
    }

    estim_sig = estim_zero_sig;
    p1 = coeff_a;
    p2 = rs_old;

    temp1 = *p1++;
#ifdef GCCmod
    if(p1 > &coeff_a[7])
      p1 = &coeff_a[0];
#endif

    temp2 = *p2++;
#ifdef GCCmod
    if(p2 > &recon_sig[7])
      p2 = &recon_sig[0];
#endif

    estim_sig += temp1 * temp2;
    temp1 = *p1;
    temp2 = *p2;
    estim_sig += temp1 * temp2;

    /* Limit speed control parameter */

    if  (unlim_speed_cont_param > 1.0)
      speed_cont_param = 1.0;
    else
      speed_cont_param = unlim_speed_cont_param;

  
    /* Compute scale factor */

    scale_fact = (speed_cont_param * fast_scale_fact) +
                 ((1.0 - speed_cont_param) * slow_scale_fact);


    /* Convert u-law PCM to linear PCM */

    if (*input_sig < 128)
      lin_sig = (*input_sig * 16) + 8;
    else
      lin_sig = ((*input_sig - 128) * 16) + 8;

    /* Compute difference signal */

    diff_sig = lin_sig - estim_sig;

    /* Quantize difference signal */

    diff_log_sig = log10(fabs(diff_sig)) / log10(2.0);
    diff_log_norm_sig = diff_log_sig - scale_fact;

    for (i = 0; diff_log_norm_sig >= *(lut1 + i); i++) {
      if (i >= 7)
        break;
    }
    adpcm_sig = i;

    if (diff_sig < 0)
      adpcm_sig += 8;


    /* Output ADPCM word */

    *output_sig++ = adpcm_sig;
#ifdef GCCmod
    if(output_sig > &output[N-1])
      output_sig = &output[0];
#endif

    /* Inverse quantize the ADPCM signal */

    if (adpcm_sig >= 8)
      adpcm_sig -= 8;

    quant_diff_log_norm_sig = *(lut2 + adpcm_sig);
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

    p1 = ps_old;
    temp5 = *p1++;
#ifdef GCCmod
    if(p1 > &p_sig[7])
      p1 = &p_sig[0];
#endif

    if (temp5 >= 0.0)
      temp2 =  temp1;
    else
      temp2 = -temp1;

    temp5 = *p1;
    if (temp5 >= 0.0)
      temp3 =  temp1;
    else
      temp3 = -temp1;

    p1 = coeff_a;
    temp5 = *p1++;
#ifdef GCCmod
    if(p1 > &coeff_a[7])
      p1 = &coeff_a[0];
#endif
 
    if (fabs(temp5) <= 0.5)
      temp4 = 4 * (temp5) * temp2;
    else if (temp5 > 0.5)
      temp4 =  temp2;
    else
      temp4 = -temp2;

    temp5 = *p1;

    temp6 = (0.9921875) * (temp5) + (7.8125e-3) * (temp3 - temp4);

    if (temp6 > 0.75)
      temp6 =  0.75;
    else if (temp6 < -0.75)
      temp6 = -0.75;


    /* Compute fast scale factor */

    temp7 = *(lut3 + adpcm_sig);

    fast_scale_fact = ((0.96875) * scale_fact) + ((3.125e-2) * temp7);

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
      temp1 = 0.0;

      p1 = coeff_a;
      for (i = 0; i < 2; i++)
        {
        *p1++ = temp1;
#ifdef GCCmod
      if(p1 > &coeff_a[7])
        p1 = &coeff_a[0];
#endif
        }

      p2 = coeff_b;
      for (i = 0; i < 6; i++)
        {
        *p2++ = temp1;
#ifdef GCCmod
      if(p2 > &coeff_b[7])
        p2 = &coeff_b[0];
#endif
        }

    }
    else {

      /* Compute a1 */

      temp7 = ((0.99609375) * (*coeff_a)) + ((1.171875e-2) * temp2);

      temp8 = 0.9375 - temp6;
      if (temp7 > temp8)
        temp7 = temp8;
      else if (temp7 < -temp8)
        temp7 = -temp8;


      /* Update pole (a) coefficients */

      p1 = coeff_a;
      *p1++ = temp7;
#ifdef GCCmod
      if(p1 > &coeff_a[7])
        p1 = &coeff_a[0];
#endif

      *p1 = temp6;

      /* Update zero (b) coefficients */

      if (quant_diff_signal > 0.0)
        temp1 =  1.0;
      else if (quant_diff_signal == 0.0)
        temp1 =  0.0;
      else
        temp1 = -1.0;

      p1 = qds_old;
      p2 = coeff_b;
      p3 = coeff_b;

      temp5 = 0.99609375;
      temp7 = 7.8125e-3;
      for (i = 0; i < 6; i++) {
        temp2 = *p1++;
#ifdef GCCmod
        if(p1 > &quant_diff_sig[7])
          p1 = &quant_diff_sig[0];
#endif

        temp3 = *p2++;
#ifdef GCCmod
        if(p2 > &coeff_b[7])
          p2 = &coeff_b[0];
#endif

        if (temp2 >= 0.0)
          temp4 = temp1;
        else
          temp4 = -temp1;
        *p3++ = (temp5 * temp3) + (temp7 * temp4);
#ifdef GCCmod
      if(p3 > &coeff_b[7])
        p3 = &coeff_b[0];
#endif

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

    temp1 = *(lut4 + adpcm_sig);

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

    *qds = quant_diff_signal;
    *ps = p_signal;
    *rs = recon_signal;

    input_sig++;
#ifdef GCCmod
    if(input_sig > &input[N-1])
      input_sig = &input[0];
#endif

    qds--;
#ifdef GCCmod
    if(qds < &quant_diff_sig[0])
      qds = &quant_diff_sig[7];
#endif

    qds_old--;
#ifdef GCCmod
    if(qds_old < &quant_diff_sig[0])
      qds_old = &quant_diff_sig[7];
#endif

    ps--;
#ifdef GCCmod
    if(ps < &p_sig[0])
      ps = &p_sig[7];
#endif

    ps_old--;
#ifdef GCCmod
    if(ps_old < &p_sig[0])
      ps_old = &p_sig[7];
#endif

    rs-- ;
#ifdef GCCmod
    if(rs < &recon_sig[0])
      rs = &recon_sig[7];
#endif
 
    rs_old--;
#ifdef GCCmod
    if(rs_old < &recon_sig[0])
      rs_old = &recon_sig[7];
#endif
  }
}  
