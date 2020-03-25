/*
+--------------------------------------------------------------------------+
| CHStone : a suite of benchmark programs for C-based High-Level Synthesis |
| ======================================================================== |
|                                                                          |
| * Collected and Modified : Y. Hara, H. Tomiyama, S. Honda,               |
|                            H. Takada and K. Ishii                        |
|                            Nagoya University, Japan                      |
|                                                                          |
| * Remark :                                                               |
|    1. This source code is modified to unify the formats of the benchmark |
|       programs in CHStone.                                               |
|    2. Test vectors are added for CHStone.                                |
|    3. If "main_result" is 0 at the end of the program, the program is    |
|       correctly executed.                                                |
|    4. Please follow the copyright of each benchmark program.             |
+--------------------------------------------------------------------------+
*/
/* crypto/bf/bf.c */
/* Copyright (C) 1995-1997 Eric Young (eay@mincom.oz.au)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@mincom.oz.au).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@mincom.oz.au).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@mincom.oz.au)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@mincom.oz.au)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */
#include <stdio.h>
#include "bf.h"

void BF_set_key (int len, unsigned char *data);
void BF_encrypt (BF_LONG * data, int encrypt);
void BF_cfb64_encrypt (unsigned char *in, unsigned char *out, long length,
		       unsigned char *ivec, int *num, int encrypt);

void
local_memcpy (BF_LONG * s1, const BF_LONG * s2, int n)
{
  BF_LONG *p1;
  const BF_LONG *p2;

  p1 = s1;
  p2 = s2;

  while (n-- > 0)
    {
      *p1 = *p2;
      p1++;
      p2++;
    }
}

void
BF_set_key (int len, unsigned char *data)
{
  int i;
  BF_LONG *p, ri, in[2];
  unsigned char *d, *end;

  local_memcpy (key_P, bf_init_P, BF_ROUNDS + 2);
  local_memcpy (key_S, bf_init_S, 4 * 256);
  p = key_P;

  if (len > ((BF_ROUNDS + 2) * 4))
    len = (BF_ROUNDS + 2) * 4;

  d = data;
  end = &(data[len]);
  for (i = 0; i < (BF_ROUNDS + 2); i++)
    {
      ri = *(d++);
      if (d >= end)
	d = data;

      ri <<= 8;
      ri |= *(d++);
      if (d >= end)
	d = data;

      ri <<= 8;
      ri |= *(d++);
      if (d >= end)
	d = data;

      ri <<= 8;
      ri |= *(d++);
      if (d >= end)
	d = data;

      p[i] ^= ri;
    }

  in[0] = 0L;
  in[1] = 0L;
  for (i = 0; i < (BF_ROUNDS + 2); i += 2)
    {
      BF_encrypt (in, BF_ENCRYPT);
      p[i] = in[0];
      p[i + 1] = in[1];
    }

  p = key_S;
  for (i = 0; i < 4 * 256; i += 2)
    {
      BF_encrypt (in, BF_ENCRYPT);
      p[i] = in[0];
      p[i + 1] = in[1];
    }

}

void
BF_encrypt (data, encrypt)
     BF_LONG *data;
     int encrypt;
{
  register BF_LONG l, r, *p, *s;
  p = key_P;
  s = &(key_S[0]);
  l = data[0];
  r = data[1];

  if (encrypt)
    {
      l ^= p[0];

      BF_ENC (r, l, s, p[1]);
      BF_ENC (l, r, s, p[2]);
      BF_ENC (r, l, s, p[3]);
      BF_ENC (l, r, s, p[4]);
      BF_ENC (r, l, s, p[5]);
      BF_ENC (l, r, s, p[6]);
      BF_ENC (r, l, s, p[7]);
      BF_ENC (l, r, s, p[8]);
      BF_ENC (r, l, s, p[9]);
      BF_ENC (l, r, s, p[10]);
      BF_ENC (r, l, s, p[11]);
      BF_ENC (l, r, s, p[12]);
      BF_ENC (r, l, s, p[13]);
      BF_ENC (l, r, s, p[14]);
      BF_ENC (r, l, s, p[15]);
      BF_ENC (l, r, s, p[16]);
      r ^= p[BF_ROUNDS + 1];
    }
  else
    {
      l ^= p[BF_ROUNDS + 1];
      BF_ENC (r, l, s, p[16]);
      BF_ENC (l, r, s, p[15]);
      BF_ENC (r, l, s, p[14]);
      BF_ENC (l, r, s, p[13]);
      BF_ENC (r, l, s, p[12]);
      BF_ENC (l, r, s, p[11]);
      BF_ENC (r, l, s, p[10]);
      BF_ENC (l, r, s, p[9]);
      BF_ENC (r, l, s, p[8]);
      BF_ENC (l, r, s, p[7]);
      BF_ENC (r, l, s, p[6]);
      BF_ENC (l, r, s, p[5]);
      BF_ENC (r, l, s, p[4]);
      BF_ENC (l, r, s, p[3]);
      BF_ENC (r, l, s, p[2]);
      BF_ENC (l, r, s, p[1]);
      r ^= p[0];
    }
  data[1] = l & 0xffffffff;
  data[0] = r & 0xffffffff;
}

void
BF_cfb64_encrypt (in, out, length, ivec, num, encrypt)
     unsigned char *in;
     unsigned char *out;
     long length;
     unsigned char *ivec;
     int *num;
     int encrypt;
{
  register BF_LONG v0, v1, t;
  register int n;
  register long l;
  BF_LONG ti[2];
  unsigned char *iv, c, cc;

  n = *num;
  l = length;
  iv = (unsigned char *) ivec;
  if (encrypt)
    {
      while (l--)
	{
	  if (n == 0)
	    {
	      n2l (iv, v0);
	      ti[0] = v0;
	      n2l (iv, v1);
	      ti[1] = v1;
	      BF_encrypt ((unsigned long *) ti, BF_ENCRYPT);
	      iv = (unsigned char *) ivec;
	      t = ti[0];
	      l2n (t, iv);
	      t = ti[1];
	      l2n (t, iv);

	      iv = (unsigned char *) ivec;
	    }
	  c = *(in++) ^ iv[n];
	  *(out++) = c;
	  iv[n] = c;
	  n = (n + 1) & 0x07;
	}
    }
  else
    {
      while (l--)
	{
	  if (n == 0)
	    {
	      n2l (iv, v0);
	      ti[0] = v0;
	      n2l (iv, v1);
	      ti[1] = v1;
	      BF_encrypt ((unsigned long *) ti, BF_ENCRYPT);
	      iv = (unsigned char *) ivec;
	      t = ti[0];
	      l2n (t, iv);
	      t = ti[1];
	      l2n (t, iv);
	      iv = (unsigned char *) ivec;
	    }
	  cc = *(in++);
	  c = iv[n];
	  iv[n] = cc;
	  *(out++) = c ^ cc;
	  n = (n + 1) & 0x07;
	}
    }
  v0 = v1 = ti[0] = ti[1] = t = c = cc = 0;
  *num = n;
}

#define N 40

int
blowfish_main ()
{
  unsigned char ukey[8];
  unsigned char indata[N];
  unsigned char outdata[N];
  unsigned char ivec[8];
  int num;
  int i, j, k, l;
  int encordec;
  int check;

  num = 0;
  k = 0;
  l = 0;
  encordec = 1;
  check = 0;
  for (i = 0; i < 8; i++)
    {
      ukey[i] = 0;
      ivec[i] = 0;
    }
  BF_set_key (8, ukey);
  i = 0;
  while (k < KEYSIZE)
    {
      while (k < KEYSIZE && i < N)
	indata[i++] = in_key[k++];

      BF_cfb64_encrypt (indata, outdata, i, ivec, &num, encordec);

      for (j = 0; j < i; j++)
	check += (outdata[j] != out_key[l++]);

      i = 0;
    }
  return check;
}

int
main ()
{
  int main_result;

      main_result = 0;
      main_result = blowfish_main ();

      printf ("%d\n", main_result);

      return main_result;
    }
