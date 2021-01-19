#include <stdio.h>
#include <algorithm>
#include <cstring>

std::pair<int, int> problems[110];
int dp[110][110];
int n, l, k;

int solve(int num, int left) {
	if (left == 0)
		return 0;

	if (num == n + 1)
		return 0;

	if (dp[num][left] != -1)
		return dp[num][left];

	dp[num][left] = solve(num + 1, left);
	if (problems[num].first <= l)
		dp[num][left] = std::max(dp[num][left], solve(num + 1, left - 1) + 100);

	if (problems[num].second <= l)
		dp[num][left] = std::max(dp[num][left], solve(num + 1, left - 1) + 140);

	return dp[num][left];
}


int main(void) {
	scanf("%d %d %d", &n, &l, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &problems[i].first, &problems[i].second);

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(1, k));
}