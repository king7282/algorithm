#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 1000000000

int n, k, dp[210][210];

int solve(int num, int left) {
	if (num == 0 && left == 0)
		return 1;

	if (num < 0)
		return 0;

	if (left == 0)
		return 0;

	if (dp[num][left] != -1)
		return dp[num][left];

	dp[num][left] = 0;
	for (int i = 0; i <= n; i++)
		dp[num][left] = (dp[num][left] + solve(num - i, left - 1)) % MOD;
	return dp[num][left];
}

int main(void) {
	scanf("%d %d", &n, &k);

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(n, k));
}