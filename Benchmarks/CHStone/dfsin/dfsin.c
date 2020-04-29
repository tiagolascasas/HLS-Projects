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
/*
 * Copyright (C) 2008
 * Y. Hara, H. Tomiyama, S. Honda, H. Takada and K. Ishii
 * Nagoya University, Japan
 * All rights reserved.
 *
 * Disclaimer of Warranty
 *
 * These software programs are available to the user without any license fee or
 * royalty on an "as is" basis. The authors disclaims any and all warranties, 
 * whether express, implied, or statuary, including any implied warranties or 
 * merchantability or of fitness for a particular purpose. In no event shall the
 * copyright-holder be liable for any incidental, punitive, or consequential damages
 * of any kind whatsoever arising from the use of these programs. This disclaimer
 * of warranty extends to the user of these programs and user's customers, employees,
 * agents, transferees, successors, and assigns.
 *
 */
#include <stdio.h>
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
/*============================================================================

This C source file is part of the SoftFloat IEC/IEEE Floating-point Arithmetic
Package, Release 2b.

Written by John R. Hauser.  This work was made possible in part by the
International Computer Science Institute, located at Suite 600, 1947 Center
Street, Berkeley, California 94704.  Funding was partially provided by the
National Science Foundation under grant MIP-9311980.  The original version
of this code was written as part of a project to build a fixed-point vector
processor in collaboration with the University of California at Berkeley,
overseen by Profs. Nelson Morgan and John Wawrzynek.  More information
is available through the Web page `http://www.cs.berkeley.edu/~jhauser/
arithmetic/SoftFloat.html'.

THIS SOFTWARE IS DISTRIBUTED AS IS, FOR FREE.  Although reasonable effort has
been made to avoid it, THIS SOFTWARE MAY CONTAIN FAULTS THAT WILL AT TIMES
RESULT IN INCORRECT BEHAVIOR.  USE OF THIS SOFTWARE IS RESTRICTED TO PERSONS
AND ORGANIZATIONS WHO CAN AND WILL TAKE FULL RESPONSIBILITY FOR ALL LOSSES,
COSTS, OR OTHER PROBLEMS THEY INCUR DUE TO THE SOFTWARE, AND WHO FURTHERMORE
EFFECTIVELY INDEMNIFY JOHN HAUSER AND THE INTERNATIONAL COMPUTER SCIENCE
INSTITUTE (possibly via similar legal warning) AGAINST ALL LOSSES, COSTS, OR
OTHER PROBLEMS INCURRED BY THEIR CUSTOMERS AND CLIENTS DUE TO THE SOFTWARE.

Derivative works are acceptable, even for commercial purposes, so long as
(1) the source code for the derivative work includes prominent notice that
the work is derivative, and (2) the source code includes prominent notice with
these four paragraphs for those parts of this code that are retained.

=============================================================================*/

#include "milieu.h"
#include "softfloat.h"

/*----------------------------------------------------------------------------
| Floating-point rounding mode, extended double-precision rounding precision,
| and exception flags.
*----------------------------------------------------------------------------*/
int8 float_rounding_mode = float_round_nearest_even;
int8 float_exception_flags = 0;

/*----------------------------------------------------------------------------
| Primitive arithmetic functions, including multi-word arithmetic, and
| division and square root approximations.  (Can be specialized to target if
| desired.)
*----------------------------------------------------------------------------*/
#include "softfloat-macros.h"

/*----------------------------------------------------------------------------
| Functions and definitions to determine:  (1) whether tininess for underflow
| is detected before or after rounding by default, (2) what (if anything)
| happens when exceptions are raised, (3) how signaling NaNs are distinguished
| from quiet NaNs, (4) the default generated quiet NaNs, and (5) how NaNs
| are propagated from function inputs to output.  These details are target-
| specific.
*----------------------------------------------------------------------------*/
#include "softfloat-specialize.h"

/*----------------------------------------------------------------------------
| Returns the fraction bits of the double-precision floating-point value `a'.
*----------------------------------------------------------------------------*/

INLINE bits64
extractFloat64Frac(float64 a)
{

    return a & LIT64(0x000FFFFFFFFFFFFF);
}

/*----------------------------------------------------------------------------
| Returns the exponent bits of the double-precision floating-point value `a'.
*----------------------------------------------------------------------------*/

INLINE int16
extractFloat64Exp(float64 a)
{

    return (a >> 52) & 0x7FF;
}

/*----------------------------------------------------------------------------
| Returns the sign bit of the double-precision floating-point value `a'.
*----------------------------------------------------------------------------*/

INLINE flag
extractFloat64Sign(float64 a)
{

    return a >> 63;
}

/*----------------------------------------------------------------------------
| Normalizes the subnormal double-precision floating-point value represented
| by the denormalized significand `aSig'.  The normalized exponent and
| significand are stored at the locations pointed to by `zExpPtr' and
| `zSigPtr', respectively.
*----------------------------------------------------------------------------*/

static void
normalizeFloat64Subnormal(bits64 aSig, int16 *zExpPtr, bits64 *zSigPtr)
{
    int8 shiftCount;

    shiftCount = countLeadingZeros64(aSig) - 11;
    *zSigPtr = aSig << shiftCount;
    *zExpPtr = 1 - shiftCount;
}

/*----------------------------------------------------------------------------
| Packs the sign `zSign', exponent `zExp', and significand `zSig' into a
| double-precision floating-point value, returning the result.  After being
| shifted into the proper positions, the three fields are simply added
| together to form the result.  This means that any integer portion of `zSig'
| will be added into the exponent.  Since a properly normalized significand
| will have an integer portion equal to 1, the `zExp' input should be 1 less
| than the desired result exponent whenever `zSig' is a complete, normalized
| significand.
*----------------------------------------------------------------------------*/

INLINE float64
packFloat64(flag zSign, int16 zExp, bits64 zSig)
{

    return (((bits64)zSign) << 63) + (((bits64)zExp) << 52) + zSig;
}

/*----------------------------------------------------------------------------
| Takes an abstract floating-point value having sign `zSign', exponent `zExp',
| and significand `zSig', and returns the proper double-precision floating-
| point value corresponding to the abstract input.  Ordinarily, the abstract
| value is simply rounded and packed into the double-precision format, with
| the inexact exception raised if the abstract input cannot be represented
| exactly.  However, if the abstract value is too large, the overflow and
| inexact exceptions are raised and an infinity or maximal finite value is
| returned.  If the abstract value is too small, the input value is rounded
| to a subnormal number, and the underflow and inexact exceptions are raised
| if the abstract input cannot be represented exactly as a subnormal double-
| precision floating-point number.
|     The input significand `zSig' has its binary point between bits 62
| and 61, which is 10 bits to the left of the usual location.  This shifted
| significand must be normalized or smaller.  If `zSig' is not normalized,
| `zExp' must be 0; in that case, the result returned is a subnormal number,
| and it must not require rounding.  In the usual case that `zSig' is
| normalized, `zExp' must be 1 less than the ``true'' floating-point exponent.
| The handling of underflow and overflow follows the IEC/IEEE Standard for
| Binary Floating-Point Arithmetic.
*----------------------------------------------------------------------------*/

static float64
roundAndPackFloat64(flag zSign, int16 zExp, bits64 zSig)
{
    int8 roundingMode;
    flag roundNearestEven, isTiny;
    int16 roundIncrement, roundBits;

    roundingMode = float_rounding_mode;
    roundNearestEven = (roundingMode == float_round_nearest_even);
    roundIncrement = 0x200;
    if (!roundNearestEven)
    {
        if (roundingMode == float_round_to_zero)
        {
            roundIncrement = 0;
        }
        else
        {
            roundIncrement = 0x3FF;
            if (zSign)
            {
                if (roundingMode == float_round_up)
                    roundIncrement = 0;
            }
            else
            {
                if (roundingMode == float_round_down)
                    roundIncrement = 0;
            }
        }
    }
    roundBits = zSig & 0x3FF;
    if (0x7FD <= (bits16)zExp)
    {
        if ((0x7FD < zExp) || ((zExp == 0x7FD) && ((sbits64)(zSig + roundIncrement) < 0)))
        {
            float_raise(float_flag_overflow | float_flag_inexact);
            return packFloat64(zSign, 0x7FF, 0) - (roundIncrement == 0);
        }
        if (zExp < 0)
        {
            isTiny = (float_detect_tininess == float_tininess_before_rounding) || (zExp < -1) || (zSig + roundIncrement < LIT64(0x8000000000000000));
            shift64RightJamming(zSig, -zExp, &zSig);
            zExp = 0;
            roundBits = zSig & 0x3FF;
            if (isTiny && roundBits)
                float_raise(float_flag_underflow);
        }
    }
    if (roundBits)
        float_exception_flags |= float_flag_inexact;
    zSig = (zSig + roundIncrement) >> 10;
    zSig &= ~(((roundBits ^ 0x200) == 0) & roundNearestEven);
    if (zSig == 0)
        zExp = 0;
    return packFloat64(zSign, zExp, zSig);
}

/*----------------------------------------------------------------------------
| Takes an abstract floating-point value having sign `zSign', exponent `zExp',
| and significand `zSig', and returns the proper double-precision floating-
| point value corresponding to the abstract input.  This routine is just like
| `roundAndPackFloat64' except that `zSig' does not have to be normalized.
| Bit 63 of `zSig' must be zero, and `zExp' must be 1 less than the ``true''
| floating-point exponent.
*----------------------------------------------------------------------------*/

static float64
normalizeRoundAndPackFloat64(flag zSign, int16 zExp, bits64 zSig)
{
    int8 shiftCount;

    shiftCount = countLeadingZeros64(zSig) - 1;
    return roundAndPackFloat64(zSign, zExp - shiftCount, zSig << shiftCount);
}

/*----------------------------------------------------------------------------
| Returns the result of converting the 32-bit two's complement integer `a'
| to the double-precision floating-point format.  The conversion is performed
| according to the IEC/IEEE Standard for Binary Floating-Point Arithmetic.
*----------------------------------------------------------------------------*/

float64
int32_to_float64(int32 a)
{
    flag zSign;
    uint32 absA;
    int8 shiftCount;
    bits64 zSig;

    if (a == 0)
        return 0;
    zSign = (a < 0);
    absA = zSign ? -a : a;
    shiftCount = countLeadingZeros32(absA) + 21;
    zSig = absA;
    return packFloat64(zSign, 0x432 - shiftCount, zSig << shiftCount);
}

/*----------------------------------------------------------------------------
| Returns the result of adding the absolute values of the double-precision
| floating-point values `a' and `b'.  If `zSign' is 1, the sum is negated
| before being returned.  `zSign' is ignored if the result is a NaN.
| The addition is performed according to the IEC/IEEE Standard for Binary
| Floating-Point Arithmetic.
*----------------------------------------------------------------------------*/

static float64
addFloat64Sigs(float64 a, float64 b, flag zSign)
{
    int16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig;
    int16 expDiff;

    aSig = extractFloat64Frac(a);
    aExp = extractFloat64Exp(a);
    bSig = extractFloat64Frac(b);
    bExp = extractFloat64Exp(b);
    expDiff = aExp - bExp;
    aSig <<= 9;
    bSig <<= 9;
    if (0 < expDiff)
    {
        if (aExp == 0x7FF)
        {
            if (aSig)
                return propagateFloat64NaN(a, b);
            return a;
        }
        if (bExp == 0)
            --expDiff;
        else
            bSig |= LIT64(0x2000000000000000);
        shift64RightJamming(bSig, expDiff, &bSig);
        zExp = aExp;
    }
    else if (expDiff < 0)
    {
        if (bExp == 0x7FF)
        {
            if (bSig)
                return propagateFloat64NaN(a, b);
            return packFloat64(zSign, 0x7FF, 0);
        }
        if (aExp == 0)
            ++expDiff;
        else
        {
            aSig |= LIT64(0x2000000000000000);
        }
        shift64RightJamming(aSig, -expDiff, &aSig);
        zExp = bExp;
    }
    else
    {
        if (aExp == 0x7FF)
        {
            if (aSig | bSig)
                return propagateFloat64NaN(a, b);
            return a;
        }
        if (aExp == 0)
            return packFloat64(zSign, 0, (aSig + bSig) >> 9);
        zSig = LIT64(0x4000000000000000) + aSig + bSig;
        zExp = aExp;
        goto roundAndPack;
    }
    aSig |= LIT64(0x2000000000000000);
    zSig = (aSig + bSig) << 1;
    --zExp;
    if ((sbits64)zSig < 0)
    {
        zSig = aSig + bSig;
        ++zExp;
    }
roundAndPack:
    return roundAndPackFloat64(zSign, zExp, zSig);
}

/*----------------------------------------------------------------------------
| Returns the result of subtracting the absolute values of the double-
| precision floating-point values `a' and `b'.  If `zSign' is 1, the
| difference is negated before being returned.  `zSign' is ignored if the
| result is a NaN.  The subtraction is performed according to the IEC/IEEE
| Standard for Binary Floating-Point Arithmetic.
*----------------------------------------------------------------------------*/

static float64
subFloat64Sigs(float64 a, float64 b, flag zSign)
{
    int16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig;
    int16 expDiff;

    aSig = extractFloat64Frac(a);
    aExp = extractFloat64Exp(a);
    bSig = extractFloat64Frac(b);
    bExp = extractFloat64Exp(b);
    expDiff = aExp - bExp;
    aSig <<= 10;
    bSig <<= 10;
    if (0 < expDiff)
        goto aExpBigger;
    if (expDiff < 0)
        goto bExpBigger;
    if (aExp == 0x7FF)
    {
        if (aSig | bSig)
            return propagateFloat64NaN(a, b);
        float_raise(float_flag_invalid);
        return float64_default_nan;
    }
    if (aExp == 0)
    {
        aExp = 1;
        bExp = 1;
    }
    if (bSig < aSig)
        goto aBigger;
    if (aSig < bSig)
        goto bBigger;
    return packFloat64(float_rounding_mode == float_round_down, 0, 0);
bExpBigger:
    if (bExp == 0x7FF)
    {
        if (bSig)
            return propagateFloat64NaN(a, b);
        return packFloat64(zSign ^ 1, 0x7FF, 0);
    }
    if (aExp == 0)
        ++expDiff;
    else
        aSig |= LIT64(0x4000000000000000);
    shift64RightJamming(aSig, -expDiff, &aSig);
    bSig |= LIT64(0x4000000000000000);
bBigger:
    zSig = bSig - aSig;
    zExp = bExp;
    zSign ^= 1;
    goto normalizeRoundAndPack;
aExpBigger:
    if (aExp == 0x7FF)
    {
        if (aSig)
            return propagateFloat64NaN(a, b);
        return a;
    }
    if (bExp == 0)
        --expDiff;
    else
        bSig |= LIT64(0x4000000000000000);
    shift64RightJamming(bSig, expDiff, &bSig);
    aSig |= LIT64(0x4000000000000000);
aBigger:
    zSig = aSig - bSig;
    zExp = aExp;
normalizeRoundAndPack:
    --zExp;
    return normalizeRoundAndPackFloat64(zSign, zExp, zSig);
}

/*----------------------------------------------------------------------------
| Returns the result of adding the double-precision floating-point values `a'
| and `b'.  The operation is performed according to the IEC/IEEE Standard for
| Binary Floating-Point Arithmetic.
*----------------------------------------------------------------------------*/

float64
float64_add(float64 a, float64 b)
{
    flag aSign, bSign;

    aSign = extractFloat64Sign(a);
    bSign = extractFloat64Sign(b);
    if (aSign == bSign)
        return addFloat64Sigs(a, b, aSign);
    else
        return subFloat64Sigs(a, b, aSign);
}

/*----------------------------------------------------------------------------
| Returns the result of multiplying the double-precision floating-point values
| `a' and `b'.  The operation is performed according to the IEC/IEEE Standard
| for Binary Floating-Point Arithmetic.
*----------------------------------------------------------------------------*/

float64
float64_mul(float64 a, float64 b)
{
    flag aSign, bSign, zSign;
    int16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig0, zSig1;

    aSig = extractFloat64Frac(a);
    aExp = extractFloat64Exp(a);
    aSign = extractFloat64Sign(a);
    bSig = extractFloat64Frac(b);
    bExp = extractFloat64Exp(b);
    bSign = extractFloat64Sign(b);
    zSign = aSign ^ bSign;
    if (aExp == 0x7FF)
    {
        if (aSig || ((bExp == 0x7FF) && bSig))
            return propagateFloat64NaN(a, b);
        if ((bExp | bSig) == 0)
        {
            float_raise(float_flag_invalid);
            return float64_default_nan;
        }
        return packFloat64(zSign, 0x7FF, 0);
    }
    if (bExp == 0x7FF)
    {
        if (bSig)
            return propagateFloat64NaN(a, b);
        if ((aExp | aSig) == 0)
        {
            float_raise(float_flag_invalid);
            return float64_default_nan;
        }
        return packFloat64(zSign, 0x7FF, 0);
    }
    if (aExp == 0)
    {
        if (aSig == 0)
            return packFloat64(zSign, 0, 0);
        normalizeFloat64Subnormal(aSig, &aExp, &aSig);
    }
    if (bExp == 0)
    {
        if (bSig == 0)
            return packFloat64(zSign, 0, 0);
        normalizeFloat64Subnormal(bSig, &bExp, &bSig);
    }
    zExp = aExp + bExp - 0x3FF;
    aSig = (aSig | LIT64(0x0010000000000000)) << 10;
    bSig = (bSig | LIT64(0x0010000000000000)) << 11;
    mul64To128(aSig, bSig, &zSig0, &zSig1);
    zSig0 |= (zSig1 != 0);
    if (0 <= (sbits64)(zSig0 << 1))
    {
        zSig0 <<= 1;
        --zExp;
    }
    return roundAndPackFloat64(zSign, zExp, zSig0);
}

/*----------------------------------------------------------------------------
| Returns the result of dividing the double-precision floating-point value `a'
| by the corresponding value `b'.  The operation is performed according to
| the IEC/IEEE Standard for Binary Floating-Point Arithmetic.
*----------------------------------------------------------------------------*/

float64
float64_div(float64 a, float64 b)
{
    flag aSign, bSign, zSign;
    int16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig;
    bits64 rem0, rem1, term0, term1;

    aSig = extractFloat64Frac(a);
    aExp = extractFloat64Exp(a);
    aSign = extractFloat64Sign(a);
    bSig = extractFloat64Frac(b);
    bExp = extractFloat64Exp(b);
    bSign = extractFloat64Sign(b);
    zSign = aSign ^ bSign;
    if (aExp == 0x7FF)
    {
        if (aSig)
            return propagateFloat64NaN(a, b);
        if (bExp == 0x7FF)
        {
            if (bSig)
                return propagateFloat64NaN(a, b);
            float_raise(float_flag_invalid);
            return float64_default_nan;
        }
        return packFloat64(zSign, 0x7FF, 0);
    }
    if (bExp == 0x7FF)
    {
        if (bSig)
            return propagateFloat64NaN(a, b);
        return packFloat64(zSign, 0, 0);
    }
    if (bExp == 0)
    {
        if (bSig == 0)
        {
            if ((aExp | aSig) == 0)
            {
                float_raise(float_flag_invalid);
                return float64_default_nan;
            }
            float_raise(float_flag_divbyzero);
            return packFloat64(zSign, 0x7FF, 0);
        }
        normalizeFloat64Subnormal(bSig, &bExp, &bSig);
    }
    if (aExp == 0)
    {
        if (aSig == 0)
            return packFloat64(zSign, 0, 0);
        normalizeFloat64Subnormal(aSig, &aExp, &aSig);
    }
    zExp = aExp - bExp + 0x3FD;
    aSig = (aSig | LIT64(0x0010000000000000)) << 10;
    bSig = (bSig | LIT64(0x0010000000000000)) << 11;
    if (bSig <= (aSig + aSig))
    {
        aSig >>= 1;
        ++zExp;
    }
    zSig = estimateDiv128To64(aSig, 0, bSig);
    if ((zSig & 0x1FF) <= 2)
    {
        mul64To128(bSig, zSig, &term0, &term1);
        sub128(aSig, 0, term0, term1, &rem0, &rem1);
        while ((sbits64)rem0 < 0)
        {
            --zSig;
            add128(rem0, rem1, 0, bSig, &rem0, &rem1);
        }
        zSig |= (rem1 != 0);
    }
    return roundAndPackFloat64(zSign, zExp, zSig);
}

/*----------------------------------------------------------------------------
| Returns 1 if the double-precision floating-point value `a' is less than or
| equal to the corresponding value `b', and 0 otherwise.  The comparison is
| performed according to the IEC/IEEE Standard for Binary Floating-Point
| Arithmetic.
*----------------------------------------------------------------------------*/

flag float64_le(float64 a, float64 b)
{
    flag aSign, bSign;

    if (((extractFloat64Exp(a) == 0x7FF) && extractFloat64Frac(a)) || ((extractFloat64Exp(b) == 0x7FF) && extractFloat64Frac(b)))
    {
        float_raise(float_flag_invalid);
        return 0;
    }
    aSign = extractFloat64Sign(a);
    bSign = extractFloat64Sign(b);
    if (aSign != bSign)
        return aSign || ((bits64)((a | b) << 1) == 0);
    return (a == b) || (aSign ^ (a < b));
}

flag float64_ge(float64 a, float64 b)
{
    return float64_le(b, a);
}

// added by hiroyuki@acm.org
float64
float64_neg(float64 x)
{
    return (((~x) & 0x8000000000000000ULL) | (x & 0x7fffffffffffffffULL));
}

float64
float64_abs(float64 x)
{
    return (x & 0x7fffffffffffffffULL);
}

float64
local_sin(float64 rad)
{
    float64 app;
    float64 diff;
    float64 m_rad2;
    int inc;

    app = diff = rad;
    inc = 1;
    m_rad2 = float64_neg(float64_mul(rad, rad));
    do
    {
        diff = float64_div(float64_mul(diff, m_rad2),
                           int32_to_float64((2 * inc) * (2 * inc + 1)));
        app = float64_add(app, diff);
        inc++;
    } while (float64_ge(float64_abs(diff), 0x3ee4f8b588e368f1ULL)); /* 0.00001 */
    return app;
}

double
ullong_to_double(unsigned long long x)
{
    union {
        double d;
        unsigned long long ll;
    } t;

    t.ll = x;
    return t.d;
}

/*
+--------------------------------------------------------------------------+
| * Test Vectors (added for CHStone)                                       |
|     test_in : input data                                                 |
|     test_out : expected output data                                      |
+--------------------------------------------------------------------------+
*/
#define N 36
const float64 test_in[N] = {
    0x0000000000000000ULL,  /*      0  */
    0x3fc65717fced55c1ULL,  /*   PI/18 */
    0x3fd65717fced55c1ULL,  /*   PI/9  */
    0x3fe0c151fdb20051ULL,  /*   PI/6  */
    0x3fe65717fced55c1ULL,  /*  2PI/9  */
    0x3febecddfc28ab31ULL,  /*  5PI/18 */
    0x3ff0c151fdb20051ULL,  /*   PI/3  */
    0x3ff38c34fd4fab09ULL,  /*  7PI/18 */
    0x3ff65717fced55c1ULL,  /*  4PI/9  */
    0x3ff921fafc8b0079ULL,  /*   PI/2  */
    0x3ffbecddfc28ab31ULL,  /*  5PI/9  */
    0x3ffeb7c0fbc655e9ULL,  /* 11PI/18 */
    0x4000c151fdb20051ULL,  /*  2PI/3  */
    0x400226c37d80d5adULL,  /* 13PI/18 */
    0x40038c34fd4fab09ULL,  /*  7PI/9  */
    0x4004f1a67d1e8065ULL,  /*  5PI/6  */
    0x40065717fced55c1ULL,  /*  8PI/9  */
    0x4007bc897cbc2b1dULL,  /* 17PI/18 */
    0x400921fafc8b0079ULL,  /*   PI    */
    0x400a876c7c59d5d5ULL,  /* 19PI/18 */
    0x400becddfc28ab31ULL,  /* 10PI/9  */
    0x400d524f7bf7808dULL,  /*  7PI/6  */
    0x400eb7c0fbc655e9ULL,  /* 11PI/9  */
    0x40100e993dca95a3ULL,  /* 23PI/18 */
    0x4010c151fdb20051ULL,  /*  8PI/6  */
    0x4011740abd996affULL,  /* 25PI/18 */
    0x401226c37d80d5adULL,  /* 13PI/9  */
    0x4012d97c3d68405bULL,  /*  3PI/2  */
    0x40138c34fd4fab09ULL,  /* 14PI/9  */
    0x40143eedbd3715b7ULL,  /* 29PI/18 */
    0x4014f1a67d1e8065ULL,  /* 15PI/9  */
    0x4015a45f3d05eb13ULL,  /* 31PI/18 */
    0x40165717fced55c1ULL,  /* 16PI/9  */
    0x401709d0bcd4c06fULL,  /* 33PI/18 */
    0x4017bc897cbc2b1dULL,  /* 17PI/9  */
    0x40186f423ca395cbULL}; /* 35PI/18 */

const float64 test_out[N] = {
    0x0000000000000000ULL,  /*  0.000000 */
    0x3fc63a1a335aadcdULL,  /*  0.173648 */
    0x3fd5e3a82b09bf3eULL,  /*  0.342020 */
    0x3fdfffff91f9aa91ULL,  /*  0.500000 */
    0x3fe491b716c242e3ULL,  /*  0.642787 */
    0x3fe8836f672614a6ULL,  /*  0.766044 */
    0x3febb67ac40b2bedULL,  /*  0.866025 */
    0x3fee11f6127e28adULL,  /*  0.939693 */
    0x3fef838b6adffac0ULL,  /*  0.984808 */
    0x3fefffffe1cbd7aaULL,  /*  1.000000 */
    0x3fef838bb0147989ULL,  /*  0.984808 */
    0x3fee11f692d962b4ULL,  /*  0.939693 */
    0x3febb67b77c0142dULL,  /*  0.866026 */
    0x3fe883709d4ea869ULL,  /*  0.766045 */
    0x3fe491b81d72d8e8ULL,  /*  0.642788 */
    0x3fe00000ea5f43c8ULL,  /*  0.500000 */
    0x3fd5e3aa4e0590c5ULL,  /*  0.342021 */
    0x3fc63a1d2189552cULL,  /*  0.173648 */
    0x3ea6aedffc454b91ULL,  /*  0.000001 */
    0xbfc63a1444ddb37cULL,  /* -0.173647 */
    0xbfd5e3a4e68f8f3eULL,  /* -0.342019 */
    0xbfdffffd494cf96bULL,  /* -0.499999 */
    0xbfe491b61cb9a3d3ULL,  /* -0.642787 */
    0xbfe8836eb2dcf815ULL,  /* -0.766044 */
    0xbfebb67a740aae32ULL,  /* -0.866025 */
    0xbfee11f5912d2157ULL,  /* -0.939692 */
    0xbfef838b1ac64afcULL,  /* -0.984808 */
    0xbfefffffc2e5dc8fULL,  /* -1.000000 */
    0xbfef838b5ea2e7eaULL,  /* -0.984808 */
    0xbfee11f7112dae27ULL,  /* -0.939693 */
    0xbfebb67c2c31cb4aULL,  /* -0.866026 */
    0xbfe883716e6fd781ULL,  /* -0.766045 */
    0xbfe491b9cd1b5d56ULL,  /* -0.642789 */
    0xbfe000021d0ca30dULL,  /* -0.500001 */
    0xbfd5e3ad0a69caf7ULL,  /* -0.342021 */
    0xbfc63a23c48863ddULL}; /* -0.173649 */

int main()
{
    int main_result;
    int i;
    main_result = 0;
    for (i = 0; i < N; i++)
    {
        float64 result;
        result = local_sin(test_in[i]);
        main_result += (result != test_out[i]);

        printf("input=%016llx expected=%016llx output=%016llx (%lf)\n",
               test_in[i], test_out[i], result, ullong_to_double(result));
    }
    printf("%d\n", main_result);
    return main_result;
}
