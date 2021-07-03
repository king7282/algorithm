#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <climits>

std::vector<std::pair<int, int>> virus;
int map[51][51], n, m, result, visited[51][51], mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
bool check[1 << 10];

void solve(int cnt, int bitmask) {
	if (check[bitmask] == true)
		return;

	check[bitmask] = true;
	if (cnt == m) {
		std::queue<std::pair<int, int>> qu;
		memset(visited, -1, sizeof(visited));

		for (int i = 0; i < virus.size(); i++) {
			if ((bitmask & (1 << i)) != 0) {
				qu.push(virus[i]);
				visited[virus[i].first][virus[i].second] = 0;
			}
		}

		while (!qu.empty()) {
			auto front = qu.front();
			qu.pop();

			for (int i = 0; i < 4; i++) {
				int nx = front.first + mov[i][0], ny = front.second + mov[i][1];

				if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n))
					continue;

				if (visited[nx][ny] != -1 || map[nx][ny] == 1)
					continue;

				visited[nx][ny] = visited[front.first][front.second] + 1;
				qu.push({ nx, ny });
			}
		}

		int tmp = 0;
		bool flag = true;
		for (int i = 1; i <= n && flag; i++) {
			for (int j = 1; j <= n && flag; j++) {
				if (map[i][j] == 0) {
					if (visited[i][j] == -1)
						flag = false;
					tmp = std::max(tmp, visited[i][j]);
				}
			}
		}

		if (flag)
			result = std::min(result, tmp);
		return;
	}

	for (int i = 0; i < virus.size(); i++) {
		if ((bitmask & (1 << i)) != 0)
			continue;

		solve(cnt + 1, bitmask | (1 << i));
	}
}

int main(void) {
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2) {
				virus.push_back({ i, j });
			}
		}
	}

	result = INT_MAX / 2;
	solve(0, 0);

	if (result == INT_MAX / 2)
		printf("-1\n");
	else
		printf("%d\n", result);
}
