/* 1024-point complex FFT (radix-2, in-place, decimation-in-time) */
/* Modified to use arrays - SMP */

#include "traps.h"

#define NPOINTS 1024
#define NSTAGES 10

float data_real[NPOINTS];
float data_imag[NPOINTS];
float coef_real[NPOINTS];
float coef_imag[NPOINTS];

void fft(float data_real[], float data_imag[], float coef_real[],
				 float coef_imag[]);

int main()
{
	input_dsp(data_real, NPOINTS, 0);

	for (int i = 0; i < NPOINTS; i++)
	{ /* was 256 - not ok? */
		data_imag[i] = 1;
		coef_real[i] = 1;
		coef_imag[i] = 1;
	}
	fft(data_real, data_imag, coef_real, coef_imag);

	output_dsp(data_real, NPOINTS, 0);
	output_dsp(data_imag, NPOINTS, 0);
	output_dsp(coef_real, NPOINTS, 0);
	output_dsp(coef_imag, NPOINTS, 0);
}

void fft(float data_real[NPOINTS], float data_imag[NPOINTS], float coef_real[NPOINTS],
				 float coef_imag[NPOINTS])
/* data_real:         real data points */
/* data_imag:         imaginary data points */
/* coef_real:         real coefficient points */
/* coef_imag:         imaginary coefficient points */
{
	float temp_real;
	float temp_imag;
	float Wr;
	float Wi;
	int groupsPerStage = 1;
	int buttersPerGroup = NPOINTS / 2;

	for (int i = 0; i < NSTAGES; ++i)
	{
		for (int j = 0; j < groupsPerStage; ++j)
		{
			Wr = coef_real[(1 << i) - 1 + j];
			Wi = coef_imag[(1 << i) - 1 + j];
			for (int k = 0; k < buttersPerGroup; ++k)
			{
				temp_real = Wr * data_real[2 * j * buttersPerGroup + buttersPerGroup + k] - Wi * data_imag[2 * j * buttersPerGroup + buttersPerGroup + k];
				temp_imag = Wi * data_real[2 * j * buttersPerGroup + buttersPerGroup + k] + Wr * data_imag[2 * j * buttersPerGroup + buttersPerGroup + k];
				data_real[2 * j * buttersPerGroup + buttersPerGroup + k] = data_real[2 * j * buttersPerGroup + k] - temp_real;
				data_real[2 * j * buttersPerGroup + k] += temp_real;
				data_imag[2 * j * buttersPerGroup + buttersPerGroup + k] = data_imag[2 * j * buttersPerGroup + k] - temp_imag;
				data_imag[2 * j * buttersPerGroup + k] += temp_imag;
			}
		}
		groupsPerStage <<= 1;
		buttersPerGroup >>= 1;
	}
}
