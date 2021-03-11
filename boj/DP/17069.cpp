#include <stdio.h>
#include <algorithm>
#include <cstring>

int n, map[35][35];
long long dp[35][35][3];
int mov[3][2] = { {1, 0}, {0, 1}, {1, 1} };

long long solve(int x, int y, int type) {
	if (x == n && y == n)
		return 1;

	if (dp[x][y][type] != -1)
		return dp[x][y][type];

	dp[x][y][type] = 0;
	for (int i = 0; i < 3; i++) {
		if (type != 2 && (i != 2 && type != i))
			continue;

		int nx = x + mov[i][0], ny = y + mov[i][1];

		if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n))
			continue;

		if (map[nx][y] != 0 || map[x][ny] != 0 || map[nx][ny] != 0)
			continue;

		dp[x][y][type] += solve(nx, ny, i);
	}

	return dp[x][y][type];
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &map[i][j]);

	
	memset(dp, -1, sizeof(dp));
	printf("%lld\n", solve(1, 2, 1));
}