
/*
   G.722 Lower Sub-band Adpcm - Block 5L
   ==========================
   This program implements the "Reconstructed Signal Calculator" for the 
   decoder output in the lower sub-band.
*/
 
int block5l(int ILR, int DETL, int MODE, int SL, int *YL)
  {
  int RIL, SIL, index, WD1, WD2, DL;

  /* INVQBL p.317 */

  /* check MODE, then compute WD1 and SIL */
  if (MODE == 1)
    {
    RIL = ILR;
    index = TBL18_IL6[RIL];
    WD1 = TBL14_QQ6[index] << 3;
    SIL = TBL18_SIL[RIL];
    }
  else if (MODE == 2)
    {
    RIL = (ILR >> 1) & 0x1f;
    index = TBL19_IL5[RIL];
    WD1 = TBL14_QQ5[index] << 3;
    SIL = TBL19_SIL[RIL];
    }
  else if (MODE == 3)
    {
    RIL = (ILR >> 2) & 0xf;
    index = TBL17_IL4[RIL];
    WD1 = TBL14_QQ4[index] << 3;
    SIL = TBL17_SIL[RIL];
    }

  /* ready to compute WD2 */ 

  if (SIL == 0)       WD2 =  WD1;
  else if (SIL == -1) WD2 = -WD1;

  /* compute  DL */

  DL = (DETL * WD2) >> 15;

  /* RECONS  p.317 */

  *YL = SL + DL;
  
  return OK;
  }
