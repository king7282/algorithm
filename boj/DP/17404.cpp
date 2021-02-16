#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>

int dp[1010][3][3], n;
int input[1010][3];

int solve(int num, int color, int first) {
	if (num == n + 1)
		return 0;
	
	if (dp[num][color][first] != -1)
		return dp[num][color][first];

	dp[num][color][first] = INT_MAX / 2;
	for (int i = 0; i < 3; i++) {
		if (i == color)
			continue;
		if (num == n && i == first)
			continue;

		dp[num][color][first] = std::min(dp[num][color][first], solve(num + 1, i, first) + input[num][i]);
	}

	return dp[num][color][first];
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d %d", &input[i][0], &input[i][1], &input[i][2]);

	memset(dp, -1, sizeof(dp));
	int result = INT_MAX / 2;
	for (int i = 0; i < 3; i++)
		result = std::min(result, solve(2, i, i) + input[1][i]);

	printf("%d\n", result);
}