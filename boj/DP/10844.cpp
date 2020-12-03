#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 1000000000

int n, dp[110][10];

int func(int num, int prev) {
	if (num == n + 1)
		return 1;

	if (dp[num][prev] != -1)
		return dp[num][prev];

	dp[num][prev] = 0;
	if (prev != 0)
		dp[num][prev] = (dp[num][prev] + func(num + 1, prev - 1)) % MOD;

	if (prev != 9)
		dp[num][prev] = (dp[num][prev] + func(num + 1, prev + 1)) % MOD;

	return dp[num][prev];
}

int main(void) {
	scanf("%d", &n);

	memset(dp, -1, sizeof(dp));
	int result = 0;
	for (int i = 1; i <= 9; i++) {
		result = (result + func(2, i)) % MOD;
	}

	printf("%d\n", result);
}