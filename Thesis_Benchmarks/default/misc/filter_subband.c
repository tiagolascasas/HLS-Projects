#define Ns 32
#define Ny 64
#define Nz 512
#define Nm 1024

void filter_subband(double z[Nz], double s[Ns], double m[Nm])
{
    double y[Ny];
    int i, j;
    for (i = 0; i < Ny; i++)
    {
        y[i] = 0.0;
        for (j = 0; j < Nz / Ny; j++)
            y[i] += z[i + Ny * j];
    }
    for (i = 0; i < Ns; i++)
    {
        s[i] = 0.0;
        for (j = 0; j < Ny; j++)
            s[i] += m[Ns * i + j] * y[j];
    }
}

int main()
{
    double z[Nz] = {0};
    double s[Ns] = {0};
    double m[Nm] = {0};
    filter_subband(z, s, m);
    return 0;
}