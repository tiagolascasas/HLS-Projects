
/*
   G.722 Lower Sub-band Adpcm - Block 2L 
   ==========================
   This program implements the "Inverse Quantization of the Difference Signal"
   in the lower sub-band as described on p.311.
*/

int block2l(int IL, int DETL, int *DLT) 
  {
  int RIL, index, WD1, WD2, SIL;

  RIL = (IL >> 2) & 0xf;

  index = TBL17_IL4[RIL];
  SIL = TBL17_SIL[RIL];

  WD1 = TBL14_QQ4[index] << 3;

  if(SIL == 0) WD2 =  WD1;
  else         WD2 = -WD1;

  *DLT = (DETL * WD2) >> 15;

  return OK;
  } 
