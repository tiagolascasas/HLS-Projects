/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  DSPLIB  DSP Signal Processing Library                                   */
/*                                                                          */
/*  This library contains proprietary intellectual property of Texas        */
/*  Instruments, Inc.  The library and its source code are protected by     */
/*  various copyrights, and portions may also be protected by patents or    */
/*  other legal protections.                                                */
/*                                                                          */
/*  This software is licensed for use with Texas Instruments TMS320         */
/*  family DSPs.  This license was provided to you prior to installing      */
/*  the software.  You may review this license by consulting the file       */
/*  TI_license.PDF which accompanies the files in this library.             */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */


/* ======================================================================== */
/*                                                                          */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_dotprod                                                         */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      29-Mar-2002                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          int DSP_dotprod                                                 */
/*          (                                                               */
/*              const short *x,    // first input vector  //                */
/*              const short *y,    // second input vector //                */
/*              int nx             // number of elements  //                */
/*          );                                                              */
/*                                                                          */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This routine takes two vectors and calculates their vector          */
/*      product.  The inputs are 16-bit number, and the result is           */
/*      a 32-bit number.                                                    */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      nx must be a multiple of 2 and greater than 2.                      */
/*      Vectors x and y must be aligned on word boundaries.                 */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

int DSP_dotprod_c(const short *x, const short *y, int nx)
{
    int sum = 0, i;


    for (i = 0; i < nx; i++)
        sum += x[i] * y[i];

    return sum;
}

/* ======================================================================== */
/*  End of file:  dsp_dotprod.c                                             */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
