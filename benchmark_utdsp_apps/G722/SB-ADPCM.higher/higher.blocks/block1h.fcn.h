/*
 * G.722 Higher Sub-band Adpcm - Block 1H
 * ===========================
 * This program implements the "Difference signal computation and quantization"
 * in the higher sub-band as described on p.319.
 */

#ifndef TrapsH
#define TrapsH
#include "traps.h"
#endif

#ifndef OK
#define OK 1
#endif

/* function prototype */
int block1h(int XH, int SH, int DETH, int *IH);

int block1h(int XH, int SH, int DETH, int *IH)
  {
  int EH, SIH, WD, MIH;

  /* SUBTRA p319 */

  EH = XH - SH;

  /* QUANTL p319 */

  SIH = EH >> 15;

  if(SIH == 0)
    WD = EH;
  else
    WD = 32767 - EH & 32767;

  /* Note: the following two if-else's are highly dependent
   *       on the present values in TBL14 and TBL20.
   *       (i.e. these statements must be revised if the
   *       values in the abovementioned tables are changed
   */

  if(WD > 0 && WD < (564<<3)*DETH>>15) MIH = 1;
  else                                 MIH = 2;

  if(SIH == -1)
    *IH = MIH - 1;
  else
    *IH = MIH | 2;

  return OK;
  }
