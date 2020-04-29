/* ************************************************************************ */
/*                                                                          */
/*          THE SOFTWARE IMPLEMENTATION OF A SOFT-DECISION                  */
/*                  SEQUENTIAL DECODING ALGORITHM                           */
/*                 FOR A (32,16) EXTENDED BCH CODE                          */
/*                         version 1.0                                      */
/*                                                                          */
/* Author: Stephen Ho                                                       */
/* Date  : Feb., 1994                                                       */
/*                                                                          */
/* ************************************************************************ */

#include <stdio.h>
#include <math.h>
#include <time.h>

#define n 32       /* length of each code word */
#define k 16       /* number of information bits in each codeword */
#define Q 58       /* each received bit is magnified by Q */
#define MAXSIZE 58 /* maximum number of nodes in the stack */
#define TRUE 1     /* boolean algebra */
#define FALSE 0    /* boolean algebra */
#define GROUP 2    /* we "group" every 8 bit into 1 element */
#define SNR 10     /* signal-to-noise ratio in dB */
#define TRIALNUMBER 10000
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
unsigned char q0[n] = {128, 64, 32, 16, 8, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 200, 100, 50, 25, 196,
                       170, 157, 134, 139, 69, 234, 117, 242, 177, 144, 143};
unsigned char q1[n] = {0, 0, 0, 0, 0, 0, 0, 0, 128, 64, 32, 16, 8, 4, 2, 1, 120, 60, 30, 15, 255,
                       7, 123, 197, 26, 141, 190, 95, 215, 19, 241, 175};
unsigned char *T[GROUP] = {q0, q1};

/*      w[i] represents the weight of i in binary. */
unsigned char w[256] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1,
                        0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0,
                        0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1,
                        0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
                        0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1,
                        0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0,
                        0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};

/*   (unit0[i],unit1[i]) represents a vector with 1 at ith position and zeros */
/* elsewhere. */
unsigned char unit0[16] = {128, 64, 32, 16, 8, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char unit1[16] = {0, 0, 0, 0, 0, 0, 0, 0, 128, 64, 32, 16, 8, 4, 2, 1};
unsigned char *unit[GROUP] = {unit0, unit1};
float r[n];

unsigned char M[n];      /* branch metric */
unsigned char update[n]; /* update vector */

/* Each key is a MAXSIZE-entry array. */
unsigned char level[MAXSIZE];
short acc_metric[MAXSIZE];
unsigned char stlabel[GROUP][MAXSIZE];
char next[MAXSIZE];
char prior[MAXSIZE];

char start, last, topnode, newnode;
char freestart, freelast;
unsigned char listsize, Decoded, Terminate, insert_at;
short best;                     /* accumulated metric of the best sequence so far. */
unsigned char bestlabel[GROUP]; /* state label of the best sequence so far. */
unsigned char brhlabel;

main()
{
    long count;

    for (count = 0; count < TRIALNUMBER; count++)
    {
        GenRxVector(count);
        CompBrhMetric();
        InitializeList();

        do
        {
            /*    if the level of topnode is equal to n or the stack is */
            /* empty, terminate the decoding algorithm. */
            if (level[start] == n || start == -1)
                Decoded = TRUE;
            else
            {
                topnode = start;
                AllocateNewnode();
                Divergence();
                if (level[start] < k)
                {
                    if (acc_metric[newnode] < best)
                    {
                        listsize = listsize + 1;
                        InsertList(newnode);
                        /*   Stack overflow.  The last node in the linked- */
                        /* list will be deleted. */
                        if (listsize == MAXSIZE)
                            Overflow();
                    }
                    else
                        /* Free memory space of newnode. */
                        FreeOneNode(newnode);
                }
                else
                {
                    /*  The nodes reached level k. */
                    UnlinkTopnode();
                    do
                    {
                        Extension();
                    } while (level[topnode] < n);

                    if (acc_metric[topnode] > acc_metric[newnode])
                    {
                        FreeOneNode(topnode);
                        if (acc_metric[newnode] < best)
                            CompletePath(newnode);
                        else
                        {
                            listsize = listsize - 1;
                            FreeOneNode(newnode);
                        }
                    }
                    else
                    {
                        FreeOneNode(newnode);
                        if (acc_metric[topnode] < best)
                            CompletePath(topnode);
                        else
                        {
                            listsize = listsize - 1;
                            FreeOneNode(topnode);
                        }
                    }
                }
            }
        } while (!Decoded);
    }
}

void GenRxVector(seed) /* Compute received vectors. */
    int seed;
{
    register int j;
    double sigma = sqrt(0.5 * exp10(-0.1 * SNR));
    double U1, U2;
    long ltime = time(NULL);
    int stime = (unsigned)(ltime / 2 + seed);
    /*  Use the current time as the seed for the random numbers generator. */
    srand(stime);
    for (j = 0; j < n; j++)
    {
        do
        {
            U1 = (double)((rand() % 2147483647) / 2147483647.0);
            U2 = (double)((rand() % 2147483647) / 2147483647.0);
        } while (U1 == 0 || U1 == 1 || U2 == 0 || U2 == 1);
        /*  Suppose -1 is transmitted. */
        r[j] = sigma * sqrt(-2.0 * log(U1)) * cos(2 * PI * U2) - 1.0;
    }
}

void CompBrhMetric() /* Compute branch metric and update vector. */
{
    register int i, j;
    float metric;

    for (i = 0; i < n; i++)
    {
        if (r[i] < 0)
        {
            /* Branch metric of branch with branch label=0 equals to zero. */
            update[i] = 0;
            metric = (float)((-Q * r[i]) + 0.5);
            M[i] = (unsigned char)(metric);
        }
        else
        {
            metric = (float)((Q * r[i]) + 0.5);
            M[i] = (unsigned char)(metric);
            /* Branch metric of branch with branch label=1 equals to zero. */
            update[i] = 1;
        }
    }
}

void InitializeList() /* Initialize the linked-list by setting all keys 0. */
{
    register int i;

    best = 32767; /* 2^15 - 1 = 32767 */
    bestlabel[0] = 0;
    bestlabel[1] = 0;
    Decoded = FALSE;
    freestart = -1; /* empty freelist */
    freelast = -1;
    start = 0; /* First node in the list is given an index 0. */
    last = start;
    level[start] = 0;
    acc_metric[start] = 0;
    for (i = 0; i < GROUP; i++)
        stlabel[i][start] = 0;
    next[start] = -1;
    prior[start] = -1;
    listsize = 1;
}

void AllocateNewnode() /* Allocate memory space for newnode. */
{
    if (freestart == -1)    /* If freelist is empty, using the node with */
        newnode = listsize; /* index equals to listsize. */
    else                    /* Otherwise, use the first node of the free */
    {                       /* list. */
        newnode = freestart;
        freestart = next[freestart];
    }
}

void Divergence() /* Update topnode and newnode in divergence mode. */
{
    register int i;

    /* For code in systematic form, branch label of the original node is */
    /* always 0. */
    if (update[level[topnode]] == 0)
    {
        for (i = 0; i < GROUP; i++)
            stlabel[i][newnode] = stlabel[i][topnode] ^ unit[i][level[topnode]];
    }
    else /* Update state label of topnode. */
    {
        for (i = 0; i < GROUP; i++)
        {
            stlabel[i][newnode] = stlabel[i][topnode];
            stlabel[i][topnode] = stlabel[i][topnode] ^ unit[i][level[topnode]];
        }
    }
    acc_metric[newnode] = acc_metric[topnode] + M[level[topnode]];
    level[topnode] = level[topnode] + 1;
    level[newnode] = level[topnode];
}

void Overflow() /* Check stack overflow. */
{
    listsize = listsize - 1;
    freestart = last;
    freelast = last;
    last = prior[last];
    prior[freestart] = -1;
    next[last] = -1;
}

void UnlinkTopnode() /* Unlink the topnode from the stack. */
{
    if (next[topnode] != -1)
    {
        start = next[topnode];
        prior[start] = -1;
    }
    prior[topnode] = -1;
    next[topnode] = -1;
}

void Extension() /* Update topnode and newnode in extension mode. */
{
    register int i;

    brhlabel = 0;
    for (i = 0; i < GROUP; i++)
        brhlabel = brhlabel + (w[stlabel[i][topnode] & T[i][level[topnode]]]);
    brhlabel = brhlabel % 2;
    if (brhlabel != update[level[topnode]])
        acc_metric[topnode] = acc_metric[topnode] + M[level[topnode]];
    level[topnode] = level[topnode] + 1;

    brhlabel = brhlabel ^ T[1][level[topnode]];
    if (brhlabel != update[level[newnode]])
        acc_metric[newnode] = acc_metric[newnode] + M[level[newnode]];
    level[newnode] = level[newnode] + 1;
}

void CompletePath(path) /* Insert a node at level n. */
    char path;          /* `path' is the index of the path with smaller */
{                       /* accumulated metric. */
    register int i;
    best = acc_metric[path];
    for (i = 0; i < GROUP; i++)
        bestlabel[i] = stlabel[i][path];
    InsertList(path);

    /* If a complete path is not inserted at the last spot, nodes below */
    /* can be free. */
    if (insert_at != listsize)
    {
        next[freelast] = next[path];
        freelast = last;
        last = path;
        next[last] = -1;
        listsize = insert_at;
    }
}

void FreeOneNode(current) /* Free memory space of one node. */
    char current;         /* `current' is the index of the deleting node. */
{
    if (freestart == -1)
    {
        freestart = current;
        freelast = current;
        next[freelast] = -1;
        prior[freelast] = -1;
    }
    else
    {
        next[current] = freestart;
        freestart = current;
    }
}

void InsertList(new)   /* Insert new node to the stack. */
    unsigned char new; /* `new' is the index of the inserting node. */
{
    char old, current;
    current = start;
    old = -1;
    insert_at = 1;

    while (current != -1)
    {
        if ((acc_metric[current] < acc_metric[new]) || ((acc_metric[current] == acc_metric[new]) && (level[current] > level[new])))
        {
            old = current;
            current = next[current];
            insert_at = insert_at + 1;
        }
        else /* sorted in increasing order of accumulated metric */
        {
            if (prior[current] != -1)
            {
                next[old] = new;
                next[new] = current;
                prior[new] = old;
                prior[current] = new;
                return;
            }
            else /* new first node */
            {
                next[new] = current;
                prior[new] = -1;
                prior[current] = new;
                start = new;
                return;
            }
        }
    }

    next[old] = new; /* new last node */
    next[new] = -1;
    prior[new] = old;
    last = new;
}
