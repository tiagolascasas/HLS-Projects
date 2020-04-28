/* 32nd-order Normalized Lattice filter processing 64 points */
/* Modified to use arrays - SMP */

#include <stdio.h>
#include "traps.h"
#define NPOINTS 64
#define ORDER 32

float input[NPOINTS];
float output[NPOINTS];

/* the following values of coefficient and internal_state is define arbitrary */

float coefficient[NPOINTS] = {
    0.25, 0.51, 0.75, -0.25, 0.5, 0.75, 0.7, 0.625,
    0.21, 0.22, 0.93, 0.81, 0.48, 0.208, 0.4, 0.6,
    0.25, 0.35, 0.875, 0.295, 0.25, 0.725, 0.380, 0.295,
    0.2, 0.22, 0.73, 0.91, 0.48, 0.28, 0.694, 0.6,
    0.25, 0.5, 0.75, 0.525, 0.5, 0.75, -0.5, 0.725,
    0.62, 0.272, 0.83, 0.81, 0.48, 0.28, 0.814, 0.56,
    0.25, 0.5, 0.75, -0.25, 0.5, 0.75, -0.810, 0.25,
    0.02, 0.252, 0.913, 0.81, 0.468, 0.28, 0.4, 0.36};

float internal_state[NPOINTS] = {
    0.25, 0.5, 0.75, -0.29, 0.5, 0.75, -0.3, 0.422,
    0.82, 0.922, 0.63, 0.71, 0.48, 0.218, -0.24, 0.6,
    0.92, 0.22, 0.93, 0.51, 0.498, 0.28, -0.84, 0.26,
    0.25, 0.95, 0.75, -0.27, 0.5, 0.75, 0.80, 0.25,
    0.25, 0.25, 0.735, -0.25, 0.5, 0.75, 0.20, 0.525,
    0.92, 0.22, 0.31, 0.81, 0.468, 0.288, -0.14, 0.65,
    0.2, 0.272, 0.93, 0.91, 0.485, 0.218, -0.4, 0.6,
    0.82, 0.72, 0.63, 0.21, 0.438, 0.928, -0.24, 0.6};

void latnrm(float data[NPOINTS], float outa[NPOINTS], float coefficient[NPOINTS],
            float internal_state[NPOINTS]);

int main()
{
    input_dsp(input, NPOINTS, 0); /*new added  */

    latnrm(input, output, coefficient, internal_state);

    output_dsp(output, NPOINTS, 0); /* new added */
}

void latnrm(float data[NPOINTS], float outa[NPOINTS], float coefficient[NPOINTS],
            float internal_state[NPOINTS])
/* data:            input sample array */
/* outa:            output sample array */
/* coefficient:     coefficient array */
/* internal_state:  internal state array */
{
    //---------------------
    FILE *f = fopen("latnrm_32_64.dot", "w");
    int n_const = 0;
    int n_temp = 0;
    int ne = 0;
    int n_op = 0;

    int n_sum = 0;
    int n_left = 0;
    int n_right = 0;
    int n_top = 0;
    int n_bottom = 0;

    int n_data[NPOINTS] = {0};
    int n_outa[NPOINTS] = {0};
    int n_coefficient[NPOINTS] = {0};
    int n_internal_state[NPOINTS] = {0};
    fprintf(f, "Digraph G{\n");
    for (int i = 0; i < NPOINTS; i++)
    {
        n_data[i]++;
        fprintf(f, "\"data[%d]_%d_l\" [label=\"data[%d]\", att1=var, att2=inte, att3=float ];\n", i, n_data[i], i);
        n_coefficient[i]++;
        fprintf(f, "\"coefficient[%d]_%d_l\" [label=\"coefficient[%d]\", att1=var, att2=inte, att3=float ];\n", i, n_coefficient[i], i);
        n_internal_state[i]++;
        fprintf(f, "\"internal_state[%d]_%d_l\" [label=\"internal_state[%d]\", att1=var, att2=inte, att3=float ];\n", i, n_internal_state[i], i);
    }
    //---------------------

    float left;
    float right;
    float top;
    //---------------------
    n_const++;
    fprintf(f, "const%d [label=\"0.0\", att1=const];\n", n_const);
    fprintf(f, "\"bottom_%d\" [label=sum, att1=var, att2=loc, att3=float ];\n", n_bottom + 1);
    ne++;
    fprintf(f, "const%d->\"bottom_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_bottom + 1, ne, ne);
    n_bottom++;
    //---------------------
    float bottom = 0;
    float sum;

    for (int i = 0; i < NPOINTS; i++)
    {
        //---------------------
        n_top++;
        fprintf(f, "\"top_%d\" [label=top, att1=var, att2=loc, att3=float ];\n", n_top);
        ne++;
        fprintf(f, "\"data[%d]_%d_l\"->\"top_%d\" [label=\"%d\", ord=\"%d\"];\n", i, n_data[i], n_top, ne, ne);
        //---------------------
        top = data[i];

        for (int j = 1; j < ORDER; j++)
        {
            //---------------------
            n_left++;
            fprintf(f, "\"left_%d\" [label=\"left\", att1=var, att2=loc, att3=float ];\n", n_left);
            ne++;
            fprintf(f, "top_%d->\"left_%d\" [label=\"%d\", ord=\"%d\"];\n", n_top, n_left, ne, ne);
            //---------------------
            left = top;

            //---------------------
            n_right++;
            fprintf(f, "\"right_%d\" [label=\"right\", att1=var, att2=loc, att3=float ];\n", n_right);
            ne++;
            fprintf(f, "\"internal_state[%d]_%d_l\"->\"right_%d\" [label=\"%d\", ord=\"%d\"];\n", j, n_internal_state[j], n_right, ne, ne);
            //---------------------
            right = internal_state[j];

            //---------------------
            n_internal_state[j]++;
            fprintf(f, "\"internal_state[%d]_%d_l\" [label=\"internal_state[%d]\", att1=var, att2=inte, att3=float ];\n", j, n_internal_state[j], j);
            ne++;
            fprintf(f, "bottom_%d->\"internal_state[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_bottom, j, n_internal_state[j], ne, ne);
            //---------------------
            internal_state[j] = bottom;

            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"coefficient[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", j - 1, n_coefficient[j - 1], n_op, ne, ne);
            ne++;
            fprintf(f, "\"left_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_left, n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"coefficient[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", j, n_coefficient[j], n_op, ne, ne);
            ne++;
            fprintf(f, "\"right_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_right, n_op, ne, ne);
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

            n_top++;
            fprintf(f, "\"top_%d\" [label=\"top\", att1=var, att2=loc, att3=float ];\n", n_top);
            ne++;
            fprintf(f, "temp%d->\"top_%d\" [label=\"%d\", ord=\"%d\"];\n", n_temp, n_top, ne, ne);
            //---------------------
            top = coefficient[j - 1] * left - coefficient[j] * right;

            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l71_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"coefficient[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", j - 1, n_coefficient[j - 1], n_op, ne, ne);
            ne++;
            fprintf(f, "\"right_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_right, n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l71_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"coefficient[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", j, n_coefficient[j], n_op, ne, ne);
            ne++;
            fprintf(f, "\"left_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_left, n_op, ne, ne);
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

            n_bottom++;
            fprintf(f, "\"bottom_%d\" [label=\"left\", att1=var, att2=loc, att3=float ];\n", n_bottom);
            ne++;
            fprintf(f, "temp%d->\"bottom_%d\" [label=\"%d\", ord=\"%d\"];\n", n_temp, n_bottom, ne, ne);
            //---------------------
            bottom = coefficient[j - 1] * right + coefficient[j] * left;
        }
        //---------------------
        n_internal_state[ORDER]++;
        fprintf(f, "\"internal_state[%d]_%d_l\" [label=\"internal_state[%d]\", att1=var, att2=inte, att3=float ];\n", ORDER, n_internal_state[ORDER], ORDER);
        ne++;
        fprintf(f, "bottom_%d->\"internal_state[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_bottom, ORDER, n_internal_state[ORDER], ne, ne);
        //---------------------
        internal_state[ORDER] = bottom;

        //---------------------
        n_internal_state[ORDER + 1]++;
        fprintf(f, "\"internal_state[%d]_%d_l\" [label=\"internal_state[%d]\", att1=var, att2=inte, att3=float ];\n", ORDER + 1, n_internal_state[ORDER + 1], ORDER + 1);
        ne++;
        fprintf(f, "top_%d->\"internal_state[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_top, ORDER + 1, n_internal_state[ORDER + 1], ne, ne);
        //---------------------
        internal_state[ORDER + 1] = top;

        //---------------------
        n_const++;
        fprintf(f, "const%d [label=\"0.0\", att1=const];\n", n_const);
        n_sum++;
        fprintf(f, "\"sum_%d\" [label=sum, att1=var, att2=loc, att3=float ];\n", n_sum);
        ne++;
        fprintf(f, "const%d->\"sum_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_sum, ne, ne);
        //---------------------
        sum = 0.0;

        for (int j = 0; j < ORDER; j++)
        {
            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"internal_state[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", j, n_internal_state[j], n_op, ne, ne);
            ne++;
            fprintf(f, "\"coefficient[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", j + ORDER, n_coefficient[j + ORDER], n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);
            n_op++;
            fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(f, "temp%d->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp, n_op, ne);
            ne++;
            fprintf(f, "sum_%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_sum, n_op, ne);
            n_sum++;
            fprintf(f, "\"sum_%d\" [label=sum, att1=var, att2=loc, att3=float ];\n", n_sum);
            ne++;
            fprintf(f, "op%d->sum_%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_sum, ne);
            //---------------------
            sum += internal_state[j] * coefficient[j + ORDER];
        }
        //---------------------
        n_outa[i]++;
        fprintf(f, "\"outa[%d]_%d_l\" [label=\"outa[%d]\", att1=var, att2=inte, att3=float ];\n", i, n_outa[i], i);
        ne++;
        fprintf(f, "sum_%d->\"outa[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_sum, i, n_outa[i], ne, ne);
        //---------------------
        outa[i] = sum;
    }
    //---------------------
    fprintf(f, "}\n");
    fclose(f);
    //---------------------
}
