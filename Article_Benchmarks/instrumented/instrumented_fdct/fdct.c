#include <stdio.h>
#include <math.h>
#include <stdlib.h>
short dct_io_ptr[256];
short dct_o[256];
void fdct(short dct_io_ptr[256], short dct_o[256], int num_fdcts)
{
    FILE *log_file_0 = fopen("fdct.dot", "w+");
    if (log_file_0 == NULL)
    {
        printf("Error opening file fdct.dot\n");
        exit(1);
    }
    fprintf(log_file_0, "Digraph G {\n");
    //---------------------
    int n_const = 0;
    int n_temp = 0;
    int n_op = 0;
    int n_mux = 0;
    int ne = 0;
    int n_dct_io_tmp[256] = {0};
    int n_short[const][c1] = {0};
    int n_f0 = 0;
    int n_f1 = 0;
    int n_f2 = 0;
    int n_f3 = 0;
    int n_f4 = 0;
    int n_f5 = 0;
    int n_f6 = 0;
    int n_f7 = 0;
    int n_g0 = 0;
    int n_g1 = 0;
    int n_h0 = 0;
    int n_h1 = 0;
    int n_p0 = 0;
    int n_p1 = 0;
    int n_r0 = 0;
    int n_r1 = 0;
    int n_P0 = 0;
    int n_P1 = 0;
    int n_R0 = 0;
    int n_R1 = 0;
    int n_g2 = 0;
    int n_g3 = 0;
    int n_h2 = 0;
    int n_h3 = 0;
    int n_q0a = 0;
    int n_s0a = 0;
    int n_q0 = 0;
    int n_q1 = 0;
    int n_s0 = 0;
    int n_s1 = 0;
    int n_Q0 = 0;
    int n_Q1 = 0;
    int n_S0 = 0;
    int n_S1 = 0;
    int n_F0 = 0;
    int n_F1 = 0;
    int n_F2 = 0;
    int n_F3 = 0;
    int n_F4 = 0;
    int n_F5 = 0;
    int n_F6 = 0;
    int n_F7 = 0;
    int n_F0r = 0;
    int n_F1r = 0;
    int n_F2r = 0;
    int n_F3r = 0;
    int n_F4r = 0;
    int n_F5r = 0;
    int n_F6r = 0;
    int n_F7r = 0;
    int n_int[i] = {0};
    int n_dct_io_ptr[256] = {0};
    int n_dct_o[256] = {0};
    int n_num_fdcts = 0;
    //---------------------
    //---------------------
    //---------------------
    short dct_io_tmp[256];
    //---------------------
    //---------------------
    unsigned short const c1 = 0x2C62, c3 = 0x25A0;
    //---------------------
    //---------------------
    unsigned short const c5 = 0x1924, c7 = 0x08D4;
    //---------------------
    //---------------------
    unsigned short const c0 = 0xB505, c2 = 0x29CF;
    //---------------------
    //---------------------
    unsigned short const c6 = 0x1151;
    //---------------------
    //---------------------
    short f0, f1, f2, f3, f4, f5, f6, f7; // Spatial domain samples.
    //---------------------
    //---------------------
    int g0, g1, h0, h1, p0, p1; // Even-half intermediate.
    //---------------------
    //---------------------
    short r0, r1; // Even-half intermediate.
    //---------------------
    //---------------------
    int P0, P1, R0, R1; // Even-half intermediate.
    //---------------------
    //---------------------
    short g2, g3, h2, h3; // Odd-half intermediate.
    //---------------------
    //---------------------
    short q0a, s0a, q0, q1, s0, s1; // Odd-half intermediate.
    //---------------------
    //---------------------
    short Q0, Q1, S0, S1; // Odd-half intermediate.
    //---------------------
    //---------------------
    int F0, F1, F2, F3, F4, F5, F6, F7; // Freq. domain results.
    //---------------------
    //---------------------
    int F0r, F1r, F2r, F3r, F4r, F5r, F6r, F7r; // Rounded, truncated results.
    //---------------------
    //---------------------
    unsigned int i, j, i_1;
    //---------------------
    n_const++;
    fprintf(log_file_0, "\"const%d\" [label=\"0\", att1=const];\n", n_const);
    n_i_1++;
    fprintf(log_file_0, "\"i_1_%d\" [label=\"i_1\", att1=var, att2=, att3=];\n", n_i_1);
    ne++;
    fprintf(log_file_0, "\"const_%d\" -> \"i_1_%d\" [label=\"%d\", ord=\"%d\"];", n_const, n_i_1, n_ne, n_ne);
    //---------------------
    i_1 = 0;
    for (i = 0; i < num_fdcts; i++)
    {
        for (j = 0; j < 8; j++)
        {
            //---------------------
            n_f0++;
            fprintf(log_file_0, "\"f0_%d\" [label=\"f0\", att1=var, att2=loc, att3=short];\n", n_f0);
            ne++;
            fprintf(log_file_0, "\"dct_io_ptr[%d]_%d_l\" -> \"f0_%d\" [label=\"%d\", ord=\"%d\"];", 0 + i_1, n_dct_io_ptr[0 + i_1], n_f0, n_ne, n_ne);
            //---------------------
            f0 = dct_io_ptr[0 + i_1];
            //---------------------
            n_f1++;
            fprintf(log_file_0, "\"f1_%d\" [label=\"f1\", att1=var, att2=loc, att3=short];\n", n_f1);
            ne++;
            fprintf(log_file_0, "\"dct_io_ptr[%d]_%d_l\" -> \"f1_%d\" [label=\"%d\", ord=\"%d\"];", 8 + i_1, n_dct_io_ptr[8 + i_1], n_f1, n_ne, n_ne);
            //---------------------
            f1 = dct_io_ptr[8 + i_1];
            //---------------------
            n_f2++;
            fprintf(log_file_0, "\"f2_%d\" [label=\"f2\", att1=var, att2=loc, att3=short];\n", n_f2);
            ne++;
            fprintf(log_file_0, "\"dct_io_ptr[%d]_%d_l\" -> \"f2_%d\" [label=\"%d\", ord=\"%d\"];", 16 + i_1, n_dct_io_ptr[16 + i_1], n_f2, n_ne, n_ne);
            //---------------------
            f2 = dct_io_ptr[16 + i_1];
            //---------------------
            n_f3++;
            fprintf(log_file_0, "\"f3_%d\" [label=\"f3\", att1=var, att2=loc, att3=short];\n", n_f3);
            ne++;
            fprintf(log_file_0, "\"dct_io_ptr[%d]_%d_l\" -> \"f3_%d\" [label=\"%d\", ord=\"%d\"];", 24 + i_1, n_dct_io_ptr[24 + i_1], n_f3, n_ne, n_ne);
            //---------------------
            f3 = dct_io_ptr[24 + i_1];
            //---------------------
            n_f4++;
            fprintf(log_file_0, "\"f4_%d\" [label=\"f4\", att1=var, att2=loc, att3=short];\n", n_f4);
            ne++;
            fprintf(log_file_0, "\"dct_io_ptr[%d]_%d_l\" -> \"f4_%d\" [label=\"%d\", ord=\"%d\"];", 32 + i_1, n_dct_io_ptr[32 + i_1], n_f4, n_ne, n_ne);
            //---------------------
            f4 = dct_io_ptr[32 + i_1];
            //---------------------
            n_f5++;
            fprintf(log_file_0, "\"f5_%d\" [label=\"f5\", att1=var, att2=loc, att3=short];\n", n_f5);
            ne++;
            fprintf(log_file_0, "\"dct_io_ptr[%d]_%d_l\" -> \"f5_%d\" [label=\"%d\", ord=\"%d\"];", 40 + i_1, n_dct_io_ptr[40 + i_1], n_f5, n_ne, n_ne);
            //---------------------
            f5 = dct_io_ptr[40 + i_1];
            //---------------------
            n_f6++;
            fprintf(log_file_0, "\"f6_%d\" [label=\"f6\", att1=var, att2=loc, att3=short];\n", n_f6);
            ne++;
            fprintf(log_file_0, "\"dct_io_ptr[%d]_%d_l\" -> \"f6_%d\" [label=\"%d\", ord=\"%d\"];", 48 + i_1, n_dct_io_ptr[48 + i_1], n_f6, n_ne, n_ne);
            //---------------------
            f6 = dct_io_ptr[48 + i_1];
            //---------------------
            n_f7++;
            fprintf(log_file_0, "\"f7_%d\" [label=\"f7\", att1=var, att2=loc, att3=short];\n", n_f7);
            ne++;
            fprintf(log_file_0, "\"dct_io_ptr[%d]_%d_l\" -> \"f7_%d\" [label=\"%d\", ord=\"%d\"];", 56 + i_1, n_dct_io_ptr[56 + i_1], n_f7, n_ne, n_ne);
            //---------------------
            f7 = dct_io_ptr[56 + i_1];
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"f7_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f7, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"f0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f0, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_g0++;
            fprintf(log_file_0, "\"g0_%d\" [label=\"g0\", att1=var, att2=loc, att3=int];\n", n_g0);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"g0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_g0, n_ne, n_ne);
            //---------------------
            g0 = f0 + f7;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"f7_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f7, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"f0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f0, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_h2++;
            fprintf(log_file_0, "\"h2_%d\" [label=\"h2\", att1=var, att2=loc, att3=short];\n", n_h2);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"h2_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_h2, n_ne, n_ne);
            //---------------------
            h2 = f0 - f7;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"f6_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f6, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"f1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f1, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_g1++;
            fprintf(log_file_0, "\"g1_%d\" [label=\"g1\", att1=var, att2=loc, att3=int];\n", n_g1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"g1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_g1, n_ne, n_ne);
            //---------------------
            g1 = f1 + f6;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"f6_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f6, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"f1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f1, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_h3++;
            fprintf(log_file_0, "\"h3_%d\" [label=\"h3\", att1=var, att2=loc, att3=short];\n", n_h3);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"h3_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_h3, n_ne, n_ne);
            //---------------------
            h3 = f1 - f6;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"f5_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f5, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"f2_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f2, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_h1++;
            fprintf(log_file_0, "\"h1_%d\" [label=\"h1\", att1=var, att2=loc, att3=int];\n", n_h1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"h1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_h1, n_ne, n_ne);
            //---------------------
            h1 = f2 + f5;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"f5_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f5, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"f2_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f2, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_g3++;
            fprintf(log_file_0, "\"g3_%d\" [label=\"g3\", att1=var, att2=loc, att3=short];\n", n_g3);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"g3_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_g3, n_ne, n_ne);
            //---------------------
            g3 = f2 - f5;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"f4_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f4, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"f3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f3, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_h0++;
            fprintf(log_file_0, "\"h0_%d\" [label=\"h0\", att1=var, att2=loc, att3=int];\n", n_h0);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"h0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_h0, n_ne, n_ne);
            //---------------------
            h0 = f3 + f4;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"f4_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f4, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"f3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f3, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_g2++;
            fprintf(log_file_0, "\"g2_%d\" [label=\"g2\", att1=var, att2=loc, att3=short];\n", n_g2);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"g2_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_g2, n_ne, n_ne);
            //---------------------
            g2 = f3 - f4;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"h0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_h0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"g0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_g0, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_p0++;
            fprintf(log_file_0, "\"p0_%d\" [label=\"p0\", att1=var, att2=loc, att3=int];\n", n_p0);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"p0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_p0, n_ne, n_ne);
            //---------------------
            p0 = g0 + h0;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"h0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_h0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"g0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_g0, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_r0++;
            fprintf(log_file_0, "\"r0_%d\" [label=\"r0\", att1=var, att2=loc, att3=short];\n", n_r0);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"r0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_r0, n_ne, n_ne);
            //---------------------
            r0 = g0 - h0;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"h1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_h1, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"g1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_g1, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_p1++;
            fprintf(log_file_0, "\"p1_%d\" [label=\"p1\", att1=var, att2=loc, att3=int];\n", n_p1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"p1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_p1, n_ne, n_ne);
            //---------------------
            p1 = g1 + h1;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"h1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_h1, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"g1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_g1, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_r1++;
            fprintf(log_file_0, "\"r1_%d\" [label=\"r1\", att1=var, att2=loc, att3=short];\n", n_r1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"r1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_r1, n_ne, n_ne);
            //---------------------
            r1 = g1 - h1;
            //---------------------
            n_q1++;
            fprintf(log_file_0, "\"q1_%d\" [label=\"q1\", att1=var, att2=loc, att3=short];\n", n_q1);
            ne++;
            fprintf(log_file_0, "\"g2_%d\" -> \"q1_%d\" [label=\"%d\", ord=\"%d\"];", n_g2, n_q1, n_ne, n_ne);
            //---------------------
            q1 = g2;
            //---------------------
            n_s1++;
            fprintf(log_file_0, "\"s1_%d\" [label=\"s1\", att1=var, att2=loc, att3=short];\n", n_s1);
            ne++;
            fprintf(log_file_0, "\"h2_%d\" -> \"s1_%d\" [label=\"%d\", ord=\"%d\"];", n_h2, n_s1, n_ne, n_ne);
            //---------------------
            s1 = h2;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"g3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_g3, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"h3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_h3, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_s0a++;
            fprintf(log_file_0, "\"s0a_%d\" [label=\"s0a\", att1=var, att2=loc, att3=short];\n", n_s0a);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"s0a_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_s0a, n_ne, n_ne);
            //---------------------
            s0a = h3 + g3;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"g3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_g3, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"h3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_h3, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_q0a++;
            fprintf(log_file_0, "\"q0a_%d\" [label=\"q0a\", att1=var, att2=loc, att3=short];\n", n_q0a);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"q0a_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_q0a, n_ne, n_ne);
            //---------------------
            q0a = h3 - g3;
            //---------------------
            n_const++;
            fprintf(log_file_0, "\"const%d\" [label=\"16\", att1=const];\n", n_const);
            n_const++;
            fprintf(log_file_0, "\"const%d\" [label=\"0x7FFF\", att1=const];\n", n_const);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"c0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_c0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"s0a_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_s0a, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_s0++;
            fprintf(log_file_0, "\"s0_%d\" [label=\"s0\", att1=var, att2=loc, att3=short];\n", n_s0);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"s0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_s0, n_ne, n_ne);
            //---------------------
            s0 = (s0a * c0 + 0x7FFF) >> 16;
            //---------------------
            n_const++;
            fprintf(log_file_0, "\"const%d\" [label=\"16\", att1=const];\n", n_const);
            n_const++;
            fprintf(log_file_0, "\"const%d\" [label=\"0x7FFF\", att1=const];\n", n_const);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"c0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_c0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"q0a_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_q0a, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_q0++;
            fprintf(log_file_0, "\"q0_%d\" [label=\"q0\", att1=var, att2=loc, att3=short];\n", n_q0);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"q0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_q0, n_ne, n_ne);
            //---------------------
            q0 = (q0a * c0 + 0x7FFF) >> 16;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"p1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_p1, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"p0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_p0, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_P0++;
            fprintf(log_file_0, "\"P0_%d\" [label=\"P0\", att1=var, att2=loc, att3=int];\n", n_P0);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"P0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_P0, n_ne, n_ne);
            //---------------------
            P0 = p0 + p1;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"p1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_p1, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"p0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_p0, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_P1++;
            fprintf(log_file_0, "\"P1_%d\" [label=\"P1\", att1=var, att2=loc, att3=int];\n", n_P1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"P1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_P1, n_ne, n_ne);
            //---------------------
            P1 = p0 - p1;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"r0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_r0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"c2_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c2, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"r1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_r1, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"c6_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c6, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_temp, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_R1++;
            fprintf(log_file_0, "\"R1_%d\" [label=\"R1\", att1=var, att2=loc, att3=int];\n", n_R1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"R1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_R1, n_ne, n_ne);
            //---------------------
            R1 = c6 * r1 + c2 * r0;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"r1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_r1, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"c2_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c2, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"r0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_r0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"c6_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c6, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_temp, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_R0++;
            fprintf(log_file_0, "\"R0_%d\" [label=\"R0\", att1=var, att2=loc, att3=int];\n", n_R0);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"R0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_R0, n_ne, n_ne);
            //---------------------
            R0 = c6 * r0 - c2 * r1;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"q0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_q0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"q1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_q1, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_Q1++;
            fprintf(log_file_0, "\"Q1_%d\" [label=\"Q1\", att1=var, att2=loc, att3=short];\n", n_Q1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"Q1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_Q1, n_ne, n_ne);
            //---------------------
            Q1 = q1 + q0;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"q0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_q0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"q1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_q1, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_Q0++;
            fprintf(log_file_0, "\"Q0_%d\" [label=\"Q0\", att1=var, att2=loc, att3=short];\n", n_Q0);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"Q0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_Q0, n_ne, n_ne);
            //---------------------
            Q0 = q1 - q0;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"s0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_s0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"s1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_s1, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_S1++;
            fprintf(log_file_0, "\"S1_%d\" [label=\"S1\", att1=var, att2=loc, att3=short];\n", n_S1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"S1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_S1, n_ne, n_ne);
            //---------------------
            S1 = s1 + s0;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"s0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_s0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"s1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_s1, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_S0++;
            fprintf(log_file_0, "\"S0_%d\" [label=\"S0\", att1=var, att2=loc, att3=short];\n", n_S0);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"S0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_S0, n_ne, n_ne);
            //---------------------
            S0 = s1 - s0;
            //---------------------
            n_F0++;
            fprintf(log_file_0, "\"F0_%d\" [label=\"F0\", att1=var, att2=loc, att3=int];\n", n_F0);
            ne++;
            fprintf(log_file_0, "\"P0_%d\" -> \"F0_%d\" [label=\"%d\", ord=\"%d\"];", n_P0, n_F0, n_ne, n_ne);
            //---------------------
            F0 = P0;
            //---------------------
            n_F4++;
            fprintf(log_file_0, "\"F4_%d\" [label=\"F4\", att1=var, att2=loc, att3=int];\n", n_F4);
            ne++;
            fprintf(log_file_0, "\"P1_%d\" -> \"F4_%d\" [label=\"%d\", ord=\"%d\"];", n_P1, n_F4, n_ne, n_ne);
            //---------------------
            F4 = P1;
            //---------------------
            n_F2++;
            fprintf(log_file_0, "\"F2_%d\" [label=\"F2\", att1=var, att2=loc, att3=int];\n", n_F2);
            ne++;
            fprintf(log_file_0, "\"R1_%d\" -> \"F2_%d\" [label=\"%d\", ord=\"%d\"];", n_R1, n_F2, n_ne, n_ne);
            //---------------------
            F2 = R1;
            //---------------------
            n_F6++;
            fprintf(log_file_0, "\"F6_%d\" [label=\"F6\", att1=var, att2=loc, att3=int];\n", n_F6);
            ne++;
            fprintf(log_file_0, "\"R0_%d\" -> \"F6_%d\" [label=\"%d\", ord=\"%d\"];", n_R0, n_F6, n_ne, n_ne);
            //---------------------
            F6 = R0;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"S1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_S1, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"c1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c1, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"Q1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_Q1, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"c7_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c7, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_temp, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_F1++;
            fprintf(log_file_0, "\"F1_%d\" [label=\"F1\", att1=var, att2=loc, att3=int];\n", n_F1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"F1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F1, n_ne, n_ne);
            //---------------------
            F1 = c7 * Q1 + c1 * S1;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"Q1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_Q1, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"c1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c1, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"S1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_S1, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"c7_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c7, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_temp, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_F7++;
            fprintf(log_file_0, "\"F7_%d\" [label=\"F7\", att1=var, att2=loc, att3=int];\n", n_F7);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"F7_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F7, n_ne, n_ne);
            //---------------------
            F7 = c7 * S1 - c1 * Q1;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"S0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_S0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"c5_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c5, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"Q0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_Q0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"c3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c3, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_temp, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_F5++;
            fprintf(log_file_0, "\"F5_%d\" [label=\"F5\", att1=var, att2=loc, att3=int];\n", n_F5);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"F5_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F5, n_ne, n_ne);
            //---------------------
            F5 = c3 * Q0 + c5 * S0;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"Q0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_Q0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"c5_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c5, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"S0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_S0, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"c3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c3, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_temp, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_F3++;
            fprintf(log_file_0, "\"F3_%d\" [label=\"F3\", att1=var, att2=loc, att3=int];\n", n_F3);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"F3_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F3, n_ne, n_ne);
            //---------------------
            F3 = c3 * S0 - c5 * Q0;
            //---------------------
            n_dct_io_tmp[0 + i_1]++;
            fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" [label=\"dct_io_tmp[%d]\", att1=var, att2=loc, att3=short];\n", 0 + i_1, n_dct_io_tmp[0 + i_1], 0 + i_1);
            ne++;
            fprintf(log_file_0, "\"F0_%d\" -> \"dct_io_tmp[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_F0, 0 + i_1, n_dct_io_tmp[0 + i_1], n_ne, n_ne);
            //---------------------
            dct_io_tmp[0 + i_1] = F0;
            //---------------------
            n_const++;
            fprintf(log_file_0, "\"const%d\" [label=\"13\", att1=const];\n", n_const);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"F1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F1, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_dct_io_tmp[8 + i_1]++;
            fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" [label=\"dct_io_tmp[%d]\", att1=var, att2=loc, att3=short];\n", 8 + i_1, n_dct_io_tmp[8 + i_1], 8 + i_1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"dct_io_tmp[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_temp, 8 + i_1, n_dct_io_tmp[8 + i_1], n_ne, n_ne);
            //---------------------
            dct_io_tmp[8 + i_1] = F1 >> 13;
            //---------------------
            n_const++;
            fprintf(log_file_0, "\"const%d\" [label=\"13\", att1=const];\n", n_const);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"F2_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F2, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_dct_io_tmp[16 + i_1]++;
            fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" [label=\"dct_io_tmp[%d]\", att1=var, att2=loc, att3=short];\n", 16 + i_1, n_dct_io_tmp[16 + i_1], 16 + i_1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"dct_io_tmp[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_temp, 16 + i_1, n_dct_io_tmp[16 + i_1], n_ne, n_ne);
            //---------------------
            dct_io_tmp[16 + i_1] = F2 >> 13;
            //---------------------
            n_const++;
            fprintf(log_file_0, "\"const%d\" [label=\"13\", att1=const];\n", n_const);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"F3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F3, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_dct_io_tmp[24 + i_1]++;
            fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" [label=\"dct_io_tmp[%d]\", att1=var, att2=loc, att3=short];\n", 24 + i_1, n_dct_io_tmp[24 + i_1], 24 + i_1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"dct_io_tmp[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_temp, 24 + i_1, n_dct_io_tmp[24 + i_1], n_ne, n_ne);
            //---------------------
            dct_io_tmp[24 + i_1] = F3 >> 13;
            //---------------------
            n_dct_io_tmp[32 + i_1]++;
            fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" [label=\"dct_io_tmp[%d]\", att1=var, att2=loc, att3=short];\n", 32 + i_1, n_dct_io_tmp[32 + i_1], 32 + i_1);
            ne++;
            fprintf(log_file_0, "\"F4_%d\" -> \"dct_io_tmp[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_F4, 32 + i_1, n_dct_io_tmp[32 + i_1], n_ne, n_ne);
            //---------------------
            dct_io_tmp[32 + i_1] = F4;
            //---------------------
            n_const++;
            fprintf(log_file_0, "\"const%d\" [label=\"13\", att1=const];\n", n_const);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"F5_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F5, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_dct_io_tmp[40 + i_1]++;
            fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" [label=\"dct_io_tmp[%d]\", att1=var, att2=loc, att3=short];\n", 40 + i_1, n_dct_io_tmp[40 + i_1], 40 + i_1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"dct_io_tmp[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_temp, 40 + i_1, n_dct_io_tmp[40 + i_1], n_ne, n_ne);
            //---------------------
            dct_io_tmp[40 + i_1] = F5 >> 13;
            //---------------------
            n_const++;
            fprintf(log_file_0, "\"const%d\" [label=\"13\", att1=const];\n", n_const);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"F6_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F6, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_dct_io_tmp[48 + i_1]++;
            fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" [label=\"dct_io_tmp[%d]\", att1=var, att2=loc, att3=short];\n", 48 + i_1, n_dct_io_tmp[48 + i_1], 48 + i_1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"dct_io_tmp[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_temp, 48 + i_1, n_dct_io_tmp[48 + i_1], n_ne, n_ne);
            //---------------------
            dct_io_tmp[48 + i_1] = F6 >> 13;
            //---------------------
            n_const++;
            fprintf(log_file_0, "\"const%d\" [label=\"13\", att1=const];\n", n_const);
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
            ne++;
            fprintf(log_file_0, "\"F7_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F7, n_op, n_ne, n_ne);
            n_temp++;
            fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
            ne++;
            fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
            n_dct_io_tmp[56 + i_1]++;
            fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" [label=\"dct_io_tmp[%d]\", att1=var, att2=loc, att3=short];\n", 56 + i_1, n_dct_io_tmp[56 + i_1], 56 + i_1);
            ne++;
            fprintf(log_file_0, "\"temp_%d\" -> \"dct_io_tmp[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_temp, 56 + i_1, n_dct_io_tmp[56 + i_1], n_ne, n_ne);
            //---------------------
            dct_io_tmp[56 + i_1] = F7 >> 13;
            //---------------------
            //---------------------
            i_1++;
        }
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"56\", att1=const];\n", n_const);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"i_1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_i_1, n_op, n_ne, n_ne);
        n_i_1++;
        fprintf(log_file_0, "\"i_1_%d\" [label=\"i_1\", att1=var, att2=, att3=];\n", n_i_1);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"i_1_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_i_1, n_ne, n_ne);
        //---------------------
        i_1 += 56;
    }
    //---------------------
    n_const++;
    fprintf(log_file_0, "\"const%d\" [label=\"0\", att1=const];\n", n_const);
    n_i_1++;
    fprintf(log_file_0, "\"i_1_%d\" [label=\"i_1\", att1=var, att2=, att3=];\n", n_i_1);
    ne++;
    fprintf(log_file_0, "\"const_%d\" -> \"i_1_%d\" [label=\"%d\", ord=\"%d\"];", n_const, n_i_1, n_ne, n_ne);
    //---------------------
    i_1 = 0;
    for (i = 0; i < 8 * num_fdcts; i++)
    {
        //---------------------
        n_f0++;
        fprintf(log_file_0, "\"f0_%d\" [label=\"f0\", att1=var, att2=loc, att3=short];\n", n_f0);
        ne++;
        fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" -> \"f0_%d\" [label=\"%d\", ord=\"%d\"];", 0 + i_1, n_dct_io_tmp[0 + i_1], n_f0, n_ne, n_ne);
        //---------------------
        f0 = dct_io_tmp[0 + i_1];
        //---------------------
        n_f1++;
        fprintf(log_file_0, "\"f1_%d\" [label=\"f1\", att1=var, att2=loc, att3=short];\n", n_f1);
        ne++;
        fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" -> \"f1_%d\" [label=\"%d\", ord=\"%d\"];", 1 + i_1, n_dct_io_tmp[1 + i_1], n_f1, n_ne, n_ne);
        //---------------------
        f1 = dct_io_tmp[1 + i_1];
        //---------------------
        n_f2++;
        fprintf(log_file_0, "\"f2_%d\" [label=\"f2\", att1=var, att2=loc, att3=short];\n", n_f2);
        ne++;
        fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" -> \"f2_%d\" [label=\"%d\", ord=\"%d\"];", 2 + i_1, n_dct_io_tmp[2 + i_1], n_f2, n_ne, n_ne);
        //---------------------
        f2 = dct_io_tmp[2 + i_1];
        //---------------------
        n_f3++;
        fprintf(log_file_0, "\"f3_%d\" [label=\"f3\", att1=var, att2=loc, att3=short];\n", n_f3);
        ne++;
        fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" -> \"f3_%d\" [label=\"%d\", ord=\"%d\"];", 3 + i_1, n_dct_io_tmp[3 + i_1], n_f3, n_ne, n_ne);
        //---------------------
        f3 = dct_io_tmp[3 + i_1];
        //---------------------
        n_f4++;
        fprintf(log_file_0, "\"f4_%d\" [label=\"f4\", att1=var, att2=loc, att3=short];\n", n_f4);
        ne++;
        fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" -> \"f4_%d\" [label=\"%d\", ord=\"%d\"];", 4 + i_1, n_dct_io_tmp[4 + i_1], n_f4, n_ne, n_ne);
        //---------------------
        f4 = dct_io_tmp[4 + i_1];
        //---------------------
        n_f5++;
        fprintf(log_file_0, "\"f5_%d\" [label=\"f5\", att1=var, att2=loc, att3=short];\n", n_f5);
        ne++;
        fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" -> \"f5_%d\" [label=\"%d\", ord=\"%d\"];", 5 + i_1, n_dct_io_tmp[5 + i_1], n_f5, n_ne, n_ne);
        //---------------------
        f5 = dct_io_tmp[5 + i_1];
        //---------------------
        n_f6++;
        fprintf(log_file_0, "\"f6_%d\" [label=\"f6\", att1=var, att2=loc, att3=short];\n", n_f6);
        ne++;
        fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" -> \"f6_%d\" [label=\"%d\", ord=\"%d\"];", 6 + i_1, n_dct_io_tmp[6 + i_1], n_f6, n_ne, n_ne);
        //---------------------
        f6 = dct_io_tmp[6 + i_1];
        //---------------------
        n_f7++;
        fprintf(log_file_0, "\"f7_%d\" [label=\"f7\", att1=var, att2=loc, att3=short];\n", n_f7);
        ne++;
        fprintf(log_file_0, "\"dct_io_tmp[%d]_%d_l\" -> \"f7_%d\" [label=\"%d\", ord=\"%d\"];", 7 + i_1, n_dct_io_tmp[7 + i_1], n_f7, n_ne, n_ne);
        //---------------------
        f7 = dct_io_tmp[7 + i_1];
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"f7_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f7, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"f0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f0, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_g0++;
        fprintf(log_file_0, "\"g0_%d\" [label=\"g0\", att1=var, att2=loc, att3=int];\n", n_g0);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"g0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_g0, n_ne, n_ne);
        //---------------------
        g0 = f0 + f7;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"f7_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f7, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"f0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f0, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_h2++;
        fprintf(log_file_0, "\"h2_%d\" [label=\"h2\", att1=var, att2=loc, att3=short];\n", n_h2);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"h2_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_h2, n_ne, n_ne);
        //---------------------
        h2 = f0 - f7;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"f6_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f6, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"f1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f1, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_g1++;
        fprintf(log_file_0, "\"g1_%d\" [label=\"g1\", att1=var, att2=loc, att3=int];\n", n_g1);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"g1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_g1, n_ne, n_ne);
        //---------------------
        g1 = f1 + f6;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"f6_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f6, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"f1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f1, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_h3++;
        fprintf(log_file_0, "\"h3_%d\" [label=\"h3\", att1=var, att2=loc, att3=short];\n", n_h3);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"h3_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_h3, n_ne, n_ne);
        //---------------------
        h3 = f1 - f6;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"f5_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f5, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"f2_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f2, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_h1++;
        fprintf(log_file_0, "\"h1_%d\" [label=\"h1\", att1=var, att2=loc, att3=int];\n", n_h1);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"h1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_h1, n_ne, n_ne);
        //---------------------
        h1 = f2 + f5;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"f5_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f5, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"f2_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f2, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_g3++;
        fprintf(log_file_0, "\"g3_%d\" [label=\"g3\", att1=var, att2=loc, att3=short];\n", n_g3);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"g3_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_g3, n_ne, n_ne);
        //---------------------
        g3 = f2 - f5;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"f4_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f4, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"f3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f3, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_h0++;
        fprintf(log_file_0, "\"h0_%d\" [label=\"h0\", att1=var, att2=loc, att3=int];\n", n_h0);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"h0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_h0, n_ne, n_ne);
        //---------------------
        h0 = f3 + f4;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"f4_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_f4, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"f3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_f3, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_g2++;
        fprintf(log_file_0, "\"g2_%d\" [label=\"g2\", att1=var, att2=loc, att3=short];\n", n_g2);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"g2_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_g2, n_ne, n_ne);
        //---------------------
        g2 = f3 - f4;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"h0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_h0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"g0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_g0, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_p0++;
        fprintf(log_file_0, "\"p0_%d\" [label=\"p0\", att1=var, att2=loc, att3=int];\n", n_p0);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"p0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_p0, n_ne, n_ne);
        //---------------------
        p0 = g0 + h0;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"h0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_h0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"g0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_g0, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_r0++;
        fprintf(log_file_0, "\"r0_%d\" [label=\"r0\", att1=var, att2=loc, att3=short];\n", n_r0);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"r0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_r0, n_ne, n_ne);
        //---------------------
        r0 = g0 - h0;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"h1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_h1, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"g1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_g1, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_p1++;
        fprintf(log_file_0, "\"p1_%d\" [label=\"p1\", att1=var, att2=loc, att3=int];\n", n_p1);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"p1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_p1, n_ne, n_ne);
        //---------------------
        p1 = g1 + h1;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"h1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_h1, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"g1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_g1, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_r1++;
        fprintf(log_file_0, "\"r1_%d\" [label=\"r1\", att1=var, att2=loc, att3=short];\n", n_r1);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"r1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_r1, n_ne, n_ne);
        //---------------------
        r1 = g1 - h1;
        //---------------------
        n_q1++;
        fprintf(log_file_0, "\"q1_%d\" [label=\"q1\", att1=var, att2=loc, att3=short];\n", n_q1);
        ne++;
        fprintf(log_file_0, "\"g2_%d\" -> \"q1_%d\" [label=\"%d\", ord=\"%d\"];", n_g2, n_q1, n_ne, n_ne);
        //---------------------
        q1 = g2;
        //---------------------
        n_s1++;
        fprintf(log_file_0, "\"s1_%d\" [label=\"s1\", att1=var, att2=loc, att3=short];\n", n_s1);
        ne++;
        fprintf(log_file_0, "\"h2_%d\" -> \"s1_%d\" [label=\"%d\", ord=\"%d\"];", n_h2, n_s1, n_ne, n_ne);
        //---------------------
        s1 = h2;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"g3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_g3, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"h3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_h3, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_s0a++;
        fprintf(log_file_0, "\"s0a_%d\" [label=\"s0a\", att1=var, att2=loc, att3=short];\n", n_s0a);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"s0a_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_s0a, n_ne, n_ne);
        //---------------------
        s0a = h3 + g3;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"g3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_g3, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"h3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_h3, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_q0a++;
        fprintf(log_file_0, "\"q0a_%d\" [label=\"q0a\", att1=var, att2=loc, att3=short];\n", n_q0a);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"q0a_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_q0a, n_ne, n_ne);
        //---------------------
        q0a = h3 - g3;
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"16\", att1=const];\n", n_const);
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"0x7FFF\", att1=const];\n", n_const);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"c0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_c0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"q0a_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_q0a, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_q0++;
        fprintf(log_file_0, "\"q0_%d\" [label=\"q0\", att1=var, att2=loc, att3=short];\n", n_q0);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"q0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_q0, n_ne, n_ne);
        //---------------------
        q0 = (q0a * c0 + 0x7FFF) >> 16;
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"16\", att1=const];\n", n_const);
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"0x7FFF\", att1=const];\n", n_const);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"c0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_c0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"s0a_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_s0a, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_s0++;
        fprintf(log_file_0, "\"s0_%d\" [label=\"s0\", att1=var, att2=loc, att3=short];\n", n_s0);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"s0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_s0, n_ne, n_ne);
        //---------------------
        s0 = (s0a * c0 + 0x7FFF) >> 16;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"p1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_p1, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"p0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_p0, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_P0++;
        fprintf(log_file_0, "\"P0_%d\" [label=\"P0\", att1=var, att2=loc, att3=int];\n", n_P0);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"P0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_P0, n_ne, n_ne);
        //---------------------
        P0 = p0 + p1;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"p1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_p1, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"p0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_p0, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_P1++;
        fprintf(log_file_0, "\"P1_%d\" [label=\"P1\", att1=var, att2=loc, att3=int];\n", n_P1);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"P1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_P1, n_ne, n_ne);
        //---------------------
        P1 = p0 - p1;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"r0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_r0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"c2_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c2, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"r1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_r1, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"c6_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c6, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_temp, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_R1++;
        fprintf(log_file_0, "\"R1_%d\" [label=\"R1\", att1=var, att2=loc, att3=int];\n", n_R1);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"R1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_R1, n_ne, n_ne);
        //---------------------
        R1 = c6 * r1 + c2 * r0;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"r1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_r1, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"c2_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c2, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"r0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_r0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"c6_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c6, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_temp, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_R0++;
        fprintf(log_file_0, "\"R0_%d\" [label=\"R0\", att1=var, att2=loc, att3=int];\n", n_R0);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"R0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_R0, n_ne, n_ne);
        //---------------------
        R0 = c6 * r0 - c2 * r1;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"q0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_q0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"q1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_q1, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_Q1++;
        fprintf(log_file_0, "\"Q1_%d\" [label=\"Q1\", att1=var, att2=loc, att3=short];\n", n_Q1);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"Q1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_Q1, n_ne, n_ne);
        //---------------------
        Q1 = q1 + q0;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"q0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_q0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"q1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_q1, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_Q0++;
        fprintf(log_file_0, "\"Q0_%d\" [label=\"Q0\", att1=var, att2=loc, att3=short];\n", n_Q0);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"Q0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_Q0, n_ne, n_ne);
        //---------------------
        Q0 = q1 - q0;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"s0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_s0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"s1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_s1, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_S1++;
        fprintf(log_file_0, "\"S1_%d\" [label=\"S1\", att1=var, att2=loc, att3=short];\n", n_S1);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"S1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_S1, n_ne, n_ne);
        //---------------------
        S1 = s1 + s0;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"s0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_s0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"s1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_s1, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_S0++;
        fprintf(log_file_0, "\"S0_%d\" [label=\"S0\", att1=var, att2=loc, att3=short];\n", n_S0);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"S0_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_S0, n_ne, n_ne);
        //---------------------
        S0 = s1 - s0;
        //---------------------
        n_F0++;
        fprintf(log_file_0, "\"F0_%d\" [label=\"F0\", att1=var, att2=loc, att3=int];\n", n_F0);
        ne++;
        fprintf(log_file_0, "\"P0_%d\" -> \"F0_%d\" [label=\"%d\", ord=\"%d\"];", n_P0, n_F0, n_ne, n_ne);
        //---------------------
        F0 = P0;
        //---------------------
        n_F4++;
        fprintf(log_file_0, "\"F4_%d\" [label=\"F4\", att1=var, att2=loc, att3=int];\n", n_F4);
        ne++;
        fprintf(log_file_0, "\"P1_%d\" -> \"F4_%d\" [label=\"%d\", ord=\"%d\"];", n_P1, n_F4, n_ne, n_ne);
        //---------------------
        F4 = P1;
        //---------------------
        n_F2++;
        fprintf(log_file_0, "\"F2_%d\" [label=\"F2\", att1=var, att2=loc, att3=int];\n", n_F2);
        ne++;
        fprintf(log_file_0, "\"R1_%d\" -> \"F2_%d\" [label=\"%d\", ord=\"%d\"];", n_R1, n_F2, n_ne, n_ne);
        //---------------------
        F2 = R1;
        //---------------------
        n_F6++;
        fprintf(log_file_0, "\"F6_%d\" [label=\"F6\", att1=var, att2=loc, att3=int];\n", n_F6);
        ne++;
        fprintf(log_file_0, "\"R0_%d\" -> \"F6_%d\" [label=\"%d\", ord=\"%d\"];", n_R0, n_F6, n_ne, n_ne);
        //---------------------
        F6 = R0;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"S1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_S1, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"c1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c1, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"Q1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_Q1, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"c7_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c7, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_temp, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_F1++;
        fprintf(log_file_0, "\"F1_%d\" [label=\"F1\", att1=var, att2=loc, att3=int];\n", n_F1);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"F1_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F1, n_ne, n_ne);
        //---------------------
        F1 = c7 * Q1 + c1 * S1;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"Q1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_Q1, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"c1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c1, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"S1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_S1, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"c7_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c7, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_temp, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_F7++;
        fprintf(log_file_0, "\"F7_%d\" [label=\"F7\", att1=var, att2=loc, att3=int];\n", n_F7);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"F7_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F7, n_ne, n_ne);
        //---------------------
        F7 = c7 * S1 - c1 * Q1;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"S0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_S0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"c5_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c5, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"Q0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_Q0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"c3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c3, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_temp, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_F5++;
        fprintf(log_file_0, "\"F5_%d\" [label=\"F5\", att1=var, att2=loc, att3=int];\n", n_F5);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"F5_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F5, n_ne, n_ne);
        //---------------------
        F5 = c3 * Q0 + c5 * S0;
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"Q0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_Q0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"c5_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c5, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"S0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_S0, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"c3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_c3, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"-\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_temp, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_F3++;
        fprintf(log_file_0, "\"F3_%d\" [label=\"F3\", att1=var, att2=loc, att3=int];\n", n_F3);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"F3_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F3, n_ne, n_ne);
        //---------------------
        F3 = c3 * S0 - c5 * Q0;
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"3\", att1=const];\n", n_const);
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"0x0006\", att1=const];\n", n_const);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"F0_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F0, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_F0r++;
        fprintf(log_file_0, "\"F0r_%d\" [label=\"F0r\", att1=var, att2=loc, att3=int];\n", n_F0r);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"F0r_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F0r, n_ne, n_ne);
        //---------------------
        F0r = (F0 + 0x0006) >> 3;
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"16\", att1=const];\n", n_const);
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"0x7FFF\", att1=const];\n", n_const);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"F1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F1, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_F1r++;
        fprintf(log_file_0, "\"F1r_%d\" [label=\"F1r\", att1=var, att2=loc, att3=int];\n", n_F1r);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"F1r_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F1r, n_ne, n_ne);
        //---------------------
        F1r = (F1 + 0x7FFF) >> 16;
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"16\", att1=const];\n", n_const);
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"0x7FFF\", att1=const];\n", n_const);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"F2_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F2, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_F2r++;
        fprintf(log_file_0, "\"F2r_%d\" [label=\"F2r\", att1=var, att2=loc, att3=int];\n", n_F2r);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"F2r_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F2r, n_ne, n_ne);
        //---------------------
        F2r = (F2 + 0x7FFF) >> 16;
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"16\", att1=const];\n", n_const);
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"0x7FFF\", att1=const];\n", n_const);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"F3_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F3, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_F3r++;
        fprintf(log_file_0, "\"F3r_%d\" [label=\"F3r\", att1=var, att2=loc, att3=int];\n", n_F3r);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"F3r_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F3r, n_ne, n_ne);
        //---------------------
        F3r = (F3 + 0x7FFF) >> 16;
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"3\", att1=const];\n", n_const);
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"0x0004\", att1=const];\n", n_const);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"F4_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F4, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_F4r++;
        fprintf(log_file_0, "\"F4r_%d\" [label=\"F4r\", att1=var, att2=loc, att3=int];\n", n_F4r);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"F4r_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F4r, n_ne, n_ne);
        //---------------------
        F4r = (F4 + 0x0004) >> 3;
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"16\", att1=const];\n", n_const);
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"0x7FFF\", att1=const];\n", n_const);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"F5_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F5, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_F5r++;
        fprintf(log_file_0, "\"F5r_%d\" [label=\"F5r\", att1=var, att2=loc, att3=int];\n", n_F5r);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"F5r_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F5r, n_ne, n_ne);
        //---------------------
        F5r = (F5 + 0x7FFF) >> 16;
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"16\", att1=const];\n", n_const);
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"0x7FFF\", att1=const];\n", n_const);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"F6_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F6, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_F6r++;
        fprintf(log_file_0, "\"F6r_%d\" [label=\"F6r\", att1=var, att2=loc, att3=int];\n", n_F6r);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"F6r_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F6r, n_ne, n_ne);
        //---------------------
        F6r = (F6 + 0x7FFF) >> 16;
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"16\", att1=const];\n", n_const);
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"0x7FFF\", att1=const];\n", n_const);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"F7_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_F7, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\">>\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_temp, n_op, n_ne, n_ne);
        n_temp++;
        fprintf(log_file_0, "\"temp%d\" [label=\"temp%d\", att1=var, att2=loc, att3=float];\n", n_temp, n_temp);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"temp_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_temp, n_ne, n_ne);
        n_F7r++;
        fprintf(log_file_0, "\"F7r_%d\" [label=\"F7r\", att1=var, att2=loc, att3=int];\n", n_F7r);
        ne++;
        fprintf(log_file_0, "\"temp_%d\" -> \"F7r_%d\" [label=\"%d\", ord=\"%d\"];", n_temp, n_F7r, n_ne, n_ne);
        //---------------------
        F7r = (F7 + 0x7FFF) >> 16;
        //---------------------
        n_dct_o[0 + i_1]++;
        fprintf(log_file_0, "\"dct_o[%d]_%d_l\" [label=\"dct_o[%d]\", att1=var, att2=inte, att3=short];\n", 0 + i_1, n_dct_o[0 + i_1], 0 + i_1);
        ne++;
        fprintf(log_file_0, "\"F0r_%d\" -> \"dct_o[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_F0r, 0 + i_1, n_dct_o[0 + i_1], n_ne, n_ne);
        //---------------------
        dct_o[0 + i_1] = F0r;
        //---------------------
        n_dct_o[1 + i_1]++;
        fprintf(log_file_0, "\"dct_o[%d]_%d_l\" [label=\"dct_o[%d]\", att1=var, att2=inte, att3=short];\n", 1 + i_1, n_dct_o[1 + i_1], 1 + i_1);
        ne++;
        fprintf(log_file_0, "\"F1r_%d\" -> \"dct_o[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_F1r, 1 + i_1, n_dct_o[1 + i_1], n_ne, n_ne);
        //---------------------
        dct_o[1 + i_1] = F1r;
        //---------------------
        n_dct_o[2 + i_1]++;
        fprintf(log_file_0, "\"dct_o[%d]_%d_l\" [label=\"dct_o[%d]\", att1=var, att2=inte, att3=short];\n", 2 + i_1, n_dct_o[2 + i_1], 2 + i_1);
        ne++;
        fprintf(log_file_0, "\"F2r_%d\" -> \"dct_o[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_F2r, 2 + i_1, n_dct_o[2 + i_1], n_ne, n_ne);
        //---------------------
        dct_o[2 + i_1] = F2r;
        //---------------------
        n_dct_o[3 + i_1]++;
        fprintf(log_file_0, "\"dct_o[%d]_%d_l\" [label=\"dct_o[%d]\", att1=var, att2=inte, att3=short];\n", 3 + i_1, n_dct_o[3 + i_1], 3 + i_1);
        ne++;
        fprintf(log_file_0, "\"F3r_%d\" -> \"dct_o[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_F3r, 3 + i_1, n_dct_o[3 + i_1], n_ne, n_ne);
        //---------------------
        dct_o[3 + i_1] = F3r;
        //---------------------
        n_dct_o[4 + i_1]++;
        fprintf(log_file_0, "\"dct_o[%d]_%d_l\" [label=\"dct_o[%d]\", att1=var, att2=inte, att3=short];\n", 4 + i_1, n_dct_o[4 + i_1], 4 + i_1);
        ne++;
        fprintf(log_file_0, "\"F4r_%d\" -> \"dct_o[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_F4r, 4 + i_1, n_dct_o[4 + i_1], n_ne, n_ne);
        //---------------------
        dct_o[4 + i_1] = F4r;
        //---------------------
        n_dct_o[5 + i_1]++;
        fprintf(log_file_0, "\"dct_o[%d]_%d_l\" [label=\"dct_o[%d]\", att1=var, att2=inte, att3=short];\n", 5 + i_1, n_dct_o[5 + i_1], 5 + i_1);
        ne++;
        fprintf(log_file_0, "\"F5r_%d\" -> \"dct_o[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_F5r, 5 + i_1, n_dct_o[5 + i_1], n_ne, n_ne);
        //---------------------
        dct_o[5 + i_1] = F5r;
        //---------------------
        n_dct_o[6 + i_1]++;
        fprintf(log_file_0, "\"dct_o[%d]_%d_l\" [label=\"dct_o[%d]\", att1=var, att2=inte, att3=short];\n", 6 + i_1, n_dct_o[6 + i_1], 6 + i_1);
        ne++;
        fprintf(log_file_0, "\"F6r_%d\" -> \"dct_o[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_F6r, 6 + i_1, n_dct_o[6 + i_1], n_ne, n_ne);
        //---------------------
        dct_o[6 + i_1] = F6r;
        //---------------------
        n_dct_o[7 + i_1]++;
        fprintf(log_file_0, "\"dct_o[%d]_%d_l\" [label=\"dct_o[%d]\", att1=var, att2=inte, att3=short];\n", 7 + i_1, n_dct_o[7 + i_1], 7 + i_1);
        ne++;
        fprintf(log_file_0, "\"F7r_%d\" -> \"dct_o[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];", n_F7r, 7 + i_1, n_dct_o[7 + i_1], n_ne, n_ne);
        //---------------------
        dct_o[7 + i_1] = F7r;
        //---------------------
        n_const++;
        fprintf(log_file_0, "\"const%d\" [label=\"8\", att1=const];\n", n_const);
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
        ne++;
        fprintf(log_file_0, "\"const_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"r\"];", n_const, n_op, n_ne, n_ne);
        ne++;
        fprintf(log_file_0, "\"i_1_%d\" -> \"op_%d\" [label=\"%d\", ord=\"%d\", pos=\"l\"];", n_i_1, n_op, n_ne, n_ne);
        n_i_1++;
        fprintf(log_file_0, "\"i_1_%d\" [label=\"i_1\", att1=var, att2=, att3=];\n", n_i_1);
        ne++;
        fprintf(log_file_0, "\"op_%d\" -> \"i_1_%d\" [label=\"%d\", ord=\"%d\"];", n_op, n_i_1, n_ne, n_ne);
        //---------------------
        i_1 += 8;
    }
    fprintf(log_file_0, "}");
    fclose(log_file_0);
}

int main()
{
    int i;
    /*input data*/
    for (i = 0; i < 4 * 8 * 8; i++)
    {
        dct_io_ptr[i] = i;
    }
    fdct(dct_io_ptr, dct_o, 4);
    /*write data stream to output*/
    // for now just calculate a checksum
    long checksum = 0;
    for (i = 0; i < 4 * 8 * 8; i++)
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
