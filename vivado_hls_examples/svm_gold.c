#include<stdio.h>
#include<math.h>
#include"svm.h"
/*
void svm_predict(float test_vector[D_sv], float *sum) {
	float diff;
	float norma;
	for (int i = 0; i < N_sv; i++) {
		for (int j = 0; j < D_sv; j++) {
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
void svm_partial_predict(int width, float* sum, float test_vector[D_sv],
		float sv_coef[N_sv / 2], float sup_vectors[D_sv][N_sv / 2], int offset) {
	int i, j;
	float diff, norma = 0;
	*sum = 0;

	for (i = 0; i < width; i++) {
		for (j = 0; j < D_sv; j++) {
			diff = test_vector[j] - sup_vectors[j][i + offset];
			norma = norma + diff * diff;
		}
		*sum = *sum + exp(-gamma * norma) * sv_coef[i + offset];
		norma = 0;
	}
}

void svm_partitioned_predict(float test_vector[D_sv], float *sum) {
	float diff, sum1, sum2;
	svm_partial_predict(N_sv/2, &sum1, test_vector, coef1, sv1, 0);
	svm_partial_predict(N_sv/2, &sum2, test_vector, coef2, sv2, N_sv / 2);
	*sum = sum1 + sum2 - b;
}
