#include <stdio.h>
#include <algorithm>
#include <queue>
#include <cstring>

int visited[310][310];
int mov[8][2] = { {1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {1, -2}, {2, -1}, {-1, -2}, {-2, -1} };
int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);

		int sx, sy, ex, ey;
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);

		std::queue<std::pair<int, int>> qu;
		qu.push({ sx, sy });
		memset(visited, -1, sizeof(visited));
		visited[sx][sy] = 0;

		while (!qu.empty()) {
			auto front = qu.front();
			qu.pop();

			for (int i = 0; i < 8; i++) {
				int nx = front.first + mov[i][0], ny = front.second + mov[i][1];

				if (!(0 <= nx && nx < n && 0 <= ny && ny < n))
					continue;
				if (visited[nx][ny] != -1)
					continue;

				visited[nx][ny] = visited[front.first][front.second] + 1;
				qu.push({ nx, ny });
			}
		}

		printf("%d\n", visited[ex][ey]);
	}
}