#include <stdio.h>
#include <stdlib.h>

#define NR1 (8)
#define NC1 (4)
#define NC2 (8)

void DSPF_sp_mat_mul_cplx_cn(float x1[64], int r1, int c1, float x2[64], int c2, float y[128])
{
    FILE *f = fopen("DSPF_sp_mat_mul_cplx_cn.dot", "w+");
    if (f == NULL)
    {
        printf("Error opening file DSPF_sp_mat_mul_cplx_cn.dot\n");
        exit(1);
    }
    fprintf(f, "Digraph G {\n");
    //---------------------
    int n_const = 0;
    int n_temp = 0;
    int n_op = 0;
    int n_mux = 0;
    int ne = 0;
    int n_real = 0;
    int n_imag = 0;
    int n_i = 0;
    int n_j = 0;
    int n_k = 0;
    int n_x1[64] = {0};
    int n_r1 = 0;
    int n_c1 = 0;
    int n_x2[64] = {0};
    int n_c2 = 0;
    int n_y[128] = {0};
    for (int _i = 0; _i < 64; _i++)
    {
        n_x1[_i]++;
        fprintf(f, "\"x1[%d]_%d_l\" [label=\"x1[%d]\", att1=var, att2=inte, att3=float ];\n", _i, n_x1[_i], _i);
    }
    for (int _i = 0; _i < 64; _i++)
    {
        n_x2[_i]++;
        fprintf(f, "\"x2[%d]_%d_l\" [label=\"x2[%d]\", att1=var, att2=inte, att3=float ];\n", _i, n_x2[_i], _i);
    }
    for (int _i = 0; _i < 128; _i++)
    {
        n_y[_i]++;
        fprintf(f, "\"y[%d]_%d_l\" [label=\"y[%d]\", att1=var, att2=inte, att3=float ];\n", _i, n_y[_i], _i);
    }
    //---------------------

    float real, imag;
    //---------------------
    //---------------------
    int i, j, k;
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            //---------------------
            n_const++;
            fprintf(f, "const%d [label=\"0\", att1=const];\n", n_const);
            n_real++;
            fprintf(f, "real_%d [label=\"real\", att1=var, att2=loc, att3=float];\n", n_real);
            ne++;
            fprintf(f, "\"const%d\"->\"real_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_real, ne, ne);
            //---------------------
            real = 0;
            //---------------------
            n_const++;
            fprintf(f, "const%d [label=\"0\", att1=const];\n", n_const);
            n_imag++;
            fprintf(f, "imag_%d [label=\"imag\", att1=var, att2=loc, att3=float];\n", n_imag);
            ne++;
            fprintf(f, "\"const%d\"->\"imag_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_imag, ne, ne);
            //---------------------
            imag = 0;
            for (k = 0; k < c1; k++)
            {
                //---------------------
                n_op++;
                fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
                n_temp++;
                fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
                ne++;
                fprintf(f, "\"x1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", i * 2 * c1 + 2 * k, n_x1[i * 2 * c1 + 2 * k], n_op, ne, ne);
                ne++;
                fprintf(f, "\"x2[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", k * 2 * c2 + 2 * j, n_x2[k * 2 * c2 + 2 * j], n_op, ne, ne);
                ne++;
                fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

                n_op++;
                fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
                n_temp++;
                fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
                ne++;
                fprintf(f, "\"x1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", i * 2 * c1 + 2 * k + 1, n_x1[i * 2 * c1 + 2 * k + 1], n_op, ne, ne);
                ne++;
                fprintf(f, "\"x2[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", k * 2 * c2 + 2 * j + 1, n_x2[k * 2 * c2 + 2 * j + 1], n_op, ne, ne);
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

                n_real++;
                fprintf(f, "\"real_%d\" [label=\"real\", att1=var, att2=loc, att3=float ];\n", n_real);
                ne++;
                fprintf(f, "temp%d->\"real_%d\" [label=\"%d\", ord=\"%d\"];\n", n_temp, n_real, ne, ne);
                //---------------------
                real += (x1[i * 2 * c1 + 2 * k] * x2[k * 2 * c2 + 2 * j] - x1[i * 2 * c1 + 2 * k + 1] * x2[k * 2 * c2 + 2 * j + 1]);
                //---------------------
                n_op++;
                fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
                n_temp++;
                fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
                ne++;
                fprintf(f, "\"x1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", i * 2 * c1 + 2 * k, n_x1[i * 2 * c1 + 2 * k], n_op, ne, ne);
                ne++;
                fprintf(f, "\"x2[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", k * 2 * c2 + 2 * j + 1, n_x2[k * 2 * c2 + 2 * j + 1], n_op, ne, ne);
                ne++;
                fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

                n_op++;
                fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
                n_temp++;
                fprintf(f, "temp%d [label=\"temp_l70_i%d\", att1=var, att2=loc, att3=float ];\n", n_temp, n_temp);
                ne++;
                fprintf(f, "\"x1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", i * 2 * c1 + 2 * k + 1, n_x1[i * 2 * c1 + 2 * k + 1], n_op, ne, ne);
                ne++;
                fprintf(f, "\"x2[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", k * 2 * c2 + 2 * j, n_x2[k * 2 * c2 + 2 * j], n_op, ne, ne);
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

                n_imag++;
                fprintf(f, "\"imag_%d\" [label=\"imag\", att1=var, att2=loc, att3=float ];\n", n_imag);
                ne++;
                fprintf(f, "temp%d->\"imag_%d\" [label=\"%d\", ord=\"%d\"];\n", n_temp, n_imag, ne, ne);
                //---------------------
                imag += (x1[i * 2 * c1 + 2 * k] * x2[k * 2 * c2 + 2 * j + 1] + x1[i * 2 * c1 + 2 * k + 1] * x2[k * 2 * c2 + 2 * j]);
            }
            //---------------------
            n_y[i * 2 * c2 + 2 * j]++;
            fprintf(f, "\"y[%d]_%d_l\" [label=\"y[%d]\", att1=var, att2=inte, att3=float ];\n", i * 2 * c2 + 2 * j, n_y[i * 2 * c2 + 2 * j], i * 2 * c2 + 2 * j);
            ne++;
            fprintf(f, "real_%d->\"y[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_real, i * 2 * c2 + 2 * j, n_y[i * 2 * c2 + 2 * j], ne, ne);
            //---------------------
            y[i * 2 * c2 + 2 * j] = real;
            //---------------------
            n_y[i * 2 * c2 + 2 * j + 1]++;
            fprintf(f, "\"y[%d]_%d_l\" [label=\"y[%d]\", att1=var, att2=inte, att3=float ];\n", i * 2 * c2 + 2 * j + 1, n_y[i * 2 * c2 + 2 * j + 1], i * 2 * c2 + 2 * j + 1);
            ne++;
            fprintf(f, "imag_%d->\"y[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_imag, i * 2 * c2 + 2 * j + 1, n_y[i * 2 * c2 + 2 * j + 1], ne, ne);
            //---------------------
            y[i * 2 * c2 + 2 * j + 1] = imag;
        }
    }
    fclose(f);
}
int main()
{
    float ptr_y_cn[2 * NR1 * NC2] = {0};
    for (int i = 0; i < 2 * NR1 * NC2; i++)
        ptr_y_cn[i] = rand();

    float ptr_x1[2 * NR1 * NC1] = {0};
    for (int i = 0; i < 2 * NR1 * NC1; i++)
        ptr_x1[i] = rand();

    float ptr_x2[2 * NC1 * NC2] = {0};
    for (int i = 0; i < 2 * NC1 * NC2; i++)
        ptr_x2[i] = rand();

    DSPF_sp_mat_mul_cplx_cn(ptr_x1, NR1, NC1, ptr_x2, NC2, ptr_y_cn);

    return 0;
}