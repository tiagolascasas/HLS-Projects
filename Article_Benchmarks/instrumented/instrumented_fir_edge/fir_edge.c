#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define LENGTH 600
#define SIZE WIDTH *LENGTH

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

int K[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

void fir_edge(int p1[SIZE], int p2[SIZE], int in[SIZE]);

void fir(int p1[SIZE], int p2[SIZE], int in[SIZE])
{
    //---------------------
    FILE *f = fopen("fir.dot", "w");
    int n_const = 0;
    int n_temp = 0;
    int ne = 0;
    int n_op = 0;
    int n_mux = 0;

    int n_sumval = 0;

    int n_p1[SIZE] = {0};
    int n_in[SIZE] = {0};
    fprintf(f, "Digraph G{\n");
    for (int i = 0; i < SIZE; i++)
    {
        n_p1[i]++;
        fprintf(f, "\"p1[%d]_%d_l\" [label=\"p1[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_p1[i], i);
        n_in[i]++;
        fprintf(f, "\"in[%d]_%d_l\" [label=\"in[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_in[i], i);
    }
    int n_K[9] = {0};
    for (int i = 0; i < 9; i++)
    {
        n_K[i]++;
        fprintf(f, "\"K[%d]_%d_l\" [label=\"K[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_K[i], i);
    }
    //---------------------
    for (int i = 0; i < SIZE; i++)
    {
        //---------------------
        n_const++;
        fprintf(f, "const%d [label=\"%d\", att1=const];\n", n_const, i);
        n_in[i]++;
        fprintf(f, "\"in[%d]_%d_l\" [label=\"in[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_in[i], i);
        ne++;
        fprintf(f, "\"const%d\"->\"in[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_const, i, n_in[i], ne, ne);
        //---------------------
        in[i] = i;
    }

    for (int row = 0; row <= LENGTH - 3; row++)
    {
        for (int col = 0; col <= WIDTH - 3; col++)
        {
            //---------------------
            n_const++;
            fprintf(f, "const%d [label=\"0\", att1=const];\n", n_const);
            n_sumval++;
            fprintf(f, "\"sumval_%d\" [label=sumval, att1=var, att2=loc, att3=int ];\n", n_sumval);
            ne++;
            fprintf(f, "const%d->\"sumval_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_sumval, ne, ne);
            //---------------------
            int sumval = 0;

            for (int wrow = 0; wrow < 3; wrow++)
            {
                for (int wcol = 0; wcol < 3; wcol++)
                {
                    //---------------------
                    n_op++;
                    fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
                    n_temp++;
                    fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
                    ne++;
                    fprintf(f, "\"in[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", (row + wrow) * WIDTH + col + wcol, n_in[(row + wrow) * WIDTH + col + wcol], n_op, ne, ne);
                    ne++;
                    fprintf(f, "\"K[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", wrow * 3 + wcol, n_K[wrow * 3 + wcol], n_op, ne, ne);
                    ne++;
                    fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

                    n_op++;
                    fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
                    ne++;
                    fprintf(f, "temp%d->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp, n_op, ne, ne);
                    ne++;
                    fprintf(f, "sumval_%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_sumval, n_op, ne, ne);
                    n_sumval++;
                    fprintf(f, "\"sumval_%d\" [label=sumval, att1=var, att2=loc, att3=int ];\n", n_sumval);
                    ne++;
                    fprintf(f, "op%d->sumval_%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_sumval, ne, ne);
                    //---------------------
                    sumval += in[(row + wrow) * WIDTH + col + wcol] * K[wrow * 3 + wcol];
                }
            }
            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\">>\", att1=op];\n", n_op);
            ne++;
            fprintf(f, "sumval_%d->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_sumval, n_op, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"4\", att1=const];\n", n_const);
            ne++;
            fprintf(f, "const%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);
            n_sumval++;
            fprintf(f, "\"sumval_%d\" [label=sumval, att1=var, att2=loc, att3=int];\n", n_sumval);
            ne++;
            fprintf(f, "op%d->sumval_%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_sumval, ne, ne);
            //---------------------
            sumval = sumval >> 4;
            //---------------------
            n_p1[row * WIDTH + col]++;
            fprintf(f, "\"p1[%d]_%d_l\" [label=\"p1[%d]\", att1=var, att2=inte, att3=int ];\n", row * WIDTH + col, n_p1[row * WIDTH + col], row * WIDTH + col);
            ne++;
            fprintf(f, "sumval_%d->\"p1[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_sumval, row * WIDTH + col, n_p1[row * WIDTH + col], ne, ne);
            //---------------------
            p1[row * WIDTH + col] = sumval;
        }
    }
    //---------------------
    fprintf(f, "}\n");
    fclose(f);
    //---------------------
}

void edge(int p1[SIZE], int p2[SIZE])
{
    //---------------------
    FILE *f = fopen("edge.dot", "w");
    int n_const = 0;
    int n_temp = 0;
    int ne = 0;
    int n_op = 0;
    int n_mux = 0;

    int n_htmp = 0;
    int n_vtmp = 0;
    int n_sum = 0;

    int n_p1[SIZE] = {0};
    int n_p2[SIZE] = {0};
    fprintf(f, "Digraph G{\n");
    for (int i = 0; i < SIZE; i++)
    {
        n_p1[i]++;
        fprintf(f, "\"p1[%d]_%d_l\" [label=\"p1[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_p1[i], i);
        n_p2[i]++;
        fprintf(f, "\"p2[%d]_%d_l\" [label=\"p2[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_p2[i], i);
    }
    int n_K[9] = {0};
    for (int i = 0; i < 9; i++)
    {
        n_K[i]++;
        fprintf(f, "\"K[%d]_%d_l\" [label=\"K[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_K[i], i);
    }
    //---------------------
    for (int v = 0; v <= LENGTH - 3; v++)
    {
        for (int h = 0; h <= WIDTH - 3; h++)
        {
            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", (v + 2) * WIDTH + h, n_p1[(v + 2) * WIDTH + h], n_op, ne, ne);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", v * WIDTH + h, n_p1[v * WIDTH + h], n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", (v + 2) * WIDTH + h + 2, n_p1[(v + 2) * WIDTH + h + 2], n_op, ne, ne);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", v * WIDTH + h + 2, n_p1[v * WIDTH + h + 2], n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp - 2, n_op, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", (v + 2) * WIDTH + h + 1, n_p1[(v + 2) * WIDTH + h + 1], n_op, ne, ne);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", v * WIDTH + h + 1, n_p1[v * WIDTH + h + 1], n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            n_const++;
            fprintf(f, "const%d [label=\"2\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_const, n_op, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp - 3, n_op, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
            n_htmp++;
            fprintf(f, "htmp_%d [label=\"htmp\", att1=var, att2=loc, att3=int ];\n", n_htmp);
            ne++;
            fprintf(f, "op%d->htmp_%d [label=\"%d\", ord=\"%d\" ];\n", n_op, n_htmp, ne, ne);
            //---------------------
            int htmp = (p1[(v + 2) * WIDTH + h] - p1[v * WIDTH + h]) +
                       (p1[(v + 2) * WIDTH + h + 2] - p1[v * WIDTH + h + 2]) +
                       2 * (p1[(v + 2) * WIDTH + h + 1] - p1[v * WIDTH + h + 1]);

            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\"<\", att1=op];\n", n_op);
            ne++;
            fprintf(f, "\"htmp_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_htmp, n_op, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"0\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"htmp_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_htmp, n_op, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"-1\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);
            ne++;
            fprintf(f, "\"op%d\"->temp%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_op, n_temp, ne, ne);

            n_mux++;
            fprintf(f, "mux%d [label=mux%d, att1=mux, att2=op%d];\n", n_mux, n_mux, n_op - 1);
            ne++;
            fprintf(f, "\"op%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"sel\"];\n", n_op - 1, n_mux, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"t\"];\n", n_temp, n_mux, ne, ne);
            ne++;
            fprintf(f, "\"htmp_%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"f\"];\n", n_htmp, n_mux, ne, ne);

            n_htmp++;
            fprintf(f, "\"htmp_%d\" [label=\"htmp\", att1=var, att2=loc, att3=int ];\n", n_htmp);
            ne++;
            fprintf(f, "\"mux%d\"->htmp_%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_mux, n_htmp, ne, ne);
            //---------------------
            htmp = (htmp < 0) ? -htmp : htmp;

            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", v * WIDTH + h + 2, n_p1[v * WIDTH + h + 2], n_op, ne, ne);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", v * WIDTH + h, n_p1[v * WIDTH + h], n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", (v + 2) * WIDTH + h + 2, n_p1[(v + 2) * WIDTH + h + 2], n_op, ne, ne);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", (v + 2) * WIDTH + h, n_p1[(v + 2) * WIDTH + h], n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp - 2, n_op, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", p1[(v + 1) * WIDTH + h + 2], n_p1[(v + 1) * WIDTH + h + 2], n_op, ne, ne);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", p1[(v + 1) * WIDTH + h], n_p1[(v + 1) * WIDTH + h], n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            n_const++;
            fprintf(f, "const%d [label=\"2\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_const, n_op, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp - 3, n_op, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
            n_vtmp++;
            fprintf(f, "vtmp_%d [label=\"vtmp\", att1=var, att2=loc, att3=int];\n", n_vtmp);
            ne++;
            fprintf(f, "op%d->vtmp_%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_vtmp, ne, ne);
            //---------------------
            int vtmp = (p1[v * WIDTH + h + 2] - p1[v * WIDTH + h]) +
                       (p1[(v + 2) * WIDTH + h + 2] - p1[(v + 2) * WIDTH + h]) +
                       2 * (p1[(v + 1) * WIDTH + h + 2] - p1[(v + 1) * WIDTH + h]);

            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\"<\", att1=op];\n", n_op);
            ne++;
            fprintf(f, "\"vtmp_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_vtmp, n_op, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"0\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"vtmp_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_vtmp, n_op, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"-1\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);
            ne++;
            fprintf(f, "\"op%d\"->temp%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_op, n_temp, ne, ne);

            n_mux++;
            fprintf(f, "mux%d [label=mux%d, att1=mux, att2=op%d];\n", n_mux, n_mux, n_op - 1);
            ne++;
            fprintf(f, "\"op%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"sel\"];\n", n_op - 1, n_mux, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"t\"];\n", n_temp, n_mux, ne, ne);
            ne++;
            fprintf(f, "\"vtmp_%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"f\"];\n", n_vtmp, n_mux, ne, ne);

            n_vtmp++;
            fprintf(f, "\"vtmp_%d\" [label=\"vtmp\", att1=var, att2=loc, att3=int ];\n", n_vtmp);
            ne++;
            fprintf(f, "\"mux%d\"->vtmp_%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_mux, n_vtmp, ne, ne);
            //---------------------
            vtmp = (vtmp < 0) ? -vtmp : vtmp;

            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(f, "\"htmp_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_htmp, n_op, ne, ne);
            ne++;
            fprintf(f, "\"vtmp_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_vtmp, n_op, ne, ne);
            n_sum++;
            fprintf(f, "sum_%d [label=\"sum\", att1=var, att2=loc, att3=int ];\n", n_sum);
            ne++;
            fprintf(f, "op%d->sum_%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_sum, ne, ne);
            //---------------------
            int sum = htmp + vtmp;

            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\">\", att1=op];\n", n_op);
            ne++;
            fprintf(f, "\"sum_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_sum, n_op, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"255\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);

            n_mux++;
            fprintf(f, "mux%d [label=mux%d, att1=mux, att2=op%d];\n", n_mux, n_mux, n_op);
            ne++;
            fprintf(f, "\"op%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"sel\"];\n", n_op, n_mux, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"255\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"t\"];\n", n_const, n_mux, ne, ne);
            ne++;
            fprintf(f, "\"sum_%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"f\"];\n", n_sum, n_mux, ne, ne);

            n_sum++;
            fprintf(f, "\"sum_%d\" [label=\"sum\", att1=var, att2=loc, att3=int ];\n", n_sum);
            ne++;
            fprintf(f, "\"mux%d\"->sum_%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_mux, n_sum, ne, ne);
            //---------------------
            sum = (sum > 255) ? 255 : sum;

            //---------------------
            n_p2[(v + 1) * WIDTH + h + 1]++;
            fprintf(f, "\"p2[%d]_%d_l\" [label=\"p2[%d]\", att1=var, att2=inte, att3=int ];\n", (v + 1) * WIDTH + h + 1, n_p2[(v + 1) * WIDTH + h + 1], (v + 1) * WIDTH + h + 1);
            ne++;
            fprintf(f, "sum_%d->\"p2[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_sum, (v + 1) * WIDTH + h + 1, n_p2[(v + 1) * WIDTH + h + 1], ne, ne);
            //---------------------
            p2[(v + 1) * WIDTH + h + 1] = sum;
        }
    }
    //---------------------
    fprintf(f, "}\n");
    fclose(f);
    //---------------------
}

int main(void)
{
    srand(0);
    int *p1 = malloc(sizeof(int) * SIZE);
    int *p2 = malloc(sizeof(int) * SIZE);
    int *in = malloc(sizeof(int) * SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        in[i] = rand();
        p1[i] = rand();
        p2[i] = rand();
    }

    fir(p1, p2, in);
    edge(p1, p2);

    for (int i = 0; i < SIZE; i++)
    {
        in[i] = rand();
        p1[i] = rand();
        p2[i] = rand();
    }

    fir_edge(p1, p2, in);

    return 0;
}

void fir_edge(int p1[SIZE], int p2[SIZE], int in[SIZE])
{
    //---------------------
    FILE *f = fopen("fir_edge.dot", "w");
    int n_const = 0;
    int n_temp = 0;
    int ne = 0;
    int n_op = 0;
    int n_mux = 0;

    int n_htmp = 0;
    int n_vtmp = 0;
    int n_sum = 0;
    int n_sumval = 0;

    int n_p1[SIZE] = {0};
    int n_p2[SIZE] = {0};
    int n_in[SIZE] = {0};
    fprintf(f, "Digraph G{\n");
    for (int i = 0; i < SIZE; i++)
    {
        n_p1[i]++;
        fprintf(f, "\"p1[%d]_%d_l\" [label=\"p1[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_p1[i], i);
        n_p2[i]++;
        fprintf(f, "\"p2[%d]_%d_l\" [label=\"p2[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_p2[i], i);
        n_in[i]++;
        fprintf(f, "\"in[%d]_%d_l\" [label=\"in[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_in[i], i);
    }
    int n_K[9] = {0};
    for (int i = 0; i < 9; i++)
    {
        n_K[i]++;
        fprintf(f, "\"K[%d]_%d_l\" [label=\"K[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_K[i], i);
    }
    //---------------------

    for (int i = 0; i < SIZE; i++)
    {
        //---------------------
        n_const++;
        fprintf(f, "const%d [label=\"%d\", att1=const];\n", n_const, i);
        n_in[i]++;
        fprintf(f, "\"in[%d]_%d_l\" [label=\"in[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_in[i], i);
        ne++;
        fprintf(f, "\"const%d\"->\"in[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_const, i, n_in[i], ne, ne);
        //---------------------
        in[i] = i;
    }

    for (int row = 0; row <= LENGTH - 3; row++)
    {
        for (int col = 0; col <= WIDTH - 3; col++)
        {
            //---------------------
            n_const++;
            fprintf(f, "const%d [label=\"0\", att1=const];\n", n_const);
            n_sumval++;
            fprintf(f, "\"sumval_%d\" [label=sumval, att1=var, att2=loc, att3=int ];\n", n_sumval);
            ne++;
            fprintf(f, "const%d->\"sumval_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_sumval, ne, ne);
            //---------------------
            int sumval = 0;

            for (int wrow = 0; wrow < 3; wrow++)
            {
                for (int wcol = 0; wcol < 3; wcol++)
                {
                    //---------------------
                    n_op++;
                    fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
                    n_temp++;
                    fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
                    ne++;
                    fprintf(f, "\"in[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", (row + wrow) * WIDTH + col + wcol, n_in[(row + wrow) * WIDTH + col + wcol], n_op, ne, ne);
                    ne++;
                    fprintf(f, "\"k[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", wrow * 3 + wcol, n_K[wrow * 3 + wcol], n_op, ne, ne);
                    ne++;
                    fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

                    n_op++;
                    fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
                    ne++;
                    fprintf(f, "temp%d->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp, n_op, ne, ne);
                    ne++;
                    fprintf(f, "sumval_%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_sumval, n_op, ne, ne);
                    n_sumval++;
                    fprintf(f, "\"sumval_%d\" [label=sumval, att1=var, att2=loc, att3=int ];\n", n_sumval);
                    ne++;
                    fprintf(f, "op%d->sumval_%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_sumval, ne, ne);
                    //---------------------
                    sumval += in[(row + wrow) * WIDTH + col + wcol] * K[wrow * 3 + wcol];
                }
            }
            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\">>\", att1=op];\n", n_op);
            ne++;
            fprintf(f, "sumval_%d->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_sumval, n_op, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"4\", att1=const];\n", n_const);
            ne++;
            fprintf(f, "const%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);
            n_sumval++;
            fprintf(f, "\"sumval_%d\" [label=sumval, att1=var, att2=loc, att3=int ];\n", n_sumval);
            ne++;
            fprintf(f, "op%d->sumval_%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_sumval, ne, ne);
            //---------------------
            sumval = sumval >> 4;
            //---------------------
            n_p1[row * WIDTH + col]++;
            fprintf(f, "\"p1[%d]_%d_l\" [label=\"p1[%d]\", att1=var, att2=inte, att3=int ];\n", row * WIDTH + col, n_p1[row * WIDTH + col], row * WIDTH + col);
            ne++;
            fprintf(f, "sumval_%d->\"p1[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_sumval, row * WIDTH + col, n_p1[row * WIDTH + col], ne, ne);
            //---------------------
            p1[row * WIDTH + col] = sumval;
        }
    }

    for (int v = 0; v <= LENGTH - 3; v++)
    {
        for (int h = 0; h <= WIDTH - 3; h++)
        {
            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", (v + 2) * WIDTH + h, n_p1[(v + 2) * WIDTH + h], n_op, ne, ne);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", v * WIDTH + h, n_p1[v * WIDTH + h], n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", (v + 2) * WIDTH + h + 2, n_p1[(v + 2) * WIDTH + h + 2], n_op, ne, ne);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", v * WIDTH + h + 2, n_p1[v * WIDTH + h + 2], n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp - 2, n_op, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", (v + 2) * WIDTH + h + 1, n_p1[(v + 2) * WIDTH + h + 1], n_op, ne, ne);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", v * WIDTH + h + 1, n_p1[v * WIDTH + h + 1], n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            n_const++;
            fprintf(f, "const%d [label=\"2\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_const, n_op, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp - 3, n_op, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
            n_htmp++;
            fprintf(f, "htmp_%d [label=\"htmp\", att1=var, att2=loc, att3=int ];\n", n_htmp);
            ne++;
            fprintf(f, "op%d->htmp_%d [label=\"%d\", ord=\"%d\" ];\n", n_op, n_htmp, ne, ne);
            //---------------------
            int htmp = (p1[(v + 2) * WIDTH + h] - p1[v * WIDTH + h]) +
                       (p1[(v + 2) * WIDTH + h + 2] - p1[v * WIDTH + h + 2]) +
                       2 * (p1[(v + 2) * WIDTH + h + 1] - p1[v * WIDTH + h + 1]);

            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\"<\", att1=op];\n", n_op);
            ne++;
            fprintf(f, "\"htmp_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_htmp, n_op, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"0\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"htmp_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_htmp, n_op, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"-1\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);
            ne++;
            fprintf(f, "\"op%d\"->temp%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_op, n_temp, ne, ne);

            n_mux++;
            fprintf(f, "mux%d [label=mux%d, att1=mux, att2=op%d];\n", n_mux, n_mux, n_op - 1);
            ne++;
            fprintf(f, "\"op%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"sel\"];\n", n_op - 1, n_mux, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"t\"];\n", n_temp, n_mux, ne, ne);
            ne++;
            fprintf(f, "\"htmp_%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"f\"];\n", n_htmp, n_mux, ne, ne);

            n_htmp++;
            fprintf(f, "\"htmp_%d\" [label=\"htmp\", att1=var, att2=loc, att3=int ];\n", n_htmp);
            ne++;
            fprintf(f, "\"mux%d\"->htmp_%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_mux, n_htmp, ne, ne);
            //---------------------
            htmp = (htmp < 0) ? -htmp : htmp;

            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", v * WIDTH + h + 2, n_p1[v * WIDTH + h + 2], n_op, ne, ne);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", v * WIDTH + h, n_p1[v * WIDTH + h], n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", (v + 2) * WIDTH + h + 2, n_p1[(v + 2) * WIDTH + h + 2], n_op, ne, ne);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", (v + 2) * WIDTH + h, n_p1[(v + 2) * WIDTH + h], n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp - 2, n_op, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"-\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", p1[(v + 1) * WIDTH + h + 2], n_p1[(v + 1) * WIDTH + h + 2], n_op, ne, ne);
            ne++;
            fprintf(f, "\"p1[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", p1[(v + 1) * WIDTH + h], n_p1[(v + 1) * WIDTH + h], n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            n_const++;
            fprintf(f, "const%d [label=\"2\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_const, n_op, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
            ne++;
            fprintf(f, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp - 3, n_op, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
            n_vtmp++;
            fprintf(f, "vtmp_%d [label=\"vtmp\", att1=var, att2=loc, att3=int];\n", n_vtmp);
            ne++;
            fprintf(f, "op%d->vtmp_%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_vtmp, ne, ne);
            //---------------------
            int vtmp = (p1[v * WIDTH + h + 2] - p1[v * WIDTH + h]) +
                       (p1[(v + 2) * WIDTH + h + 2] - p1[(v + 2) * WIDTH + h]) +
                       2 * (p1[(v + 1) * WIDTH + h + 2] - p1[(v + 1) * WIDTH + h]);

            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\"<\", att1=op];\n", n_op);
            ne++;
            fprintf(f, "\"vtmp_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_vtmp, n_op, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"0\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);

            n_op++;
            fprintf(f, "op%d [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(f, "temp%d [label=\"temp_l77_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, n_temp);
            ne++;
            fprintf(f, "\"vtmp_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_vtmp, n_op, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"-1\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);
            ne++;
            fprintf(f, "\"op%d\"->temp%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_op, n_temp, ne, ne);

            n_mux++;
            fprintf(f, "mux%d [label=mux%d, att1=mux, att2=op%d];\n", n_mux, n_mux, n_op - 1);
            ne++;
            fprintf(f, "\"op%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"sel\"];\n", n_op - 1, n_mux, ne, ne);
            ne++;
            fprintf(f, "\"temp%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"t\"];\n", n_temp, n_mux, ne, ne);
            ne++;
            fprintf(f, "\"vtmp_%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"f\"];\n", n_vtmp, n_mux, ne, ne);

            n_vtmp++;
            fprintf(f, "\"vtmp_%d\" [label=\"vtmp\", att1=var, att2=loc, att3=int ];\n", n_vtmp);
            ne++;
            fprintf(f, "\"mux%d\"->vtmp_%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_mux, n_vtmp, ne, ne);
            //---------------------
            vtmp = (vtmp < 0) ? -vtmp : vtmp;

            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(f, "\"htmp_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_htmp, n_op, ne, ne);
            ne++;
            fprintf(f, "\"vtmp_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_vtmp, n_op, ne, ne);
            n_sum++;
            fprintf(f, "sum_%d [label=\"sum\", att1=var, att2=loc, att3=int ];\n", n_sum);
            ne++;
            fprintf(f, "op%d->sum_%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_sum, ne, ne);
            //---------------------
            int sum = htmp + vtmp;

            //---------------------
            n_op++;
            fprintf(f, "op%d [label=\">\", att1=op];\n", n_op);
            ne++;
            fprintf(f, "\"sum_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_sum, n_op, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"255\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);

            n_mux++;
            fprintf(f, "mux%d [label=mux%d, att1=mux, att2=op%d];\n", n_mux, n_mux, n_op);
            ne++;
            fprintf(f, "\"op%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"sel\"];\n", n_op, n_mux, ne, ne);
            n_const++;
            fprintf(f, "const%d [label=\"255\", att1=var, att2=loc, att3=int ];\n", n_const);
            ne++;
            fprintf(f, "\"const%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"t\"];\n", n_const, n_mux, ne, ne);
            ne++;
            fprintf(f, "\"sum_%d\"->mux%d [label=\"%d\", ord=\"%d\", pos=\"f\"];\n", n_sum, n_mux, ne, ne);

            n_sum++;
            fprintf(f, "\"sum_%d\" [label=\"sum\", att1=var, att2=loc, att3=int ];\n", n_sum);
            ne++;
            fprintf(f, "\"mux%d\"->sum_%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_mux, n_sum, ne, ne);
            //---------------------
            sum = (sum > 255) ? 255 : sum;

            //---------------------
            n_p2[(v + 1) * WIDTH + h + 1]++;
            fprintf(f, "\"p2[%d]_%d_l\" [label=\"p2[%d]\", att1=var, att2=inte, att3=int ];\n", (v + 1) * WIDTH + h + 1, n_p2[(v + 1) * WIDTH + h + 1], (v + 1) * WIDTH + h + 1);
            ne++;
            fprintf(f, "sum_%d->\"p2[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_sum, (v + 1) * WIDTH + h + 1, n_p2[(v + 1) * WIDTH + h + 1], ne, ne);
            //---------------------
            p2[(v + 1) * WIDTH + h + 1] = sum;
        }
    }
    //---------------------
    fprintf(f, "}\n");
    fclose(f);
    //---------------------
}