#include <stdio.h>
#include <algorithm>
#include <cstring>

int mov[3][2] = { {1, 0}, {0, 1}, {1, 1} }, n;
int dp[21][21][3], map[21][21];

int solve(int x, int y, int d) {
	if (x == n && y == n)
		return 1;

	if (dp[x][y][d] != -1)
		return dp[x][y][d];

	dp[x][y][d] = 0;
	for (int i = 0; i < 3; i++) {
		if (d == 2 || i == 2 || i == d) {

			int nx = x + mov[i][0], ny = y + mov[i][1];

			if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n))
				continue;

			if (map[nx][ny] == 1)
				continue;

			if (i == 2 && (map[x][ny] == 1 || map[nx][y] == 1)) {
				continue;
			}

			dp[x][y][d] += solve(nx, ny, i);
		}
	}

	return dp[x][y][d];
}
int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &map[i][j]);

	memset(dp, -1, sizeof(dp));

	printf("%d\n", solve(1, 2, 1));
}