#include <stdio.h>
#include <algorithm>
#include <cstring>

long long dp[110];

long long solve(int num) {
	if (num == 0)
		return 0;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = solve(num - 1) + 1;
	
	for (int i = num - 3; i >= 1; i--) {
		dp[num] = std::max(dp[num], solve(i) * (long long)(num - i - 1));
	}

	return dp[num];
}

int main(void) {
	int n;
	scanf("%d", &n);

	memset(dp, -1, sizeof(dp));
	printf("%lld\n", solve(n));
}