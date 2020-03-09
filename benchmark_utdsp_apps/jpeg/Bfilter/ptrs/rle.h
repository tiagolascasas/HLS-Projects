/*
 * rle.h --
 *
 */


typedef struct RleElem {
    /*uchar*/int index;
    int value;
} RleElem;

typedef struct RLE {
    int dc;
    /*uchar*/int numAC;
    RleElem ac[63];
} RLE;

/*#define ALLOC_RLE()     ((RLE *)malloc(sizeof(RLE)))*/

/*
 * An MCU (minimum coding unit) is an array of RLE blocks
 */
typedef RLE *MCU;

extern MCU *mcuTable;
extern int numMCU;
extern int currMCU;

#define MakeMCU(dcPtr)          (mcuTable[numMCU++])
