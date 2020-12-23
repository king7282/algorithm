#include <stdio.h>
#include <algorithm>
#include <cstring>

int dp[1010], n, input[1010];

int solve(int num) {
	if (dp[num] != -1)
		return dp[num];

	dp[num] = 1;
	for (int i = num + 1; i <= n; i++) {
		if (input[num] > input[i])
			dp[num] = std::max(dp[num], solve(i) + 1);
	}
	return dp[num];
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", input + i);

	memset(dp, -1, sizeof(dp));

	int result = 0;
	for (int i = 1; i <= n; i++)
		result = std::max(result, solve(i));
	printf("%d\n", result);
}