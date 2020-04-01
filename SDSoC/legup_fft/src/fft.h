#define Input_Size  64
#define inverse     0

#define abs(a) ( ((a) < 0) ? -(a) : (a) )

void fft(short old_Re[Input_Size], short old_Im[Input_Size], short Real[Input_Size], short Imag[Input_Size]);

void fft_sw(short old_Re[Input_Size], short old_Im[Input_Size], short Real[Input_Size], short Imag[Input_Size]);
