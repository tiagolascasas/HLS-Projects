#include <stdio.h>
#include <stdlib.h>
int K[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

#define WIDTH 4
#define LENGTH 4
#define SIZE WIDTH *LENGTH

void fir(int p1[LENGTH][WIDTH], int in[LENGTH][WIDTH])
{
    FILE *f = fopen("fir.dot", "w+");
    if (f == NULL)
    {
        printf("Error opening file fir.dot\n");
        exit(1);
    }
    fprintf(f, "Digraph G {\n");
    //---------------------
    int n_const = 0;
    int n_temp = 0;
    int n_op = 0;
    int n_mux = 0;
    int ne = 0;
    int n_col = 0;
    int n_row = 0;
    int n_wrow = 0;
    int n_wcol = 0;
    int n_v = 0;
    int n_h = 0;
    int n_i = 0;
    int n_j = 0;
    int n_sumval = 0;
    int n_p1[4][4] = {0};
    int n_in[4][4] = {0};
    int n_K[9] = {0};
    //---------------------

    //---------------------
    //---------------------
    int col, row, wrow, wcol, v, h;
    //---------------------
    //---------------------
    int i, j;
    for (row = 0; row <= LENGTH - 3; row++)
    {
        for (col = 0; col <= WIDTH - 3; col++)
        {
            //---------------------
            //---------------------
            int sumval = 0;
            for (wrow = 0; wrow < 3; wrow++)
            {
                for (wcol = 0; wcol < 3; wcol++)
                {
                    //---------------------
                    //---------------------
                    sumval += in[row + wrow][col + wcol] * K[wrow * 3 + wcol];
                }
            }
            //---------------------
            //---------------------
            sumval = sumval >> 4; //(sumval * scala) >> 8;
            //---------------------
            //---------------------
            p1[row][col] = sumval;
        }
    }
    fclose(log_file_0);
}
