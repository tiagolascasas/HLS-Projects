/*
   G.722 Higher Sub-band Adpcm - Block 3H
   ==========================
   This program implements the "Quantizer scale factor adaptation"
   in the lower sub-band as described on p.320.
*/

#ifndef TrapsH
#define TrapsH
#include "traps.h"
#endif

#ifndef OK
#define OK 1
#endif

#ifndef RESET
#define RESET -1
#endif

/* global arrays */
#ifndef tbl14WH
#define tbl14WH
int TBL14_WH[3]   = { 0, -214, 798};
#endif

#ifndef tbl15ILB
#define tbl15ILB
int TBL15_ILB[32] = {2048, 2093, 2139, 2186, 2233, 2282, 2332, 2383,
                     2435, 2489, 2543, 2599, 2656, 2714, 2774, 2834,
                     2896, 2960, 3025, 3091, 3158, 3228, 3298, 3371,
                     3444, 3520, 3597, 3676, 3756, 3838, 3922, 4008};
#endif

#ifndef tbl21IH2
#define tbl21IH2
int TBL21_IH2[4]  = { 2, 1, 2, 1};
#endif

/* static variables */
int B3H_NBH, B3H_NBPH, B3H_DEPH;

/* function prototype */
int block3h(int IH, int RS, int *DETH);

int block3h(int IH, int RS, int *DETH)
  {
  int IH2, WD, WH, WD1, WD2, WD3, NBPH;

  /* RESET handling */

  if(RS == 1)
    {
    B3H_NBH  = 0;
    B3H_NBPH = 0;
    *DETH    = 32;
    B3H_DEPH = 32;
    return RESET;
    }
  else
    {
    B3H_NBH = B3H_NBPH;
    *DETH   = B3H_DEPH;
    }

  /* LOGSCL (p321) */

  IH2      = TBL21_IH2[IH];
  WH       = TBL14_WH[IH2];
  WD       = (B3H_NBH * 32512) >> 15;
  NBPH     = WD + WH;
  B3H_NBPH = NBPH;

  if(NBPH < 0) NBPH = 0;
  else if (NBPH > 22528) NBPH = 22528;

  /* SCALEL (p321) */

  WD1 = (NBPH >> 6) & 31;
  WD2 = NBPH >> 11;

  if(WD2 == 11)
    WD3 = TBL15_ILB[WD1] << 1;
  else
    WD3 = TBL15_ILB[WD1] >> (10-WD2);

  B3H_DEPH = WD3 << 2;

  return OK;
  }
