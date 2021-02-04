#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#include <climits>

struct node {
	int x, y, block;
	node(int x, int y, int block) : x(x), y(y), block(block) {}
};

int map[1010][1010], visited[1010][1010][11];
int mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

int main(void) {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%1d", &map[i][j]);
		}
	}

	std::queue<node> qu;
	memset(visited, -1, sizeof(visited));
	
	visited[1][1][0] = 1;
	qu.push(node(1, 1, 0));

	while (!qu.empty()) {
		node front = qu.front();
		qu.pop();

		for (int i = 0; i < 4; i++) {
			int nx = front.x + mov[i][0], ny = front.y + mov[i][1];
			if (!(1 <= nx && nx <= n && 1 <= ny && ny <= m))
				continue;

			if (map[nx][ny] + front.block > k)
				continue;

			if (visited[nx][ny][front.block + map[nx][ny]] == -1) {
				visited[nx][ny][front.block + map[nx][ny]] = visited[front.x][front.y][front.block] + 1;
				qu.push(node(nx, ny, front.block + map[nx][ny]));
			}
		}
	}

	int result = INT_MAX / 2;
	for (int i = 0; i <= k; i++) {
		if (visited[n][m][i] != -1)
			result = std::min(result, visited[n][m][i]);
	}
	if (result == INT_MAX / 2)
		printf("-1\n");
	else
		printf("%d\n", result);
}