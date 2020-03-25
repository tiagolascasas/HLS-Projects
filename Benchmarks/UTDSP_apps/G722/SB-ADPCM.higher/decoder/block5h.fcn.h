/*
 * G.722 Higher Sub-band Adpcm - Block 5H
 * ==========================
 * This program implements the "Reconstructed Signal Saturation" 
 * in the higher sub-band as described on p.323.
 */

#ifndef TrapsH
#define TrapsH
#include "traps.h"
#endif

#ifndef OK
#define OK 1
#endif

/* function prototype */
int block5h(int YH, int *RH);

int block5h(int YH, int *RH) 
  {
  if (YH > 16383)       *RH =  16383;
  else if (YH < -16384) *RH = -16384;
  else                  *RH =  YH;

  return OK;
  }
