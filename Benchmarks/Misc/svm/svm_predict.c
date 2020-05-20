#define GAMMA 8
#define B 0
#define N_FEATURES 1248
#define N_SUP_VECT 18

int svm_predict(float test_vector[N_SUP_VECT], float sup_vectors[N_SUP_VECT][N_FEATURES], float sv_coeff[N_FEATURES])
{
    float diff;
    float norma;
    int sum = 0;
    for (int i = 0; i < N_FEATURES; i++)
    {
        for (int j = 0; j < N_SUP_VECT; j++)
        {
            diff = test_vector[j] - sup_vectors[j][i];
            diff = diff * diff;
            norma = norma + diff;
        }
        sum = sum + (exp(-GAMMA * norma) * sv_coeff[i]);
        norma = 0;
    }
    sum = sum - B;
    return sum;
}

int main()
{
    float test_vector[N_SUP_VECT] = {0};
    float sv_coeff[N_FEATURES] = {0};
    float sup_vectors[N_SUP_VECT][N_FEATURES] = {0};
    for (int i = 0; i < N_SUP_VECT; i++)
    {
        test_vector[i] = i;
        for (int j = 0; j < N_FEATURES; j++)
        {
            sv_coeff[j] = i / 2;
            sup_vectors[i][j] = i + j;
        }
    }

    int res = svm_predict(test_vector, sup_vectors, sv_coeff);
    return 0;
}