#include <stdio.h>
#include <cstring>
#include <algorithm>
#define MOD 1000000000

int dp[1000010][22], eexp[22];

int solve(int num, int p) {
	if (num == 0)
		return 1;

	if (num < 0)
		return 0;
	if (p < 0)
		return 0;

	if (dp[num][p] != -1)
		return dp[num][p];

	dp[num][p] = 0;

	dp[num][p] = (dp[num][p] + solve(num - eexp[p], p)) % MOD;
	dp[num][p] = (dp[num][p] + solve(num, p - 1)) % MOD;

	return dp[num][p];
}

int main(void) {
	int n;
	scanf("%d", &n);
	
	eexp[0] = 1;

	for (int i = 1; i <= 20; i++)
		eexp[i] = eexp[i - 1] * 2;

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(n, 20));
}