#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>

int dp[1010][1010];
int n, input[1010];

int solve(int num, int card) {
	if (card > n)
		return INT_MAX / 2;

	if (num == n + 1) {
		if (card == n)
			return 0;

		return INT_MAX / 2;
	}

	if (dp[num][card] != -1)
		return dp[num][card];

	dp[num][card] = std::min(solve(num + 1, card), solve(num, card + num) + input[num]);

	return dp[num][card];
}
int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", input + i);

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(1, 0));
}