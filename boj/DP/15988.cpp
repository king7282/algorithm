#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 1000000009

int dp[1000010];

int solve(int num) {
	if (num == 0)
		return 1;
	if (num < 0)
		return 0;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = (solve(num - 1) + solve(num - 2)) % MOD;
	dp[num] = (dp[num] + solve(num - 3)) % MOD;

	return dp[num];
}

int main(void) {
	int test;
	scanf("%d", &test);
	memset(dp, -1, sizeof(dp));

	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
		printf("%d\n", solve(n));
	}
}