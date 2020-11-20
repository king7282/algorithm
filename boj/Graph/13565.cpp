#include <stdio.h>
#include <algorithm>
#include <queue>

int map[1010][1010], mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
bool visited[1010][1010];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%1d", &map[i][j]);
		}
	}

	visited[0][1] = true;
	std::queue<std::pair<int, int>> qu;
	qu.push(std::make_pair(0, 1));

	while (!qu.empty()) {
		std::pair<int, int> front = qu.front();
		qu.pop();

		for (int i = 0; i < 4; i++) {
			int nx = front.first + mov[i][0], ny = front.second + mov[i][1];

			if (!(0 <= nx && nx <= n + 1 && 1 <= ny && ny <= m))
				continue;

			if (map[nx][ny] != 0 || visited[nx][ny] == true)
				continue;

			visited[nx][ny] = true;
			qu.push(std::make_pair(nx, ny));
		}
	}

	if (visited[n + 1][1] == true) {
		printf("YES\n");
	}
	else
		printf("NO\n");
}