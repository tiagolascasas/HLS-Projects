
#define gamma 8
#define b 0
#define N_FEATURES 1248
#define N_SUP_VECT 18


const float sv_coeff[N_FEATURES] ={ 1 , 2, 2 ,1};
const float sup_vectors[N_SUP_VECT][N_FEATURES]={{1,5,2.2 ,1.1}, {1,2,4 ,1.1},{1,2.1,2.2 ,1.1},{1,8,2.2 ,1.1}};


float coef1[N_FEATURES/2];
float coef2[N_FEATURES/2];
float sv1[N_SUP_VECT][N_FEATURES/2];
float sv2[N_SUP_VECT][N_FEATURES/2];
