#ifndef TrapsH
#define TrapsH
#include "traps.h"
#endif

#include "block2h.fcn.h"
#include "block3h.fcn.h"
#include "block4h.fcn.h"
#include "block5h.fcn.h"

int IH, DETH, DH, YH, RH;

void main()
  {
  int RS, flag, dummy;
  IH   = 0;
  DETH = 0;
  DH   = 0;
  YH   = 0;
  RH   = 0;
  RS   = 0;

  while(1)
    {
    flag = input_dsp(&IH, 1, 1);
/*  input_dsp(&dummy, 1, 1); */
    if(flag)
      {
      block2h(IH, DETH, &DH);
      block3h(IH, RS, &DETH);
      block4h(DH, RS, &YH);
      block5h(YH, &RH);
      output_dsp(&RH, 1, 1);
      }
    else
      break;
    }
  }
