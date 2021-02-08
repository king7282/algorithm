#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>

int dp[100010];

int solve(int num) {
	if (num == 0)
		return 0;
	if (num < 0)
		return INT_MAX / 2;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = std::min(INT_MAX / 2, std::min(solve(num - 2), solve(num - 5)) + 1);
	return dp[num];
}

int main(void) {
	int n;
	scanf("%d", &n);

	memset(dp, -1, sizeof(dp));
	
	if (solve(n) >= INT_MAX / 2)
		printf("-1\n");
	else
		printf("%d\n", solve(n));
}