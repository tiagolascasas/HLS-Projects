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

//#include "dotprod_viv.h"
#include <stdio.h>
#include <stdlib.h>

#define NX 4



int DSP_dotprod_graph(const short *x, const short *y, int nx)
{
    
	

	short n_x[NX]={0};
	short n_y[NX]={0};
	short n_sum=0;
	int n_const=0;
	int n_temp=0;
	int n_op=0;
	int n_out=0;
	int ne=0;
	FILE *f=fopen("dotprod_1_graph.dot","w");
	fprintf(f,"Digraph G{\n");
	
	int sum = 0, i;
	
     n_const++;
	 fprintf(f,"const%d [label=\"0\", att1=const];\n",n_const);
	 fprintf(f,"\"sum_%d\" [label=\"sum\", att1=var, att2=loc, att3=int ];\n",n_sum+1);
	 ne++;
	 fprintf(f,"const%d->\"sum_%d\" [label=\"%d\", ord=\"%d\"];\n",n_const,n_sum+1,ne,ne);
	 n_sum++;

    for (i = 0; i < nx; i++){
        sum += x[i] * y[i];
		
	  	fprintf(f,"\"x[%d]_%d_l\" [label=\"x[%d]\", att1=var, att2=inte, att3=short ];\n" ,i, n_x[i] ,i);//nc-5
		fprintf(f,"\"y[%d]_%d_r\" [label=\"y[%d]\", att1=var, att2=inte, att3=short ];\n" ,i, n_y[i] ,i);//nc-5
		n_op++;
		fprintf(f,"op%d [label=\"*\", att1=op];\n",n_op);//nc-3
		n_temp++;
		fprintf(f,"temp%d [label=\"temp_l83_i%d\", att1=var, att2=loc, att3=int ];\n",n_temp,n_temp);//nc-2
		   
		ne++;
		fprintf(f,"\"x[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n",i, n_x[i],n_op,ne,ne);
		ne++;
		fprintf(f,"\"y[%d]_%d_r\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n",i,n_y[i],n_op,ne,ne);
		ne++;
		fprintf(f,"op%d->temp%d [label=\"%d\", ord=\"%d\"];\n",n_op,n_temp,ne,ne);
		   
		fprintf(f,"temp%d [label=\"temp_l83_i%d\", att1=var, att2=loc, att3=int ];\n",n_temp,n_temp);//nc-2
		fprintf(f,"\"sum_%d\" [label=sum, att1=var, att2=loc, att3=int ];\n",n_sum);
		n_op++;
		fprintf(f,"op%d [label=\"+\", att1=op ];\n",n_op);//nc-1
		fprintf(f,"\"sum_%d\" [label=sum, att1=var, att2=loc, att3=int ];\n",n_sum+1);
		   
		ne++;		   
		fprintf(f,"temp%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n",n_temp,n_op,ne,ne);
		ne++;
		fprintf(f,"\"sum_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n",n_sum,n_op,ne,ne);
		ne++;
		fprintf(f,"op%d->\"sum_%d\" [label=\"%d\", ord=\"%d\"];\n",n_op,n_sum+1,ne,ne);
	    n_sum++;

	}
	
	fprintf(f,"\"sum_%d\" [label=sum, att1=var, att2=loc, att3=int ];\n",n_sum);
	fprintf(f,"\"out_%d\" [label=*out, att1=var, att2=inte, att3=int ];\n",n_out);
	fprintf(f,"\"sum_%d\"->out_%d [label=\"%d\", ord=\"%d\"];\n",n_sum,n_out,ne,ne);
	ne++;
	
	
	fprintf(f,"}\n");	
	fclose(f);
    return sum;

}

int main()
{	short x[NX] = {1, 2};
	short y[NX] = {3, 4};
	DSP_dotprod_graph(x, y, NX);
}

/* ======================================================================== */
/*  End of file:  dsp_dotprod.c                                             */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
