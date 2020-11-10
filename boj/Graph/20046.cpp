#include <stdio.h>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

struct node {
	int x, y, weight;
	node(int x, int y, int weight) : x(x), y(y), weight(weight) {}
};

bool operator<(node a, node b) {
	return a.weight > b.weight;
}

int mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
std::priority_queue<node> qu;
int input[1010][1010], visited[1010][1010];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &input[i][j]);
		}
	}

	if (input[1][1] == -1 || input[n][m] == -1) {
		printf("-1\n");
		return 0;
	}
	memset(visited, 0x7f, sizeof(visited));
	visited[1][1] = input[1][1];
	qu.push(node(1, 1, input[1][1]));
	while (!qu.empty()) {
		node top = qu.top();
		qu.pop();

		for (int i = 0; i < 4; i++) {
			int nx = top.x + mov[i][0], ny = top.y + mov[i][1];
			if (!(1 <= nx && nx <= n && 1 <= ny && ny <= m))
				continue;

			if (input[nx][ny] == -1)
				continue;

			if (visited[nx][ny] > top.weight + input[nx][ny]) {
				visited[nx][ny] = top.weight + input[nx][ny];
				qu.push(node(nx, ny, top.weight + input[nx][ny]));
			}
		}
	}

	if (visited[n][m] >= INT_MAX / 2) {
		printf("-1\n");
	}
	else
		printf("%d\n", visited[n][m]);
}