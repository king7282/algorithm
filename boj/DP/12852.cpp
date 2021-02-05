#include <stdio.h>
#include <algorithm>
#include <cstring>

int dp[1000010], prev[1000010];

int solve(int num) {
	if (num == 1)
		return 0;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = solve(num - 1) + 1;
	prev[num] = num - 1;
	if (num % 3 == 0 && dp[num] > solve(num / 3) + 1) {
		dp[num] = solve(num / 3) + 1;
		prev[num] = num / 3;
	}

	if (num % 2 == 0 && dp[num] > solve(num / 2) + 1) {
		dp[num] = solve(num / 2) + 1;
		prev[num] = num / 2;
	}

	return dp[num];
}

void trace(int num) {
	printf("%d ", num);
	if (num == 1)
		return;

	trace(prev[num]);
}
int main(void) {
	int n;
	scanf("%d", &n);

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(n));
	trace(n);
}