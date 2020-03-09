/*
   G.722 Receive QMF
   =================
   This program implements the "Receive Quadrature Mirror Filter"
   as described in section 5.2.2 of CCITT Rec. G.722 (pp.296-298)

   The program is written in DSP-style C
*/

#include "traps.h"

#define OK 1;
#define Nqmf 16
#define TAPS 12
#define SHIFTfactor16 8    /* SHIFTfactor16=y-16, where y=32  */

int XD[Nqmf] = { 0, 0, 0, 0, 0, 0, 0, 0,	/* incoming data is stored */
	         0, 0, 0, 0, 0, 0, 0, 0};	/* in a decreasing order.  */
						/* i.e. if sample(i) is    */
int XS[Nqmf] = { 0, 0, 0, 0, 0, 0, 0, 0,	/* stored in XS[j], then   */
                 0, 0, 0, 0, 0, 0, 0, 0};	/* sample(i+1) will be     */
						/* stored in XS[j-1].      */

int QMFT_Heven[Nqmf] = {   3,  -11,  12,   32, -210, 951,
			3876, -805, 362, -156,   53, -11, 0, 0, 0, 0};

int QMFT_Hodd[Nqmf]  = { -11,   53, -156, 362, -805, 3867,
			 951, -210,   32,  12,  -11,    3, 0, 0, 0, 0};

int mlow, mhigh, index, result1, result2;
int a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11;
int ReceiveQMF();

void main()
{
  int byte1, byte2;
  index = 0;

  while(1) {
    byte1 = input_dsp(&mlow, 1, 1);
    byte2 = input_dsp(&mhigh, 1, 1);
    if(!byte1 && !byte2) break;
    ReceiveQMF(&index, mlow, mhigh, &result1, &result2);
    output_dsp(&result1, 1, 1);
    output_dsp(&result2, 1, 1);
  }
}

int ReceiveQMF (int *idx, int RL, int RH, int *Xout1, int *Xout2)
{
  int XDtemp, XStemp, He, Ho, WD1, WD2, XOUT1, XOUT2;
  int *XDptr, *XSptr, *Heptr, *Hoptr;
  int i;
  int *XDLowerBound, *XSLowerBound;
  int *XDUpperBound, *XSUpperBound;
  int *Hevenptr;
  int *Hoddptr;

  XDLowerBound = XD;
  XSLowerBound = XS;
  XDUpperBound = XDLowerBound+(Nqmf-1);
  XSUpperBound = XSLowerBound+(Nqmf-1);
  Hevenptr = QMFT_Heven;
  Hoddptr  = QMFT_Hodd;

  XDptr = XDLowerBound + *idx;
  XSptr = XSLowerBound + *idx;
  /* RECA */				/* RECB */
  *XDptr = RL - RH; 			*XSptr = RL + RH;

  *idx  = *idx - 1;
  if(*idx < 0) *idx = Nqmf - 1;

/*
   ACCUMC 				ACCUMD
   ======				======
*/
  WD1    = 0;				WD2    = 0;
  Heptr  = Hevenptr;			Hoptr  = Hoddptr;
  XDtemp = *XDptr++;			XStemp = *XSptr++;
  He     = *Heptr++;			Ho     = *Hoptr++;
#ifdef GCCmod
  if(XDptr > XDUpperBound) XDptr = XDLowerBound;
  if(XSptr > XSUpperBound) XSptr = XSLowerBound;
#endif 
  for(i=0;i<TAPS-1;i++) {
    WD1   += XDtemp * He;		WD2   += XStemp * Ho;
    XDtemp = *XDptr++;			XStemp = *XSptr++;
    He     = *Heptr++;			Ho     = *Hoptr++;
#ifdef GCCmod
    if(XDptr > XDUpperBound) XDptr = XDLowerBound;
    if(XSptr > XSUpperBound) XSptr = XSLowerBound;
#endif
  }
  WD1 += XDtemp * He;			WD2 += XStemp * Ho;

  XOUT1 = WD1 >> SHIFTfactor16;		
  if(XOUT1 >  16383) XOUT1 =  16383;	
  if(XOUT1 < -16384) XOUT1 = -16384;	

  XOUT2 = WD2 >> SHIFTfactor16;
  if(XOUT2 >  16383) XOUT2 =  16383;
  if(XOUT2 < -16384) XOUT2 = -16384;
/*
   SELECT
   ======
*/
  *Xout1 = XOUT1;
  *Xout2 = XOUT2;

  return OK;
}
