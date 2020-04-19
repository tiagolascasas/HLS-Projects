#include <stdio.h>
#include <math.h>

#define gamma 0
#define b 0
#define N_FEATURES 6
#define N_SUP_VECT 4

const float sv_coeff[N_FEATURES] = {1, 2, 2, 1, 2, 1};

const float sup_vectors[N_SUP_VECT][N_FEATURES] = {
    {1, 5, 2.2, 1.1, 2.2, 1.1},
    {1, 2, 4, 1.1, 2.2, 1.1},
    {1, 2.1, 2.2, 1.1, 2.2, 1.1},
    {1, 8, 2.2, 1.1, 2.2, 1.1}};

float coef1[N_FEATURES / 2] = {1, 2, 2};
float coef2[N_FEATURES / 2] = {1, 2, 1};

float sv1[N_SUP_VECT][N_FEATURES / 2] = {
    {1, 5, 2.2},
    {1, 2, 4},
    {1, 2.1, 2.2},
    {1, 8, 2.2}};

float sv2[N_SUP_VECT][N_FEATURES / 2] = {
    {1.1, 2.2, 1.1},
    {1.1, 2.2, 1.1},
    {1.1, 2.2, 1.1},
    {1.1, 2.2, 1.1}};

void svm_predict(float test_vector[N_SUP_VECT], float *sum)
{
    float diff;
    float norma;
    int count = 0;
    for (int i = 0; i < N_FEATURES; i++)
    {
        for (int j = 0; j < N_SUP_VECT; j++)
        {
            diff = test_vector[j] - sup_vectors[j][i];
            diff = diff * diff;
            norma = norma + diff;
            count++;
        }
        printf("i = %d, norma = %f\n", i, norma);
        *sum = *sum + (exp(-gamma * norma) * sv_coeff[i]);
        norma = 0;
    }
    *sum = *sum - b;
    printf("Count 1: %d\n", count);
}

/**
 * Partitioned SVM version from Tsoutsouras et al.
 */
void svm_partial_predict(int width, float *sum, float test_vector[N_SUP_VECT],
                         float sv_coef[N_FEATURES / 2],
                         float sup_vectors[N_SUP_VECT][N_FEATURES / 2],
                         int offset)
{
    int i, j;
    int count = 0;
    float diff, norma = 0;
    *sum = 0;

    for (i = 0; i < width; i++)
    {
        for (j = 0; j < N_SUP_VECT; j++)
        {
            diff = test_vector[j] - sup_vectors[j][i + offset];
            norma = norma + diff * diff;
            count++;
        }
        *sum = *sum + exp(-gamma * norma) * sv_coef[i + offset];
        printf("i = %d, norma = %f\n", i + offset, norma);
        norma = 0;
    }
    printf("Count 2: %d\n", count);
}

void svm_partitioned_predict(float test_vector[N_SUP_VECT], float *sum)
{
    float diff, sum1, sum2;
    svm_partial_predict(N_FEATURES / 2, &sum1, test_vector, coef1, sv1, 0);
    svm_partial_predict(N_FEATURES / 2, &sum2, test_vector, coef2, sv2,
                        N_FEATURES / 2);
    *sum = sum1 + sum2 - b;
}

int main()
{
    float s1, s2;
    float test_vector[N_SUP_VECT] = {1, 0, 1.1, 0.2};
    svm_predict(test_vector, &s1);
    svm_partitioned_predict(test_vector, &s2);
    printf("%f -- %f\n", s1, s2);
    return 0;
}