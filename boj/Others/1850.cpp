#include <stdio.h>

long long gcd(long long a, long long b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main(void) {
	long long a, b;
	scanf("%lld %lld", &a, &b);

	long long result = gcd(a, b);

	for (long long i = 0; i < result; i++) {
		printf("1");
	}
	printf("\n");
}