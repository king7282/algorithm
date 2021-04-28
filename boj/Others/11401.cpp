#include <stdio.h>
#include <algorithm>
#define MOD 1000000007

long long power(long long p, long long t) {
	if (t == 0)
		return 1;

	long long tmp = power(p, t / 2);

	tmp = (tmp * tmp) % MOD;
	if (t % 2 == 1)
		tmp = (tmp * p) % MOD;

	return tmp;
}

int main(void) {
	long long n, p;
	scanf("%lld %lld", &n, &p);

	long long upper = 1, lower = 1;

	for (long long i = 1; i <= n; i++)
		upper = (upper * i) % MOD;

	for (long long i = 1; i <= p; i++)
		lower = (lower * i) % MOD;
	for (long long i = 1; i <= (n - p); i++)
		lower = (lower * i) % MOD;

	printf("%lld\n", upper * power(lower, MOD - 2) % MOD);
}