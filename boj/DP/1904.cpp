#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 15746

int dp[1000010], n;

int solve(int num) {
	if (num == n)
		return 1;
	if (num > n)
		return 0;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = (solve(num + 1) + solve(num + 2)) % MOD;
	return dp[num];
}

int main(void) {
	scanf("%d", &n);

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(0));
}