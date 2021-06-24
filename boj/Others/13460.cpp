#include <stdio.h>
#include <algorithm>

char map[12][12];
int result = 11, n, m, mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

void solve(int cnt) {
	if (cnt > 10)
		return;

	char tmp[11][11];
	std::pair<int, int> red, blue;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			tmp[i][j] = map[i][j];
			if (map[i][j] == 'R') {
				red.first = i, red.second = j;
			}
			else if (map[i][j] == 'B') {
				blue.first = i, blue.second = j;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		bool flag = true, finish = false;

		int bx = blue.first, by = blue.second, rx = red.first, ry = red.second;

		while (1) {
			bx += mov[i][0], by += mov[i][1];

			if (map[bx][by] == 'O') {
				bx -= mov[i][0], by -= mov[i][1];
				flag = false;
				break;
			}

			if (map[bx][by] != '.') {
				bx -= mov[i][0], by -= mov[i][1];
				break;
			}

			std::swap(map[bx][by], map[bx - mov[i][0]][by - mov[i][1]]);
		}

		while (1) {
			rx += mov[i][0], ry += mov[i][1];

			if (map[rx][ry] == 'O') {
				map[rx - mov[i][0]][ry - mov[i][1]] = '.';
				finish = true;
				break;
			}
			if (map[rx][ry] != '.')
				break;

			std::swap(map[rx][ry], map[rx - mov[i][0]][ry - mov[i][1]]);
		}

		while (1) {
			bx += mov[i][0], by += mov[i][1];

			if (map[bx][by] == 'O') {
				flag = false;
				break;
			}
			if (map[bx][by] != '.')
				break;

			std::swap(map[bx][by], map[bx - mov[i][0]][by - mov[i][1]]);
		}

		if (flag && finish) {
			result = std::min(result, cnt);
		}
		else if (flag) {
			solve(cnt + 1);
		}

		for (int a = 1; a <= n; a++) {
			for (int b = 1; b <= m; b++) {
				map[a][b] = tmp[a][b];
			}
		}
	}
}

int main(void) {
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf(" %c", &map[i][j]);
		}
	}

	solve(1);

	if (result == 11)
		printf("-1\n");
	else
		printf("%d\n", result);
}