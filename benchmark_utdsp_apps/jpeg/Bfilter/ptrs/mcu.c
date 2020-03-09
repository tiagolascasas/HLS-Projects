/*
 * mcu.c --
 *
 * Support for MCU allocation, deallocation, and printing.
 *
 */

/*
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
*/
#include "traps.h"
#include "jpeg.h"
#include "rle.h"
#include "proto.h"

MCU *mcuTable; 
MCU ban1[6];
/*char*/int ban23[768];
int numMCU;
int currMCU;

/*
 *--------------------------------------------------------------
 *
 * MakeMCU, InitMcuTable --
 *
 *	InitMcuTable does a big malloc to get the amount of memory
 *	we'll need for storing MCU's, once we know the size of our
 *	input and output images.
 *	MakeMCU returns an MCU for input parsing.
 *
 * Results:
 *	A new MCU
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */
void
InitMcuTable(numMCU,blocksInMCU)
    int numMCU;
    int blocksInMCU;
{
    int i, mcuSize;
    /*char*/int *buffer;

    /*
     * Compute size of on MCU (in bytes).  Round up so it's on a
     * boundary for any alignment.  In this code, we assume this
     * is a whole multiple of sizeof(double).
     */
    mcuSize = blocksInMCU * sizeof(RLE);
    mcuSize = JroundUp(mcuSize,sizeof(/*double*/float));

    /*
     * Allocate the MCU table, and a buffer which will contain all
     * the data.  Then carve up the buffer by hand.  Note that
     * mcuTable[0] points to the buffer, in case we want to free
     * it up later.
     */
    mcuTable = (MCU *)ban1;  /*(MCU *)malloc(numMCU * sizeof(MCU));*/
    buffer   = (/*char*/int*)ban23;  /*(char *)malloc(numMCU * mcuSize);*/
    for (i=0; i<numMCU; i++) {
	mcuTable[i] = (MCU)(buffer + i*mcuSize);
    }
}

#define MakeMCU(dcPtr)		(mcuTable[numMCU++])
