#include <stdio.h>

int map[110][110], mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
int tmp[110][110];
int n, m;

void dfs(int x, int y) {
	map[x][y] = 2;

	for (int i = 0; i < 4; i++) {
		int nx = x + mov[i][0], ny = y + mov[i][1];

		if (!(1 <= nx && nx <= n && 1 <= ny && ny <= m))
			continue;

		if (map[nx][ny] == 0)
			dfs(nx, ny);
	}
}

int main(void) {
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &map[i][j]);

	int result = 0;
	while (1) {
		int cnt = 0;

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				tmp[i][j] = map[i][j];

		dfs(1, 1);

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (map[i][j] != 1)
					continue;

				cnt++;
				int t = 0;
				for (int k = 0; k < 4; k++) {
					int nx = i + mov[k][0], ny = j + mov[k][1];

					if (!(1 <= nx && nx <= n && 1 <= ny && ny <= m))
						continue;

					if (map[nx][ny] == 2)
						t++;
				}

				if (t >= 2) {
					tmp[i][j] = 0;
				}
			}
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				map[i][j] = tmp[i][j];
			}
		}

		if (cnt == 0)
			break;

		result++;
	}

	printf("%d\n", result);
}