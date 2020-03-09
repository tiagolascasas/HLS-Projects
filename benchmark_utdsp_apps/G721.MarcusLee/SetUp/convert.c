#include <stdio.h>

#define SIGN_BIT        (0x80)          /* Sign bit for a A-law byte. */
#define QUANT_MASK      (0xf)           /* Quantization field mask. */
#define NSEGS           (8)             /* Number of A-law segments. */
#define SEG_SHIFT       (4)             /* Left shift for segment number. */
#define SEG_MASK        (0x70)          /* Segment field mask. */

static short seg_end[8] = {0xFF, 0x1FF, 0x3FF, 0x7FF,
                            0xFFF, 0x1FFF, 0x3FFF, 0x7FFF};

#define BIAS            (0x84)          /* Bias for linear code. */

int ulaw2linear( unsigned char );
unsigned char linear2ulaw( int );
static int search(int, short*, int);

void main (int argc, char *argv[])
  { 
  FILE *fd, *fd1;
  unsigned char ulaw; 
  short linearPCM;
  int i,n=0;

  if(   (argc != 4) 
     || (*argv[1] != '-') 
     || (*(argv[1]+1) != 'u' &&  *(argv[1]+1) != 'p') )
    {
    printf("==================================================\n");
    printf("usage: convert -[u|p] source_file destination_file\n\n");
    printf("       -u option to convert from ulaw to linearPCM\n");
    printf("       -p option to convert from linearPCM to ulaw\n");
    printf("==================================================\n");
    exit(1);
    }
  fd = fopen (argv[2],"rb");
  if(fd==NULL)
    {
    printf("error: cannot open source_file\n");
    exit(1);
    }
  fd1 = fopen (argv[3], "wb");
  if(fd1==NULL)
    {
    printf("error: cannot open destination_file\n");
    exit(1);
    }

  if( (*argv[1]=='-') && (*(argv[1]+1) == 'u') )
    {
    while(1)
      { 
      i = fread(&ulaw, sizeof(unsigned char), 1, fd);
      if(i != 1)
        {
        printf("linearPCM file size: %d elements\n",n);
        fclose(fd);
        fclose(fd1);
        exit(1);
        }
      n++;
      linearPCM = (short)ulaw2linear ( ulaw );
      fwrite (&linearPCM, sizeof(short), 1, fd1); 
      }
    }
  else if ( (*argv[1]=='-') && (*(argv[1]+1) == 'p') )
    {
    while(1)
      {
      i = fread(&linearPCM, sizeof(short), 1, fd);
      if(i != 1)
        {
        printf("ulaw file size: %d elements\n",n);
        fclose(fd);
        fclose(fd1);
        exit(1);
        }
      n++;
      ulaw = linear2ulaw ( (int)linearPCM );
      fwrite (&ulaw, sizeof(unsigned char), 1, fd1);
      }
    }
  }

/*
 * linear2ulaw() - Convert a linear PCM value to u-law
 *
 * In order to simplify the encoding process, the original linear magnitude
 * is biased by adding 33 which shifts the encoding range from (0 - 8158) to
 * (33 - 8191). The result can be seen in the following encoding table:
 *
 *      Biased Linear Input Code        Compressed Code
 *      ------------------------        ---------------
 *      00000001wxyza                   000wxyz
 *      0000001wxyzab                   001wxyz
 *      000001wxyzabc                   010wxyz
 *      00001wxyzabcd                   011wxyz
 *      0001wxyzabcde                   100wxyz
 *      001wxyzabcdef                   101wxyz
 *      01wxyzabcdefg                   110wxyz
 *      1wxyzabcdefgh                   111wxyz
 *
 * Each biased linear code has a leading 1 which identifies the segment
 * number. The value of the segment number is equal to 7 minus the number
 * of leading 0's. The quantization interval is directly available as the
 * four bits wxyz.  * The trailing bits (a - h) are ignored.
 *
 * Ordinarily the complement of the resulting code word is used for
 * transmission, and so the code word is complemented before it is returned.
 *
 * For further information see John C. Bellamy's Digital Telephony, 1982,
 * John Wiley & Sons, pps 98-111 and 472-476.
 */
unsigned char linear2ulaw( int pcm_val) /* 2's complement (16-bit range) */
  {
  int mask;
  int seg;
  unsigned char uval;

  /* Get the sign and the magnitude of the value. */
  if (pcm_val < 0) 
    {
    pcm_val = BIAS - pcm_val;
    mask = 0x7F;
    } 
  else 
    {
    pcm_val += BIAS;
    mask = 0xFF;
    }

  /* Convert the scaled magnitude to segment number. */
  seg = search(pcm_val, seg_end, 8);

  /*
   * Combine the sign, segment, quantization bits;
   * and complement the code word.
   */
  if (seg >= 8)           /* out of range, return maximum value. */
    return (0x7F ^ mask);
  else 
    {
    uval = (seg << 4) | ((pcm_val >> (seg + 3)) & 0xF);
    return (uval ^ mask);
    }
  }

/*
 * ulaw2linear() - Convert a u-law value to 16-bit linear PCM
 *
 * First, a biased linear code is derived from the code word. An unbiased
 * output can then be obtained by subtracting 33 from the biased code.
 *
 * Note that this function expects to be passed the complement of the
 * original code word. This is in keeping with ISDN conventions.
 */

int ulaw2linear( unsigned char   u_val)
  {
  int t;

  /* Complement to obtain normal u-law value. */
  u_val = ~u_val;

  /*
   * Extract and bias the quantization bits. Then
   * shift up by the segment number and subtract out the bias.
   */
  t = ((u_val & QUANT_MASK) << 3) + BIAS;
  t <<= ((unsigned)u_val & SEG_MASK) >> SEG_SHIFT;

  return ((u_val & SIGN_BIT) ? (BIAS - t) : (t - BIAS));
  }

static int search( int val, short *table, int size )
  {
  int i;
  for (i = 0; i < size; i++) 
    {
    if (val <= *table++)
    return (i);
    }
  return (size);
  }

/*
 * linear2alaw() - Convert a 16-bit linear PCM value to 8-bit A-law
 *
 * linear2alaw() accepts an 16-bit integer and encodes it as A-law data.
 *
 *              Linear Input Code       Compressed Code
 *      ------------------------        ---------------
 *      0000000wxyza                    000wxyz
 *      0000001wxyza                    001wxyz
 *      000001wxyzab                    010wxyz
 *      00001wxyzabc                    011wxyz
 *      0001wxyzabcd                    100wxyz
 *      001wxyzabcde                    101wxyz
 *      01wxyzabcdef                    110wxyz
 *      1wxyzabcdefg                    111wxyz
 *
 * For further information see John C. Bellamy's Digital Telephony, 1982,
 * John Wiley & Sons, pps 98-111 and 472-476.
 */
unsigned char
linear2alaw(
        int             pcm_val)        /* 2's complement (16-bit range) */
{
        int             mask;
        int             seg;
        unsigned char   aval;

        if (pcm_val >= 0) {
                mask = 0xD5;            /* sign (7th) bit = 1 */
        } else {
                mask = 0x55;            /* sign bit = 0 */
                pcm_val = -pcm_val - 8;
        }

        /* Convert the scaled magnitude to segment number. */
        seg = search(pcm_val, seg_end, 8);

        /* Combine the sign, segment, and quantization bits. */

        if (seg >= 8)           /* out of range, return maximum value. */
                return (0x7F ^ mask);
        else {
                aval = seg << SEG_SHIFT;
                if (seg < 2)
                        aval |= (pcm_val >> 4) & QUANT_MASK;
                else
                        aval |= (pcm_val >> (seg + 3)) & QUANT_MASK;
                return (aval ^ mask);
        }
}

/*
 * alaw2linear() - Convert an A-law value to 16-bit linear PCM
 *
 */
int
alaw2linear(
        unsigned char   a_val)
{
        int             t;
        int             seg;

        a_val ^= 0x55;

        t = (a_val & QUANT_MASK) << 4;
        seg = ((unsigned)a_val & SEG_MASK) >> SEG_SHIFT;
        switch (seg) {
        case 0:
                t += 8;
                break;
        case 1:
                t += 0x108;
                break;
        default:
                t += 0x108;
                t <<= seg - 1;
        }
        return ((a_val & SIGN_BIT) ? t : -t);
}

