#include "traps.h"
/*#define NumofInput 115*/
#define NoiseFactor 1/5   /*overall average*/
#define NoiseDegree 0.42 /*coordinates off by 20%*/


float Input[2];
float output[2];
int end;
/*signed*/ float I_x;
/*signed */float I_y;
signed int x;
int  a;
int b;
float snr;
int count=0;
int noise=0;
main()
{
float *out;
float *in;
/*int count=0;
int noise=0;*/
int total=0;
out=output;
in=Input;

while(1){
x=input_dsp(Input,2,0);
if (!x) break;	
total++;		
I_x=*in;
I_y=*(in+1);
/*output_dsp(&I_x,1,0);
output_dsp(&x,1,2);*/

/*input_dsp(Input,1,0);
I_y=*in;*/
		/*input_dsp(&end,1,2);
		if (!end) break;

output_dsp(&I_y,1,0);*/

a=fabs(I_x);
b=fabs(I_y);

if (a>=b)
   {

     *out=
I_x*((a>2)?(1+NoiseDegree):(1-NoiseDegree));
    
*(out+1)=I_y*((b<=2)?(1+NoiseDegree):(1-NoiseDegree));
noise++;
   }
else{



   *out= I_x;
   *(out+1)= I_y;

}

output_dsp(output,2,0);
}
snr=(float)(noise*100)/total;
/*output_dsp(&snr,1,0);*/
if (*out==0)
count++;
 }
