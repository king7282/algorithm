#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#include <climits>

char map[1010][1010];
int fire[1010][1010], visited[1010][1010];
int mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int n, m;
		scanf("%d %d", &m, &n);

		memset(visited, -1, sizeof(visited));
		memset(fire, -1, sizeof(fire));
		memset(map, 0, sizeof(map));

		std::queue<std::pair<int, int>> f_qu, qu;

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf(" %c", &map[i][j]);

				if (map[i][j] == '@') {
					qu.push({ i, j });
					visited[i][j] = 0;
				}

				if (map[i][j] == '*') {
					f_qu.push({ i, j });
					fire[i][j] = 0;
				}
			}
		}
		while (!f_qu.empty()) {
			std::pair<int, int> front = f_qu.front();
			f_qu.pop();

			for (int i = 0; i < 4; i++) {
				int nx = front.first + mov[i][0], ny = front.second + mov[i][1];

				if (!(1 <= nx && nx <= n && 1 <= ny && ny <= m))
					continue;

				if (map[nx][ny] == '#' || fire[nx][ny] != -1)
					continue;

				fire[nx][ny] = fire[front.first][front.second] + 1;
				f_qu.push({ nx, ny });
			}
		}

		while (!qu.empty()) {
			std::pair<int, int> front = qu.front();
			qu.pop();

			for (int i = 0; i < 4; i++) {
				int nx = front.first + mov[i][0], ny = front.second + mov[i][1];

				if (!(0 <= nx && nx <= n + 1 && 0 <= ny && ny <= m + 1))
					continue;

				if (map[nx][ny] == '#' || visited[nx][ny] != -1)
					continue;

				if (fire[nx][ny] != -1 && fire[nx][ny] <= visited[front.first][front.second] + 1)
					continue;

				visited[nx][ny] = visited[front.first][front.second] + 1;
				qu.push({ nx, ny });
			}
		}

		int result = INT_MAX / 2;

		for (int i = 0; i <= n; i++) {
			if (visited[i][0] != -1)
				result = std::min(result, visited[i][0]);
			if (visited[i][m + 1] != -1)
				result = std::min(result, visited[i][m + 1]);
		}

		for (int i = 0; i <= m; i++) {
			if (visited[0][i] != -1)
				result = std::min(result, visited[0][i]);
			if (visited[n + 1][i] != -1)
				result = std::min(result, visited[n + 1][i]);
		}

		if (result == INT_MAX / 2)
			printf("IMPOSSIBLE\n");
		else
			printf("%d\n", result);
	}
}