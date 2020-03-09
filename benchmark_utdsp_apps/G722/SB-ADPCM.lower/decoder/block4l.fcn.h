
/*
   G.722 Lower Sub-band Adpcm - Block 4L
   ==========================
   This program implements the "Adaptive predictor and 
   reconstructed signal calculator"
   in the lower sub-band as described on p.313.
*/

int block4l(int DLT, int RS, int *SL)
  {
  int WD1, WD2, WD3, WD4, WD5;
  int *upperptr, *lowerptr;
  int SG0, SG1, SG2, SGi;
  int *DLTptr, DLTval;
  int *BLptr,  BLval;
  int *BPLptr;
  int SZLtmp;
  int SPL;
  int i;

  /* RESET handling */

  if(RS == 1)
    {
    BLptr = B4L_BLi;
    BPLptr = B4L_BPLi;
    DLTptr = B4L_DLTi;

    for(i=0; i<N; i++)
      {
      *BLptr++ = 0;
      *BPLptr++ = 0;
      *DLTptr++ = 0;
      }
    B4L_PLT  = 0; B4L_PLT1 = 0; B4L_PLT2 = 0;
    B4L_RLT  = 0; B4L_RLT1 = 0; B4L_RLT2 = 0;
    B4L_APL2 = 0; B4L_AL2  = 0;
    B4L_APL1 = 0; B4L_AL1  = 0;
    return RESET;
    }
  else
    {
    BLptr = B4L_BLi;
    BPLptr = B4L_BPLi;

    for(i=0; i<N; i++) *BLptr++ = *BPLptr++;

    lowerptr = B4L_DLTi + (N-1);
    upperptr = lowerptr--;

    for(i=0; i<(N-1); i++) *upperptr-- = *lowerptr--;

    B4L_PLT2 = B4L_PLT1; B4L_PLT1 = B4L_PLT;
    B4L_RLT2 = B4L_RLT1; B4L_RLT1 = B4L_RLT;
    B4L_AL2  = B4L_APL2; B4L_AL1  = B4L_APL1;
    }

  /* PARREC (p314) */

  B4L_PLT = DLT + B4L_SZL;

  /* RECONS (p314) */

  B4L_RLT = *SL + DLT;

  /* UPZERO (p314) */

  if(DLT == 0) WD1 = 0;
  else         WD1 = 128;
  SG0 = DLT >> StdSHIFT;

  DLTptr = B4L_DLTi;
  DLTval = *DLTptr++;
  BLptr  = B4L_BLi;
  BLval  = *BLptr++;
  BPLptr = B4L_BPLi;

  for(i=0; i<5; i++)
    {
    SGi = DLTval >> StdSHIFT;

    if(SG0 == SGi) WD2 =  WD1;
    else           WD2 = -WD1;

    WD3 = (BLval * 32640) >> StdSHIFT;

    *BPLptr++ = WD2 + WD3;
    DLTval = *DLTptr++;
    BLval  = *BLptr++;
    }
  SGi = DLTval >> StdSHIFT;

  if(SG0 == SGi) WD2 =  WD1;
  else           WD2 = -WD1;

  WD3 = (BLval * 32640) >> StdSHIFT;

  *BPLptr = WD2 + WD3;

  /* UPPOL2 (p315) */

  SG0 = B4L_PLT  >> StdSHIFT;
  SG1 = B4L_PLT1 >> StdSHIFT;
  SG2 = B4L_PLT2 >> StdSHIFT;

  WD1 = B4L_AL1 << 2;

  if(SG0 == SG2) WD3 =  128;
  else           WD3 = -128;

  WD4  = WD2 + WD3;
  WD5  = (B4L_AL2 * 32512) >> StdSHIFT;
  B4L_APL2 = WD4 + WD5;

  if(B4L_APL2 > 12288)       B4L_APL2 =  12288;
  else if(B4L_APL2 < -12288) B4L_APL2 = -12288;

  /* UPPOL1 (p315) */

  if(SG0 == SG1) WD1 =  192;
  else           WD1 = -192;

  WD2  = (B4L_AL1 * 32640) >> StdSHIFT;
  B4L_APL1 = WD1 + WD2;

  WD3 = 15360 - B4L_APL2;

  if(B4L_APL1 > WD3)       B4L_APL1 =  WD3;
  else if(B4L_APL1 < -WD3) B4L_APL1 = -WD3;

  /* FILTEZ (p316) */

  BLptr  = B4L_BLi+(N-1);
  DLTptr = B4L_DLTi+(N-1);
  SZLtmp = 0;
  BLval  = *BLptr--;
  DLTval = *DLTptr--;

  for(i=0; i< N-1; i++)
    {
    SZLtmp += (DLTval * BLval) >> (StdSHIFT - 1);
    BLval  = *BLptr--;
    DLTval = *DLTptr--;
    }
  SZLtmp += (DLTval * BLval) >> (StdSHIFT - 1);
  B4L_SZL = SZLtmp;

  /* FILTEP (p316) */

  WD1 = (B4L_RLT1 * B4L_AL1) >> (StdSHIFT - 1);
  WD2 = (B4L_RLT2 * B4L_AL2) >> (StdSHIFT - 1);

  SPL = WD1 + WD2;

  /* PREDIC (p316) */

  *SL = SPL + B4L_SZL;

  return OK;
  }
