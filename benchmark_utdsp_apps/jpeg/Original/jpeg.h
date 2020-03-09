/*
 * jpeg.h --
 *
 * Basic jpeg data structure definitions.
 *
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



typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

/*
 * The following structure stores basic information about one component.
 */
typedef struct JpegComponentInfo {
    /*
     * These values are fixed over the whole image.
     * They are read from the SOF marker.
     */
    short componentId;		/* identifier for this component (0..255) */
    short componentIndex;	/* its index in SOF or cPtr->compInfo[] */
    short hSampFactor;		/* horizontal sampling factor (1..4) */
    short vSampFactor;		/* vertical sampling factor (1..4) */
    short quantTblNo;		/* quantization table selector (0..3) */

    /*
     * These values may vary between scans
    /* They are read from the SOS marker.
    */
    short dcTblNo;		/* DC entropy table selector (0..3) */
    short acTblNo;		/* AC entropy table selector (0..3) */

    /* 
     * These values are computed during startup.
     */
    int trueCompWidth;		/* component's image width in samples */
    int trueCompHeight;		/* component's image height in samples */

    /*
     * the above are the logical dimensions of the Downsampled image
     * These values are computed before starting a scan of the component
     */
    short MCUwidth;		/* number of blocks per MCU, horizontally */
    short MCUheight;		/* number of blocks per MCU, vertically */
    short MCUblocks;		/* MCUwidth * MCUheight */

    /*
     * The next two values are the trueCompXXX values rounded up
     * to multiples of the MCU dimensions; these are the working
     * dimensions of the array as it is passed through the DCT or IDCT
     * step.  NOTE: these values differ depending on whether the
     * component is interleaved or not!!
     */
    int downsampledWidth;	/* image width in samples, after expansion */
    int downsampledHeight;	/* image height in samples, after expansion */
} JpegComponentInfo;


/*
 * One of the following structures is created for each huffman coding
 * table.  We use the same structure for encoding and decoding, so there
 * may be some extra fields for encoding that aren't used in the decoding
 * and vice-versa.
 */
typedef struct HuffmanTable {
    /*
     * These two fields directly represent the contents of a JPEG DHT
     * marker
     */
    uchar bits[17];
    uchar huffval[256];

    /*
     * This field is used only during compression.  It's initialized
     * FALSE when the table is created, and set TRUE when it's been
     * output to the file.
     */
    int sentTable;

    /*
     * The remaining fields are computed from the above to allow more
     * efficient coding and decoding.  These fields should be considered
     * private to the Huffman compression & decompression modules.
     */
    ushort ehufco[256];
    char ehufsi[256];

    ushort mincode[17];
    int maxcode[18];
    short valptr[17];
    int numbits[256];
    int value[256];
} HuffmanTable;

/*
 * One of the following structures is used to pass around the
 * compression information.
 */
typedef struct CompressInfo {
    int imageWidth;		/* input image width */
    int imageHeight;		/* input image height */
    int dataPrecision;		/* bits of precision in image data */

    /*
     * These three values are not used by the JPEG code, only copied
     * into the JFIF APP0 marker.  densityUnit can be 0 for unknown, 1
     * for dots/inch, or 2 for dots/cm.  Note that the pixel aspect ratio
     * is defined by Xdensity/Ydensity even when densityUnit=0.
     */
    uchar densityUnit;		/* JFIF code for pixel size units */
    ushort Xdensity;		/* Horizontal pixel density */
    ushort Ydensity;		/* Vertical pixel density */


    /*
     *compInfo[i] describes component that appears i'th in SOF
     */
    JpegComponentInfo *compInfo;
    short numComponents;	/* # of color components in JPEG image */

    /*
     * Pointers to coefficient quantization tables, or NULL if not
     * defined
     */
    short *quantTblPtrs[4];

    /*
     * Pointers to Huffman coding tables, or NULL if not defined 
     */
    HuffmanTable *dcHuffTblPtrs[4];
    HuffmanTable *acHuffTblPtrs[4];

    /*
     * The restart interval can be specified in absolute MCUs by
     * setting restartInterval, or in MCU rows by setting
     * restartInRows (in which case the correct restartInterval will
     * be figured for each scan).
     */
    short restartInterval;	/* MCUs/(restart interval), 0 -> no restart */
    int restartInRows;		/* if > 0, MCU rows per restart interval */

    /*
     * These fields are computed during JpegCompress startup
     */
    short maxHsampFactor;	/* largest hSampFactor */
    short maxVsampFactor;	/* largest vSampFactor */

    /*
     * These fields are valid during any one scan
     */
    short compsInScan;		/* # of JPEG components output this time */

    /*
     * *curCompInfo[i] describes component that appears i'th in SOS
     */
    JpegComponentInfo *curCompInfo[4];

    int MCUsPerRow;		/* # of MCUs across the image */
    int MCUrowsInScan;		/* # of MCU rows in the image */

    short blocksInMCU;		/* # of DCT blocks per MCU */

    /*
     * MCUmembership[i] is index in curCompInfo of component owning
     */
    short MCUmembership[10];

    /* 
     * These fields are private data for the entropy encoder
     */
    short lastDcVal[4];		/* last DC coef for each comp */
    short restartsToGo;		/* MCUs left in this restart interval */
    short nextRestartNum;	/* # of next RSTn marker (0..7) */
} CompressInfo;

/*
 * One of the following structures is used to pass around the
 * decompression information.
 */
typedef struct DecompressInfo {
    /*
     * These fields are set by ReadFileHeader or ReadScanHeader
     */
    int imageWidth;		/* overall image width */
    int imageHeight;		/* overall image height */

    short dataPrecision;	/* bits of precision in image data */

    /* These three values are not used by the JPEG code, merely copied */
    /* from the JFIF APP0 marker (if any). */
    uchar densityUnit;		/* JFIF code for pixel size units */
    ushort Xdensity;		/* Horizontal pixel density */
    ushort Ydensity;		/* Vertical pixel density */

    short numComponents;	/* # of color components in JPEG image */
    JpegComponentInfo *compInfo;
    /* compInfo[i] describes component that appears i'th in SOF */

    short *quantTblPtrs[4];
    /* ptrs to coefficient quantization tables, or NULL if not defined */

    HuffmanTable *dcHuffTblPtrs[4];
    HuffmanTable *acHuffTblPtrs[4];
    /* ptrs to Huffman coding tables, or NULL if not defined */

    short restartInterval;	/* MCUs per restart interval, 0 = no restart */

    /*
     * These fields are computed during JpegDecompress startup
     */
    short maxHsampFactor;	/* largest hSampFactor */
    short maxVsampFactor;	/* largest vSampFactor */

    /*
     * These fields are valid during any one scan
     */
    short compsInScan;		/* # of JPEG components input this time */

    /*
     * *curCompInfo[i] describes component that appears i'th in SOS
     */
    JpegComponentInfo *curCompInfo[4];

    int MCUsPerRow;		/* # of MCUs across the image */
    int MCUrowsInScan;		/* # of MCU rows in the image */

    /*
     * MCUmembership[i] is index in curCompInfo of component owning
     * i'th block in an MCU
     */
    short MCUmembership[10];
    short blocksInMCU;		/* # of DCT blocks per MCU */

    /*
     * these fields are private data for the entropy encoder
     */
    short lastDcVal[4];		/* last DC coef for each comp */
    short restartsToGo;		/* MCUs left in this restart interval */
    short nextRestartNum;	/* # of next RSTn marker (0..7) */
} DecompressInfo;

#define RST0    0xD0            /* RST0 marker code */

/*
 * The following variables keep track of the input buffer for the JPEG
 * data, which is read by ReadJpegData
 */
extern uchar inputBuffer[];	/* Input buffer for JPEG data */
extern int numInputBytes;	/* The total number of bytes in inputBuffer */
extern int maxInputBytes;	/* Size of inputBuffer */
extern int inputBufferOffset;	/* Offset of current byte */

/*
 *--------------------------------------------------------------
 *
 * GetJpegChar, UnGetJpegChar --
 *
 *	Macros to get the next character from the input stream.
 *
 * Results:
 *	GetJpegChar returns the next character in the stream, or EOF
 *	UnGetJpegChar returns nothing.
 *
 * Side effects:
 *	A byte is consumed or put back into the inputBuffer.
 *
 *--------------------------------------------------------------
 */
#define GetJpegChar()							\
    ((inputBufferOffset < numInputBytes)?				\
     inputBuffer[inputBufferOffset++]:					\
     (numInputBytes = 2+ReadJpegData(inputBuffer+2,JPEG_BUF_SIZE-2),	\
      inputBufferOffset = 2,						\
      ((inputBufferOffset < numInputBytes)?				\
       inputBuffer[inputBufferOffset++]:				\
       EOF)))

#define UnGetJpegChar(ch)	(inputBuffer[--inputBufferOffset]=(ch))
