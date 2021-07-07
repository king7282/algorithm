#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#include <climits>

struct info {
	int x, y, jump;

	info(int x, int y, int jump) : x(x), y(y), jump(jump) {}
};

int map[210][210], visited[210][210][32];
int mov_normal[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
int mov_horse[8][2] = { {1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {-1, -2}, {-2, -1}, {1, -2}, {2, -1} };
std::queue<info> qu;

int main(void) {
	int k, n, m;
	scanf("%d %d %d", &k, &m, &n);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	
	memset(visited, -1, sizeof(visited));
	visited[1][1][k] = 0;
	qu.push({ 1, 1, k });

	while (!qu.empty()) {
		auto front = qu.front();
		qu.pop();

		for (int i = 0; i < 4; i++) {
			int nx = front.x + mov_normal[i][0], ny = front.y + mov_normal[i][1];

			if (!(1 <= nx && nx <= n && 1 <= ny && ny <= m))
				continue;

			if (visited[nx][ny][front.jump] != -1 || map[nx][ny] == 1)
				continue;

			visited[nx][ny][front.jump] = visited[front.x][front.y][front.jump] + 1;
			qu.push({ nx, ny, front.jump });
		}

		if (front.jump == 0)
			continue;

		for (int i = 0; i < 8; i++) {
			int nx = front.x + mov_horse[i][0], ny = front.y + mov_horse[i][1];

			if (!(1 <= nx && nx <= n && 1 <= ny && ny <= m))
				continue;

			if (visited[nx][ny][front.jump - 1] != -1 || map[nx][ny] == 1)
				continue;

			visited[nx][ny][front.jump - 1] = visited[front.x][front.y][front.jump] + 1;
			qu.push({ nx, ny, front.jump - 1 });
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