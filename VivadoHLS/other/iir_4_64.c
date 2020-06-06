/* 4-cascaded IIR biquad filter processing 64 points */
/* Modified to use arrays - SMP */

#define NPOINTS 64
#define NSECTIONS 4

float input[NPOINTS];
float output[NPOINTS];
float coefficient[NSECTIONS][NSECTIONS][NSECTIONS];
float internal_state[8][NSECTIONS][2];

void iir(float input[NPOINTS], float output[NPOINTS],
         float coefficient[NSECTIONS][NSECTIONS][NSECTIONS],
         float internal_state[8][NSECTIONS][2])
{
#pragma HLS STREAM variable=input dim=1
    int i, imod8, imodNSECTIONS;
    int j;

    float state_2, state_1;
    float coef_a21, coef_a11, coef_b21, coef_b11;
    float sum;

    for (i = 0; i < NPOINTS; ++i)
    {
        sum = input[i];

        for (j = 0; j < NSECTIONS; ++j)
        {
            state_2 = internal_state[i][j][0];
            state_1 = internal_state[i][j][1];

            sum -= internal_state[i][j][0] * coefficient[i][j][0] +
                   internal_state[i][j][1] * coefficient[i][j][1];

            internal_state[i][j][0] = internal_state[i][j][1];
            internal_state[i][j][1] = sum;

            sum += state_2 * coefficient[i][j][2] + state_1 * coefficient[i][j][3];
        }
        output[i] = sum;
    }
}
