#include <stdio.h>
#include <math.h>

#define NUM_DCTS 4 // 5400 NTSC: 720x480 => 90 x 60 blocks of 8x8; if 1 then 8x8 DCT

#define N 8 // fixed
#define M N *N

#define SIZE NUM_DCTS *M

short dct_io_ptr[SIZE];
short dct_o[SIZE];

void fdct(short dct_io_ptr[SIZE], short dct_o[SIZE], int num_fdcts)
{
    short dct_io_tmp[SIZE];

    const unsigned short c1 = 0x2C62, c3 = 0x25A0;
    const unsigned short c5 = 0x1924, c7 = 0x08D4;
    const unsigned short c0 = 0xB505, c2 = 0x29CF;
    const unsigned short c6 = 0x1151;

    short f0, f1, f2, f3, f4, f5, f6, f7;       // Spatial domain samples.
    int g0, g1, h0, h1, p0, p1;                 // Even-half intermediate.
    short r0, r1;                               // Even-half intermediate.
    int P0, P1, R0, R1;                         // Even-half intermediate.
    short g2, g3, h2, h3;                       // Odd-half intermediate.
    short q0a, s0a, q0, q1, s0, s1;             // Odd-half intermediate.
    short Q0, Q1, S0, S1;                       // Odd-half intermediate.
    int F0, F1, F2, F3, F4, F5, F6, F7;         // Freq. domain results.
    int F0r, F1r, F2r, F3r, F4r, F5r, F6r, F7r; // Rounded, truncated results.

    unsigned i, j, i_1;

    i_1 = 0;
    for (i = 0; i < num_fdcts; i++)
    {
        for (j = 0; j < N; j++)
        {
            f0 = dct_io_ptr[0 + i_1];
            f1 = dct_io_ptr[8 + i_1];
            f2 = dct_io_ptr[16 + i_1];
            f3 = dct_io_ptr[24 + i_1];
            f4 = dct_io_ptr[32 + i_1];
            f5 = dct_io_ptr[40 + i_1];
            f6 = dct_io_ptr[48 + i_1];
            f7 = dct_io_ptr[56 + i_1];

            g0 = f0 + f7;
            h2 = f0 - f7;
            g1 = f1 + f6;
            h3 = f1 - f6;
            h1 = f2 + f5;
            g3 = f2 - f5;
            h0 = f3 + f4;
            g2 = f3 - f4;

            p0 = g0 + h0;
            r0 = g0 - h0;
            p1 = g1 + h1;
            r1 = g1 - h1;
            q1 = g2;
            s1 = h2;

            s0a = h3 + g3;
            q0a = h3 - g3;
            s0 = (s0a * c0 + 0x7FFF) >> 16;
            q0 = (q0a * c0 + 0x7FFF) >> 16;

            P0 = p0 + p1;
            P1 = p0 - p1;
            R1 = c6 * r1 + c2 * r0;
            R0 = c6 * r0 - c2 * r1;

            Q1 = q1 + q0;
            Q0 = q1 - q0;
            S1 = s1 + s0;
            S0 = s1 - s0;

            F0 = P0;
            F4 = P1;
            F2 = R1;
            F6 = R0;

            F1 = c7 * Q1 + c1 * S1;
            F7 = c7 * S1 - c1 * Q1;
            F5 = c3 * Q0 + c5 * S0;
            F3 = c3 * S0 - c5 * Q0;

            dct_io_tmp[0 + i_1] = F0;
            dct_io_tmp[8 + i_1] = F1 >> 13;
            dct_io_tmp[16 + i_1] = F2 >> 13;
            dct_io_tmp[24 + i_1] = F3 >> 13;
            dct_io_tmp[32 + i_1] = F4;
            dct_io_tmp[40 + i_1] = F5 >> 13;
            dct_io_tmp[48 + i_1] = F6 >> 13;
            dct_io_tmp[56 + i_1] = F7 >> 13;

            i_1++;
        }

        i_1 += 56;
    }

    i_1 = 0;
    for (i = 0; i < N * num_fdcts; i++)
    {
        f0 = dct_io_tmp[0 + i_1];
        f1 = dct_io_tmp[1 + i_1];
        f2 = dct_io_tmp[2 + i_1];
        f3 = dct_io_tmp[3 + i_1];
        f4 = dct_io_tmp[4 + i_1];
        f5 = dct_io_tmp[5 + i_1];
        f6 = dct_io_tmp[6 + i_1];
        f7 = dct_io_tmp[7 + i_1];

        g0 = f0 + f7;
        h2 = f0 - f7;
        g1 = f1 + f6;
        h3 = f1 - f6;
        h1 = f2 + f5;
        g3 = f2 - f5;
        h0 = f3 + f4;
        g2 = f3 - f4;

        p0 = g0 + h0;
        r0 = g0 - h0;
        p1 = g1 + h1;
        r1 = g1 - h1;
        q1 = g2;
        s1 = h2;

        s0a = h3 + g3;
        q0a = h3 - g3;
        q0 = (q0a * c0 + 0x7FFF) >> 16;
        s0 = (s0a * c0 + 0x7FFF) >> 16;

        P0 = p0 + p1;
        P1 = p0 - p1;
        R1 = c6 * r1 + c2 * r0;
        R0 = c6 * r0 - c2 * r1;

        Q1 = q1 + q0;
        Q0 = q1 - q0;
        S1 = s1 + s0;
        S0 = s1 - s0;

        F0 = P0;
        F4 = P1;
        F2 = R1;
        F6 = R0;

        F1 = c7 * Q1 + c1 * S1;
        F7 = c7 * S1 - c1 * Q1;
        F5 = c3 * Q0 + c5 * S0;
        F3 = c3 * S0 - c5 * Q0;

        F0r = (F0 + 0x0006) >> 3;
        F1r = (F1 + 0x7FFF) >> 16;
        F2r = (F2 + 0x7FFF) >> 16;
        F3r = (F3 + 0x7FFF) >> 16;
        F4r = (F4 + 0x0004) >> 3;
        F5r = (F5 + 0x7FFF) >> 16;
        F6r = (F6 + 0x7FFF) >> 16;
        F7r = (F7 + 0x7FFF) >> 16;

        dct_o[0 + i_1] = F0r;
        dct_o[1 + i_1] = F1r;
        dct_o[2 + i_1] = F2r;
        dct_o[3 + i_1] = F3r;
        dct_o[4 + i_1] = F4r;
        dct_o[5 + i_1] = F5r;
        dct_o[6 + i_1] = F6r;
        dct_o[7 + i_1] = F7r;

        i_1 += 8;
    }
}

int main()
{
    int i;

    /* input data */
    for (i = 0; i < NUM_DCTS * M; i++)
    {
        dct_io_ptr[i] = i;
    }

    fdct(dct_io_ptr, dct_o, NUM_DCTS);

    /* write data stream to output */
    // for now just calculate a checksum
    long checksum = 0;
    for (i = 0; i < NUM_DCTS * M; i++)
    {
        checksum += abs(dct_o[i]);
    }
    printf("checksum = %ld\n", checksum);
    if (checksum == 4844)
        printf("RIGHT!\n");
    else
        printf("WRONG!\n");
    return 0;
}
