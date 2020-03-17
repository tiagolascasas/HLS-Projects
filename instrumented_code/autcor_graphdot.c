/*===============================================================================
*
*       TEXAS INSTRUMENTS, INC.         
*
*       AUTOCORRELATION
*
*       Revision Date:  04/16/97
*/

/* DSP performance:
   (N/2) *M + 16 + M/4
   For N=160 and M=10;
   816 cycles or 4.08 µsec
*/

#include <stdio.h>
#include "autcor_viv.h"

short ac[M]; // --- Resulting array of autocorrelation

short sd[N+M]; // --- Input array of autocorrelation


void main() {
  int tmp;
  
  //void autcor(short ac[],short sd[], int N, int M) {
  int i,k,sum;
  int nc=0;
  for(i=0;i<N; i++){
	sd[i]=i;  
  }
  
  FILE *f=fopen("graph_autcor.dot","w");
   int n_const=0;
   int n_temp=0;
   int n_op=0;
   int ne=0;
   short n_sd[N+M]={0};
   short n_ac[M]={0};
   short n_sum=0;
   
  fprintf(f,"Digraph G{\n");
  for (i = 0; i < M; i++){
    sum = 0;

	n_const++;
	fprintf(f,"const%d [label=\"0\", att1=const];\n",n_const);
	fprintf(f,"\"sum_%d\" [label=sum, att1=var, att2=loc, att3=int ];\n",n_sum+1);
	ne++;
	fprintf(f,"const%d->\"sum_%d\" [label=\"%d\", ord=\"%d\"];\n",n_const,n_sum+1,ne,ne);
	n_sum++;

	 
    for (k = 0; k < N; k++) {
      sum += sd[k+M] * sd[k+M-i];
	  //create graph
	  
	  	fprintf(f,"\"sd[%d]_%d_l\" [label=\"sd[%d]\", att1=var, att2=inte, att3=short ];\n" ,k+M, n_sd[k+M] ,k+M);//nc-5
		fprintf(f,"\"sd[%d]_%d_r\" [label=\"sd[%d]\", att1=var, att2=inte, att3=short ];\n" ,k+M-i, n_sd[k+M-i] ,k+M-i);//nc-5
		n_op++;
		fprintf(f,"op%d [label=\"*\", att1=op];\n",n_op);//nc-3
		n_temp++;
		fprintf(f,"temp%d [label=\"temp_l57_i%d\", att1=var, att2=loc, att3=short ];\n",n_temp,n_temp);//nc-2
		   
		ne++;
		fprintf(f,"\"sd[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n",k+M, n_sd[k+M],n_op,ne,ne);
		ne++;
		fprintf(f,"\"sd[%d]_%d_r\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n",k+M-i,n_sd[k+M-i],n_op,ne,ne);
		ne++;
		fprintf(f,"op%d->temp%d [label=\"%d\", ord=\"%d\"];\n",n_op,n_temp,ne,ne);
		   
		fprintf(f,"temp%d [label=\"temp_l57_i%d\", att1=var, att2=loc, att3=short ];\n",n_temp,n_temp);//nc-2
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
		   
	 //finish loop graph  
    }
	ac[i] = (sum >> 15);
	//start_graph
	n_const++;
	fprintf(f,"const%d [label=\"15\" , att1=const];\n",n_const);//nc-2
	n_op++;
	fprintf(f,"op%d [label=\">>\", att1=op];\n",n_op);//nc-3

	fprintf(f,"\"ac[%d]_%d\" [label=\"ac[%d]\", att1=var, att2=inte, att3=short ];\n" ,i, n_ac[i]+1 ,i);//nc-5

	ne++;		   
	fprintf(f,"const%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n",n_const,n_op,ne,ne);
	ne++;
	fprintf(f,"\"sum_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n",n_sum,n_op,ne,ne);
	ne++;
	fprintf(f,"op%d->\"ac[%d]_%d\" [label=\"%d\", ord=\"%d\"];\n",n_op,i,n_ac[i]+1,ne,ne);
	n_ac[i]++;
	//finish graph

  }
  fprintf(f,"}\n");
    for(i=0;i<M; i++){
	printf("%d \n",ac[i]);  
  }
  fclose(f);

}


