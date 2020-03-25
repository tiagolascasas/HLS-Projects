#include<stdio.h>
#include<math.h>
#include"svm.h"
/*
void svm_predict(float test_vector[N_SUP_VECT], float *sum) {
	float diff;
	float norma;
	for (int i = 0; i < N_FEATURES; i++) {
		for (int j = 0; j < N_SUP_VECT; j++) {
			diff = test_vector[j] - sup_vectors[j][i];
			diff = diff * diff;
			norma = norma + diff;
		}
		*sum = *sum + (exp(-gamma * norma) * sv_coeff[i]);
		norma = 0;
	}
	*sum = *sum - b;
}*/

/**
 * Partitioned SVM version from Tsoutsouras et al.
 */
void svm_partial_predict(int width, float* sum, float test_vector[N_SUP_VECT],
		float sv_coef[N_FEATURES / 2], float sup_vectors[N_SUP_VECT][N_FEATURES / 2], int offset) {
	int i, j;
	float diff, norma = 0;
	*sum = 0;

	for (i = 0; i < width; i++) {
		for (j = 0; j < N_SUP_VECT; j++) {
			diff = test_vector[j] - sup_vectors[j][i + offset];
			norma = norma + diff * diff;
		}
		*sum = *sum + exp(-gamma * norma) * sv_coef[i + offset];
		norma = 0;
	}
}

void svm_partitioned_predict(float test_vector1[N_SUP_VECT/2], float test_vector2[N_SUP_VECT/2], float *sum) {
	float diff, sum1, sum2;
#pragma HLS dataflow
	svm_partial_predict(N_FEATURES/2, &sum1, test_vector1, coef1, sv1, 0);
	svm_partial_predict(N_FEATURES/2, &sum2, test_vector2, coef2, sv2, N_FEATURES / 2);
	*sum = sum1 + sum2 - b;
}
