#include <stdio.h>

long long gcd(long long a, long long b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main(void) {
	long long a, b;

	scanf("%lld %lld", &a, &b);

	printf("%lld\n", a * b / gcd(a, b));
}