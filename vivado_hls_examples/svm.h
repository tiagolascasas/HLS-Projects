
#define gamma 8
#define b 0
#define N_sv 1248
#define D_sv 18


float sv_coeff[N_sv] ={ 1 , 2, 2 ,1};
float sup_vectors[D_sv][N_sv]={{1,5,2.2 ,1.1}, {1,2,4 ,1.1},{1,2.1,2.2 ,1.1},{1,8,2.2 ,1.1}};


float coef1[N_sv/2];
float coef2[N_sv/2];
float sv1[D_sv][N_sv/2];
float sv2[D_sv][N_sv/2];
