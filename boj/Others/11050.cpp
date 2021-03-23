#include <stdio.h>

long long fac[11];

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);
	fac[0] = 1;

	for (long long i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i;

	printf("%lld\n", fac[n] / (fac[n - k] * fac[k]));
}