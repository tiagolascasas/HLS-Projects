#include "traps.h"


#define NumofInput 115
void Differential();
void Convolutional();

float    ConstellationX[32]={ 
-4.00,0.00,0.00,4.00,4.00,0.00,0.00,-4.00,-2.00,-2.00,2.00,2.00,2.00,2.00,-2.00,-2.00,-3.00,1.00,-3.00,1.00,3.00,-1.00,3.00,-1.00,1.00,-3.00,1.00,1.00,-1.00,3.00,-1.00,-1.00
};
float    ConstellationY[32]={ 
1.00,-3.00,1.00,1.00,-1.00,3.00,-1.00,-1.00,3.00,-1.00,3.00,-1.00,-3.00,1.00,-3.00,1.00,-2.00,-2.00,2.00,2.00,2.00,2.00,-2.00,-2.00,4.00,0.00,0.00,-4.00,-4.00,0.00,0.00,4.00
};
float x;
float y;
int output[5];
int Inbit[4*NumofInput];
int ylast[3]={0,0,0};
int s[3]={0,0,0};
int and[2];
int Input[NumofInput];
int index;
int xx;
main()
{
int count;
int i;
int p;
int j=0;
int k;
int bomb;


int *inbit;
int *input;
int *out;
float *px;
float *py;

bomb=0;
out=output;
px=ConstellationX;
py=ConstellationY;
inbit=Inbit;
input=Input;
while(1)
{
if (bomb==0)
xx=input_dsp(Input,1,2);
if (!xx) bomb++;
if (bomb==4) break;
/* for (count=0; count<NumofInput+3; count++)
{  */
inbit=Inbit;
*inbit++=(*input&8)>>3;
*inbit++=(*input&4)>>2;
*inbit++=(*input&2)>>1 ;
*inbit=*input&1;

#ifdef GCCmod
inbit=Inbit;
printf("input is %d\n",*input);
puts("input bit string is: ");
for(j=0;j<3;j++)
printf("%d ",*inbit++);
printf("%d\n\n",*inbit);
puts("old delaystate:");
for(j=0;j<3;j++)
printf("%d ",s[j]);
printf("\n");
#endif
/* output_dsp(Inbit,4,2);
input++;
*/

Differential(Inbit,ylast);
Convolutional(output);
inbit=Inbit;
*(out+3)=*(inbit+2);
*(out+4)=*(inbit+3);
p=4;
index=0;
for(k=0;k<4;k++)
{
if (*out==1)
 
  index=index+pow(2.00,(float)p);
out++;
  p--;
}
if (*out==1)
index++;
x=*(px+index);
y=*(py+index);
/*output_dsp(output,5,2);
output_dsp(&index,1,2);*/
output_dsp(&x,1,0);
output_dsp(&y,1,0);

#ifdef GCCmod
puts("new delaystate:");
for(j=0;j<3;j++)
printf("%d ",s[j]);
printf("\n\n");

printf("output is %d and its constellation cord: X=%f   Y=%f\n",index,x,y);
puts("output bit string is:");
for(j=0;j<4;j++)
printf("%d ",output[j]);
printf("%d\n\n",output[j]);
puts("---------------------------");
#endif

/*output_dsp(s,3,2);*/
out=output; 
if(p==0)  /*added to avoid having a func call at the
	end of for*/
j++;
else
j++;

}

}


void Differential(Inbit,ylast)
int *Inbit;
int *ylast;
{
int i;
int *out;
out=output;

*(out+1)=*Inbit^*(ylast+1);
*(out+2)=(*Inbit&*(ylast+1))^*(ylast+2)^*(Inbit+1);
*(ylast+1)=*(out+1);
*(ylast+2)=*(out+2);


} 
void Convolutional(output)
int *output;
{
int *a;
int *pts;
int s3to2;
int i;
a=and;
pts=s;
*output=*pts;
s3to2=*(output+2)^*(output+1)^*(pts+2);
*a=*pts&(*(pts+1)^*(output+2));
*(a+1)=*pts&*(output+1);
*(pts+2)=*pts;
*pts=*(pts+1)^*(output+2)^*(a+1);

*(pts+1)=s3to2^*a;
/**(a+1)=*pts&*(output+1);
*pts=*(pts+1)^*(output+2)^*(a+1);*/
/**output=*pts;
*(pts+2)=*pts;*/
}






