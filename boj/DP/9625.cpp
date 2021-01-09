#include <stdio.h>
#include <algorithm>
#include <cstring>

int dp[100][2];

int solve(int num, int type) {
	if (num == 0) {
		if (type == 0)
			return 1;
		return 0;
	}

	if (dp[num][type] != -1)
		return dp[num][type];

	if (type == 0)
		dp[num][type] = solve(num - 1, 1);

	if (type == 1)
		dp[num][type] = solve(num - 1, 0) + solve(num - 1, 1);

	return dp[num][type];
}

int main(void) {
	int k;
	scanf("%d", &k);

	memset(dp, -1, sizeof(dp));

	printf("%d %d\n", solve(k, 0), solve(k, 1));
}