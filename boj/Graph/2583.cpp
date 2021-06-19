#include <stdio.h>
#include <algorithm>
#include <vector>

int n, m, cnt, mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
int map[110][110];
bool check[110][110];

void solve(int x, int y) {
	check[x][y] = true;
	cnt++;

	for(int i = 0; i < 4; i++) {
		int nx = x + mov[i][0], ny = y + mov[i][1];

		if (!(0 <= nx && nx < n && 0 <= ny && ny < m))
			continue;

		if (check[nx][ny] == true || map[nx][ny] == 1)
			continue;
		solve(nx, ny);
	}
}

int main(void) {
	int k;
	scanf("%d %d %d", &m, &n, &k);

	for (int i = 1; i <= k; i++) {
		int sx, sy, ex, ey;
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);

		for (int x = sx; x < ex; x++) {
			for (int y = sy; y < ey; y++) {
				map[x][y] = 1;
			}
		}
	}

	std::vector<int> result;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0 && check[i][j] == false) {
				cnt = 0;
				solve(i, j);
				result.push_back(cnt);
			}
		}
	}

	std::sort(result.begin(), result.end());
	printf("%d\n", result.size());

	for (int i = 0; i < result.size(); i++)
		printf("%d ", result[i]);
}