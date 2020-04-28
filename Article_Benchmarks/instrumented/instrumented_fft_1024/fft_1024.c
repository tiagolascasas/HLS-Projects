/* 1024-point complex FFT (radix-2, in-place, decimation-in-time) */
/* Modified to use arrays - SMP */

#include <stdio.h>
#include "traps.h"

#define NPOINTS 1024
#define NSTAGES 10

float data_real[NPOINTS];
float data_imag[NPOINTS];
float coef_real[NPOINTS];
float coef_imag[NPOINTS];

void fft(float data_real[NPOINTS], float data_imag[NPOINTS], float coef_real[NPOINTS],
         float coef_imag[NPOINTS]);

int main()
{
    input_dsp(data_real, NPOINTS, 0);

    for (int i = 0; i < NPOINTS; i++)
    { /* was 256 - not ok? */
        data_imag[i] = 1;
        coef_real[i] = 1;
        coef_imag[i] = 1;
    }
    fft(data_real, data_imag, coef_real, coef_imag);

    output_dsp(data_real, NPOINTS, 0);
    output_dsp(data_imag, NPOINTS, 0);
    output_dsp(coef_real, NPOINTS, 0);
    output_dsp(coef_imag, NPOINTS, 0);
}

void fft(float data_real[NPOINTS], float data_imag[NPOINTS], float coef_real[NPOINTS],
         float coef_imag[NPOINTS])
/* data_real:         real data points */
/* data_imag:         imaginary data points */
/* coef_real:         real coefficient points */
/* coef_imag:         imaginary coefficient points */
{
    //---------------------
    FILE *f = fopen("fft_1024.dot", "w");
    int n_const = 0;
    int n_temp = 0;
    int ne = 0;
    int n_op = 0;

    int n_temp_real = 0;
    int n_temp_imag = 0;
    int n_Wr = 0;
    int n_Wi = 0;

    int n_data_real[NPOINTS] = {0};
    int n_data_imag[NPOINTS] = {0};
    int n_coef_real[NPOINTS] = {0};
    int n_coef_imag[NPOINTS] = {0};
    fprintf(f, "Digraph G{\n");
    for (int i = 0; i < NPOINTS; i++)
    {
        n_data_real[i]++;
        fprintf(f, "\"data_real[%d]_%d_l\" [label=\"data_real[%d]\", att1=var, att2=inte, att3=float ];\n", i, n_data_real[i], i);
        n_data_imag[i]++;
        fprintf(f, "\"data_imag[%d]_%d_l\" [label=\"data_imag[%d]\", att1=var, att2=inte, att3=float ];\n", i, n_data_real[i], i);
        n_coef_real[i]++;
        fprintf(f, "\"coef_real[%d]_%d_l\" [label=\"coef_real[%d]\", att1=var, att2=inte, att3=float ];\n", i, n_data_real[i], i);
        n_coef_imag[i]++;
        fprintf(f, "\"coef_imag[%d]_%d_l\" [label=\"coef_imag[%d]\", att1=var, att2=inte, att3=float ];\n", i, n_data_real[i], i);
    }
    //---------------------
    float temp_real;
    float temp_imag;
    float Wr;
    float Wi;
    int groupsPerStage = 1;
    int buttersPerGroup = NPOINTS / 2;

    for (int i = 0; i < NSTAGES; ++i)
    {
        for (int j = 0; j < groupsPerStage; ++j)
        {
            int shift = (1 << i) - 1 + j;
            //---------------------
            n_Wr++;
            fprintf(f, "Wr_%d [label=Wr, att1=var, att2=loc, att3=float ];\n", n_Wr);
            ne++;
            fprintf(f, "\"coef_real[%d]_%d_l\"-> Wr_%d [label=\"%d\", ord=\"%d\"];\n", shift, n_coef_real[shift], n_Wr, ne, ne);
            //---------------------
            Wr = coef_real[shift];

            //---------------------
            n_Wi++;
            fprintf(f, "Wi_%d [label=Wi, att1=var, att2=loc, att3=float ];\n", n_Wi);
            ne++;
            fprintf(f, "\"coef_imag[%d]_%d_l\"-> Wi_%d [label=\"%d\", ord=\"%d\"];\n", shift, n_coef_imag[shift], n_Wi, ne, ne);
            //---------------------
            Wi = coef_imag[shift];
            for (int k = 0; k < buttersPerGroup; ++k)
            {
                int index = 2 * j * buttersPerGroup + buttersPerGroup + k;
                //---------------------
                n_op++;
                fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
                n_temp++;
                fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
                ne++;
                fprintf(f, "\"data_real[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", index, n_data_real[index], n_op, ne, ne);
                ne++;
                fprintf(f, "\"Wr_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_Wr, n_op, ne, ne);
                ne++;
                fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

                n_op++;
                fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
                n_temp++;
                fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
                ne++;
                fprintf(f, "\"data_imag[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", index, n_data_imag[index], n_op, ne, ne);
                ne++;
                fprintf(f, "\"Wi_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_Wi, n_op, ne, ne);
                ne++;
                fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

                n_op++;
                fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
                ne++;
                fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp, n_op, ne, ne);
                ne++;
                fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
                n_temp++;
                fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
                ne++;
                fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

                n_temp_real++;
                fprintf(f, "\"temp_real_%d\" [label=\"temp_real\", att1=var, att2=loc, att3=float ];\n", n_temp_real);
                ne++;
                fprintf(f, "temp%d->\"temp_real_%d\" [label=\"%d\", ord=\"%d\"];\n", n_temp, n_temp_real, ne, ne);
                //---------------------
                temp_real = Wr * data_real[2 * j * buttersPerGroup + buttersPerGroup + k] - Wi * data_imag[2 * j * buttersPerGroup + buttersPerGroup + k];

                //---------------------
                n_op++;
                fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
                n_temp++;
                fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
                ne++;
                fprintf(f, "\"data_real[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", index, n_data_real[index], n_op, ne, ne);
                ne++;
                fprintf(f, "\"Wi_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_Wi, n_op, ne, ne);
                ne++;
                fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

                n_op++;
                fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
                n_temp++;
                fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
                ne++;
                fprintf(f, "\"data_imag[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", index, n_data_imag[index], n_op, ne, ne);
                ne++;
                fprintf(f, "\"Wr_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_Wr, n_op, ne, ne);
                ne++;
                fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

                n_op++;
                fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
                ne++;
                fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp, n_op, ne, ne);
                ne++;
                fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
                n_temp++;
                fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
                ne++;
                fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

                n_temp_imag++;
                fprintf(f, "\"temp_imag_%d\" [label=\"temp_real\", att1=var, att2=loc, att3=float ];\n", n_temp_imag);
                ne++;
                fprintf(f, "temp%d->\"temp_imag_%d\" [label=\"%d\", ord=\"%d\"];\n", n_temp, n_temp_imag, ne, ne);
                //---------------------
                temp_imag = Wi * data_real[index] + Wr * data_imag[index];

                //---------------------
                n_op++;
                fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
                ne++;
                fprintf(f, "\"data_real[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", index, n_data_real[index], n_op, ne, ne);
                ne++;
                fprintf(f, "\"temp_real_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp_real, n_op, ne, ne);
                n_temp++;
                fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
                ne++;
                fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);
                n_data_real[index]++;
                fprintf(f, "\"data_real[%d]_%d_l\" [label=\"data_real[%d]\", att1=var, att2=inte, att3=float ];\n", index, n_data_real[index], index);
                fprintf(f, "temp%d->\"data_real[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_temp, index, n_data_real[index], ne, ne);
                //---------------------
                data_real[2 * j * buttersPerGroup + buttersPerGroup + k] = data_real[2 * j * buttersPerGroup + k] - temp_real;

                //---------------------
                n_op++;
                fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
                ne++;
                fprintf(f, "\"temp_real_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp_real, n_op, ne, ne);
                ne++;
                fprintf(f, "\"data_real[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", index, n_data_real[index], n_op, ne, ne);
                n_data_real[index]++;
                fprintf(f, "\"data_real[%d]_%d_l\" [label=\"data_real[%d]\", att1=var, att2=inte, att3=float ];\n", index, n_data_real[index], index);
                ne++;
                fprintf(f, "\"op%d\"->\"data_real[%d]_%d_l\" [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_op, index, n_data_real[index], ne, ne);
                //---------------------
                data_real[2 * j * buttersPerGroup + k] += temp_real;

                //---------------------
                n_op++;
                fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
                ne++;
                fprintf(f, "\"data_imag[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", index, n_data_imag[index], n_op, ne, ne);
                ne++;
                fprintf(f, "\"temp_imag_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp_imag, n_op, ne, ne);
                n_temp++;
                fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
                ne++;
                fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);
                n_data_imag[index]++;
                fprintf(f, "\"data_imag[%d]_%d_l\" [label=\"data_imag[%d]\", att1=var, att2=inte, att3=float ];\n", index, n_data_imag[index], index);
                fprintf(f, "temp%d->\"data_imag[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_temp, index, n_data_imag[index], ne, ne);
                //---------------------
                data_imag[2 * j * buttersPerGroup + buttersPerGroup + k] = data_imag[2 * j * buttersPerGroup + k] - temp_imag;

                //---------------------
                n_op++;
                fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
                ne++;
                fprintf(f, "\"temp_imag_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp_imag, n_op, ne, ne);
                ne++;
                fprintf(f, "\"data_imag[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", index, n_data_imag[index], n_op, ne, ne);
                n_data_imag[index]++;
                fprintf(f, "\"data_imag[%d]_%d_l\" [label=\"data_imag[%d]\", att1=var, att2=inte, att3=float ];\n", index, n_data_imag[index], index);
                ne++;
                fprintf(f, "\"op%d\"->\"data_imag[%d]_%d_l\" [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_op, index, n_data_imag[index], ne, ne);
                //---------------------
                data_imag[2 * j * buttersPerGroup + k] += temp_imag;
            }
        }
        groupsPerStage <<= 1;
        buttersPerGroup >>= 1;
    }
    //---------------------
    fprintf(f, "}\n");
    fclose(f);
    //---------------------
}
