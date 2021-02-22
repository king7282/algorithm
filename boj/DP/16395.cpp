#include <stdio.h>

long long dp[110][110];

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);

	dp[0][0] = 1;

	for (int i = 1; i < n; i++) {
		dp[i][0] = 1;

		for (int j = 1; j <= i; j++) {
			dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
		}
	}

	printf("%lld\n", dp[n - 1][k - 1]);
}