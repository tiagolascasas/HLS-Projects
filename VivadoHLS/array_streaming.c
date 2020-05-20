int array_streaming(int a[5], int b[5]) {
#pragma HLS STREAM variable=a dim=1
#pragma HLS STREAM variable=b dim=1
	int sum = 0;
	for (int i = 0; i < 5; i++) {
		int index = b[i] + 1;
		sum += a[index];
	}
	return sum;
}

