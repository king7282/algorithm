#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>

int dp[52][52], n, m, mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
bool running[52][52];
char map[52][52];

int solve(int x, int y) {
	if (!(1 <= x && x <= n && 1 <= y && y <= m))
		return 0;
	if (map[x][y] == 'H')
		return 0;

	if (running[x][y] == true)
		return INT_MAX / 2;

	if (dp[x][y] != -1)
		return dp[x][y];

	dp[x][y] = 0;
	running[x][y] = true;
	for (int i = 0; i < 4; i++) {
		int nx = x + mov[i][0] * map[x][y], ny = y + mov[i][1] * map[x][y];

		dp[x][y] = std::max(dp[x][y], solve(nx, ny) + 1);
	}

	dp[x][y] = std::min(dp[x][y], INT_MAX / 2);
	running[x][y] = false;
	return dp[x][y];
}

int main(void) {
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		getchar();
		for (int j = 1; j <= m; j++) {
			scanf("%c", &map[i][j]);
			if (map[i][j] != 'H')
				map[i][j] -= '0';
		}
	}

	memset(dp, -1, sizeof(dp));
	int result = solve(1, 1);
	if (result >= INT_MAX / 2)
		printf("-1\n");
	else
		printf("%d\n", result);
}