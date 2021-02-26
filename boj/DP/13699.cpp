#include <stdio.h>

long long dp[40];

int main(void) {
	int n;
	scanf("%d", &n);

	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			dp[i] += dp[j] * dp[i - j - 1];
		}
	}

	printf("%lld\n", dp[n]);
}