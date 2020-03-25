/*
 * huffd.c --
 *
 * Code for decoding JPEG data.  Large parts are grabbed from the IJG
 * software, so:
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "jpeg.h"
#include "rle.h"
#include "io.h"
#include "proto.h"

#define RST0    0xD0            /* RST0 marker code */

static long getBuffer;		/* current bit-extraction buffer */
static int bitsLeft;		/* # of unused bits in it */

/*
 * The following variables keep track of the input buffer for the JPEG
 * data, which is read by ReadJpegData
 */
uchar inputBuffer[JPEG_BUF_SIZE]; /* Input buffer for JPEG data */
int numInputBytes;		/* The total number of bytes in inputBuffer */
int maxInputBytes;		/* Size of inputBuffer */
int inputBufferOffset;		/* Offset of current byte */

unsigned int bitMask[] = {  0xffffffff, 0x7fffffff, 0x3fffffff, 0x1fffffff, 
			    0x0fffffff, 0x07ffffff, 0x03ffffff, 0x01ffffff,
			    0x00ffffff, 0x007fffff, 0x003fffff, 0x001fffff,
			    0x000fffff, 0x0007ffff, 0x0003ffff, 0x0001ffff,
			    0x0000ffff, 0x00007fff, 0x00003fff, 0x00001fff,
			    0x00000fff, 0x000007ff, 0x000003ff, 0x000001ff,
			    0x000000ff, 0x0000007f, 0x0000003f, 0x0000001f,
			    0x0000000f, 0x00000007, 0x00000003, 0x00000001};

/*
 *--------------------------------------------------------------
 *
 * FixHuffTbl --
 *
 *	Compute derived values for a Huffman table one the DHT marker
 *	has been processed.  This generates both the encoding and
 *	decoding tables.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */

static void 
FixHuffTbl (htbl)
    HuffmanTable *htbl;
{
    int p, i, l, lastp, si;
    char huffsize[257];
    ushort huffcode[257];
    ushort code;
    int size;
    int value, ll, ul;

    /*
     * Figure C.1: make table of Huffman code length for each symbol
     * Note that this is in code-length order.
     */
    p = 0;
    for (l = 1; l <= 16; l++) {
	for (i = 1; i <= (int)htbl->bits[l]; i++)
	    huffsize[p++] = (char)l;
    }
    huffsize[p] = 0;
    lastp = p;


    /*
     * Figure C.2: generate the codes themselves
     * Note that this is in code-length order.
     */
    code = 0;
    si = huffsize[0];
    p = 0;
    while (huffsize[p]) {
	while (((int)huffsize[p]) == si) {
	    huffcode[p++] = code;
	    code++;
	}
	code <<= 1;
	si++;
    }

    /*
     * Figure C.3: generate encoding tables
     * These are code and size indexed by symbol value
     * Set any codeless symbols to have code length 0; this allows
     * EmitBits to detect any attempt to emit such symbols.
     */
    memset (htbl->ehufsi, 0, sizeof(htbl->ehufsi));

    for (p = 0; p < lastp; p++) {
	htbl->ehufco[htbl->huffval[p]] = huffcode[p];
	htbl->ehufsi[htbl->huffval[p]] = huffsize[p];
    }

    /*
     * Figure F.15: generate decoding tables
     */
    p = 0;
    for (l = 1; l <= 16; l++) {
	if (htbl->bits[l]) {
	    htbl->valptr[l] = p;
	    htbl->mincode[l] = huffcode[p];
	    p += htbl->bits[l];
	    htbl->maxcode[l] = huffcode[p - 1];
	} else {
	    htbl->maxcode[l] = -1;
	}
    }

    /*
     * We put in this value to ensure HuffDecode terminates.
     */
    htbl->maxcode[17] = 0xFFFFFL;

    /*
     * Build the numbits, value lookup tables.
     * These table allow us to gather 8 bits from the bits stream,
     * and immediately lookup the size and value of the huffman codes.
     * If size is zero, it means that more than 8 bits are in the huffman
     * code (this happens about 3-4% of the time).
     */
    bzero (htbl->numbits, sizeof(htbl->numbits));
    for (p=0; p<lastp; p++) {
	size = huffsize[p];
	if (size <= 8) {
	    value = htbl->huffval[p];
	    code = huffcode[p];
	    ll = code << (8-size);
	    if (size < 8) {
		ul = ll | bitMask[24+size];
	    } else {
		ul = ll;
	    }
	    for (i=ll; i<=ul; i++) {
		htbl->numbits[i] = size;
		htbl->value[i] = value;
	    }
	}
    }
}

/*
 * Code for extracting the next N bits from the input stream.
 * (N never exceeds 15 for JPEG data.)
 * This needs to go as fast as possible!
 *
 * We read source bytes into getBuffer and dole out bits as needed.
 * If getBuffer already contains enough bits, they are fetched in-line
 * by the macros get_bits() and get_bit().  When there aren't enough bits,
 * FillBitBuffer is called; it will attempt to fill getBuffer to the
 * "high water mark", then extract the desired number of bits.  The idea,
 * of course, is to minimize the function-call overhead cost of entering
 * FillBitBuffer.
 * On most machines MIN_GET_BITS should be 25 to allow the full 32-bit width
 * of getBuffer to be used.  (On machines with wider words, an even larger
 * buffer could be used.)  
 */

#define BITS_PER_LONG	(8*sizeof(long))
#define MIN_GET_BITS  (BITS_PER_LONG-7)	   /* max value for long getBuffer */

/*
 * bmask[n] is mask for n rightmost bits
 */
static int bmask[] = {0x0000,
	 0x0001, 0x0003, 0x0007, 0x000F,
	 0x001F, 0x003F, 0x007F, 0x00FF,
	 0x01FF, 0x03FF, 0x07FF, 0x0FFF,
	 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF};


/*
 *--------------------------------------------------------------
 *
 * FillBitBuffer --
 *
 *	Load up the bit buffer with at least nbits
 *	Process any stuffed bytes at this time.
 *
 * Results:
 *	None
 *
 * Side effects:
 *	The bitwise global variables are updated.
 *
 *--------------------------------------------------------------
 */

static void
FillBitBuffer (nbits)
    int nbits;
{
    int c, c2;

    while (bitsLeft < MIN_GET_BITS) {
	c = GetJpegChar ();

	/*
	 * If it's 0xFF, check and discard stuffed zero byte
	 */
	if (c == 0xFF) {
	    c2 = GetJpegChar ();

	    if (c2 != 0) {

		/*
		 * Oops, it's actually a marker indicating end of
		 * compressed data.  Better put it back for use later.
		 */
		UnGetJpegChar (c2);
		UnGetJpegChar (c);

		/*
		 * There should be enough bits still left in the data
		 * segment; if so, just break out of the while loop.
		 */
		if (bitsLeft >= nbits)
		    break;

		/*
		 * Uh-oh.  Corrupted data: stuff zeroes into the data
		 * stream, since this sometimes occurs when we are on the
		 * last show_bits(8) during decoding of the Huffman
		 * segment.
		 */
		c = 0;
	    }
	}
	/*
	 * OK, load c into getBuffer
	 */
	getBuffer = (getBuffer << 8) | c;
	bitsLeft += 8;
    }
}


/* Macros to make things go at some speed! */
/* NB: parameter to get_bits should be simple variable, not expression */

#define show_bits(nbits,rv) {						\
    if (bitsLeft < nbits) FillBitBuffer(nbits);				\
    rv = (getBuffer >> (bitsLeft-(nbits))) & bmask[nbits];		\
}

#define show_bits8(rv) {						\
	if (bitsLeft < 8) FillBitBuffer(8);				\
	rv = (getBuffer >> (bitsLeft-8)) & 0xff;			\
}

#define flush_bits(nbits) {						\
	bitsLeft -= (nbits);						\
}

#define get_bits(nbits,rv) {						\
	if (bitsLeft < nbits) FillBitBuffer(nbits);			\
	rv = ((getBuffer >> (bitsLeft -= (nbits)))) & bmask[nbits];	\
}

#define get_bit(rv) {							\
	if (!bitsLeft) FillBitBuffer(1);				\
	rv = (getBuffer >> (--bitsLeft)) & 1;	 			\
}

/*
 *--------------------------------------------------------------
 *
 * HuffDecode --
 *
 *	Taken from Figure F.16: extract next coded symbol from
 *	input stream.  This should becode a macro.
 *
 * Results:
 *	Next coded symbol
 *
 * Side effects:
 *	Bitstream is parsed.
 *
 *--------------------------------------------------------------
 */
#define HuffDecode(htbl,rv)						\
{									\
    int l, code, temp;							\
									\
    /*									\
     * If the huffman code is less than 8 bits, we can use the fast	\
     * table lookup to get its value.  It's more than 8 bits about	\
     * 3-4% of the time.						\
     */									\
    show_bits8(code);							\
    if (htbl->numbits[code]) {						\
	flush_bits(htbl->numbits[code]);				\
	rv=htbl->value[code];						\
    }  else {								\
	flush_bits(8);							\
	l = 8;								\
	while (code > htbl->maxcode[l]) {				\
	    get_bit(temp);						\
	    code = (code << 1) | temp;					\
	    l++;							\
	}								\
									\
	/*								\
	 * With garbage input we may reach the sentinel value l = 17.	\
	 */								\
									\
	if (l > 16) {							\
	    fprintf (stderr, "Corrupt JPEG data: bad Huffman code");	\
	    rv = 0;		/* fake a zero as the safest result */	\
	} else {							\
	    rv = htbl->huffval[htbl->valptr[l] +			\
		((int)(code - htbl->mincode[l]))];			\
	}								\
    }									\
}


/*
 *--------------------------------------------------------------
 *
 * HuffExtend --
 *
 *	Code and table for Figure F.12: extend sign bit
 *
 * Results:
 *	The extended value.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */

static int extendTest[16] =	/* entry n is 2**(n-1) */
{0, 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000};

static int extendOffset[16] =	/* entry n is (-1 << n) + 1 */
{0, ((-1) << 1) + 1, ((-1) << 2) + 1, ((-1) << 3) + 1, ((-1) << 4) + 1,
 ((-1) << 5) + 1, ((-1) << 6) + 1, ((-1) << 7) + 1, ((-1) << 8) + 1,
 ((-1) << 9) + 1, ((-1) << 10) + 1, ((-1) << 11) + 1, ((-1) << 12) + 1,
 ((-1) << 13) + 1, ((-1) << 14) + 1, ((-1) << 15) + 1};

#define HuffExtend(x,s) {					\
    if ((x) < extendTest[s]) {					\
	(x) += extendOffset[s];					\
    }								\
}



/*
 *--------------------------------------------------------------
 *
 * HuffDecoderInit --
 *
 *	Initialize for a Huffman-compressed scan. This is invoked after
 *	reading the SOS marker.
 *
 * Results:
 *	None
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */
void 
HuffDecoderInit (dcPtr)
    DecompressInfo *dcPtr;
{
    short ci;
    JpegComponentInfo *compptr;

    /*
     * Initialize static variables
     */
    bitsLeft = 0;

    for (ci = 0; ci < dcPtr->compsInScan; ci++) {
	compptr = dcPtr->curCompInfo[ci];
	/*
	 * Make sure requested tables are present
	 */
	if ((dcPtr->dcHuffTblPtrs[compptr->dcTblNo] == NULL) ||
	    (dcPtr->acHuffTblPtrs[compptr->acTblNo] == NULL)) {
	    fprintf (stderr, "Error: Use of undefined Huffman table\n");
	    exit (1);
	}

	/*
	 * Compute derived values for Huffman tables.
	 * We may do this more than once for same table, but it's not a
	 * big deal
	 */
	FixHuffTbl (dcPtr->dcHuffTblPtrs[compptr->dcTblNo]);
	FixHuffTbl (dcPtr->acHuffTblPtrs[compptr->acTblNo]);

	/*
	 * Initialize DC predictions to 0
	 */
	dcPtr->lastDcVal[ci] = 0;
    }

    /*
     * Initialize restart stuff
     */
    dcPtr->restartsToGo = dcPtr->restartInterval;
    dcPtr->nextRestartNum = 0;
}

/*
 *--------------------------------------------------------------
 *
 * ProcessRestart --
 *
 *	Check for a restart marker & resynchronize decoder.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	BitStream is parsed, bit buffer is reset, etc.
 *
 *--------------------------------------------------------------
 */
static void 
ProcessRestart (dcPtr)
    DecompressInfo *dcPtr;
{
    int c, nbytes;
    short ci;

    /*
     * Throw away any unused bits remaining in bit buffer
     */
    nbytes = bitsLeft / 8;
    bitsLeft = 0;

    /*
     * Scan for next JPEG marker
     */
    do {
	do {			/* skip any non-FF bytes */
	    nbytes++;
	    c = GetJpegChar ();
	} while (c != 0xFF);
	do {			/* skip any duplicate FFs */
	    /*
	     * we don't increment nbytes here since extra FFs are legal
	     */
	    c = GetJpegChar ();
	} while (c == 0xFF);
    } while (c == 0);		/* repeat if it was a stuffed FF/00 */

    if (nbytes != 1)
	fprintf (stderr, 
	   "Corrupt JPEG data: %d extraneous bytes before marker 0x%02x",
		 nbytes - 1, c);

    if (c != (RST0 + dcPtr->nextRestartNum)) {
	/*
	 * Uh-oh, the restart markers have been messed up too.
	 * Just bail out.
	 */
	fprintf (stderr, "Error: Corrupt JPEG data.  Exiting...\n");
	exit(1);
    }

    /*
     * Re-initialize DC predictions to 0
     */
    for (ci = 0; ci < dcPtr->compsInScan; ci++)
	dcPtr->lastDcVal[ci] = 0;

    /*
     * Update restart state
     */
    dcPtr->restartsToGo = dcPtr->restartInterval;
    dcPtr->nextRestartNum = (dcPtr->nextRestartNum + 1) & 7;
}


/*
 *--------------------------------------------------------------
 *
 * DecodeMCUrle --
 *
 *	Decode a single MCU worth of RLE data.  This includes
 *	modifying the dc value so the real value, not the
 *	difference is returned.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Bitstream is parsed.
 *
 *--------------------------------------------------------------
 */
void
DecodeMCUrle (dcPtr, mcuRLE)
    DecompressInfo *dcPtr;
    MCU mcuRLE;
{
    register int s, k, r;
    short blkn, ci, n;
    register RLE *rle;
    HuffmanTable *dctbl;
    HuffmanTable *actbl;
    JpegComponentInfo *compptr;

    /*
     * Account for restart interval, process restart marker if needed
     */
    if (dcPtr->restartInterval) {
	if (dcPtr->restartsToGo == 0)
	    ProcessRestart (dcPtr);
	dcPtr->restartsToGo--;
    }

    /*
     * Outer loop handles each block in the MCU
     */
    for (blkn = 0; blkn < dcPtr->blocksInMCU; blkn++) {
	rle = mcuRLE+blkn;
	ci = dcPtr->MCUmembership[blkn];
	compptr = dcPtr->curCompInfo[ci];
	actbl = dcPtr->acHuffTblPtrs[compptr->acTblNo];
	dctbl = dcPtr->dcHuffTblPtrs[compptr->dcTblNo];

	/*
	 * Section F.2.2.1: decode the DC coefficient difference
	 */
	HuffDecode (dctbl,s);
	if (s) {
	    get_bits(s,r);
	    HuffExtend(r,s);
	} else {
	    r = 0;
	}

	/* 
	 * Convert DC difference to actual value, update lastDcVal
	 */
	r += dcPtr->lastDcVal[ci];
	dcPtr->lastDcVal[ci] = r;

	/*
	 * Descale and output the DC coefficient (assumes ZAG[0] = 0)
	 */
	rle->dc = r;

	/*
	 * Section F.2.2.2: decode the AC coefficients
	 */
	n=0;
	k=1;
	while (k < 64) {
	    HuffDecode (actbl,r);

	    s = r & 0xf;

	    if (s) {
		k += (r >> 4);
		get_bits(s,r);
		HuffExtend(r,s);

		/*
		 * Put index, value pair in rle
		 */
		rle->ac[n].index = k++;
		rle->ac[n].value = r;
		n++;
	    } else if (r == 0xf0) {
		k += 16;
	    } else {
		break;
	    }
	}
	rle->numAC = n;
    }
}
