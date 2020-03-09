/*
 * write.c --
 *
 * Code for writing JPEG files.  Large parts are grabbed
 * from the IJG software, so:
 *
 */

#include "traps.h"
#include "jpeg.h"
#include "rle.h"
#include "io.h"
#include "proto.h"
 int *null=0;

/*EmitDht*/
    HuffmanTable *htbl;

/* 
 * Enumerate all the JPEG marker codes
 */
typedef enum {
      M_SOF0 = 0xc0,
      M_SOF1 = 0xc1,
      M_SOF2 = 0xc2,
      M_SOF3 = 0xc3,

      M_SOF5 = 0xc5,
      M_SOF6 = 0xc6,
      M_SOF7 = 0xc7,

      M_JPG = 0xc8,
      M_SOF9 = 0xc9,
      M_SOF10 = 0xca,
      M_SOF11 = 0xcb,

      M_SOF13 = 0xcd,
      M_SOF14 = 0xce,
      M_SOF15 = 0xcf,

      M_DHT = 0xc4,

      M_DAC = 0xcc,

      M_RST0 = 0xd0,
      M_RST1 = 0xd1,
      M_RST2 = 0xd2,
      M_RST3 = 0xd3,
      M_RST4 = 0xd4,
      M_RST5 = 0xd5,
      M_RST6 = 0xd6,
      M_RST7 = 0xd7,

      M_SOI = 0xd8,
      M_EOI = 0xd9,
      M_SOS = 0xda,
      M_DQT = 0xdb,
      M_DNL = 0xdc,
      M_DRI = 0xdd,
      M_DHP = 0xde,
      M_EXP = 0xdf,

      M_APP0 = 0xe0,
      M_APP15 = 0xef,

      M_JPG0 = 0xf0,
      M_JPG13 = 0xfd,
      M_COM = 0xfe,

      M_TEM = 0x01,

      M_ERROR = 0x100
} JpegMarker;

/*
 *--------------------------------------------------------------
 *
 * EmitMarker --
 *
 *	Emit a marker code into the output stream.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */
/*static*/ void
EmitMarker (mark)
    JpegMarker mark;
{
    EmitByte (0xFF);
    EmitByte (mark);
}

/*
 *--------------------------------------------------------------
 *
 * Emit2bytes --
 *
 *	Emit a 2-byte integer; these are always MSB first in JPEG
 *	files
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */
/*static*/ void
Emit2bytes (value)
    int value;
{
    EmitByte ((value >> 8) & 0xFF);
    EmitByte (value & 0xFF);
}

/*
 *--------------------------------------------------------------
 *
 * EmitDqt --
 *
 *	Gives DQT marker, plus the quantization table.
 *
 * Results:
 *	The precision used (0 = 8bits, 1 = 16bits)
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */
/*static*/ int
EmitDqt (cPtr, index)
    CompressInfo *cPtr;
    int index;
{
    int *data = *(cPtr->quantTblPtrs+index);
    int prec = 0;
    int i,kk;

    for (i = 0; i < 64; i++) {
	if (*(data+i) > 255)
	    prec = 1;
    }

    EmitMarker (M_DQT);

    Emit2bytes (prec ? 64 * 2 + 1 + 2 : 64 + 1 + 2);

    EmitByte (index + (prec << 4));

    for (i = 0; i < 64; i++) {
	if (prec)
	    EmitByte (*(data+i) >> 8);
	EmitByte (*(data+i) & 0xFF);
        kk=0;
    }

    return prec;
}

/*
 *--------------------------------------------------------------
 *
 * EmitDht --
 *
 *	Emit a DHT marker, follwed by the huffman data.
 *
 * Results:
 *	None
 *
 * Side effects:
 *	None
 *
 *--------------------------------------------------------------
 */
/*static*/ void
EmitDht (cPtr, index, isAc)
    CompressInfo *cPtr;
    int index;
    int isAc;
{
    int length, i,kk;

    if (isAc) {
	htbl = *(cPtr->acHuffTblPtrs+index);
	index += 0x10;		/* output index has AC bit set */
    } else {
	htbl = *(cPtr->dcHuffTblPtrs+index);
    }

    if (htbl == (HuffmanTable *)null /*NULL*/) {
  /*	fprintf (stderr, "Huffman table 0x%02x was not defined\n", index);  */
    /*	exit (1);   */
    }

    if (!htbl->sentTable) {
	EmitMarker (M_DHT);

	length = 0;
	for (i = 1; i <= 16; i++)
	    length += *(htbl->bits+i);

	Emit2bytes (length + 2 + 1 + 16);
	EmitByte (index);

	for (i = 1; i <= 16; i++)  {
	    EmitByte (*(htbl->bits+i));
             kk=0;
              }

	for (i = 0; i < length; i++)  {
	    EmitByte (*(htbl->huffval+i));
             kk=0;
               }

	htbl->sentTable = 1;
    }
}

/*
 *--------------------------------------------------------------
 *
 * EmitDri --
 *
 *	Emit a DRI marker
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */
/*static*/ void
EmitDri (cPtr)
    CompressInfo * cPtr;
{
    EmitMarker (M_DRI);
    Emit2bytes (4);	/* length */
    Emit2bytes ((int)cPtr->restartInterval);
}

/*
 *--------------------------------------------------------------
 *
 * EmitSof --
 *
 *	Emit a SOF marker plus data.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */
/*static*/ void
EmitSof (cPtr, code)
    CompressInfo * cPtr;
    JpegMarker code;
{
    int i,kk;

    EmitMarker (code);

    Emit2bytes (3 * cPtr->numComponents + 2 + 5 + 1);	/* length */

    if ((cPtr->imageHeight > 65535) ||
	(cPtr->imageWidth > 65535)) {
/*	fprintf (stderr, "Maximum image dimension for JFIF is 65535 pixels\n");  */
    /*	exit (1);   */
    }

    EmitByte (cPtr->dataPrecision);
    Emit2bytes ((int)cPtr->imageHeight);
    Emit2bytes ((int)cPtr->imageWidth);

    EmitByte (cPtr->numComponents);

    for (i = 0; i < cPtr->numComponents; i++) {
	EmitByte ((*(cPtr->compInfo+i)).componentId);
	EmitByte (((*(cPtr->compInfo+i)).hSampFactor << 4)
		   + (*(cPtr->compInfo+i)).vSampFactor);
	EmitByte ((*(cPtr->compInfo+i)).quantTblNo);
          kk=0;
    }
}

/*
 *--------------------------------------------------------------
 *
 * EmitSos --
 *
 *	Emit a SOS marker plus data.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */
/*static*/ void
EmitSos (cPtr)
    CompressInfo * cPtr;
{
    int i,kk;

    EmitMarker (M_SOS);

    Emit2bytes (2*cPtr->compsInScan + 2 + 1 + 3);	/* length */

    EmitByte (cPtr->compsInScan);

    for (i = 0; i < cPtr->compsInScan; i++) {
	EmitByte ((*(cPtr->curCompInfo+i))->componentId);
	EmitByte (((*(cPtr->curCompInfo+i))->dcTblNo << 4)
		   + (*(cPtr->curCompInfo+i))->acTblNo);
        kk=0;
    }

    EmitByte (0);		/* Spectral selection start */
    EmitByte (63);	/* Spectral selection end */
    EmitByte (0);		/* Successive approximation */
}

/*
 *--------------------------------------------------------------
 *
 * EmitJfifApp0 --
 *
 *	Emit a JFIF-compliant APP0 marker
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------
 */
/*static*/ void
EmitJfifApp0 (cPtr)
    CompressInfo *cPtr;
{

    /*
     * Header structure:
     * Length of APP0 block	(2 bytes)
     * Block ID			(4 bytes - ASCII "JFIF")
     * Zero byte		(1 byte to terminate the ID string)
     * Version Major, Minor	(2 bytes - 0x01, 0x01)
     * Units			(1 byte - 0x00 = none, 0x01 = inch, 0x02 = cm)
     * Xdpu			(2 bytes - dots per unit horizontal)
     * Ydpu			(2 bytes - dots per unit vertical)
     * Thumbnail X size		(1 byte)
     * Thumbnail Y size		(1 byte)
     */

    EmitMarker (M_APP0);
    Emit2bytes (2 + 4 + 1 + 2 + 1 + 2 + 2 + 1 + 1);	/* length */
    EmitByte (0x4A);	/* Identifier: ASCII "JFIF" */
    EmitByte (0x46);
    EmitByte (0x49);
    EmitByte (0x46);
    EmitByte (0);
    EmitByte (1);	/* Major version */
    EmitByte (1);	/* Minor version */
    EmitByte (cPtr->densityUnit);	/* Pixel size information */
    Emit2bytes ((int)cPtr->Xdensity);
    Emit2bytes ((int)cPtr->Ydensity);
    EmitByte (0);	/* No thumbnail image */
    EmitByte (0);
}

/*
 *--------------------------------------------------------------
 *
 * WriteFileTrailer --
 *
 *	Write the End of image marker at the end of a JPEG file.
 *
 *	XXX: This is hardwored into stdout.
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
WriteFileTrailer (cPtr)
    CompressInfo *cPtr;
{
    EmitMarker (M_EOI);
}

/*
 *--------------------------------------------------------------
 *
 * WriteScanHeader --
 *
 *	Write the start of a scan (everything through the SOS marker).
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
WriteScanHeader (cPtr)
    CompressInfo *cPtr;
{
    int i,kk;

    /*
     * Emit Huffman tables.  Note that EmitDht takes care of
     * suppressing duplicate tables.
     */
    for (i = 0; i < cPtr->compsInScan; i++) {
	EmitDht (cPtr, (*(cPtr->curCompInfo+i))->dcTblNo, 0);
	EmitDht (cPtr, (*(cPtr->curCompInfo+i))->acTblNo, 1);
         kk=0;
    }

    /*
     * Emit DRI if required --- note that DRI value could change for each
     * scan. If it doesn't, a tiny amount of space is wasted in
     * multiple-scan files. We assume DRI will never be nonzero for one
     * scan and zero for a later one.
     */
    if (cPtr->restartInterval)
	EmitDri (cPtr);

    EmitSos (cPtr);
}

/*
 *--------------------------------------------------------------
 *
 * WriteFileHeader --
 *
 *	Write the file header.
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
WriteFileHeader (cPtr)
    CompressInfo *cPtr;
{
    int /*char*/ qtInUse[4];
    int i, prec;
    int isBaseline,kk;

    /*
     * First the SOI marker
     */
    EmitMarker (M_SOI);	/* first the SOI */

    /*
     * Next the JFIF APP0
     */
    EmitJfifApp0 (cPtr);
   
    /*
     * Emit DQT for each quantization table that we're using.
     */
    for (i = 0; i < 4; i++) {
	(*(qtInUse+i)) = 0;
    }

    for (i = 0; i < cPtr->numComponents; i++) {
	*(qtInUse+((*(cPtr->compInfo+i)).quantTblNo)) = 1;
    }

    prec = 0;
    for (i = 0; i < 4; i++) {
	if (*(qtInUse+i))
	    prec += EmitDqt (cPtr, i);
       kk=0;
    }

    /*
     * Now prec is nonzero iff there are any 16-bit quant tables.
     */

    /*
     * Check for a non-baseline specification.
     * Note we assume that Huffman table numbers won't be changed later.
     */
    isBaseline = 1;
    if (cPtr->dataPrecision != 8) {
	isBaseline = 0;
    }
    for (i = 0; i < cPtr->numComponents; i++) {
	if (((*(cPtr->compInfo+i)).dcTblNo > 1) || 
	    ((*(cPtr->compInfo+i)).acTblNo > 1)) {
	    isBaseline = 0;
	}
    }
    if (prec) {
	isBaseline = 0;
    }

    /*
     * Emit the proper SOF marker
     */
    if (isBaseline) {
	EmitSof (cPtr, M_SOF0);
    } else {
	EmitSof (cPtr, M_SOF1);
    }
}
