#include "fsubba_viv.h"



void filter_subband_double_graph2(double z[Nz], double s[Ns], double m[Nm])
{


   double y[Ny];
   int i,j;
   FILE *fg=fopen("fsubba_graph2.dot","w");
   fprintf(fg,"Digraph G{\n");
   //counter creation
   short n_z[Nz]={0};
   short n_s[Ns]={0};
   short n_m[Nm]={0};
   short n_y[Ny]={0};
   int n_const=0;
   int n_temp=0;
   int n_op=0;
   
   int ne=0;
  // ng++;
   //fprintf(fg,"subgraph G%d{\n",ng);
   for (i=0;i<Ny;i++)
   {

     y[i] = 0.0;
	 n_const++;
	 fprintf(fg,"const%d [label=\"0\", att1=const];\n",n_const);
	
	 fprintf(fg,"\"y[%d]_%d\" [label=\"y[%d]\", att1=var, att2=loc, att3=double ];\n",i,n_y[i]+1,i);
	 ne++;
	 fprintf(fg,"const%d->\"y[%d]_%d\" [ ord=\"%d\"];\n",n_const,i,n_y[i]+1,ne,ne);
	 n_y[i]++;
	// ng++;
	// fprintf(fg,"subgraph G%d{\n",ng);
     for (j=0; j<(Nz/Ny);j++){
		  
          y[i] += z[i+Ny*j];
		  
		  fprintf(fg,"\"z[%d]_%d\" [label=\"z[%d]\", att1=var, att2=inte, att3=double ];\n",i+Ny*j,n_z[i+Ny*j],i+Ny*j);//nc-2
		  n_op++;
		  fprintf(fg,"op%d [label=\"+\", att1=op];\n", n_op);//nc-1
		 
          fprintf(fg,"\"y[%d]_%d\" [label=\"y[%d]\", att1=var, att2=loc, att3=double ];\n",i,n_y[i]+1,i);
		  ne++;
		  fprintf(fg,"\"z[%d]_%d\"->op%d [ ord=\"%d\", pos=\"l\"];\n",i+Ny*j,n_z[i+Ny*j],n_op,ne,ne);
		  ne++;
		  fprintf(fg,"\"y[%d]_%d\"->op%d [ ord=\"%d\", pos=\"r\"];\n",i,n_y[i],n_op, ne,ne);
		  ne++;
		  fprintf(fg,"op%d->\"y[%d]_%d\" [ ord=\"%d\"];\n",n_op, i,n_y[i]+1 ,ne, ne);
		  n_y[i]++;
		  
	 }
	
	//fprintf(fg,"};\n");
   }
   //fprintf(fg,"};\n");	  

   //ng++;
   //fprintf(fg,"subgraph G%d{\n",ng);
   for (i=0;i<Ns;i++)
   {
	   
       s[i]=0.0;
	   n_const++;
	   fprintf(fg,"const%d [label=\"0\", att1=const];\n",n_const);
	   
	   fprintf(fg,"\"s[%d]_%d\" [label=\"s[%d]\", att1=var, att2=inte, att3=double ];\n",i,n_s[i]+1,i);
	   ne++;
	   fprintf(fg,"const%d->\"s[%d]_%d\" [ ord=\"%d\"] ;\n",n_const,i,n_s[i]+1,ne,ne);
	   n_s[i]++;
	    //ng++;
       //fprintf(fg,"subgraph G%d{\n",ng);
       for (j=0; j<Ny;j++){
		  
           s[i] += m[Ns*i+j] * y[j];
		   
	
		   fprintf(fg,"\"m[%d]_%d\" [label=\"m[%d]\", att1=var, att2=inte, att3=double ];\n" ,Ns*i+j, n_m[Ns*i+j] ,Ns*i+j);//nc-5
		   fprintf(fg,"\"y[%d]_%d\" [label=\"y[%d]\", att1=var, att2=loc, att3=double ];\n",j,n_y[j],j);//nc-4
		   n_op++;
		   fprintf(fg,"op%d [label=\"*\", att1=op];\n",n_op);//nc-3
		   n_temp++;
		   fprintf(fg,"temp%d [label=\"temp_l86_i%d\", att1=var, att2=loc, att3=double ];\n",n_temp,n_temp);//nc-2
		   
		   ne++;
		   fprintf(fg,"\"m[%d]_%d\"->op%d [ ord=\"%d\", pos=\"l\"];\n",Ns*i+j, n_m[Ns*i+j],n_op,ne,ne);
		   ne++;
		   fprintf(fg,"\"y[%d]_%d\"->op%d [ ord=\"%d\", pos=\"r\"];\n",j,n_y[j],n_op,ne,ne);
		   ne++;
		   fprintf(fg,"op%d->temp%d [ ord=\"%d\"];\n",n_op,n_temp,ne,ne);
		   
		   fprintf(fg,"temp%d [label=\"temp_l86_i%d\", att1=var, att2=loc, att3=double ];\n",n_temp,n_temp);//nc-2
		   fprintf(fg,"\"s[%d]_%d\" [label=\"s[%d]\", att1=var, att2=inte, att3=double ];\n",i,n_s[i],i);
		   n_op++;
		   fprintf(fg,"op%d [label=\"+\", att1=op ];\n",n_op, i);//nc-1
		   fprintf(fg,"\"s[%d]_%d\" [label=\"s[%d]\", att1=var, att2=inte, att3=double ];\n",i,n_s[i]+1,i);
		   
		   ne++;		   
		   fprintf(fg,"temp%d->op%d [ ord=\"%d\", pos=\"r\"];\n",n_temp,n_op,ne,ne);
		   ne++;
		   fprintf(fg,"\"s[%d]_%d\"->op%d [ ord=\"%d\", pos=\"l\"];\n",i,n_s[i],n_op,ne,ne);
		   ne++;
		   fprintf(fg,"op%d->\"s[%d]_%d\" [ ord=\"%d\"];\n",n_op,i,n_s[i]+1,ne,ne);
	       n_s[i]++;
	   } 
	//fprintf(fg,"};\n");   
   }
   //fprintf(fg,"};\n"); 
   /*
			n_temp++;
			fprintf(fg,"temp%d [label=\"temp_le\", att1=var, att2=loc, att3=double ];\n",n_temp,n_temp);//nc-2
			fprintf(fg,"\"s[%d]_%d\" [label=\"s[%d]\", att1=var, att2=inte, att3=double ];\n",Ns-1,n_s[Ns-1],Ns-1);
		   n_op++;
		   fprintf(fg,"op%d [label=\"+\", att1=op ];\n",n_op, i);//nc-1
		   fprintf(fg,"\"s[%d]_%d\" [label=\"s[%d]\", att1=var, att2=inte, att3=double ];\n",Ns-1,n_s[Ns-1]+1,Ns-1);
		   
		   ne++;		   
		   fprintf(fg,"temp%d->op%d [ ord=\"%d\", pos=\"r\"];\n",n_temp,n_op,ne,ne);
		   ne++;
		   fprintf(fg,"\"s[%d]_%d\"->op%d [ ord=\"%d\", pos=\"l\"];\n",Ns-1,n_s[Ns-1],n_op,ne,ne);
		   ne++;
		   fprintf(fg,"op%d->\"s[%d]_%d\" [ ord=\"%d\"];\n",n_op,Ns-1,n_s[Ns-1]+1,ne,ne);
	       n_s[i]++;   
		   */
   fprintf(fg,"}\n");	
	fclose(fg);
}


void main(){
	
	
	double z[Nz];
	double s[Ns];
	double m[Nm];
	int i;
	for(i=0; i<Nz;i++)
		z[i]=i;

	for(i=0; i<Nm; i++)
		m[i]=2*i+1;

	filter_subband_double_graph2(z,  s,m);
	for(i=0;i<Ns;i++){
		printf("%lf\n",s[i]);
	}
	
    return;
}