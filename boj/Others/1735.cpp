#include <stdio.h>

long long gcd(long long a, long long b) {
	if (b == 0)
		return a;

	return gcd(b, a % b);
}

int main(void) {
	long long a1, a2, b1, b2;
	scanf("%lld %lld %lld %lld", &a1, &a2, &b1, &b2);

	long long lower = a2 * b2, upper = a1 * b2 + b1 * a2;

	printf("%lld %lld\n", upper / gcd(upper, lower), lower / gcd(upper, lower));
}