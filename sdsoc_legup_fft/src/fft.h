#define Input_Size  64
#define inverse     0

#define abs(a) ( ((a) < 0) ? -(a) : (a) )

void fft(short old_Re[], short old_Im[], short Real[], short Imag[]);

void fft_sw(short old_Re[], short old_Im[], short Real[], short Imag[]);
