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

/*
 * Size of the output buffer
 */
#define JPEG_BUF_SIZE   4096
#define RST0    0xD0            /* RST0 marker code */

extern /*char*/int outputBuffer[JPEG_BUF_SIZE];       /* output buffer */
extern int bytesInBuffer;

/*
 *--------------------------------------------------------------
 *
 * EmitByte --
 *
 *	Write a single byte out to the output buffer, and
 *	flush if it's full.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The outp[ut buffer may get flushed.
 *
 *--------------------------------------------------------------
 */
#define EmitByte(val)  {						\
    if (bytesInBuffer >= JPEG_BUF_SIZE) {				\
	FlushBytes();							\
    }									\
    outputBuffer[bytesInBuffer++] = (/*char*/int)(val);			\
}
