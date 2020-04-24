
#include<stdio.h>

#define M 257 // no. of samples
#define N 32 // no. of coeff.

void fir_graph(int x[M],int  y[M], int c[N])
{
  FILE *f=fopen("fir_basic.dot","w");
  fprintf(f,"Digraph G{\n");	
  int output;
  short n_x[M]={0};
  short n_y[M]={0};
  short n_c[N]={0};
  short n_output=0;
  int n_const=0; 
  int n_temp=0;
  int n_op=0;
  int n_out=0;
  int ne=0;

for(int j=N-1; j<M; j++) {
	output=0;
	
	n_const++;
	fprintf(f,"const%d [label=\"0\", att1=const];\n",n_const);
	fprintf(f,"\"output_%d\" [label=\"output\", att1=var, att2=loc, att3=int ];\n",n_output+1);
	ne++;
	fprintf(f,"const%d->\"output_%d\" [label=\"%d\", ord=\"%d\"];\n",n_const,n_output+1,ne,ne);
	n_output++;
	
	// Loop 2:
	for(int i=0; i<N; i++) {
		output+=c[i]*x[j-i];
		
		fprintf(f,"\"c[%d]_%d\" [label=\"c[%d]\", att1=var, att2=inte, att3=int ];\n",i,n_c[i],i);
		fprintf(f,"\"x[%d]_%d\" [label=\"x[%d]\", att1=var, att2=inte, att3=int ];\n",j-i,n_x[j-i],j-i);
		n_op++;
		fprintf(f,"op%d [label=\"*\", att1=op];\n",n_op);//nc-3
		n_temp++;
		fprintf(f,"temp%d [label=\"temp_l34_i%d\", att1=var, att2=loc, att3=float ];\n",n_temp,n_temp);//nc-2
			   
		ne++;
		fprintf(f,"\"c[%d]_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n",i,n_c[i],n_op,ne,ne);
		ne++;
		fprintf(f,"\"x[%d]_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n",j-i,n_x[j-i],n_op,ne,ne);
		ne++;
		fprintf(f,"op%d->temp%d [label=\"%d\", ord=\"%d\"];\n",n_op,n_temp,ne,ne);
			   
		fprintf(f,"temp%d [label=\"temp_l34_i%d\", att1=var, att2=loc, att3=int ];\n",n_temp,n_temp);//nc-2
		fprintf(f,"\"output_%d\" [label=\"output\", att1=var, att2=loc, att3=int ];\n",n_output);
		n_op++;
		fprintf(f,"op%d [label=\"+\", att1=op ];\n",n_op);//nc-1
		fprintf(f,"\"output_%d\" [label=\"output\", att1=var, att2=loc, att3=int ];\n",n_output+1);
			   
		ne++;		   
		fprintf(f,"temp%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n",n_temp,n_op,ne,ne);
		ne++;
		fprintf(f,"\"output_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n",n_output,n_op,ne,ne);
		ne++;
		fprintf(f,"op%d->\"output_%d\" [label=\"%d\", ord=\"%d\"];\n",n_op,n_output+1,ne,ne);
		n_output++;
	}
	
	fprintf(f,"\"y[%d]_%d\" [label=\"y[%d]\", att1=var, att2=inte, att3=int ];\n",j,n_y[j]+1,j);
	fprintf(f,"\"output_%d\" [label=\"output\", att1=var, att2=loc, att3=int ];\n",n_output);
  
	ne++;
	fprintf(f,"\"output_%d\"->\"y[%d]_%d\" [label=\"%d\", ord=\"%d\"];\n",n_output,j,n_y[j]+1,ne,ne);
	n_y[j]++;
	y[j] = output;
}
  fprintf(f,"}");
  fclose(f);
}

int main(){
	int input[M];
	int output[M];
	int coeff[N]={2,2};
/*int coeff[N] = {1, 2, 4, -2, 1, 1, -3, 1,
1, 2, 4, -2, 1, 1, -3, 1,
1, 2, 4, -2, 1, 1, -3, 1,
1, 2, 4, -2, 1, 1, -3, 1,
};*/
	for(int i=0; i<M; i++){
		input[i]=i;
		output[i]=0;
	}
	
	fir_graph(input,output, coeff);
	
	for(int j=0; j<M; j++){
		printf("OUT: %d\n",output[j]);
	}
	
}