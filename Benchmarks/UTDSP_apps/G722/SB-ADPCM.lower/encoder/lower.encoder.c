#include "traps.h"
#include "globs.h"
#include "block1l.fcn.h"
#include "block2l.fcn.h"
#include "block3l.fcn.h"
#include "block4l.fcn.h"

int block1l(int XL, int SL, int DETL, int *IL);
int block2l(int IL, int DETL, int *DLT);
int block3l(int IL, int RS, int *DETL);
int block4l(int DLT, int RS, int *SL);

int XL, DETL, DLT, SL, IL;

void main()
  {
  int RS, flag, dummy;
  XL   = 0;
  DETL = 0;
  DLT  = 0;
  SL   = 0;
  IL   = 0;
  RS   = 0;

  while(1)
    {
    flag = input_dsp(&XL, 1, 1);
    input_dsp(&dummy, 1, 1);
    if(flag)
      {
      block1l(XL, SL, DETL, &IL);
      block2l(IL, DETL, &DLT);
      block3l(IL, RS, &DETL);
      block4l(DLT, RS, &SL);
      output_dsp(&IL, 1, 1);
      }
    else
      break;
    }
  }
