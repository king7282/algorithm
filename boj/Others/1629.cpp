#include <stdio.h>

long long power(long long p, long long q, long long mod) {
	if (q == 0)
		return 1;

	long long result = power(p, q / 2, mod);

	result = (result * result) % mod;
	if (q % 2 == 1)
		result = (result * p) % mod;

	return result;
}

int main(void) {
	long long p, q, mod;
	scanf("%lld %lld %lld", &p, &q, &mod);

	printf("%lld\n", power(p, q, mod));
}