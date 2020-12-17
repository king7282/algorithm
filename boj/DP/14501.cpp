#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>

int dp[20], n;
std::pair<int, int> input[20];

int solve(int num) {
	if (num > n + 1)
		return INT_MIN / 2;

	if (num == n + 1)
		return 0;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = std::max(solve(num + 1), solve(num + input[num].first) + input[num].second);
	return dp[num];
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &input[i].first, &input[i].second);

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(1));
}