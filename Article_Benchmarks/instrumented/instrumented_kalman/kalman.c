/**

Code for a Kalman filter
Code version of a benchmark used for evaluating the XPP-VC compiler and the XPP architecture
Jo�o M.P. Cardoso, 2002
@PACT XPP Technologies, Munich, Germany

Version v1,
Jo�o M.P. Cardoso, May 2020

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//#include "xpuports.h"

/**
	Kalman filter
*/
void kalman(int Y[16], int A[256], int K[256], int G[256], int V[4])
{
    FILE *log_file_0 = fopen("kalman.dot", "w+");
    if (log_file_0 == NULL)
    {
        printf("Error opening file kalman.dot\n");
        exit(1);
    }
    fprintf(log_file_0, "Digraph G {\n");
    //---------------------
    int n_const = 0;
    int n_temp = 0;
    int n_op = 0;
    int n_mux = 0;
    int ne = 0;
    int n_i = 0;
    int n_j = 0;
    int n_index = 0;
    int n_temp1 = 0;
    int n_X[16] = {0};
    int n_Y[16] = {0};
    int n_A[256] = {0};
    int n_K[256] = {0};
    int n_G[256] = {0};
    int n_V[4] = {0};
    n_i++;
    fprintf(log_file_0, "\"i_%d\" [label=\"i\", att1=var, att2=loc, att3=int ];\n", n_i);
    n_j++;
    fprintf(log_file_0, "\"j_%d\" [label=\"j\", att1=var, att2=loc, att3=int ];\n", n_j);
    n_index++;
    fprintf(log_file_0, "\"index_%d\" [label=\"index\", att1=var, att2=loc, att3=int ];\n", n_index);
    n_temp1++;
    fprintf(log_file_0, "\"temp1_%d\" [label=\"temp\", att1=var, att2=loc, att3=int ];\n", n_temp1);
    for (int _i = 0; _i < 16; _i++)
    {
        n_Y[_i]++;
        fprintf(log_file_0, "\"Y[%d]_%d_l\" [label=\"Y[%d]\", att1=var, att2=inte, att3=int ];\n", _i, n_Y[_i], _i);
    }
    for (int _i = 0; _i < 256; _i++)
    {
        n_A[_i]++;
        fprintf(log_file_0, "\"A[%d]_%d_l\" [label=\"A[%d]\", att1=var, att2=inte, att3=int ];\n", _i, n_A[_i], _i);
    }
    for (int _i = 0; _i < 256; _i++)
    {
        n_K[_i]++;
        fprintf(log_file_0, "\"K[%d]_%d_l\" [label=\"K[%d]\", att1=var, att2=inte, att3=int ];\n", _i, n_K[_i], _i);
    }
    for (int _i = 0; _i < 256; _i++)
    {
        n_G[_i]++;
        fprintf(log_file_0, "\"G[%d]_%d_l\" [label=\"G[%d]\", att1=var, att2=inte, att3=int ];\n", _i, n_G[_i], _i);
    }
    for (int _i = 0; _i < 4; _i++)
    {
        n_V[_i]++;
        fprintf(log_file_0, "\"V[%d]_%d_l\" [label=\"V[%d]\", att1=var, att2=inte, att3=int ];\n", _i, n_V[_i], _i);
    }
    //---------------------
    //---------------------
    //---------------------
    int i, j, index, temp;
    //---------------------
    //---------------------
    int X[16];
    //---------------------
    //---------------------
    /*Initializing state Vector X*/
    for (i = 0; i < 16; i++)
    {
        //---------------------
        n_const++;
        fprintf(log_file_0, "const%d [label=\"0\", att1=const];\n", n_const);
        n_X[i]++;
        fprintf(log_file_0, "\"X[%d]_%d_l\" [label=\"X[%d]\", att1=var, att2=loc, att3=int ];\n", i, n_X[i], i);
        ne++;
        fprintf(log_file_0, "\"const%d\"->\"X[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_const, i, n_X[i], ne, ne);
        //---------------------
        X[i] = 0;
    }
    //---------------------
    //---------------------
    /*Initializing state Vector Y*/
    for (i = 13; i < 16; i++)
    {
        //---------------------
        n_const++;
        fprintf(log_file_0, "const%d [label=\"0\", att1=const];\n", n_const);
        n_Y[i]++;
        fprintf(log_file_0, "\"Y[%d]_%d_l\" [label=\"Y[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_Y[i], i);
        ne++;
        fprintf(log_file_0, "\"const%d\"->\"Y[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_const, i, n_Y[i], ne, ne);
        //---------------------
        Y[i] = 0;
    }
    //---------------------
    //---------------------
    /*-- Computing state Vector X*/
    for (i = 0; i < 16; i++)
    {
        //---------------------
        n_const++;
        fprintf(log_file_0, "const%d [label=\"0\", att1=const];\n", n_const);
        n_temp1++;
        fprintf(log_file_0, "\"temp_%d\" [label=\"temp\", att1=var, att2=loc, att3=int ];\n", n_temp1);
        ne++;
        fprintf(log_file_0, "\"const%d\"->\"temp_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_temp1, ne, ne);
        //---------------------
        temp = 0;
        for (j = 0; j < 16; j++)
        {
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(log_file_0, "temp%d [label=\"temp_l41_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, j);
            n_const++;
            fprintf(log_file_0, "const%d [label=\"16\", att1=const];\n", n_const);
            ne++;
            fprintf(log_file_0, "\"i_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_i, n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"op%d\"->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            n_temp++;
            fprintf(log_file_0, "temp%d [label=\"temp_l41_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, j);
            ne++;
            fprintf(log_file_0, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp - 1, n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"j_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_j, n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"op%d\"->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_index++;
            fprintf(log_file_0, "\"index_%d\" [label=\"index\", att1=var, att2=loc, att3=int ];\n", n_index);
            ne++;
            fprintf(log_file_0, "temp%d->\"index_%d\" [label=\"%d\", ord=\"%d\"];\n", n_temp, n_index, ne, ne);
            //---------------------
            index = i * 16 + j;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(log_file_0, "temp%d [label=\"temp_l42_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, j);
            ne++;
            fprintf(log_file_0, "\"A[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", index, n_A[index], n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"X[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", j, n_X[j], n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"op%d\"->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(log_file_0, "temp%d [label=\"temp_l42_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, j);
            ne++;
            fprintf(log_file_0, "\"K[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", index, n_K[index], n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"Y[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", j, n_Y[j], n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"op%d\"->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(log_file_0, "op%d [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp, n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp - 1, n_op, ne, ne);
            n_temp++;
            fprintf(log_file_0, "temp%d [label=\"temp_l42_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, j);
            ne++;
            fprintf(log_file_0, "op%d->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(log_file_0, "op%d [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "temp%d->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp, n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "temp_%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp1, n_op, ne, ne);
            n_temp1++;
            fprintf(log_file_0, "\"temp_%d\" [label=temp, att1=var, att2=loc, att3=int ];\n", n_temp1);
            ne++;
            fprintf(log_file_0, "op%d->temp_%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp1, ne, ne);
            //---------------------
            temp += (A[index] * X[j] + K[index] * Y[j]);
        }
        //---------------------
        n_X[i]++;
        fprintf(log_file_0, "\"X[%d]_%d_l\" [label=\"Y[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_X[i], i);
        ne++;
        fprintf(log_file_0, "\"X[%d]_%d_l\"->\"temp_%d\" [label=\"%d\", ord=\"%d\"];\n", i, n_X[i], n_temp1, ne, ne);
        //---------------------
        X[i] = temp;
    }
    //---------------------
    //---------------------
    /*-- Computing output Vector V*/
    //---------------------
    //---------------------
    // it only uses 4x16 elements of G
    for (i = 0; i < 4; i++)
    {
        //---------------------
        n_const++;
        fprintf(log_file_0, "const%d [label=\"0\", att1=const];\n", n_const);
        n_temp1++;
        fprintf(log_file_0, "\"temp_%d\" [label=\"temp\", att1=var, att2=loc, att3=int ];\n", n_temp);
        ne++;
        fprintf(log_file_0, "\"const%d\"->\"temp_%d\" [label=\"%d\", ord=\"%d\"];\n", n_const, n_temp1, ne, ne);
        //---------------------
        temp = 0;
        for (j = 0; j < 16; j++)
        {
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(log_file_0, "temp%d [label=\"temp_l52_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, j);
            n_const++;
            fprintf(log_file_0, "const%d [label=\"16\", att1=const];\n", n_const);
            ne++;
            fprintf(log_file_0, "\"i_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_i, n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"const%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_const, n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"op%d\"->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"+\", att1=op];\n", n_op);
            n_temp++;
            fprintf(log_file_0, "temp%d [label=\"temp_l52_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, j);
            ne++;
            fprintf(log_file_0, "\"temp%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp - 1, n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"j_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_j, n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"op%d\"->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_index++;
            fprintf(log_file_0, "\"index_%d\" [label=\"index\", att1=var, att2=loc, att3=int ];\n", n_index);
            ne++;
            fprintf(log_file_0, "temp%d->\"index_%d\" [label=\"%d\", ord=\"%d\"];\n", n_temp, n_index, ne, ne);
            //---------------------
            index = i * 16 + j;
            //---------------------
            n_op++;
            fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
            n_temp++;
            fprintf(log_file_0, "temp%d [label=\"temp_l52_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, j);
            ne++;
            fprintf(log_file_0, "\"G[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", index, n_G[index], n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"X[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", j, n_X[j], n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "\"op%d\"->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

            n_op++;
            fprintf(log_file_0, "op%d [label=\"+\", att1=op];\n", n_op);
            ne++;
            fprintf(log_file_0, "temp%d->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp, n_op, ne, ne);
            ne++;
            fprintf(log_file_0, "temp_%d->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", n_temp1, n_op, ne, ne);
            n_temp1++;
            fprintf(log_file_0, "\"temp_%d\" [label=temp, att1=var, att2=loc, att3=int ];\n", n_temp1);
            ne++;
            fprintf(log_file_0, "op%d->temp_%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp1, ne, ne);
            //---------------------
            temp += (G[index] * X[j]);
        }
        //---------------------
        n_op++;
        fprintf(log_file_0, "\"op%d\" [label=\"*\", att1=op];\n", n_op);
        n_temp++;
        fprintf(log_file_0, "temp%d [label=\"temp_l55_i%d\", att1=var, att2=loc, att3=int ];\n", n_temp, j);
        ne++;
        fprintf(log_file_0, "\"temp_%d\"->op%d [label=\"%d\", ord=\"%d\", pos=\"l\"];\n", n_temp1, n_op, ne, ne);
        ne++;
        fprintf(log_file_0, "\"Y[%d]_%d_l\"->op%d [label=\"%d\", ord=\"%d\", pos=\"r\"];\n", i + 1, n_Y[i + 1], n_op, ne, ne);
        ne++;
        fprintf(log_file_0, "\"op%d\"->temp%d [label=\"%d\", ord=\"%d\"];\n", n_op, n_temp, ne, ne);

        n_V[i]++;
        fprintf(log_file_0, "\"V[%d]_%d_l\" [label=\"V[%d]\", att1=var, att2=inte, att3=int ];\n", i, n_V[i], i);
        ne++;
        fprintf(log_file_0, "temp%d->\"V[%d]_%d_l\" [label=\"%d\", ord=\"%d\"];\n", n_temp, i, n_V[i], ne, ne);
        //---------------------
        V[i] = (temp * Y[i + 1]);
    }
    //---------------------
    fprintf(log_file_0, "}\n");
    fclose(log_file_0);
    //---------------------
}

int main()
{
    int i, j, tmp, index;

    int A[16 * 16];
    int K[16 * 16];
    int Y[16];
    int G[16 * 16];
    int V[4];

    /* read data stream from port 1 */
    for (i = 0; i < 12; i++)
    {
        //getstream(1, &tmp);
        tmp = i * j;
        Y[i] = tmp;
    }

    /* initialize for now:*/
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 16; j++)
        {
            index = i * 16 + j;
            G[index] = 2 * (i + j);
            K[index] = i + j;
            A[index] = i - j;
        }
    }

    kalman(Y, A, K, G, V);

    /*-- Output Vector V */
    /* write data stream to output */
    // for now just calculate a checksum
    int checksum = 0;
    for (i = 0; i < 4; i++)
    {
        //putstream(4, V[i]);
        checksum += abs(V[i]);
    }
    printf("checksum = %d\n", checksum);
    if (checksum == -410206000)
        printf("RIGHT!\n");
    else
        printf("WRONG!\n");
    return 0;
}
