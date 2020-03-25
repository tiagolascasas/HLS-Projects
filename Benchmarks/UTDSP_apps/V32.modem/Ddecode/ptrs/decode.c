/* 
   Trellis Decoding Algorithm for V.32 Modem
   Dept. of Electrical and Computer Engineering, University of Toronto   
   Kevin Fung   -   July,94 
*/
#include "traps.h"

#define Infinity 10000
#define Q     -1
#define NumTimePeriods 16 
#define NumDelayStates 8
#define NumPath_States 8
#define LARGE 1.0000
#define SMALL 1.0000
#define ABOVE 1
#define BELOW 0

float    dump1,dump2,dump3,dump4;
float    MinPath_dist [NumTimePeriods*2*NumDelayStates];
/* Min. Path PathState */
int      MinPath_ps   [NumTimePeriods*2*NumDelayStates];
/* BoundaryArea - (i.e. The 8 closet point to the input) */
int      BA [NumPath_States];
float    *Min_Path_dist;
int      *Min_Path_ps;

float    ConstellationX[32]={ 
-4.00,0.00,0.00,4.00,4.00,0.00,0.00,-4.00,-2.00,-2.00,2.00,2.00,2.00,2.00,-2.00,-2.00,-3.00,1.00,-3.00,1.00,3.00,-1.00,3.00,-1.00,1.00,-3.00,1.00,1.00,-1.00,3.00,-1.00,-1.00
};
float    ConstellationY[32]={ 
1.00,-3.00,1.00,1.00,-1.00,3.00,-1.00,-1.00,3.00,-1.00,3.00,-1.00,-3.00,1.00,-3.00,1.00,-2.00,-2.00,2.00,2.00,2.00,2.00,-2.00,-2.00,4.00,0.00,0.00,-4.00,-4.00,0.00,0.00,4.00
};
/* Appendix C */
int      BitPattern[13*4*8] ={
0x2, 0x6, 0xb, 0xd, 0x13, 0x15, 0x1a, 0x1e, 0x2, 0x6, 0x9, 0xf, 0x13, 0x15, 0x1a, 0x1e, 0x2, 0x6, 0x9, 0xf, 0x11, 0x17, 0x1a, 0x1e, 0x2, 0x6, 0xb, 0xd, 0x11, 0x17, 0x1a, 0x1e, 2, 0x6, 0xb, 0xd, 0x13, 0x14, 0x1a, 0x1d, 0x2, 0x6, 0x9, 0xf, 0x12, 0x15, 0x19, 0x1e, 0x2, 0x6, 0x9, 0xf, 0x10, 0x17, 0x19, 0x1e, 0x2, 0x6, 0xb, 0xd, 0x11, 0x16, 0x1a, 0x1d, 0x3 ,0x4, 0xb, 0xd, 0x13, 0x14, 0x1a, 0x1d, 0x0, 0x7, 0x9, 0xf, 0x12, 0x15, 0x19, 0x1e, 0x0, 0x7, 0x9, 0xf, 0x10, 0x17, 0x19, 0x1e, 0x3, 0x4, 0xb, 0xd, 0x11, 0x16, 0x1a, 0x1d, 0x2, 0x5, 0xa, 0xd, 0x13, 0x15, 0x1a, 0x1e, 0x2, 0x5, 0x8, 0xf, 0x13, 0x15, 0x1a, 0x1e, 0x1, 0x6, 0x9, 0xe, 0x11, 0x17, 0x1a, 0x1e, 0x1, 0x6, 0xb, 0xc, 0x11, 0x17, 0x1a, 0x1e, 0x2 ,0x5, 0xa, 0xd, 0x13, 0x14, 0x1a, 0x1d, 0x2, 0x5, 0x8, 0xf, 0x12, 0x15, 0x19, 0x1e, 0x1, 0x6, 0x9, 0xe, 0x10, 0x17, 0x19, 0x1e, 0x1, 0x6, 0xb, 0xc, 0x11, 0x16, 0x1a, 0x1d, 0x2,
0x5, 0xa, 0xd, 0x13, 0x15, 0x18, 0x1f, 0x2, 0x5, 0x8, 0xf, 0x13, 0x15, 0x18, 0x1f, 0x1, 0x6, 0x9, 0xe, 0x11, 0x17, 0x1b, 0x1c, 0x1, 0x6, 0xb, 0xc, 0x11, 0x17, 0x1b, 0x1c, 0x3, 0x4, 0xa, 0xd, 0x13, 0x14, 0x1a, 0x1d, 0x0, 0x7, 0x8, 0xf, 0x12, 0x15, 0x19, 0x1e, 0x0, 0x7, 0x9, 0xe, 0x10, 0x17, 0x19, 0x1e, 0x3, 0x4, 0xb, 0xc, 0x11, 0x16, 0x1a, 0x1d, 0x2, 0x5, 0xa, 0xd, 0x13, 0x14, 0x18, 0x1f, 0x2, 0x5, 0x8, 0xf, 0x12, 0x15, 0x18, 0x1f, 0x1, 0x6, 0x9, 0xe, 0x10, 0x17, 0x1b, 0x1c, 0x1, 0x6, 0xb, 0xc, 0x11, 0x16, 0x1b, 0x1c, 0x3, 0x5, 0xa, 0xd, 0x13, 0x14, 0x18, 0x1d, 0x0, 0x5, 0x8, 0xf, 0x12, 0x15, 0x19, 0x1f, 0x1, 0x7, 0x9, 0xe, 0x10, 0x17, 0x19, 0x1c, 0x1, 0x4, 0xb, 0xc, 0x11, 0x16, 0x1b, 0x1d, 0x2, 0x5, 0xa, 0xd, 0x13, 0x14, 0x18, 0x1d, 0x2, 0x5, 0x8, 0xf, 0x12, 0x15, 0x19, 0x1f, 0x1, 0x6, 0x9, 0xe, 0x10, 0x17, 0x19, 0x1c, 0x1, 0x6, 0xb, 0xc, 0x11, 0x16, 0x1b, 0x1d, 0x3,
0x5, 0xa, 0xd, 0x13, 0x14, 0x1a, 0x1d, 0x0, 0x5, 0x8, 0xf, 0x12, 0x15, 0x19, 0x1e, 0x1, 0x7, 0x9, 0xe, 0x10, 0x17, 0x19, 0x1e, 0x1, 0x4, 0xb, 0xc, 0x11, 0x16, 0x1a, 0x1d, 0x3, 0x4, 0xa, 0xd, 0x13, 0x14, 0x18, 0x1d, 0x0, 0x7, 0x8, 0xf, 0x12, 0x15, 0x19, 0x1f, 0x0, 0x7, 0x9, 0xe, 0x10, 0x17, 0x19, 0x1c, 0x3, 0x4, 0xb, 0xc, 0x11, 0x16, 0x1b, 0x1d, 0x3, 0x5, 0xa, 0xd, 0x13, 0x14, 0x18, 0x1f, 0x0, 0x5, 0x8, 0xf, 0x12, 0x15, 0x18, 0x1f, 0x1, 0x7, 0x9, 0xe, 0x10, 0x17, 0x1b, 0x1c, 0x1, 0x4, 0xb, 0xc, 0x11, 0x16, 0x1b, 0x1c} 
;

float    input[1000];

/* Return the previous delaystate given the 
 	pathstate and the present delaystate */
int      PathTable[NumDelayStates*NumPath_States]={
0,3,1,2,Q,Q,Q,Q,
Q,Q,Q,Q,4,7,6,5,
1,2,0,3,Q,Q,Q,Q,
Q,Q,Q,Q,5,6,7,4,
2,1,3,0,Q,Q,Q,Q,
Q,Q,Q,Q,7,4,5,6,
3,0,2,1,Q,Q,Q,Q,
Q,Q,Q,Q,6,5,4,7
};

/* Return the next delaystate given the 
 	pathstate and the present delaystate */
int      PathTable2[NumDelayStates*NumPath_States]={
0,6,2,4,Q,Q,Q,Q,
2,4,0,6,Q,Q,Q,Q,
4,2,6,0,Q,Q,Q,Q,
6,0,4,2,Q,Q,Q,Q,
Q,Q,Q,Q,1,5,7,3,
Q,Q,Q,Q,3,7,5,1,
Q,Q,Q,Q,7,3,1,5,
Q,Q,Q,Q,5,1,3,7
};
/* For calculating pathstate */
int      Del_ta[NumPath_States]={0,4,0,4,0,4,0,4};
int      numInputRead;



void main()
{
void TrellisDecode();

numInputRead=input_dsp(input,Infinity,0);
TrellisDecode(input,ConstellationX,ConstellationY,PathTable,PathTable2,numInputRead);

} /* End of main() */


float EuclideanDistance (A_x,A_y,B_x,B_y)
float A_x;
float A_y;
float B_x;
float B_y;
{
return (sqrt((A_x-B_x)*(A_x-B_x) + (A_y-B_y)*(A_y-B_y)));
} /* End of EuclideanDistance() */


int diagonalY1 (I_x,I_y)
float I_x,I_y;
{
if (I_y>(I_x-1)) return ABOVE;
return BELOW;
}

int diagonalY2 (I_x,I_y)
float I_x,I_y;
{
if (I_y>(I_x+1)) return ABOVE;
return BELOW;
}

/* Find the 8 closet point */
void FindBoundary(CC_x,CC_y,Index)
float CC_x,CC_y;
int *Index;
{
float I_x,I_y;
int quadrant,region,j,k;
int temp;
int *pattern;
 
pattern=BitPattern;
/* Locate Quadrant */
if ((CC_x >  0 ) && (CC_y >= 0)) quadrant = 1 ;
if ((CC_x <= 0 ) && (CC_y >  0)) quadrant = 2 ;
if ((CC_x <  0 ) && (CC_y <= 0)) quadrant = 3 ;
if ((CC_x >= 0 ) && (CC_y <  0)) quadrant = 4 ;

/* Locate Region */
I_x=fabs(CC_x);
I_y=fabs(CC_y);
if ((I_x< 1 )&&(I_x>= 0 )&&(I_y< 1  )&&(I_y>= 0 ))
   region= 1;
else if ((I_x<1 )&&(I_x>=0 )&&(I_y<2 )&&(I_y>=1))
   region= 4;
else if ((I_x<1 )&&(I_x>= 0)&&(I_y>= 2 ))
   region= 6;
else if ((I_x< 2)&&(I_x>= 1 )&&(I_y<  1 )&&(I_y >= 0 ))
   region= 2;
else if ((I_x< 2)&&(I_x>= 1 )&&(I_y<  2 )&&(I_y >= 1 ))
   region= 5;
else if ((I_x>= 2)&&(I_y<  1 )&&(I_y>= 0 ))
   region= 3;
else if ((diagonalY1(I_x,I_y)==BELOW)&&(I_x>= 2)&&(I_y<2 )&&(I_y>=1 ))
   region= 7;
else if ((diagonalY1(I_x,I_y)==BELOW)&&(I_x>= 3)&&(I_y>= 2))
   region= 12;
else if ((I_x<2 )&&(I_x>= 1)&&(I_y<3 )&&(I_y>=2 )&&(diagonalY2(I_x,I_y)==BELOW))
   region= 10;
else if ((I_x<3 )&&(I_x>=2 )&&(I_y<2 )&&(I_y>=1 )&&(diagonalY1(I_x,I_y)==ABOVE))
   region= 11;
else if ((I_x>=2 )&&(I_y>=2 )&&(diagonalY1(I_x,I_y)==ABOVE)&&(diagonalY2(I_x,I_y)==BELOW))
   region= 9;
else if ((I_x<2 )&&(I_x>=1 )&&(I_y>=2 )&&(diagonalY2(I_x,I_y)==ABOVE))
   region= 8;
else if ((I_x>= 2)&&(I_y>=3 )&&(diagonalY2(I_x,I_y)==ABOVE))
   region= 13;
else 
   region= Infinity;  /* bomb out */

/* Assign ConstellationCoord Index No. */
for (j=0;j<NumPath_States;j++){
     temp=*(pattern+(region-1)*4*8+(quadrant-1)*8+(j));
     *Index=temp;
     Index++;
}
} /* End of FindBoundary() */


int temp1;

void TrellisDecode (input,Constellation_X,Constellation_Y,PathTable,PathTable2,NIR)
float *input;
float *Constellation_X;
float *Constellation_Y;
int   *PathTable;
int   *PathTable2;
int   NIR;
{
int      T,time,i,p,s,j,c,k;
int      outpattern,prev_outpattern;
float    PathDist[NumDelayStates];
float    *Path_Dist;
int      DelayState, Path_State; /* Used for traceback */
float    I_x,I_y;
float    minPath_StateDist;
float    outdist;
float    accumdist,min_accum_dist;
int      Y1n,Y2n,Q1n,Q2n; 
int      temp2,temp3,temp4;
int      *BoundaryArea;
float    mim_dist;
int      mim_ps;
int      *Delta;

/* Initialization of variable */
T=0;
prev_outpattern=0;
Delta=Del_ta;
Path_Dist=PathDist;
BoundaryArea=BA;
Min_Path_dist=MinPath_dist;
Min_Path_ps=MinPath_ps;
for (i=0;i< NumDelayStates;i++)
   *(Min_Path_dist+i)=0.00;
for (i=0;i<(NIR/2)+NumTimePeriods;i++){
#ifdef GCCmod
printf ("---------------------------------------------- \n");
#endif

/* Viterbi Decoding Begin */

I_x = *input++;
I_y = *input++;
if (i<NIR/2){

/* Find the 8 closest points to the current Input */
FindBoundary(I_x,I_y,BoundaryArea);
#ifdef GCCmod
  printf("Viterbi: T  %i \n",T);
  printf("Viterbi: Input.x Input.y  %lf %lf \n",I_x,I_y);
#endif

k=0;
/* Compute the distance of the 8 points to the Input */
for (p=0;p<NumPath_States;p++){
   temp1=*(BoundaryArea+k);
   dump1=*(Constellation_X + temp1);
   dump2=*(Constellation_Y + temp1);
   *(Path_Dist+k)=EuclideanDistance(I_x,I_y,dump1,dump2);
#ifdef GCCmod
  printf("Viterbi: closet_point x y DIST: %i %lf %lf %lf \n",temp1,dump1,dump2,*(Path_Dist+k));
#endif
k++;
}

for (s=0;s<NumDelayStates;s++){
   mim_dist=(float) Infinity;
   p=*(Delta+s);
   for (c=0;c<4;c++){
        temp1=  *(PathTable +s*NumPath_States+p);
        dump1=  *(Min_Path_dist+T*NumDelayStates+temp1);
        dump2=  *(Path_Dist+p);
        accumdist= LARGE * dump1 + SMALL * dump2; 
        if (accumdist <mim_dist){
             mim_dist = accumdist;
             mim_ps = p;
        } /* end if */
        p++;
   }  /* end for (c,p) */
   *(Min_Path_dist+((T+1)%32)*NumDelayStates+s) = mim_dist;
   *(Min_Path_ps+((T+1)%32)*NumDelayStates+s) = mim_ps;
   #ifdef GCCmod
     printf("Viterbi: mim_dist mim_ps temp1 of T+1 %lf %i %i \n",mim_dist,mim_ps,temp1);
   #endif
} /* end for (s) */
}/* End of Viterbi Decoding */




/* Begin TraceBack at the 16th input */
if (i>=NumTimePeriods-1){

min_accum_dist = (float) Infinity;
/* Find the delay state with min_acc_dist at time T+1 */
for (s=0; s< NumDelayStates;s++){
#ifdef GCCmod
printf( "Traceback: MPd %lf \n",*(Min_Path_dist+((T+1)%32)*NumDelayStates+s));
#endif
   if (*(Min_Path_dist+((T+1)%32)*NumDelayStates+s)<min_accum_dist){
     DelayState=s;
     min_accum_dist=*(Min_Path_dist+((T+1)%32)*NumDelayStates+s);
   }
}

#ifdef GCCmod
printf( "Traceback: min_accum_dist DelayState %lf %i \n",min_accum_dist,DelayState);
#endif
/* Find path state at time T-NumTimePeriods on path ending at DelayState
    at time T */
for (time=0; time< NumTimePeriods;time++){
   temp1=*(Min_Path_ps+NumDelayStates*((((T+1)%32-time)%32+32)%32)+DelayState);
#ifdef GCCmod
printf( "Traceback: DelayState Time %i %i \n",DelayState,((T+1)%32-time));
#endif
   DelayState=*(PathTable+DelayState*NumPath_States+temp1);
#ifdef GCCmod
printf( "Traceback: DelayState Path %i %i \n",DelayState,temp1);
#endif
}
/*
Path_State= *(Min_Path_ps+(((T-(NumTimePeriods-1)+1)%32+32)%32)*NumDelayStates+DelayState); 
*/

Path_State=temp1;

#ifdef GCCmod
printf( "Traceback: Path_State %i \n",Path_State);
#endif

minPath_StateDist=(float) Infinity;
dump1=*(input-2*NumTimePeriods);
dump2=*(input-2*NumTimePeriods+1);
#ifdef GCCmod
printf( "Traceback: I_x I_y %lf %lf \n",dump1,dump2);
#endif
for (c=0;c<4;c++){
dump3=*(Constellation_X+((Path_State<<2)|c));
dump4=*(Constellation_Y+((Path_State<<2)|c));
outdist=EuclideanDistance(dump1,dump2, dump3,dump4);
if (outdist<minPath_StateDist){
    minPath_StateDist=outdist;
    outpattern=(Path_State<<2)|c;
}
}
#ifdef GCCmod
printf( "Traceback: outpattern %i \n",outpattern);
#endif


/* Begin Differential Decoding */
Y1n=(outpattern&0x8)>>3;
Y2n=(outpattern&0x4)>>2;
Q1n=Y1n^((prev_outpattern&0x8)>>3);
Q2n=((Q1n&((prev_outpattern&0x8)>>3)))^((prev_outpattern&4)>>0x2)^(Y2n);
/* End of Differential Decoding */
#ifdef GCCmod
printf( "Traceback: Y1n Y2n Q1n Q2n %i %i %i %i \n",Y1n,Y2n,Q1n,Q2n);
#endif

temp1=(Q1n<<3)+(Q2n<<2)+(outpattern&0x3);
if ( i < ((NIR/2)+NumTimePeriods-4))
output_dsp(&temp1,1,2);
#ifdef GCCmod
printf( "Traceback: output+i %i \n",(Q1n<<3)+(Q2n<<2)+(outpattern&0x3));
#endif
prev_outpattern=outpattern;

}/* End of TraceBack */


T=(T+1)%(NumTimePeriods*2);
} /* end for (i) */
} /* end of TrellisDecode() */

