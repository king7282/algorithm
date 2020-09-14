#include <stdio.h>

int main(void) {
	int test;
	scanf("%d", &test);
	long long result = 0, prev;
	scanf("%lld", &prev);
	for (int t = 1; t < test; t++) {
		long long a;
		scanf("%lld", &a);
		result += (a - prev) * (a - prev);
		prev = a;
	}

	printf("%lld\n", result);
}