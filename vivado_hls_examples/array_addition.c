#define N 1024

void array_addition(int a[N], int b[N], int c[N]) {
	for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
#pragma HLS PIPELINE II=2
		c[i] = a[i] + b[i];
	}
}
