#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 10007

int dp[1010];

int solve(int num) {
	if (num == 0 || num == 1)
		return 1;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = (solve(num - 1) + solve(num - 2) * 2) % MOD;
	return dp[num];
}

int main(void) {
	int n;
	scanf("%d", &n);
	
	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(n));
}