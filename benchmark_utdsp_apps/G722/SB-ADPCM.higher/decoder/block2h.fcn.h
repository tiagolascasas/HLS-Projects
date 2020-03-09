/*
   G.722 Higher Sub-band Adpcm - Block 2H
   ==========================
   This program implements the "Inverse Quantization of the Difference Signal"
   in the higher sub-band as described on p.320.
*/

#ifndef TrapsH
#define TrapsH
#include "traps.h"
#endif

#ifndef OK
#define OK 1
#endif

/* global arrays */
#ifndef tbl21SIH
#define tbl21SIH
int TBL21_SIH[4] = {-1, -1, 0, 0};
#endif

#ifndef tbl21IH2
#define tbl21IH2
int TBL21_IH2[4] = { 2,  1, 2, 1};
#endif

#ifndef tbl14QQ2
#define tbl14QQ2
int TBL14_QQ2[3] = { 0, 202, 926}; /* addr 0 is never used */
#endif

/* function prototype */
int block2h(int IH, int DETH, int *DH);

int block2h(int IH, int DETH, int *DH) 
  {
  int IH2, WD1, WD2, SIH;

  SIH = TBL21_SIH[IH];
  IH2 = TBL21_IH2[IH];

  WD1 = TBL14_QQ2[IH2] << 3;

  if(SIH == 0) WD2 =  WD1;
  else         WD2 = -WD1;

  *DH = (DETH * WD2) >> 15;

  return OK;
  } 
