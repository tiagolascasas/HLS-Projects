
/*
   G.722 Lower Sub-band Adpcm - Block 3L
   ==========================
   This program implements the "Quantizer scale factor adaptation"
   in the lower sub-band as described on p.311.
*/


int block3l(int IL, int RS, int *DETL)
  {
  int RIL, IL4, WD, WD1, WD2, WD3, NBPL;

  /* RESET handling */

  if(RS == 1)
    {
    B3L_NBL  = 0;
    B3L_NBPL = 0;
    *DETL    = 32;
    B3L_DEPL = 32;
    return RESET;
    }
  else
    {
    B3L_NBL = B3L_NBPL;
    *DETL   = B3L_DEPL;
    }

  /* LOGSCL (p312) */

  RIL = (IL >> 2) & 0xf;  /* extract the least sig. 4 bits */

  IL4      = TBL17_IL4[RIL];
  WD       = (B3L_NBL * 32512) >> 15;
  NBPL     = WD + TBL14_WL[IL4];
  B3L_NBPL = NBPL;

  if(NBPL < 0) NBPL = 0;
  else if (NBPL > 18432) NBPL = 18432;

  /* SCALEL (p312) */

  WD1 = (NBPL >> 6) & 31;
  WD2 = NBPL >> 11;
  if(WD2 == 9)
    WD3 = TBL15_ILB[WD1] << 1;
  else
    WD3 = TBL15_ILB[WD1] >> (8-WD2);

  B3L_DEPL = WD3 << 2;

  return OK;

  }
