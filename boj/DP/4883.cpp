#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>

int mov[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
int map[100010][4], n, dp[100010][4];

int solve(int x, int y) {
	if (!(1 <= x && x <= n && 1 <= y && y <= 3))
		return INT_MAX / 2;

	if (x == n && y == 2)
		return 0;

	if (dp[x][y] != -1)
		return dp[x][y];

	dp[x][y] = INT_MAX / 2;
	for (int i = 0; i < 4; i++) {
		int nx = x + mov[i][0], ny = y + mov[i][1];

		dp[x][y] = std::min(dp[x][y], solve(nx, ny) + map[nx][ny]);
	}

	return dp[x][y];
}
int main(void) {
	int test = 0;
	while (1) {
		scanf("%d", &n);

		if (n == 0)
			break;
		test++;

		for (int i = 1; i <= n; i++) {
			scanf("%d %d %d", &map[i][1], &map[i][2], &map[i][3]);
		}

		memset(dp, -1, sizeof(dp));
		printf("%d. %d\n", test, solve(1, 2) + map[1][2]);
	}
}