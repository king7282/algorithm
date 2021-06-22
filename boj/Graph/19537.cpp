#include <stdio.h>
#include <algorithm>
#include <queue>
#include <cstring>

struct unit {
	int m, t, a, b;
};

struct node {
	int x, y, weight;

	node(int x, int y, int weight) : x(x), y(y), weight(weight) {}
};

bool operator<(node a, node b) {
	return a.weight > b.weight;
}

int map[510][510], diff[10], check[510][510], mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} }, mul[2] = { -1, 1 };
char visited[510][510];
unit obj[62501];
std::priority_queue<node> qu;

int main(void) {
	int h, n, m, u, k;
	scanf("%d %d %d", &h, &n, &m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	for (int i = 1; i <= h; i++) {
		scanf("%d", diff + i);
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			map[i][j] = diff[map[i][j]];

	scanf("%d", &u);
	for (int i = 1; i <= u; i++) {
		scanf("%d %d %d %d", &obj[i].m, &obj[i].t, &obj[i].a, &obj[i].b);
		check[obj[i].a][obj[i].b] += mul[obj[i].t];
	}

	scanf("%d", &k);

	for (int i = 1; i <= k; i++) {
		int type, x, y;
		scanf("%d %d %d", &type, &x, &y);

		if (check[x][y] != 0 || map[x][y] == -1)
			continue;

		memset(visited, -1, sizeof(visited));
		qu.push(node(obj[type].a, obj[type].b, 0));
		visited[obj[type].a][obj[type].b] = 0;

		while (!qu.empty()) {
			node top = qu.top();
			qu.pop();
			for (int i = 0; i < 4; i++) {
				int nx = top.x + mov[i][0], ny = top.y + mov[i][1];

				if (!(0 <= nx && nx < n && 0 <= ny && ny < m))
					continue;

				if (map[nx][ny] == -1 || visited[nx][ny] != -1)
					continue;
				if (check[nx][ny] != 0 && check[nx][ny] != mul[obj[type].t])
					continue;

				if (visited[top.x][top.y] + map[nx][ny] > obj[type].m)
					continue;

				bool flag = true;
				for (int j = 0; j < 4 && flag; j++) {
					int nnx = nx + mov[j][0], nny = ny + mov[j][1];

					if (!(0 <= nnx && nnx < n && 0 <= nny && nny < m))
						continue;

					if (check[nnx][nny] != 0 && check[nnx][nny] != mul[obj[type].t])
						flag = false;
				}

				if (!(x == nx && y == ny) && !flag)
					continue;

				visited[nx][ny] = visited[top.x][top.y] + map[nx][ny];
				qu.push(node(nx, ny, visited[nx][ny]));
			}
		}

		if (visited[x][y] != -1 && visited[x][y] <= obj[type].m) {
			check[obj[type].a][obj[type].b] -= mul[obj[type].t];
			obj[type].a = x, obj[type].b = y;
			check[obj[type].a][obj[type].b] += mul[obj[type].t];
		}
	}

	for (int i = 1; i <= u; i++) {
		printf("%d %d\n", obj[i].a, obj[i].b);
	}
}