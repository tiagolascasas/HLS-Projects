#include <math.h>
#include <stdio.h>
#include "globs.h"
#include "block2l.fcn.h"
#include "block3l.fcn.h"
#include "block4l.fcn.h"
#include "block5l.fcn.h"
#include "block6l.fcn.h"

int block2l();
int block3l();
int block4l();
int block5l();
int block6l();

int IRL, DETL, DLT, SL, YL, RL;

void main()
  {
  int RS, flag, dummy, mode;
  IRL  = 0;
  DETL = 0;
  DLT  = 0;
  SL   = 0;
  YL   = 0;
  RL   = 0;
  mode = 1;

  while(1)
    {
/*
 *  flag = input_dsp(&dummy, 1, 1);
 *  if (!flag) break;
*/
    flag = input_dsp(&IRL, 1, 1);
    if(flag)
      {
      block2l(IRL, DETL, &DLT);
      block3l(IRL, RS, &DETL);
      block4l(DLT, RS, &SL);
      block5l(IRL, DETL, mode, SL, &YL);
      block6l(YL, &RL);
      output_dsp(&RL, 1, 1);
      }
    else
      break;
    }
  }
