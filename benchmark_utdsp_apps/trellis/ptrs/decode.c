/*
** 1993: Originally coded by Stephen Ho
** 1994: Ported to UofT DSP system by Yuan Zhuoyu
*/
#include "traps.h"

#define n 32            /* length of each code word */
#define k 16            /* number of information bits in each codeword */
#define Q 58            /* each received bit is magnified by Q */
#define MAXSIZE 58      /* maximum number of nodes in the stack */
#define TRUE 1          /* boolean algebra */
#define FALSE 0	        /* boolean algebra */
#define GROUP 2	        /* we "group" every 8 bit into 1 element */
#define SNR 10          /* signal-to-noise ratio in dB */
#define TRIALNUMBER 2
#define PI 3.14159255359

void GenRxVector();     /* Compute received vectors. */
void CompBrhMetric();   /* Compute branch metric and update vector. */
void InitializeList();  /* Initialize the linked-list by setting all keys 0. */
void AllocateNewnode(); /* Allocate memory space for newnode. */
void Divergence();      /* Update topnode and newnode in divergence mode. */
void Overflow();        /* Check stack overflow. */
void UnlinkTopnode();   /* Unlink the topnode from the stack. */
void Extension();       /* Update topnode and newnode in extension mode. */
void CompletePath();    /* Insert a node at level n. */
void FreeOneNode();     /* Free memory space of one node. */
void InsertList();      /* Insert new node to the stack. */

/*   Each qi[n] represents 8 rows of the trellis matrix; e.g. each element */
/* is 1 column of 8 bits.  For example, 192 represents a column vector of */
/* [1 1 0 0 0 0 0 0]. */
/*   T is a 2 x 16 matrix.  Each row of T actually represents 8 rows of the */
/* generator matrix. */
unsigned  int q0[n] = {128,64,32,16,8,4,2,1,0,0,0,0,0,0,0,0,200,100,50,25,196,
170,157,134,139,69,234,117,242,177,144,143};
unsigned  int q1[n] = {0,0,0,0,0,0,0,0,128,64,32,16,8,4,2,1,120,60,30,15,255,
7,123,197,26,141,190,95,215,19,241,175};

/*      w[i] represents the weight of i in binary. */
unsigned  int w[256] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,0,1,1,
0,1,0,0,1,1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,1,0,
0,1,0,1,1,0,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,1,
0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,
0,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,0,1,1,0,1,0,
0,1,1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};

/*   (unit0[i],unit1[i]) represents a vector with 1 at ith position and zeros */
/* elsewhere. */
unsigned  int unit0[16]={ 128, 64, 32, 16, 8, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned  int unit1[16]={ 0, 0, 0, 0, 0, 0, 0, 0, 128, 64, 32, 16, 8, 4, 2, 1};

float r[n];

unsigned  int M[n];             /* branch metric */
unsigned  int update[n];        /* update vector */

/* Each key is a MAXSIZE-entry array. */
unsigned  int level[MAXSIZE];
 int acc_metric[MAXSIZE];
unsigned  int stlabel[GROUP*MAXSIZE];
 int next[MAXSIZE];
 int prior[MAXSIZE];

 int start, last, topnode, newnode;
 int freestart, freelast;
unsigned  int listsize, Decoded, Terminate, insert_at;
 int best;	/* accumulated metric of the best sequence so far. */
unsigned  int bestlabel[GROUP];	/* state label of the best sequence so far. */
unsigned  int brhlabel;
float u1[32];
float u2[32];
float metric;



main()

{
int do1=1;
int do2=1;
int accnew;
int levelstart;
unsigned int *l;
int *acc;
int count;
int loopcount=0;
l=level; 
acc=acc_metric;




    for (count=0; count<TRIALNUMBER; count++)
    {
        GenRxVector(loopcount);
         
        CompBrhMetric();
        InitializeList();
        loopcount++;
levelstart=*(l+start);

        
 if (!Decoded || do1==1)
     {       
          do1++;
           if ( levelstart == n || start == -1)
                Decoded = TRUE;
            else
            {
                topnode = start;
               AllocateNewnode();
               Divergence();
               if ( levelstart < k )
                  {
                     accnew=*(acc+newnode);
                    if(  accnew < best )
                       {
                        listsize = listsize + 1;
                        InsertList(newnode);	
                        /*   Stack overflow.  The last node in the linked- */
                        /* list will be deleted. */
                        if (listsize == MAXSIZE )
                            Overflow();
                       }
                    else

                        FreeOneNode(newnode);
                 }
                  else
                {   
                    
                    UnlinkTopnode();
               if ( *(l+topnode)< n || do2==1){
				do2++;
                           Extension();       }
      
                    if ( *(acc+topnode) > *(acc+newnode) )
                    {
                        FreeOneNode(topnode);
                        if ( *(acc+newnode) < best )
                            CompletePath(newnode);
                        else
                        {
                            listsize = listsize - 1;
                            FreeOneNode(topnode);
                                                 
                        }  

                    }  
                    else
                    {
                        FreeOneNode(newnode);
                        if ( *(acc+topnode) < best )
                           { CompletePath(topnode);
                           }
                        else
                        {
                            listsize = listsize - 1;
                            FreeOneNode(topnode);

                              loopcount--;                       
                        }
                    }
  
     																											
                }
	
            } 
        } 
      }

/* Dump all global variables */
#define IOfp    0
#define IOint   1
#define IOuint  2
#define IObin   3

output_dsp(q0,n,IOuint);
output_dsp(q1,n,IOuint);
output_dsp(w,256,IOuint);
output_dsp(unit0,16,IOuint);
output_dsp(unit1,16,IOuint);

output_dsp(r,n,IOfp);

output_dsp(M,n,IOuint);             /* branch metric */
output_dsp(update,n,IOuint);        /* update vector */

output_dsp(level,MAXSIZE,IOuint);
output_dsp(acc_metric,MAXSIZE,IOuint);
output_dsp(stlabel,GROUP*MAXSIZE,IOuint);
output_dsp(next,MAXSIZE,IOint);
output_dsp(prior,MAXSIZE,IOint);

output_dsp(&start,1,IOint);
output_dsp(&last,1,IOint);
output_dsp(&topnode,1,IOint);
output_dsp(&newnode,1,IOint);
output_dsp(&freestart,1,IOint);
output_dsp(&freelast,1,IOint);
output_dsp(&best,1,IOint); /* accumulated metric of the best sequence so far. */

output_dsp(&listsize,1,IOuint);
output_dsp(&Decoded,1,IOuint);
output_dsp(&Terminate,1,IOuint);
output_dsp(&insert_at,1,IOuint);
output_dsp(&brhlabel,1,IOuint);

output_dsp(bestlabel,GROUP,IOuint); /*state label of the best sequence so far.*/

output_dsp(u1,32,IOfp);
output_dsp(u2,32,IOfp);
output_dsp(&metric,1,IOfp);
}

void GenRxVector(seed)   /* Compute received vectors. */
int seed;
{
float *U1;
float *U2;

float *ptr;
float a;
float c;
int j;
int i;
U1=u1;
U2=u2;
ptr=r;

input_dsp(u1,32,0);
input_dsp(u2,32,0);
a=*U1++;
c=*U2++;

    for (j=1; j<32; j++)
    {
  *ptr= sqrt(0.5*exp(-0.1*10))*sqrt(-2.0*log(a))*cos(2*PI*c)-1.0; 
        a= *U1++;
        c= *U2++;
 

    } 
 *ptr= sqrt(0.5*exp(-0.1*10))*sqrt(-2.0*log(a))*cos(2*PI*c)-1.0;

/*output_dsp(r,32,0);*/

}


void CompBrhMetric()   /* Compute branch metric and update vector. */
{
int i;

int j;
float a;

float *ptr;
float arrayr;
int flag;
unsigned  int *m;

unsigned  int *up;
up=update;
ptr=r;
m=M;
a=*ptr++;
             /* shows the last condition control to avoid ptr++ overflow*/
    for (i=1; i<n; i++)
    {
        if ( a < 0 )
        { 
            /* Branch metric of branch with branch label=0 equals to zero. */
            *up++ = 0;
            metric = (-Q*a)*10;
            *m++ = ( int)(metric);
           a=*ptr++;
flag=-1;
        }
        else
        {
            metric = (Q*a)*10;

            *m++ = ( int)(metric);
            /* Branch metric of branch with branch label=1 equals to zero. */
            *up++ = 1;
           a=*ptr++;
flag=1;
        }
    }
	if (flag=-1)
	{
	*up=0;
	metric = (-Q*a)*10;
	*m=(  int)(metric);
	}
	else
	{
	metric = (Q*a)*10;
	*m= ( int)(metric);
	*up = 1;
	}
}
void InitializeList() /* Initialize the linked-list by setting all keys 0. */
{
register int i;
unsigned  int *b;
unsigned int *l;
int *acc;
int *ne;
unsigned int *st;
int *p;
int K=0;
p=prior;
st=stlabel;
b=bestlabel;
l=level;
ne=next;
acc=acc_metric;

    best = 32767;       /* 2^15 - 1 = 32767 */
    *b = 0;
    *(b+1) = 0;
    Decoded = FALSE;
    freestart = -1;     /* empty freelist */
    freelast = -1;
    start = 0;	        /* First node in the list is given an index 0. */
    last = start;
    *(l+start) = 0;
    *(acc+start) = 0;
    for (i=0; i<GROUP; i++)
     {   *(st+k*MAXSIZE+start) = 0;
        K++;}
    *(ne+start) = -1;
    *(p+start) = -1;
    listsize = 1;
}

void AllocateNewnode()   /* Allocate memory space for newnode. */
{
int *ne;
ne=next;
    if (freestart == -1)        /* If freelist is empty, using the node with */
        newnode = listsize;     /* index equals to listsize. */
    else                        /* Otherwise, use the first node of the free */
    {                           /* list. */
        newnode = freestart;
        freestart = *(ne+freestart);
    }
}
void Divergence()   /* Update topnode and newnode in divergence mode. */{
    register int i;
unsigned *up;
int *ne;
unsigned  int *st;
int *acc;
unsigned int *l;
unsigned int *un0;
unsigned int *un1;
int a;
int K;
int count=0;
unsigned int *m;
int vofup;
m=M;
up=update;
ne=next;
st=stlabel;
acc=acc_metric;
l=level;
un0=unit0;
un1=unit1;

vofup=*(up+*(l+topnode));
K=0;
    /* For code in systematic form, branch label of the original node is */
    /* always 0. */   
    if ( vofup == 0 )
    {
        for ( i=0; i<GROUP; i++ )
        if (count==0){
a=*(un0+*(l+topnode));
 count++;       } 
else
a=*(un1+*(l+topnode));
            *(st+k*MAXSIZE+newnode) = *(st+k*MAXSIZE+topnode)^a;
K++;
    }

else        /* Update state label of topnode. */
    {
         K=0;
        for ( i=0; i<GROUP; i++ )
        {
if (count==1){
a=*(un0+*(l+topnode));
count--;      }
else
a=*(un1+*(l+topnode));
           *(st+k*MAXSIZE+newnode) = *(st+k*MAXSIZE+topnode);
            *(st+k*MAXSIZE+topnode) = *(st+k*MAXSIZE+topnode)^a;
K++;
        }
    }
    *(acc+newnode) = *(acc+topnode) + *(m+*(l+topnode));
    *(l+topnode) = *(l+topnode) + 1;
    *(l+newnode) =*( l+topnode);
}

void InsertList(new)   /* Insert new node to the stack. */
unsigned  int new;     /* `new' is the index of the inserting node. */
{
int old;
int   current;
unsigned int *l;
int *acc;
int *ne;
int *p;
int a;
int accnew;
int acccur;
p=prior;
ne=next;
acc=acc_metric;
l=level;




    current = start;
    old = -1;
    insert_at = 1;

    while ( current != -1 )
    {
        if ( (*(acc+current) < *(acc+new))
            || ((*(acc+current) == *(acc+new))
            && (*(l+current) > *(l+new))) )
        {
            old = current;
            current = *(ne+current);
            insert_at = insert_at + 1;
        }
        else    /* sorted in increasing order of accumulated metric */
        {
a=*(p+current);

            if ( a != -1 )
            {
                *(ne+old) = new;
                *(ne+new)= current;
                *(p+new) = old;
                *(p+current) = new;
                return;
            }
            else    /* new first node */
            {
                *(ne+new) = current;
                *(p+new) = -1;
                *(p+current) = new;
                start = new;
                return;
            }
        }
    }
   
    *(ne+old) = new;    /* new last node */
    *(ne+new) = -1;
    *(p+new) = old;
    last = new;
}

void Overflow()   /* Check stack overflow. */
{
int *p;
int *ne;
p=prior;
ne=next;

    listsize = listsize - 1;
    freestart = last;
    freelast = last;
    last =*(p+last);
    *(p+freestart) = -1;
    *(ne+last) = -1;
}
void UnlinkTopnode()     /* Unlink the topnode from the stack. */
{
int *p;
int *ne;
int vofne;
p=prior;
ne=next;
vofne=*(ne+topnode);
    if ( vofne != -1 )
    {
        start = *(ne+topnode);
        *(p+start) = -1;
    }
    *(p+topnode) = -1;
    *(ne+topnode) = -1;
}
void Extension()   /* Update topnode and newnode in extension mode. */
{
    register int i;
unsigned int *l;
unsigned int *up;
int *acc;
unsigned int *m;
unsigned int *ptw;
unsigned int *st;
unsigned int *b;
int a;
int c;
int upv;
int upnew;
unsigned int *t0;
unsigned int *t1;
int d=0;
int count=0;
b=bestlabel;
acc=acc_metric;
l=level;
up=update;
st=stlabel;
m=M;
ptw=w;
t0=q0;
t1=q1;
upv=*(up+*(l+topnode));
upnew=*(up+*(l+newnode));
    brhlabel = 0;
    for (i=0; i<GROUP; i++){
a=*(st+d*MAXSIZE+topnode);
d++;
                                       }
if(count==0){
c=*(t0+*(l+topnode));
count++;      }
else
c=*(t1+*(l+topnode));
         brhlabel = brhlabel + *(w+(a&c));
    brhlabel = brhlabel % 2;
    if ( brhlabel != upv )
        *(acc+topnode) =*(acc+topnode)+*(m+*(l+topnode));
    *(l+topnode) = *(l+topnode) + 1;
c=*(t1+*(l+topnode));
    brhlabel = brhlabel^c;
    if ( brhlabel != upnew )
        *(acc+newnode) =*(acc+newnode)+*(m+*(l+newnode));
    *(l+newnode) = *(l+newnode) + 1;
}

void CompletePath(path)   /* Insert a node at level n. */
 int path;                /* `path' is the index of the path with smaller */
{                         /* accumulated metric. */
    register int i;
int *acc;
unsigned int *b;
unsigned int *st;
int *ne;
int K=0;
ne=next;
acc=acc_metric;
b=bestlabel;
st=stlabel;

    best = *(acc+path);
    for (i=0; i<GROUP; i++)
       {
        *(b+k) = *(st+k*MAXSIZE+path);
         K++;
       }
    InsertList(path);

    /* If a complete path is not inserted at the last spot, nodes below */
    /* can be free. */
    if ( insert_at != listsize )
    {
        *(ne+freelast) = *(ne+path);
        freelast = last;
        last = path;
       *(ne+last) = -1;
        listsize = insert_at;
    }
}


void FreeOneNode(current)   /* Free memory space of one node. */
 int current;               /* `current' is the index of the deleting node. */
{
int *ne;
int *p;
p=prior;
ne=next;

    if ( freestart == -1 )
    {
        freestart = current;
        freelast = current;
        *(ne+freelast) = -1;
        *(p+freelast) = -1;
    }
    else
    {
        *(ne+current) = freestart;
        freestart = current;
    }
}

