#include <stdio.h>
#include <algorithm>
#include <cstring>

int dp[110][110][2];

int solve(int num, int sum, int prev) {
	if (sum < 0)
		return 0;

	if (num == 0) {
		if (sum == 0)
			return 1;
		return 0;
	}

	if (dp[num][sum][prev] != -1)
		return dp[num][sum][prev];

	dp[num][sum][prev] = solve(num - 1, sum, 0);
	if (prev == 0) {
		dp[num][sum][prev] += solve(num - 1, sum, 1);
	}
	else {
		dp[num][sum][prev] += solve(num - 1, sum - 1, 1);
	}

	return dp[num][sum][prev];
}
int main(void) {
	int test;
	scanf("%d", &test);
	memset(dp, -1, sizeof(dp));

	for (int t = 0; t < test; t++) {
		int n, k;
		scanf("%d %d", &n, &k);

		printf("%d\n", solve(n, k, 0));
	}
}