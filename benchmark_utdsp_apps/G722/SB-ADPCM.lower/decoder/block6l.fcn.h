
/* 
   G.722 Lower Sub-band Adpcm - Block 6L
   ==========================
   This program implements the "Reconstructed Signal Saturation" in the lower
   sub-band as described on p.318.
*/

int block6l(int YL, int *RL) 
  {
  if (YL > 16383)       *RL =  16383;
  else if (YL < -16384) *RL = -16384;
  else                  *RL =  YL;

  return OK;
  }
