#include "fsubba_viv.h"

void filter_subband_double_golden(double z[Nz], double s[Ns], double m[Nm])
{
#pragma HLS array_partition variable=s cyclic factor=2
#pragma HLS array_partition variable=m cyclic factor=2
#pragma HLS array_partition variable=z cyclic factor=2

   double y[Ny];

   int i,j;

   for (i=0;i<Ny;i++)
   {
#pragma HLS pipeline
#pragma unroll factor=4
     y[i] = 0.0;
     for (j=0; j<(int)Nz/Ny;j++)
          y[i] += z[i+Ny*j];
   }

   for (i=0;i<Ns;i++)
   {
#pragma HLS pipeline
#pragma unroll factor=4
       s[i]=0.0;
       for (j=0; j<Ny;j++)
           s[i] += m[Ns*i+j] * y[j];
   }
}
