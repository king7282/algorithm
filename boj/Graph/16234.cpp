#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>

std::vector<std::pair<int ,int>> un;
bool check[52][52];
int map[52][52], mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} }, n, s, e, cnt;

int aabs(int num) {
	if (num < 0)
		return num * -1;
	return num;
}

void solve(int x, int y) {
	check[x][y] = true;
	cnt += map[x][y];
	un.push_back({ x, y });
	for (int i = 0; i < 4; i++) {
		int nx = x + mov[i][0], ny = y + mov[i][1];

		if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n))
			continue;

		if (check[nx][ny] == true)
			continue;

		if (!(s <= aabs(map[x][y] - map[nx][ny]) && aabs(map[x][y] - map[nx][ny]) <= e))
			continue;

		solve(nx, ny);
	}
}

int main(void) {
	scanf("%d %d %d", &n, &s, &e);
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	int result = 0;
	while (1) {
		bool flag = false;
		memset(check, false, sizeof(check));

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (check[i][j] == false) {
					cnt = 0;
					un.clear();
					solve(i, j);
					if (cnt > map[i][j]) {
						flag = true;
						for (int k = 0; k < un.size(); k++) {
							map[un[k].first][un[k].second] = cnt / un.size();
						}
					}
				}
			}
		}

		if (!flag)
			break;
		result++;
	}

	printf("%d\n", result);
}
