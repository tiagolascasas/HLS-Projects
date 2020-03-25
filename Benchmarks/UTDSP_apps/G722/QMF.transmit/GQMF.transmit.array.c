/*
   G.722 Transmit QMF
   ==================
   This program implements the "Transmit Quadrature Mirror Filter"
   as described in section 5.2.1 of CCITT Rec. G.722 (pp.294-296)

   The program is written in DSP-style C
*/

#include <math.h>
#include <stdio.h>

#define OK 1
#define TAPS 12
#define Nqmf 16   /* actually 12, but since must be a power of 2, chose 16 */
#define SHIFTfactor15 9   /*SHIFTfactor15=y-15, where y=32  */

int QMFT_XINeven[Nqmf] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

int QMFT_XINodd[Nqmf]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int QMFT_Heven[Nqmf] = {   3,  -11,  12,   32, -210, 951,
		        3876, -805, 362, -156,   53, -11, 0, 0, 0, 0 };

int QMFT_Hodd[Nqmf]  = { -11,   53, -156, 362, -805, 3867,
		         951, -210,   32,  12,  -11,    3, 0, 0, 0, 0 };

int index, oddm, evenm, XLm, XHm;
int  a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11;
int transmitQMF();

void main()
{
  int dummy1, dummy2, byte1, byte2;
  index = 0;

  while(1) {
    byte1 = input_dsp(&evenm, 1, 1);
    byte2 = input_dsp(&oddm, 1, 1);
    if(!byte1 && !byte2) break;
    transmitQMF(&index, evenm, oddm, &XLm, &XHm);
    output_dsp(&XLm, 1, 1);
    output_dsp(&XHm, 1, 1);
  }
}

int transmitQMF(int * idx, int XINeven, int XINodd, int * XLout, int * XHout)
{
  int XA, XINe, He, XB, XINo, Ho, XH, XL;
  int *XINeptr, *Heptr, *XINoptr, *Hoptr;
  int i;
  int *XINevenLowerBound, *XINoddLowerBound;
  int *XINevenUpperBound, *XINoddUpperBound;
  int *Hevenptr;
  int *Hoddptr;

  XINevenLowerBound = QMFT_XINeven;
  XINoddLowerBound  = QMFT_XINodd;
  XINevenUpperBound = XINevenLowerBound+(Nqmf-1);
  XINoddUpperBound  = XINoddLowerBound+(Nqmf-1);
  Hevenptr = QMFT_Heven;
  Hoddptr  = QMFT_Hodd;

/* update array with new elements */

  XINeptr = XINevenLowerBound + *idx;
  XINoptr = XINoddLowerBound  + *idx;
  *XINeptr = XINeven;		*XINoptr = XINodd;
  *idx = *idx - 1;

  if(*idx < 0) *idx = Nqmf-1;

/*
   ACCUMA & ACCUMB (computed in parallel)
   ======================================
*/

  XA      = 0;			XB      = 0;
  Heptr   = Hevenptr;		Hoptr   = Hoddptr;

  XINe = *XINeptr++;		XINo = *XINoptr++;
  He   = *Heptr++;		Ho   = *Hoptr++;
#ifdef GCCmod
  if(XINeptr > XINevenUpperBound) XINeptr = XINevenLowerBound;
  if(XINoptr > XINoddUpperBound)  XINoptr = XINoddLowerBound;
#endif 
  for(i=0; i<TAPS-1; i++) {
    XA  += XINe * He;		XB  += XINo * Ho;
    XINe = *XINeptr++;		XINo = *XINoptr++;
    He   = *Heptr++;		Ho   = *Hoptr++;
#ifdef GCCmod 
  if(XINeptr > XINevenUpperBound) XINeptr = XINevenLowerBound;
  if(XINoptr > XINoddUpperBound)  XINoptr = XINoddLowerBound;
#endif 
  }
  XA  += XINe * He;		XB  += XINo * Ho;

/*
   LOWT
   ====
*/ 
  XL = (XA + XB) >> SHIFTfactor15;
  if(XL >  16383) XL =  16383;
  if(XL < -16384) XL = -16384;

/*
   HIGHT
   =====
*/ 
  XH = (XA - XB) >> SHIFTfactor15;
  if(XH >  16383) XH =  16383;
  if(XH < -16384) XH = -16384;

  *XLout = XL;
  *XHout = XH;

  return OK;
}
