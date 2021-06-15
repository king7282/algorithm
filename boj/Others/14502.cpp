#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

int mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
int map[9][9], n, m, result;
std::vector<std::pair<int, int>> starts;
bool check[9][9];

int OK(void) {
	std::queue<std::pair<int, int>> qu;

	for (int i = 0; i < starts.size(); i++)
		qu.push(starts[i]);

	memset(check, false, sizeof(check));
	while (!qu.empty()) {
		auto front = qu.front();
		qu.pop();

		for (int i = 0; i < 4; i++) {
			int nx = front.first + mov[i][0], ny = front.second + mov[i][1];

			if (!(1 <= nx && nx <= n && 1 <= ny && ny <= m))
				continue;

			if (map[nx][ny] == 1 || check[nx][ny] == true)
				continue;

			check[nx][ny] = true;
			qu.push({ nx, ny });
		}
	}

	int r = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j] == 0 && check[i][j] == false) {
				r++;
			}
		}
	}

	return r;
}

void func(int x, int y, int cnt) {
	if (cnt == 3) {
		result = std::max(result, OK());
		return;
	}

	for (int i = x; i <= n; i++) {
		if (x == i) {
			for (int j = y + 1; j <= m; j++) {
				if (map[i][j] == 0) {
					map[i][j] = 1;
					func(i, j, cnt + 1);
					map[i][j] = 0;
				}
			}
		}
		else {
			for (int j = 1; j <= m; j++) {
				if (map[i][j] == 0) {
					map[i][j] = 1;
					func(i, j, cnt + 1);
					map[i][j] = 0;
				}
			}
		}
	}
}


int main(void) {
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &map[i][j]);

			if (map[i][j] == 2) {
				starts.push_back({ i, j });
				map[i][j] = 1;
			}
		}
	}

	func(1, 0, 0);

	printf("%d\n", result);


}