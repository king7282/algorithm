#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 10007

int dp[1010][10], n;

int solve(int num, int prev) {
	if (num == n + 1)
		return 1;

	if (dp[num][prev] != -1)
		return dp[num][prev];

	dp[num][prev] = 0;
	for (int i = prev; i <= 9; i++) {
		dp[num][prev] = (dp[num][prev] + solve(num + 1, i)) % MOD;
	}

	return dp[num][prev];
}

int main(void) {
	scanf("%d", &n);
	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(1, 0));
}
