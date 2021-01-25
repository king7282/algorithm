#include <stdio.h>
#include <algorithm>
#include <cstring>

long long dp[31][31];

long long solve(int one, int half) {
	if (one == 0 && half == 0)
		return 1;

	if (dp[one][half] != -1)
		return dp[one][half];

	dp[one][half] = 0;
	if (one != 0) {
		dp[one][half] += solve(one - 1, half + 1);
	}

	if (half != 0) {
		dp[one][half] += solve(one, half - 1);
	}

	return dp[one][half];
}

int main(void) {
	memset(dp, -1, sizeof(dp));

	while (1) {
		int n;
		scanf("%d", &n);
		if (n == 0)
			break;

		printf("%lld\n", solve(n, 0));
	}
}