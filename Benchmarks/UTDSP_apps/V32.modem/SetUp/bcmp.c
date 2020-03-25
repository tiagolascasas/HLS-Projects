/*
  The code is to compare two binary files: clearout & noisedout
   and give out the hit rate. It will brake if one file exhausts.
   		
				-----Zhuoyu Yuan   Aug, 94
*/ 
#include <stdio.h>
#include <string.h>

void main (void)
{
FILE *a, *b;
char *no1,*no2;
int boolean;
int flag;
int TotalInput;
int MatchNo=0;
float rate;
int i=0;
int k=0;


a = fopen ("input","r");
b = fopen ("output","r");

no1=(char*)malloc( 80);
no2=(char*)malloc( 80);

while(1){
*no1=fgetc(a);
*no2=fgetc(b);
if (*no1==EOF&&*no2==EOF) {     /*since feof() will excuted twice for each
	                   	    file, it produce the correct EOF position.*/
flag=2;
boolean=1;
break;
}
/*printf("TotalInput=%d      MatchNo=%d\n",TotalInput,MatchNo);
printf("---------------------------\n");*/
if (*no1!=EOF)
{
/*   fread((char * ) no1,1,1,a);
   printf("  no1 = %s  	    ",no1);*/

}
else
{
   boolean = 0;
   flag=0;
         /*  if (fgetc(b)*no2==EOF)
             boolean = 1;
             flag=2;*/       
   break;
}
if (/*fgetc(b)*/*no2!=EOF)
{
  /* fread((char *) no2,1,1,b); */
/*   printf("  no2 = %s\n",no2); */
}
else
{
   boolean = 0;
   flag=1;
   break;
}

if (strcmp(no1,no2)==0) MatchNo++;       /*compare two characters*/
TotalInput++;

}
printf("\n\n");
puts("%%%%%%%%%%%%%%%%\n");
if ( boolean ==0&flag==1) printf("%s %d\n\n", "File {output} exhausts at",TotalInput);
if ( boolean ==0&flag==0) printf("%s %d\n\n", "File {input} exhausts at",TotalInput);
if ( boolean ==1&flag==2) printf("%s %d\n\n", "Both Files  exhaust at",TotalInput);

rate=(float)(MatchNo*100)/TotalInput;
puts("%%%%%%%%%%%%%%%%\n");
printf("TotalInput=%d      MatchNo=%d\n\n",TotalInput,MatchNo);

printf("Hit Rate=");
printf("%.3f",rate);
puts("%\n");

exit(0);
}
