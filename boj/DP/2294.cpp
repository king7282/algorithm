#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <climits>

int input[110], dp[110][10010];

int solve(int num, int value) {
	if (value < 0)
		return INT_MAX / 2;

	if (value == 0)
		return 0;
	
	if (num == 0)
		return INT_MAX / 2;

	if (dp[num][value] != -1)
		return dp[num][value];

	dp[num][value] = std::min(solve(num - 1, value), solve(num, value - input[num]) + 1);
	dp[num][value] = std::min(dp[num][value], INT_MAX / 2);
	
	return dp[num][value];
}

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", input + i);

	memset(dp, -1, sizeof(dp));

	if (solve(n, k) == INT_MAX / 2)
		printf("-1");
	else
		printf("%d\n", solve(n, k));
}