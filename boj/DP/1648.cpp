#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 9901

int dp[15][15][1 << 14];
int n, m;

int solve(int x, int y, int bitmask) {
	if (y == m)
		return solve(x + 1, 0, bitmask);

	if (x == n && y == 0)
		return 1;

	if (dp[x][y][bitmask] != -1)
		return dp[x][y][bitmask];

	dp[x][y][bitmask] = 0;

	if ((bitmask & (1 << y)) != 0) {
		dp[x][y][bitmask] = solve(x, y + 1, bitmask ^ (1 << y));
	}
	else {
		if(x != n - 1)
			dp[x][y][bitmask] = solve(x, y + 1, bitmask | (1 << y));

		if (y != m - 1 && (bitmask & (1 << (y + 1))) == 0) {
			dp[x][y][bitmask] = (dp[x][y][bitmask] + solve(x, y + 2, bitmask)) % MOD;
		}
	}

	return dp[x][y][bitmask];
}

int main(void) {
	scanf("%d %d", &n, &m);

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(0, 0, 0));
}