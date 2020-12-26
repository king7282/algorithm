#include <stdio.h>
#include <algorithm>
#include <cstring>

int map[510][510], n, m, dp[510][510];
int mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

int solve(int x, int y) {
	if (x == n && y == m)
		return 1;

	if (dp[x][y] != -1)
		return dp[x][y];

	dp[x][y] = 0;
	for (int i = 0; i < 4; i++) {
		int nx = x + mov[i][0], ny = y + mov[i][1];

		if (!(1 <= nx && nx <= n && 1 <= ny && ny <= m))
			continue;

		if (map[x][y] > map[nx][ny])
			dp[x][y] += solve(nx, ny);
	}

	return dp[x][y];
}

int main(void) {
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &map[i][j]);

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(1, 1));
}