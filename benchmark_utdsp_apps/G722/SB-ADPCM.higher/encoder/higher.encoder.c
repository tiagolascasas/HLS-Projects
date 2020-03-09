#ifndef TrapsH
#define TrapsH
#include "traps.h"
#endif

#include "block1h.fcn.h"
#include "block2h.fcn.h"
#include "block3h.fcn.h"
#include "block4h.fcn.h"

int XH, DETH, DH, SH, IH;

void main()
  {
  int RS, flag, dummy;
  XH   = 0;
  DETH = 0;
  DH   = 0;
  SH   = 0;
  IH   = 0;
  RS   = 0;

  while(1)
    {
    input_dsp(&dummy, 1, 1);
    flag = input_dsp(&XH, 1, 1);
    if(flag)
      {
      block1h(XH, SH, DETH, &IH);
      block2h(IH, DETH, &DH);
      block3h(IH, RS, &DETH);
      block4h(DH, RS, &SH);
      output_dsp(&IH, 1, 1);
      }
    else
      break;
    }
  }
