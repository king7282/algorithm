#include <stdio.h>
#include <algorithm>
#include <cstring>

struct info {
	int x, y, k;
};

info query[82];
int map[10][10];

bool func(int x, int y) {
	if (x == 10)
		return true;

	int nx = x, ny = y + 1;
	if (ny == 10) {
		nx++;
		ny = 1;
	}

	if (map[x][y] != 0) {
		return func(nx, ny);
	}

	bool flag = false;
	for (int i = 1; i <= 9 && !flag; i++) {
		bool flag2 = true;
		for (int k = 1; k <= 9 && flag2; k++) {
			if (map[x][k] == i || map[k][y] == i)
				flag2 = false;
		}

		int tmpx = (x - 1) / 3, tmpy = (y - 1) / 3;

		for (int a = 1; a <= 3 && flag2; a++) {
			for (int b = 1; b <= 3 && flag2; b++) {
				if (map[a + tmpx * 3][b + tmpy * 3] == i)
					flag2 = false;
			}
		}

		if (flag2) {
			map[x][y] = i;
			flag = func(nx, ny);
			map[x][y] = 0;
		}
	}
	return flag;
}
bool OK(int num) {
	memset(map, 0, sizeof(map));
	bool flag = true;
	for (int i = 1; i <= num && flag; i++) {
		if (map[query[i].x][query[i].y] != 0)
			flag = false;
		map[query[i].x][query[i].y] = query[i].k;
	}


	for (int x = 1; x <= 9 && flag; x++) {
		for (int y = 1; y <= 9 && flag; y++) {
			if (map[x][y] == 0)
				continue;

			for (int i = 1; i <= 9 && flag; i++) {
				if (i != y && map[x][y] == map[x][i])
					flag = false;

				if (i != x && map[x][y] == map[i][y])
					flag = false;
			}

			int tmpx = (x - 1) / 3, tmpy = (y - 1) / 3;

			for (int a = 1; a <= 3 && flag; a++) {
				for (int b = 1; b <= 3 && flag; b++) {
					if (a + tmpx * 3 == x && b + tmpy * 3 == y)
						continue;

					if (map[a + tmpx * 3][b + tmpy * 3] == map[x][y])
						flag = false;
				}
			}
		}
	}

	if (!flag)
		return false;

	return func(1, 1);
}

int main(void) {
	for (int i = 1; i <= 81; i++)
		scanf("%d %d %d", &query[i].x, &query[i].y, &query[i].k);

	int s = 1, e = 81, r = 0;

	while (s <= e) {
		int mid = (s + e) / 2;
		if (OK(mid)) {
			s = mid + 1;
			r = std::max(r, mid);
		}
		else
			e = mid - 1;
	}

	if (r == 81) {
		printf("-1\n");
	}
	else
		printf("%d\n", r + 1);
}