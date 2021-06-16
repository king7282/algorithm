#include <stdio.h>
#include <algorithm>
#include <cstring>

int n, m;
int map[51][51], mov[8][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, 1}, {-1, -1}, {1, -1}, {1, 1} };
bool check[51][51];

void solve(int x, int y) {
	check[x][y] = true;

	for (int i = 0; i < 8; i++) {
		int nx = x + mov[i][0], ny = y + mov[i][1];

		if (!(1 <= nx && nx <= n && 1 <= ny && ny <= m))
			continue;

		if (check[nx][ny] == true || map[nx][ny] == 0)
			continue;
		solve(nx, ny);
	}
}

int main(void) {
	while (1) {
		scanf("%d %d", &m, &n);

		if (n == 0 && m == 0)
			break;

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		memset(check, false, sizeof(check));
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (check[i][j] == false && map[i][j] == 1) {
					cnt++;
					solve(i, j);

				}
			}
		}
		printf("%d\n", cnt);
	}
}