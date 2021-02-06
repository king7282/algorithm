#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <climits>

int prices[21][21], dp[1 << 16];
int p, n;

int solve(int bitmask) {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if ((bitmask & (1 << i)) != 0)
			cnt++;
	}

	if (cnt >= p)
		return 0;

	if (dp[bitmask] != -1)
		return dp[bitmask];

	dp[bitmask] = INT_MAX / 2;

	for (int i = 0; i < n; i++) {
		if ((bitmask & (1 << i)) != 0)
			continue;
		for (int j = 0; j < n; j++) {
			if ((bitmask & (1 << j)) != 0) {
				dp[bitmask] = std::min(dp[bitmask], solve(bitmask | (1 << i)) + prices[j][i]);
			}
		}
	}

	return dp[bitmask];
}
int main(void) {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			scanf("%d", &prices[i][j]);
	}

	int start = 0;
	getchar();
	for (int i = 0; i < n; i++) {
		char input;
		scanf("%c", &input);
		if (input == 'Y')
			start |= (1 << i);
	}

	scanf("%d", &p);
	if (p != 0 && start == 0) {
		printf("-1\n");
		return 0;
	}

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(start));
}