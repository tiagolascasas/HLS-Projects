#include <stdio.h>

int main() {
	int a[5] = {56, 74, 21, 90, 68};
	int b[5] = {1, 3, 4, 2, 0};
	int res = array_streaming(a, b);
	if (res == 309)
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}
