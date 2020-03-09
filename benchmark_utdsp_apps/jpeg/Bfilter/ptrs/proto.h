/*
 * proto.h
 *
 */

#ifdef __STDC__
# define	P(s) s
#else
# define P(s) ()
#endif


/* huffc.c */
void FlushBytes P((void ));
void HuffEncoderInit P((CompressInfo *cPtr ));
void HuffEncode P((CompressInfo *cPtr , MCU mcu ));
void HuffEncoderTerm P((void ));

/* huffd.c */
void HuffDecoderInit P((DecompressInfo *dcPtr ));
void DecodeMCUrle P((DecompressInfo *dcPtr , MCU mcuRLE ));

/* main.c */
int ReadJpegData P((/*char*/int *buffer , int numBytes ));
int WriteJpegData P((/*char*/int *buffer , int numBytes ));
int main P((/*int argc , char **argv */));

/* read.c */
void ReadFileHeader P((DecompressInfo *dcPtr ));
int ReadScanHeader P((DecompressInfo *dcPtr ));

/* write.c */
void WriteFileTrailer P((CompressInfo *cPtr ));
void WriteScanHeader P((CompressInfo *cPtr ));
void WriteFileHeader P((CompressInfo *cPtr ));

/* util.c */
int JroundUp P((int a , int b ));
void DecoderStructInit P((DecompressInfo *dcPtr ));
void CopyDecoderVars P((DecompressInfo *dcPtr , CompressInfo *enPtr ));

/* mcu.c */
void InitMcuTable P((int numMCU , int blocksInMCU ));
/*void PrintMCU P((int blocksInMCU , MCU mcu ));*/

#undef P
