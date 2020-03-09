/*
 * util.c --
 */ 

#include "traps.h"
#include "jpeg.h"
#include "rle.h"
#include "proto.h"

#define MAX(a,b)        ((a)>(b)?(a):(b))
#define MIN(a,b)        ((a)<(b)?(a):(b))

/*DecoderStructInit*/
    JpegComponentInfo *compPtr;


/*
 *--------------------------------------------------------------
 *
 * JroundUp --
 *
 *      Compute a rounded up to next multiple of b; a >= 0, b > 0 
 *
 * Results:
 *      Rounded up value.
 *
 * Side effects:
 *      None.
 *
 *--------------------------------------------------------------
 */
int
JroundUp (a, b)
    int a, b;
{
    a += b - 1;
    return a - (a % b);
}

/*
 *--------------------------------------------------------------
 *
 * DecoderStructInit --
 *
 *      Initalize the rest of the fields in the decompression
 *      structure.
 *
 * Results:
 *      None.
 *
 * Side effects:
 *      None.
 *
 *--------------------------------------------------------------
 */
void
DecoderStructInit (dcPtr)
    DecompressInfo *dcPtr;

{
    int ci;

    /*
     * Compute maximum sampling factors; check factor validity
     */
    dcPtr->maxHsampFactor = 1;
    dcPtr->maxVsampFactor = 1;
    for (ci = 0; ci < dcPtr->numComponents; ci++) {
        compPtr = &dcPtr->compInfo[ci];
        if ((compPtr->hSampFactor <= 0) || (compPtr->hSampFactor > 4) ||
            (compPtr->vSampFactor <= 0) || (compPtr->vSampFactor > 4)) {
            /*fprintf (stderr,  "Error: Bogus sampling factors");
            exit(1);*/
        }
        dcPtr->maxHsampFactor = MAX(dcPtr->maxHsampFactor,compPtr->hSampFactor);
        dcPtr->maxVsampFactor = MAX(dcPtr->maxVsampFactor,compPtr->vSampFactor);
    }

    /*
     * Compute logical downsampled dimensions of components
     */
    for (ci = 0; ci < dcPtr->numComponents; ci++) {
        compPtr = &dcPtr->compInfo[ci];
        compPtr->trueCompWidth = (dcPtr->imageWidth*compPtr->hSampFactor
                    + dcPtr->maxHsampFactor - 1) / dcPtr->maxHsampFactor;
        compPtr->trueCompHeight = (dcPtr->imageHeight*compPtr->vSampFactor
                    + dcPtr->maxVsampFactor - 1) / dcPtr->maxVsampFactor;
    }


    if (dcPtr->compsInScan == 1) {
        compPtr = dcPtr->curCompInfo[0];

        /*
         * for noninterleaved scan, always one block per MCU
         */
        compPtr->MCUwidth = 1;
        compPtr->MCUheight = 1;
        compPtr->MCUblocks = 1;

        /*
         * compute physical dimensions of component
         */
        compPtr->downsampledWidth = JroundUp (compPtr->trueCompWidth, 8);
        compPtr->downsampledHeight = JroundUp (compPtr->trueCompHeight, 8);

        dcPtr->MCUsPerRow = compPtr->downsampledWidth / 8;
        dcPtr->MCUrowsInScan = compPtr->downsampledHeight / 8;

        /*
         * Prepare array describing MCU composition
         */
        dcPtr->blocksInMCU = 1;
        dcPtr->MCUmembership[0] = 0;
    } else {
        int ci, mcublks;

        if (dcPtr->compsInScan > 4) {
            /*fprintf (stderr, "Too many components for interleaved scan");
            exit (1);*/
        }

        dcPtr->MCUsPerRow = (dcPtr->imageWidth +
                             8*dcPtr->maxHsampFactor - 1) /
                            (8*dcPtr->maxHsampFactor);
        dcPtr->MCUrowsInScan = (dcPtr->imageHeight +
                                dcPtr->maxVsampFactor*8 - 1) /
                               (dcPtr->maxVsampFactor * 8);
        dcPtr->blocksInMCU = 0;

        for (ci = 0; ci < dcPtr->compsInScan; ci++) {
            compPtr = dcPtr->curCompInfo[ci];

            /*
             * for interleaved scan, sampling factors give # of blocks per
             * component
             */
            compPtr->MCUwidth = compPtr->hSampFactor;
            compPtr->MCUheight = compPtr->vSampFactor;
            compPtr->MCUblocks = compPtr->MCUwidth * compPtr->MCUheight;

            /*
             * compute physical dimensions of component
             */
            compPtr->downsampledWidth =
                    JroundUp(compPtr->trueCompWidth, 8*compPtr->MCUwidth);
            compPtr->downsampledHeight =
                    JroundUp (compPtr->trueCompHeight, 8*compPtr->MCUheight);

            /*
             * Prepare array describing MCU composition
             */
            mcublks = compPtr->MCUblocks;
            if (dcPtr->blocksInMCU + mcublks > 10) {
                /*fprintf (stderr,
                         "Sampling factors too large for interleaved scan");
                exit (1);*/
            }
            while (mcublks-- > 0) {
                dcPtr->MCUmembership[dcPtr->blocksInMCU++] = ci;
            }
        }
    }
}

/*
 *--------------------------------------------------------------
 *
 * CopyDecoderVars --
 *
 *      Copy the appropraite variables from the decoder into the
 *      encoder.  These are listed in the code.  The rest of
 *      the variables should be set up on a per scan basis.
 *
 * Results:
 *      None
 *
 * Side effects:
 *      None
 *
 *--------------------------------------------------------------
 */
void
CopyDecoderVars(dcPtr, enPtr)
    DecompressInfo *dcPtr;
    CompressInfo *enPtr;
{
    int i;

    enPtr->Xdensity = dcPtr->Xdensity;
    enPtr->Ydensity = dcPtr->Ydensity;
    enPtr->blocksInMCU = dcPtr->blocksInMCU;
    enPtr->compInfo = dcPtr->compInfo;
    enPtr->dataPrecision = dcPtr->dataPrecision;
    enPtr->densityUnit = dcPtr->densityUnit;
    enPtr->imageHeight = dcPtr->imageHeight;
    enPtr->imageWidth = dcPtr->imageWidth;
    enPtr->maxHsampFactor = dcPtr->maxHsampFactor;
    enPtr->maxVsampFactor = dcPtr->maxVsampFactor;
    enPtr->numComponents = dcPtr->numComponents;
    enPtr->restartInterval = dcPtr->restartInterval;
    enPtr->MCUsPerRow = dcPtr->MCUsPerRow;
    enPtr->MCUrowsInScan = dcPtr->MCUrowsInScan;
    for (i=0; i<10; i++) {
        enPtr->MCUmembership[i] = dcPtr->MCUmembership[i];
    }
    for (i=0; i<4; i++) {
        enPtr->acHuffTblPtrs[i] = dcPtr->acHuffTblPtrs[i];
        enPtr->dcHuffTblPtrs[i] = dcPtr->dcHuffTblPtrs[i];
        enPtr->quantTblPtrs[i] = dcPtr->quantTblPtrs[i];
        enPtr->curCompInfo[i] = dcPtr->curCompInfo[i];
        enPtr->lastDcVal[i] = 0;
    }
    enPtr->compsInScan = enPtr->numComponents;
}
