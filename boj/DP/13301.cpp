#include <stdio.h>
#include <algorithm>
#include <cstring>

long long dp[110];

long long solve(int num) {
	if (num <= 2)
		return 1;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = solve(num - 1) + solve(num - 2);
	return dp[num];
}

int main(void) {
	int n;
	scanf("%d", &n);

	if (n == 1) {
		printf("4\n");
		return 0;
	}
	memset(dp, -1, sizeof(dp));

	printf("%lld\n", solve(n) * 2 + (solve(n) + solve(n - 1)) * 2);
}
