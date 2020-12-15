#include <stdio.h>
#include <algorithm>
#include <cstring>

int map[1010][1010], dp[1010][1010];

int func(int x, int y) {
	if (x < 1 || y < 1)
		return 0;

	if (dp[x][y] != -1)
		return dp[x][y];

	dp[x][y] = std::max(func(x - 1, y), func(x, y - 1)) + map[x][y];
	
	return dp[x][y];
}

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	memset(dp, -1, sizeof(dp));
	printf("%d\n", func(n, m));
}