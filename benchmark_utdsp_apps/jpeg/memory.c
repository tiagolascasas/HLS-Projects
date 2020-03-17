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

static char myInputBuffer[1<<20];
static int myInputBufferOffset;
static int numStdinBytes;
static int stdoutTotal;

/*
 *--------------------------------------------------------------
 *
 * FillInputBuffer --
 *
 *	Create a big buffer of all the data from stdin
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */
FillInputBuffer ()
{
    numStdinBytes = fread(myInputBuffer, 1, sizeof(myInputBuffer), stdin);
}

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
ReadJpegData (buffer, numBytes)
    char *buffer;		/* Place to put new data */
    int numBytes;		/* Number of bytes to put */
{
    if (numStdinBytes-myInputBufferOffset < numBytes) {
	numBytes = numStdinBytes-myInputBufferOffset;
    }
    memcpy (buffer, myInputBuffer+myInputBufferOffset, numBytes);
    myInputBufferOffset += numBytes;
    return numBytes;
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
WriteJpegData  (buffer, numBytes)
    char *buffer;               /* Data to write */
    int numBytes;               /* Number of bytes to write */
{
    stdoutTotal += numBytes;
    return numBytes;
}
int
main(argc, argv)
    int argc;
    char **argv;
{
    DecompressInfo dcInfo;
    CompressInfo enInfo;
    int count, i, maxMcu;
    MCU mcu;

    FillInputBuffer();
    InitMcuTable (8000, 6);
    for (count=0; count<100; count++) {
	myInputBufferOffset = 0;
	numMCU = 0;
	memset (&dcInfo, 0, sizeof(dcInfo));
	memset (&enInfo, 0, sizeof(enInfo));

	/*
	 * Read the JPEG File header, up to scan header, and initialize all
	 * the variables in the decompression information structure.
	 */
	ReadFileHeader (&dcInfo);

	/*
	 * Loop through each scan in image.  ReadScanHeader returns
	 * 0 once it consumes and EOI marker.
	 */
	if (!ReadScanHeader (&dcInfo)) {
	    fprintf (stderr, "Empty JPEG file\n");
	    exit (1);
	}
	DecoderStructInit (&dcInfo);
	HuffDecoderInit (&dcInfo);

	/*
	 * Decompress everything into MCU's
	 */
	maxMcu = dcInfo.MCUsPerRow * dcInfo.MCUrowsInScan;
	for (i = 0; i < maxMcu; i++) {
	    mcu = MakeMCU(&dcInfo);
	    DecodeMCUrle (&dcInfo, mcu);
	}

	if (ReadScanHeader (&dcInfo)) {
	    fprintf (stderr, "Warning: multiple scans detected in JPEG file\n");
	    fprintf (stderr, "         not currently supported\n");
	    fprintf (stderr, "         ignoring extra scans\n");
	}

	/*
	 * Set up the compression information structure, write
	 * the file headers, and encode all the data.
	 */
	CopyDecoderVars(&dcInfo, &enInfo);
	HuffEncoderInit (&enInfo);
	WriteFileHeader (&enInfo);
	WriteScanHeader (&enInfo);
	for (i = 0; i < numMCU; i++) {
	    mcu = mcuTable[i];
	    HuffEncode (&enInfo, mcu);
	}
	HuffEncoderTerm ();
	WriteFileTrailer (&enInfo);
	FlushBytes ();
    }
    printf ("Wrote %d bytes\n", stdoutTotal);
}
