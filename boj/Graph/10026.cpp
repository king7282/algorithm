#include <stdio.h>
#include <algorithm>
#include <functional>
#include <cstring>

char map[110][110];
int n, mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
bool check[110][110];

void func(int x, int y, std::function<bool(int, int, int, int)> compar) {
	check[x][y] = true;
	for (int i = 0; i < 4; i++) {
		int nx = x + mov[i][0], ny = y + mov[i][1];

		if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n))
			continue;

		if (check[nx][ny] == true || !compar(x, y, nx, ny))
			continue;

		func(nx, ny, compar);
	}
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			scanf(" %c", &map[i][j]);
	}

	auto first = [&](int x, int y, int nx, int ny) -> bool {
		return map[x][y] == map[nx][ny];
	};

	auto second = [&](int x, int y, int nx, int ny) -> bool {
		if (map[nx][ny] == map[x][y])
			return true;
		else if ((map[x][y] == 'R' && map[nx][ny] == 'G') || (map[x][y] == 'G' && map[nx][ny] == 'R'))
			return true;
		return false;
	};

	int cnt1 = 0, cnt2 = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (check[i][j] == false) {
				cnt1++;
				func(i, j, first);
			}
		}
	}

	memset(check, false, sizeof(check));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (check[i][j] == false) {
				cnt2++;
				func(i, j, second);
			}
		}
	}

	printf("%d %d\n", cnt1, cnt2);

}