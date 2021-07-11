#include <stdio.h>
#include <algorithm>
#include <queue>
#include <cstring>

struct node {
	int x, y, weight;

	node(int x, int y, int weight) : x(x), y(y), weight(weight) {}
};

bool operator<(node a, node b) {
	return a.weight > b.weight;
}

std::priority_queue<node> qu;
int map[150][150], visited[150][150], mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

int main(void) {
	int test = 0;
	while (1) {
		int n;
		scanf("%d", &n);

		if (n == 0)
			break;

		test++;

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				scanf("%d", &map[i][j]);
		
		memset(visited, 0x7f, sizeof(visited));
		visited[1][1] = map[1][1];
		qu.push({ 1, 1, visited[1][1] });

		while (!qu.empty()) {
			auto top = qu.top();
			qu.pop();

			for (int i = 0; i < 4; i++) {
				int nx = top.x + mov[i][0], ny = top.y + mov[i][1];

				if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n))
					continue;

				if (visited[nx][ny] > visited[top.x][top.y] + map[nx][ny]) {
					visited[nx][ny] = visited[top.x][top.y] + map[nx][ny];
					qu.push({ nx ,ny, visited[nx][ny] });
				}
			}
		}

		printf("Problem %d: %d\n", test, visited[n][n]);
	}
}