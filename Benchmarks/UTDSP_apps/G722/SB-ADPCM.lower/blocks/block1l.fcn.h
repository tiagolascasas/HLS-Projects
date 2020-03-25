
/*
   G.722 Lower Sub-band Adpcm - Block 1L
   ==========================
   This program implements the "Difference signal computation and quantization"
   in the lower sub-band as described on p.309.
*/

int block1l(int XL, int SL, int DETL, int *IL)
  {
  int EL, SIL, WD, MIL, lowerbound, upperbound;
  int *Q6ptr;

  /* SUBTRA p309 */

  EL = XL - SL;

  /* QUANTL p310 */

  SIL = EL >> 15;

  if(SIL == 0)
    WD = EL;
  else
    WD = 32767 - EL & 32767;

  Q6ptr = TBL14_Q6;
  MIL = 1;
  lowerbound = ((*Q6ptr++ << 3) * DETL) >> 15;
  upperbound = ((*Q6ptr++ << 3) * DETL) >> 15;

  while( MIL < 30 )
    {
    if( WD > lowerbound  &&  WD < upperbound )
      break;
    lowerbound = upperbound;
    upperbound = ((*Q6ptr++ << 3) * DETL) >> 15;
    MIL++;
    }

  if(SIL == -1)
    *IL = TBL16_IL_negSIL[MIL];
  else
    *IL = TBL16_IL_zeroSIL[MIL];

  return OK;
  }
