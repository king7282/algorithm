#include <stdio.h>

int main(void) {
	long long A, B, C;

	scanf("%lld %lld %lld", &A, &B, &C);

	if (C - B <= 0) {
		printf("-1\n");
	}
	else {
		long long result = A / (C - B) + 1;
		printf("%lld\n", result);
	}
}