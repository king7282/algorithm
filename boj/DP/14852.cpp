#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 1000000007

long long dp[1000010][2][1 << 2];

long long solve(int num, int h, int bitmask) {
	if (num == 0) {
		if (bitmask == 0)
			return 1;
		return 0;
	}

	if (h == 2) {
		return solve(num - 1, 0, bitmask);
	}

	if (dp[num][h][bitmask] != -1)
		return dp[num][h][bitmask];

	if ((bitmask & (1 << h)) != 0) {
		dp[num][h][bitmask] = solve(num, h + 1, bitmask ^ (1 << h));
	}
	else {
		dp[num][h][bitmask] = (solve(num, h + 1, bitmask | (1 << h)) + solve(num, h + 1, bitmask)) % MOD;
		if (h == 0 && (bitmask & (1 << (h + 1))) == 0) {
			dp[num][h][bitmask] = (dp[num][h][bitmask] + solve(num, h + 2, bitmask)) % MOD;
		}
	}

	return dp[num][h][bitmask];
}

int main(void) {
	memset(dp, -1, sizeof(dp));
	int n;
	scanf("%d", &n);

	printf("%lld\n", solve(n, 0, 0));
}