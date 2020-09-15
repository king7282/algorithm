#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <time.h>
#define MOD 1000000007

long long dp[310][310][2]; // 0 : don't need, 1 : must make height

long long func(int h, int w, int flag) {
	if (flag == 1 && h > w)
		return 0;

	if (h == 1)
		return 1;

	if (h == 0) {
		if (w == 0)
			return 1;
		return 0;
	}

	if (flag == 0 && w == 0) {
		return 1;
	}

	if (dp[h][w][flag] != -1)
		return dp[h][w][flag];

	dp[h][w][flag] = func(h - 1, w - 1, flag);
	for (int i = 1; i < w; i++) {
		if (flag == 1) {
			dp[h][w][flag] = (dp[h][w][flag] + func(h - 1, i - 1, 1) * func(h, w - i, 0) % MOD) % MOD;
			dp[h][w][flag] = (dp[h][w][flag] + func(h - 1, i - 1, 0) * func(h, w - i, 1) % MOD) % MOD;
			dp[h][w][flag] = (dp[h][w][flag] - func(h - 1, i - 1, 1) * func(h, w - i, 1) % MOD + MOD) % MOD;
		}
		else {
			dp[h][w][flag] = (dp[h][w][flag] + func(h - 1, i - 1, 0) * func(h, w - i, 0)) % MOD;
		}
	}
	return dp[h][w][flag];
}
int main(void) {
	int n, w;
	scanf("%d %d", &n, &w);
	if (n > w) {
		printf("0\n");
	}
	else {
		memset(dp, -1, sizeof(dp));
		printf("%lld\n", func(n - 1, w - 1, 1));
	}
}