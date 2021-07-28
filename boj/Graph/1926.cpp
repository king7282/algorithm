#include <stdio.h>
#include <algorithm>

int map[510][510], n, m;
int width, mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
bool visited[510][510];

void dfs(int x, int y) {
	width++;
	visited[x][y] = true;

	for (int i = 0; i < 4; i++) {
		int nx = x + mov[i][0], ny = y + mov[i][1];

		if (!(1 <= nx && nx <= n && 1 <= ny && ny <= m))
			continue;

		if (map[nx][ny] == 0 || visited[nx][ny] == true)
			continue;

		dfs(nx, ny);
	}
}

int main(void) {
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &map[i][j]);

	int cnt = 0, result = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (visited[i][j] == false && map[i][j] == 1) {
				cnt++;
				width = 0;
				dfs(i, j);

				result = std::max(result, width);
			}
		}
	}

	printf("%d\n%d\n", cnt, result);
}