/*
 * main.c --
 *
 * This is the main routine for the jpeg decoder.  Large parts are
 * stolen from the IJG code, so:
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

/*main*/
    DecompressInfo dcInfo;
    DecompressInfo *dcInfob;    /*banny added*/
    CompressInfo enInfo;
    CompressInfo *enInfob;        /*banny added*/
    MCU mcu;
    RLE *rle;


int
main(/*argc, argv*/)
    /*int argc;
    char **argv;*/
{
    int i, j, k, l;
    int maxMcu;
    int b;

    dcInfob=&dcInfo;    /* banny added */
    enInfob=&enInfo;    /* banny added */

    /*memset (&dcInfo, 0, sizeof(dcInfo));*/
    dcInfob->imageWidth=
    dcInfob->imageHeight=
    dcInfob->dataPrecision=
    dcInfob->densityUnit=
    dcInfob->Xdensity=
    dcInfob->Ydensity=
    dcInfob->numComponents= 
    dcInfob->restartInterval=
    dcInfob->maxHsampFactor=
    dcInfob->maxVsampFactor=
    dcInfob->compsInScan=
    dcInfob->MCUsPerRow=
    dcInfob->MCUrowsInScan=
    dcInfob->blocksInMCU=
    dcInfob->restartsToGo=
    dcInfob->nextRestartNum=0;
    for(b=0;b<10;b++) *(dcInfob->MCUmembership+b)=0;
    for(b=0;b<4;b++) *(dcInfob->lastDcVal+b)=0;
    dcInfob->compInfo=0;
    for(b=0;b<4;b++) {*(dcInfob->quantTblPtrs+b)=0;
                      *(dcInfob->dcHuffTblPtrs+b)=0;
                      *(dcInfob->acHuffTblPtrs+b)=0;
                      *(dcInfob->curCompInfo+b)=0;}
    
    /*memset (&enInfo, 0, sizeof(enInfo));*/
    enInfob->imageWidth=
    enInfob->imageHeight=
    enInfob->dataPrecision=
    enInfob->densityUnit=
    enInfob->Xdensity=
    enInfob->Ydensity=
    enInfob->numComponents= 
    enInfob->restartInterval=
    enInfob->restartInRows=
    enInfob->maxHsampFactor=
    enInfob->maxVsampFactor=
    enInfob->compsInScan=
    enInfob->MCUsPerRow=
    enInfob->MCUrowsInScan=
    enInfob->blocksInMCU=
    enInfob->restartsToGo=
    enInfob->nextRestartNum=0;  
    for(b=0;b<10;b++) *(enInfob->MCUmembership+b)=0;
    for(b=0;b<4;b++) *(enInfob->lastDcVal+b)=0;
    enInfob->compInfo=0;
    for(b=0;b<4;b++) {*(enInfob->quantTblPtrs+b)=0;
                      *(enInfob->dcHuffTblPtrs+b)=0;
                      *(enInfob->acHuffTblPtrs+b)=0;
                      *(enInfob->curCompInfo+b)=0;}
    
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
	/*fprintf (stderr, "Empty JPEG file\n");
	exit (1);*/
    }
    DecoderStructInit (&dcInfo);
    HuffDecoderInit (&dcInfo);

    /*
     * Decompress everything into MCU's
     */
    maxMcu = dcInfob->MCUsPerRow * dcInfob->MCUrowsInScan;
    InitMcuTable (maxMcu, dcInfob->blocksInMCU);
    /*for (i = 0; i < maxMcu; i++) {
        mcu = MakeMCU(&dcInfo);
	DecodeMCUrle (&dcInfo,MakeMCU(&dcInfo));
    }*/
        DecodeMCUrle (&dcInfo,MakeMCU(&dcInfo));
        DecodeMCUrle (&dcInfo,MakeMCU(&dcInfo));
        DecodeMCUrle (&dcInfo,MakeMCU(&dcInfo));
        DecodeMCUrle (&dcInfo,MakeMCU(&dcInfo));
        DecodeMCUrle (&dcInfo,MakeMCU(&dcInfo));
        DecodeMCUrle (&dcInfo,MakeMCU(&dcInfo));

    
    if (ReadScanHeader (&dcInfo)) {
	/*fprintf (stderr, "Warning: multiple scans detected in JPEG file\n");
	fprintf (stderr, "         not currently supported\n");
	fprintf (stderr, "         ignoring extra scans\n");*/
    }

    /*
     * At this point, you can filter all the MCU's if you want.
     * For example, this loop maps all high frequency ac values 
     * (i.e., zigzag index >= 4) that are low energy (value = +/-1)
     * to zero.
     */
    for (i = 0; i < numMCU; i++) {
	mcu = mcuTable[i];
	for (j = 0; j < dcInfob->blocksInMCU; j++) {
	    rle = mcu+j;
	    for (k=0, l=0; k<rle->numAC; k++) {
		/*
		 * Copy if zigzag index < 4 or value isn't +/- 1
		 */
		if ((rle->ac[k].index < 4) ||
		    ((rle->ac[k].value != 1) && (rle->ac[k].value != -1))) {
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
    /*fflush(stdout);*/
    /*if (ferror(stdout)) {
	fprintf (stderr, "Output file write error\n");
    }*/
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
    /*char*/int *buffer;		/* Place to put new data */
    int numBytes;		/* Number of bytes to put */
{
    /*return fread(buffer, 1, numBytes, stdin);*/
    return input_dsp(buffer,numBytes,3);
    /*output_dsp(buffer,numBytes*4,3);*/
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
    /*char*/int *buffer;               /* Data to write */
    int numBytes;               /* Number of bytes to write */
{
    /*return fwrite(buffer, 1, numBytes, stdout);*/
    output_dsp(buffer,numBytes*4,3);
}
