/*
 * main.c --
 *
 * This is the main routine for the jpeg decoder.  Large parts are
 * stolen from the IJG code, so:
 *
 * Copyright (C) 1991, 1992, Thomas G. Lane.
 * Part of the Independent JPEG Group's software.
 * See the file Copyright for more details.
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

/*
 *--------------------------------------------------------------
 *
 * ReadJpegData --
 *
 *	This is an interface routine to the JPEG library.  The
 *	JPEG library calls this routine to "get more data"
 *
 * Results:
 *	Number of bytes actually returned.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */
int
    ReadJpegData(buffer, numBytes) char *buffer; /* Place to put new data */
int numBytes;                                    /* Number of bytes to put */
{
    return fread(buffer, 1, numBytes, stdin);
}

/*
 *--------------------------------------------------------------
 *
 * WriteJpegData --
 *
 *	This is an interface routine to the JPEG library.  The
 *	library calls this routine to output a block of data.
 *
 * Results:
 *	Number of bytes written.  If this is less than numBytes,
 *	it indeicates an error.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */
WriteJpegData(buffer, numBytes) char *buffer; /* Data to write */
int numBytes;                                 /* Number of bytes to write */
{
    return fwrite(buffer, 1, numBytes, stdout);
}

int
    main(argc, argv) int argc;
char **argv;
{
    DecompressInfo dcInfo;
    CompressInfo enInfo;
    int i, j, k, l;
    int maxMcu;
    MCU mcu;
    RLE *rle;

    memset(&dcInfo, 0, sizeof(dcInfo));
    memset(&enInfo, 0, sizeof(enInfo));

    /*
     * Read the JPEG File header, up to scan header, and initialize all
     * the variables in the decompression information structure.
     */
    ReadFileHeader(&dcInfo);

    /*
     * Loop through each scan in image.  ReadScanHeader returns
     * 0 once it consumes and EOI marker.
     */
    if (!ReadScanHeader(&dcInfo))
    {
        fprintf(stderr, "Empty JPEG file\n");
        exit(1);
    }
    DecoderStructInit(&dcInfo);
    HuffDecoderInit(&dcInfo);

    /*
     * Decompress everything into MCU's
     */
    maxMcu = dcInfo.MCUsPerRow * dcInfo.MCUrowsInScan;
    InitMcuTable(maxMcu, dcInfo.blocksInMCU);
    for (i = 0; i < maxMcu; i++)
    {
        mcu = MakeMCU(&dcInfo);
        DecodeMCUrle(&dcInfo, mcu);
    }

    if (ReadScanHeader(&dcInfo))
    {
        fprintf(stderr, "Warning: multiple scans detected in JPEG file\n");
        fprintf(stderr, "         not currently supported\n");
        fprintf(stderr, "         ignoring extra scans\n");
    }

    /*
     * At this point, you can filter all the MCU's if you want.
     * For example, this loop maps all high frequency ac values 
     * (i.e., zigzag index >= 4) that are low energy (value = +/-1)
     * to zero.
     */
    for (i = 0; i < numMCU; i++)
    {
        mcu = mcuTable[i];
        for (j = 0; j < dcInfo.blocksInMCU; j++)
        {
            rle = mcu + j;
            for (k = 0, l = 0; k < rle->numAC; k++)
            {
                /*
		 * Copy if zigzag index < 4 or value isn't +/- 1
		 */
                if ((rle->ac[k].index < 4) ||
                    ((rle->ac[k].value != 1) && (rle->ac[k].value != -1)))
                {
                    rle->ac[l].index = rle->ac[k].index;
                    rle->ac[l].value = rle->ac[k].value;
                    l++;
                }
            }
            rle->numAC = l;
        }
    }

    /*
     * Set up the compression information structure, write
     * the file headers, and encode all the data.
     */
    CopyDecoderVars(&dcInfo, &enInfo);
    HuffEncoderInit(&enInfo);
    WriteFileHeader(&enInfo);
    WriteScanHeader(&enInfo);
    for (i = 0; i < numMCU; i++)
    {
        mcu = mcuTable[i];
        HuffEncode(&enInfo, mcu);
    }
    HuffEncoderTerm();
    WriteFileTrailer(&enInfo);
    FlushBytes();
    fflush(stdout);
    if (ferror(stdout))
    {
        fprintf(stderr, "Output file write error\n");
    }
}
