/*
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

#ifdef __STDC__
#define P(s) s
#else
#define P(s) ()
#endif

/* huffc.c */
void FlushBytes P((void));
void HuffEncoderInit P((CompressInfo * cPtr));
void HuffEncode P((CompressInfo * cPtr, MCU mcu));
void HuffEncoderTerm P((void));

/* huffd.c */
void HuffDecoderInit P((DecompressInfo * dcPtr));
void DecodeMCUrle P((DecompressInfo * dcPtr, MCU mcuRLE));

/* main.c */
int ReadJpegData P((char *buffer, int numBytes));
int WriteJpegData P((char *buffer, int numBytes));
int main P((int argc, char **argv));

/* read.c */
void ReadFileHeader P((DecompressInfo * dcPtr));
int ReadScanHeader P((DecompressInfo * dcPtr));

/* write.c */
void WriteFileTrailer P((CompressInfo * cPtr));
void WriteScanHeader P((CompressInfo * cPtr));
void WriteFileHeader P((CompressInfo * cPtr));

/* util.c */
int JroundUp P((int a, int b));
void DecoderStructInit P((DecompressInfo * dcPtr));
void CopyDecoderVars P((DecompressInfo * dcPtr, CompressInfo *enPtr));

/* mcu.c */
void InitMcuTable P((int numMCU, int blocksInMCU));
void PrintMCU P((int blocksInMCU, MCU mcu));

#undef P
