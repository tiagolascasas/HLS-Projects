#include<stdio.h>
#include<math.h>
#include"svm.h"


void svm_predict(float test_vector[D_sv], float *sum){
	float diff;
	float norma;
	for(int i=0; i< N_sv;i++){
	#pragma HLS pipeline
		for(int j=0; j<D_sv;j++){
		diff=test_vector[j] - sup_vectors[j][i];
		diff=diff*diff;
		norma=norma + diff;
		}
    *sum = *sum + (exp(-gamma*norma)*sv_coeff[i]);
	norma=0;
	}
    *sum= *sum-b;
} 
