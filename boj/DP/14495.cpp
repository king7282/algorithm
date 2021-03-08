#include <stdio.h>
#include <cstring>
#include <algorithm>

long long dp[120];

long long solve(int num) {
	if (num <= 3)
		return 1;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = solve(num - 1) + solve(num - 3);

	return dp[num];
}

int main(void) {

	int n;
	scanf("%d", &n);

	memset(dp, -1, sizeof(dp));
	printf("%lld\n", solve(n));
}