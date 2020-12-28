#include <stdio.h>
#include <algorithm>
#include <cstring>

long long dp[110][110];
int map[110][110], n;
int mov[2][2] = { {1, 0}, {0, 1} };

long long solve(int x, int y) {
	if (x == n && y == n)
		return 1;

	if (!(1 <= x && x <= n && 1 <= y && y <= n))
		return 0;

	if (dp[x][y] != -1)
		return dp[x][y];
	
	dp[x][y] = 0;
	if (map[x][y] != 0)
		dp[x][y] = solve(x + map[x][y], y) + solve(x, y + map[x][y]);
	
	return dp[x][y];
}

int main(void) {
	scanf("%d", &n);
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &map[i][j]);

	memset(dp, -1, sizeof(dp));
	printf("%lld\n", solve(1, 1));
}