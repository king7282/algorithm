#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 1000000009

int dp[100010][4];

int solve(int num, int prev) {
	if (num == 0)
		return 1;

	if (num < 0)
		return 0;

	if (dp[num][prev] != -1)
		return dp[num][prev];

	dp[num][prev] = 0;
	for (int i = 1; i <= 3; i++) {
		if (prev == i)
			continue;
		
		dp[num][prev] = (dp[num][prev] + solve(num - i, i)) % MOD;
	}

	return dp[num][prev];
}

int main(void) {
	int test;
	scanf("%d", &test);
	memset(dp, -1, sizeof(dp));

	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);

		printf("%d\n", solve(n, 0));
	}
}