#include <stdlib.h>
#include <math.h>
int svm_predict(float test_vector[18], float sup_vectors[18][1248], float sv_coeff[1248]) {
   #pragma HLS stream variable=sv_coeff
   #pragma HLS stream variable=test_vector
   float diff;
   float norma;
   int sum = 0;
   for(int i = 0; i < 1248; i++) {
      #pragma HLS  pipeline
      for(int j = 0; j < 18; j++) {
         #pragma HLS unroll factor=18
         #pragma HLS  pipeline
         diff = test_vector[j] - sup_vectors[j][i];
         diff = diff * diff;
         norma = norma + diff;
      }
      sum = sum + (exp(-8 * norma) * sv_coeff[i]);
      norma = 0;
   }
   sum = sum - 0;
   
   return sum;
}

int main() {
   float test_vector[18] = {0};
   float sv_coeff[1248] = {0};
   float sup_vectors[18][1248] = {0};
   for(int i = 0; i < 18; i++) {
      test_vector[i] = i;
      for(int j = 0; j < 1248; j++) {
         sv_coeff[j] = i / 2;
         sup_vectors[i][j] = i + j;
      }
   }
   int res = svm_predict(test_vector, sup_vectors, sv_coeff);
   
   return 0;
}
