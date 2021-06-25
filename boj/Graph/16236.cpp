#include <stdio.h>
#include <queue>
#include <algorithm>
#include <cstring>

int n, map[31][31], mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
int visited[31][31];
std::pair<int, int> shark;

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9)
				shark.first = i, shark.second = j;
		}
	}

	int cur = 2, cnt = 0, result = 0;
	while (1) {
		std::queue<std::pair<int, int>> qu;

		memset(visited, -1, sizeof(visited));
		visited[shark.first][shark.second] = 0;
		qu.push(shark);

		while (!qu.empty()) {
			std::pair<int, int> front = qu.front();
			qu.pop();

			for (int i = 0; i < 4; i++) {
				int nx = front.first + mov[i][0], ny = front.second + mov[i][1];

				if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n))
					continue;

				if (map[nx][ny] > cur || visited[nx][ny] != -1)
					continue;

				visited[nx][ny] = visited[front.first][front.second] + 1;
				qu.push({ nx, ny });
			}
		}

		std::pair<int, int> fish{ -1, -1 };
		int tmp = 10000;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (visited[i][j] == -1 || map[i][j] == 0)
					continue;

				if (tmp > visited[i][j] && map[i][j] < cur) {
					fish.first = i, fish.second = j;
					tmp = visited[i][j];
				}
			}
		}

		if (fish.first == -1)
			break;

		result += visited[fish.first][fish.second];
		cnt++;
		if (cur == cnt) {
			cur++;
			cnt = 0;
		}

		map[fish.first][fish.second] = 9;
		map[shark.first][shark.second] = 0;

		shark = fish;
	}

	printf("%d\n", result);
}