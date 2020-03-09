#ifndef TrapsH
#define TrapsH
#include "traps.h"
#endif

#ifndef RESET
#define RESET -1
#endif

#ifndef OK
#define OK 1
#endif

#ifndef StdSHIFT
#define StdSHIFT 15
#endif

#define b4hN 6

/* static variables */
int B4H_PH;
int B4H_PH1;
int B4H_PH2;
int B4H_YH;
int B4H_RH1;
int B4H_RH2;
int B4H_APH1;
int B4H_APH2;
int B4H_AH1;
int B4H_AH2;
int B4H_SZH;
int B4H_DHi[b4hN]  = {0,0,0,0,0,0};
int B4H_BPHi[b4hN] = {0,0,0,0,0,0};
int B4H_BHi[b4hN]  = {0,0,0,0,0,0};

/* function prototype */
int block4h(int DH, int RS, int *SH);

int block4h(int DH, int RS, int *SH)
  {
  int WD1, WD2, WD3, WD4, WD5;
  int *upperptr, *lowerptr;
  int SG0, SG1, SG2, SGi;
  int *DHptr, DHval;
  int *BHptr,  BHval;
  int *BPHptr;
  int SZHtmp;
  int SPH;
  int i;

  /* RESET handling */

  if(RS == 1)
    {
    BHptr = B4H_BHi;
    BPHptr = B4H_BPHi;
    DHptr = B4H_DHi;

    for(i=0; i<b4hN; i++)
      {
      *BHptr++ = 0;
      *BPHptr++ = 0;
      *DHptr++ = 0;
      }
    B4H_PH  = 0; B4H_PH1 = 0; B4H_PH2 = 0;
    B4H_YH  = 0; B4H_RH1 = 0; B4H_RH2 = 0;
    B4H_APH2 = 0; B4H_AH2  = 0;
    B4H_APH1 = 0; B4H_AH1  = 0;
    return RESET;
    }
  else
    {
    BHptr = B4H_BHi;
    BPHptr = B4H_BPHi;

    for(i=0; i<b4hN; i++) *BHptr++ = *BPHptr++;

    lowerptr = B4H_DHi + (b4hN-1);
    upperptr = lowerptr--;

    for(i=0; i<(b4hN-1); i++) *upperptr-- = *lowerptr--;

    B4H_PH2 = B4H_PH1; B4H_PH1 = B4H_PH;
    B4H_RH2 = B4H_RH1; B4H_RH1 = B4H_YH;
    B4H_AH2  = B4H_APH2; B4H_AH1  = B4H_APH1;
    }

  /* PARREC (p314) */

  B4H_PH = DH + B4H_SZH;

  /* RECONS (p314) */

  B4H_YH = *SH + DH;

  /* UPZERO (p314) */

  if(DH == 0) WD1 = 0;
  else        WD1 = 128;
  SG0 = DH >> StdSHIFT;

  DHptr = B4H_DHi;
  DHval = *DHptr++;
  BHptr  = B4H_BHi;
  BHval  = *BHptr++;
  BPHptr = B4H_BPHi;

  for(i=0; i<5; i++)
    {
    SGi = DHval >> StdSHIFT;

    if(SG0 == SGi) WD2 =  WD1;
    else           WD2 = -WD1;

    WD3 = (BHval * 32640) >> StdSHIFT;

    *BPHptr++ = WD2 + WD3;
    DHval = *DHptr++;
    BHval  = *BHptr++;
    }
  SGi = DHval >> StdSHIFT;

  if(SG0 == SGi) WD2 =  WD1;
  else           WD2 = -WD1;

  WD3 = (BHval * 32640) >> StdSHIFT;

  *BPHptr = WD2 + WD3;

  /* UPPOL2 (p315) */

  SG0 = B4H_PH  >> StdSHIFT;
  SG1 = B4H_PH1 >> StdSHIFT;
  SG2 = B4H_PH2 >> StdSHIFT;

  WD1 = B4H_AH1 << 2;

  if(SG0 == SG2) WD3 =  128;
  else           WD3 = -128;

  WD4  = WD2 + WD3;
  WD5  = (B4H_AH2 * 32512) >> StdSHIFT;
  B4H_APH2 = WD4 + WD5;

  if(B4H_APH2 > 12288)       B4H_APH2 =  12288;
  else if(B4H_APH2 < -12288) B4H_APH2 = -12288;

  /* UPPOL1 (p315) */

  if(SG0 == SG1) WD1 =  192;
  else           WD1 = -192;

  WD2  = (B4H_AH1 * 32640) >> StdSHIFT;
  B4H_APH1 = WD1 + WD2;

  WD3 = 15360 - B4H_APH2;

  if(B4H_APH1 > WD3)       B4H_APH1 =  WD3;
  else if(B4H_APH1 < -WD3) B4H_APH1 = -WD3;

  /* FILTEZ (p316) */

  BHptr  = B4H_BHi+(b4hN-1);
  DHptr  = B4H_DHi+(b4hN-1);
  SZHtmp = 0;
  BHval  = *BHptr--;
  DHval  = *DHptr--;

  for(i=0; i< b4hN-1; i++)
    {
    SZHtmp += (DHval * BHval) >> (StdSHIFT - 1);
    BHval   = *BHptr--;
    DHval   = *DHptr--;
    }
  SZHtmp += (DHval * BHval) >> (StdSHIFT - 1);
  B4H_SZH = SZHtmp;

  /* FILTEP (p316) */

  WD1 = (B4H_RH1 * B4H_AH1) >> (StdSHIFT - 1);
  WD2 = (B4H_RH2 * B4H_AH2) >> (StdSHIFT - 1);

  SPH = WD1 + WD2;

  /* PREDIC (p316) */

  *SH = SPH + B4H_SZH;

  return OK;
  }
