/*
 * jpeg.h --
 *
 */

/*typedef unsigned char uchar;*/
typedef int ushort;
typedef int uint;

/*
 * The following structure stores basic information about one component.
 */
typedef struct JpegComponentInfo {
    /*
     * These values are fixed over the whole image.
     * They are read from the SOF marker.
     */
    int componentId;          /* identifier for this component (0..255) */
    int componentIndex;       /* its index in SOF or cPtr->compInfo[] */
    int hSampFactor;          /* horizontal sampling factor (1..4) */
    int vSampFactor;          /* vertical sampling factor (1..4) */
    int quantTblNo;           /* quantization table selector (0..3) */

    /*
     * These values may vary between scans
    /* They are read from the SOS marker.
    */
    int dcTblNo;              /* DC entropy table selector (0..3) */
    int acTblNo;              /* AC entropy table selector (0..3) */

    /* 
     * These values are computed during startup.
     */
    int trueCompWidth;          /* component's image width in samples */
    int trueCompHeight;         /* component's image height in samples */

    /*
     * the above are the logical dimensions of the Downsampled image
     * These values are computed before starting a scan of the component
     */
    int MCUwidth;             /* number of blocks per MCU, horizontally */
    int MCUheight;            /* number of blocks per MCU, vertically */
    int MCUblocks;            /* MCUwidth * MCUheight */

    /*
     * The next two values are the trueCompXXX values rounded up
     * to multiples of the MCU dimensions; these are the working
     * dimensions of the array as it is passed through the DCT or IDCT
     * step.  NOTE: these values differ depending on whether the
     * component is interleaved or not!!
     */
    int downsampledWidth;       /* image width in samples, after expansion */
    int downsampledHeight;      /* image height in samples, after expansion */
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
    /*uchar*/int bits[17];
    /*uchar*/int huffval[256];

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
    uint ehufco[256];
    /*char*/int ehufsi[256];

    uint mincode[17];
    int maxcode[18];
    int valptr[17];
    int numbits[256];
    int value[256];
} HuffmanTable;

/*
 * One of the following structures is used to pass around the
 * compression information.
 */
typedef struct CompressInfo {
    int imageWidth;             /* input image width */
    int imageHeight;            /* input image height */
    int dataPrecision;          /* bits of precision in image data */

    /*
     * These three values are not used by the JPEG code, only copied
     * into the JFIF APP0 marker.  densityUnit can be 0 for unknown, 1
     * for dots/inch, or 2 for dots/cm.  Note that the pixel aspect ratio
     * is defined by Xdensity/Ydensity even when densityUnit=0.
     */
    /*uchar*/int densityUnit;          /* JFIF code for pixel size units */
    uint Xdensity;            /* Horizontal pixel density */
    uint Ydensity;            /* Vertical pixel density */


    /*
     *compInfo[i] describes component that appears i'th in SOF
     */
    JpegComponentInfo *compInfo;
    int numComponents;        /* # of color components in JPEG image */

    /*
     * Pointers to coefficient quantization tables, or NULL if not
     * defined
     */
    int *quantTblPtrs[4];

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
    int restartInterval;      /* MCUs/(restart interval), 0 -> no restart */
    int restartInRows;          /* if > 0, MCU rows per restart interval */

    /*
     * These fields are computed during JpegCompress startup
     */
    int maxHsampFactor;       /* largest hSampFactor */
    int maxVsampFactor;       /* largest vSampFactor */

    /*
     * These fields are valid during any one scan
     */
    int compsInScan;          /* # of JPEG components output this time */

    /*
     * *curCompInfo[i] describes component that appears i'th in SOS
     */
    JpegComponentInfo *curCompInfo[4];

    int MCUsPerRow;             /* # of MCUs across the image */
    int MCUrowsInScan;          /* # of MCU rows in the image */

    int blocksInMCU;          /* # of DCT blocks per MCU */

    /*
     * MCUmembership[i] is index in curCompInfo of component owning
     */
    int MCUmembership[10];

    /* 
     * These fields are private data for the entropy encoder
     */
    int lastDcVal[4];         /* last DC coef for each comp */
    int restartsToGo;         /* MCUs left in this restart interval */
    int nextRestartNum;       /* # of next RSTn marker (0..7) */
} CompressInfo;

/*
 * One of the following structures is used to pass around the
 * decompression information.
 */
typedef struct DecompressInfo {
    /*
     * These fields are set by ReadFileHeader or ReadScanHeader
     */
    int imageWidth;             /* overall image width */
    int imageHeight;            /* overall image height */

    int dataPrecision;        /* bits of precision in image data */

    /* These three values are not used by the JPEG code, merely copied */
    /* from the JFIF APP0 marker (if any). */
    /*uchar*/int densityUnit;          /* JFIF code for pixel size units */
    uint Xdensity;            /* Horizontal pixel density */
    uint Ydensity;            /* Vertical pixel density */

    int numComponents;        /* # of color components in JPEG image */
    JpegComponentInfo *compInfo;
    /* compInfo[i] describes component that appears i'th in SOF */

    int *quantTblPtrs[4];
    /* ptrs to coefficient quantization tables, or NULL if not defined */

    HuffmanTable *dcHuffTblPtrs[4];
    HuffmanTable *acHuffTblPtrs[4];
    /* ptrs to Huffman coding tables, or NULL if not defined */

    int restartInterval;      /* MCUs per restart interval, 0 = no restart */

    /*
     * These fields are computed during JpegDecompress startup
     */
    int maxHsampFactor;       /* largest hSampFactor */
    int maxVsampFactor;       /* largest vSampFactor */

    /*
     * These fields are valid during any one scan
     */
    int compsInScan;          /* # of JPEG components input this time */

    /*
     * *curCompInfo[i] describes component that appears i'th in SOS
     */
    JpegComponentInfo *curCompInfo[4];

    int MCUsPerRow;             /* # of MCUs across the image */
    int MCUrowsInScan;          /* # of MCU rows in the image */

    /*
     * MCUmembership[i] is index in curCompInfo of component owning
     * i'th block in an MCU
     */
    int MCUmembership[10];
    int blocksInMCU;          /* # of DCT blocks per MCU */

    /*
     * these fields are private data for the entropy encoder
     */
    int lastDcVal[4];         /* last DC coef for each comp */
    int restartsToGo;         /* MCUs left in this restart interval */
    int nextRestartNum;       /* # of next RSTn marker (0..7) */
} DecompressInfo;

#define RST0    0xD0            /* RST0 marker code */

/*
 * The following variables keep track of the input buffer for the JPEG
 * data, which is read by ReadJpegData
 */
extern /*uchar*/int inputBuffer[];     /* Input buffer for JPEG data */
extern int numInputBytes;       /* The total number of bytes in inputBuffer */
extern int maxInputBytes;       /* Size of inputBuffer */
extern int inputBufferOffset;   /* Offset of current byte */

/*
 *--------------------------------------------------------------
 *
 * GetJpegChar, UnGetJpegChar --
 *
 *      Macros to get the next character from the input stream.
 *
 * Results:
 *      GetJpegChar returns the next character in the stream, or EOF
 *      UnGetJpegChar returns nothing.
 *
 * Side effects:
 *      A byte is consumed or put back into the inputBuffer.
 *
 *--------------------------------------------------------------
 */
#define GetJpegChar()                                                   \
    ((inputBufferOffset < numInputBytes)?                               \
     (/*(inputBufferOffset+=4),*/*(inputBuffer+(inputBufferOffset++))):             \
     (numInputBytes = 2+ReadJpegData(inputBuffer+2,JPEG_BUF_SIZE-2),    \
      inputBufferOffset = 2,                                            \
      ((inputBufferOffset < numInputBytes)?                             \
       (/*(inputBufferOffset+=4),*/*(inputBuffer+(inputBufferOffset++))):         \
       -1/*EOF*/)))

#define UnGetJpegChar(ch) \
(/*(inputBufferOffset-=4),*/*(inputBuffer+(--inputBufferOffset))=(ch))
