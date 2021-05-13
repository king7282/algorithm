#include <stdio.h>
#define MOD 45678

int main(void) {
	int n;
	scanf("%d", &n);

	long long result = 5, prev = 3;

	for (int i = 2; i <= n; i++) {
		result = (result + i * 5 - prev) % MOD;
		prev += 2;
	}

	printf("%lld\n", result);
}