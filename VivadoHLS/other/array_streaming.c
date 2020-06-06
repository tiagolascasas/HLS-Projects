#define N 4000

int streaming_example(int x[N]) {
	int sum = 0;
	for (int i = 0; i < N; i++)
		sum += x[i];
	return sum;
}

int bram_test(int x[N]) {
	int i;
	for (i = 0; i < N; i++)
		x[i] += 14 + x[i];
	for (i = 0; i < N; i++)
		x[i] -= x[i] + x[i];
	return 0;
}
