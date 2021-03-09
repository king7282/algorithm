#include <stdio.h>
#include <algorithm>
#include <cstring>

int dp[1010][4][1 << 4];

int solve(int num, int h, int bitmask) {
	if (num == 0) {
		if (bitmask == 0)
			return 1;
		return 0;
	}

	if (h == 4) {
		return solve(num - 1, 0, bitmask);
	}

	if (dp[num][h][bitmask] != -1)
		return dp[num][h][bitmask];

	if ((bitmask & (1 << h)) != 0) {
		dp[num][h][bitmask] = solve(num, h + 1, bitmask ^ (1 << h));
	}
	else {
		dp[num][h][bitmask] = solve(num, h + 1, bitmask | (1 << h));
		if (h != 3 && (bitmask & (1 << (h + 1))) == 0) {
			dp[num][h][bitmask] += solve(num, h + 2, bitmask);
		}
	}

	return dp[num][h][bitmask];
}

int main(void) {
	int test;
	scanf("%d", &test);
	
	memset(dp, -1, sizeof(dp));

	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);

		printf("%d\n", solve(n, 0, 0));
	}
}