#include <stdio.h>
#include <math.h>
#include "svm.h"

void svm_predict(float test_vector[N_SUP_VECT], float *sum)
{
    float diff;
    float norma;
    for (int i = 0; i < N_FEATURES; i++)
    {
        for (int j = 0; j < N_SUP_VECT; j++)
        {
            diff = test_vector[j] - sup_vectors[j][i];
            diff = diff * diff;
            norma = norma + diff;
        }
        *sum = *sum + (exp(-gamma * norma) * sv_coeff[i]);
        norma = 0;
    }
    *sum = *sum - b;
}