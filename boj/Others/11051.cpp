#include <stdio.h>
#include <algorithm>
#define MOD 10007

long long eexp(long long p, long long e) {
	if (e == 0)
		return 1;

	long long tmp = eexp(p, e / 2);
	tmp = (tmp * tmp) % MOD;

	if (e % 2 == 1)
		tmp = (tmp * p) % MOD;

	return tmp;
}

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);

	long long upper = 1, lower = 1;

	for (long long i = n; i > n - k; i--) {
		upper = (upper * i) % MOD;
	}

	for (long long i = 1; i <= k; i++) {
		lower = (lower * i) % MOD;
	}


	printf("%lld\n", (upper * eexp(lower, MOD - 2)) % MOD);
}