/*
 * mcu.c --
 *
 * Support for MCU allocation, deallocation, and printing.
 *
 * Copyright (c) 1993 Brian C. Smith, The Regents of the University
 * of California
 * All rights reserved.
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF
 * CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "jpeg.h"
#include "rle.h"
#include "proto.h"

MCU *mcuTable;
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
    InitMcuTable(numMCU, blocksInMCU) int numMCU;
int blocksInMCU;
{
    int i, mcuSize;
    char *buffer;

    /*
     * Compute size of on MCU (in bytes).  Round up so it's on a
     * boundary for any alignment.  In this code, we assume this
     * is a whole multiple of sizeof(double).
     */
    mcuSize = blocksInMCU * sizeof(RLE);
    mcuSize = JroundUp(mcuSize, sizeof(double));

    /*
     * Allocate the MCU table, and a buffer which will contain all
     * the data.  Then carve up the buffer by hand.  Note that
     * mcuTable[0] points to the buffer, in case we want to free
     * it up later.
     */
    mcuTable = (MCU *)malloc(numMCU * sizeof(MCU));
    buffer = (char *)malloc(numMCU * mcuSize);
    for (i = 0; i < numMCU; i++)
    {
        mcuTable[i] = (MCU)(buffer + i * mcuSize);
    }
}

#define MakeMCU(dcPtr) (mcuTable[numMCU++])

/*
 *--------------------------------------------------------------
 *
 * PrintMCU --
 *
 *	Send an MCU in quasi-readable form to stdout.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */
void
    PrintMCU(blocksInMCU, mcu) int blocksInMCU;
MCU mcu;
{
    RLE *rle;
    int i, b;
    static int callCount;

    for (b = 0; b < blocksInMCU; b++)
    {
        callCount++;
        rle = mcu + b;
        printf("%d: %d ", callCount, rle->dc);
        for (i = 0; i < rle->numAC; i++)
        {
            printf("(%d %d)", rle->ac[i].index, rle->ac[i].value);
        }
        printf("\n");
    }
}
