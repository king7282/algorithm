#include <stdio.h>
#include <algorithm>

int n, mov[2][3][2] = { {{0, 1}, {-1, -1}, {1, -1}}, {{0, -1}, {1, 1}, {-1, 1}} };
int result;

bool check[110][110];

void solve(int x, int y, int type, int d, int cnt) {
	if (cnt < 0)
		return;

	if (check[x][y] == true) {
		if (cnt == 0) {
			result++;
		}
		return;
	}
	check[x][y] = true;

	for (int i = 0; i < 3; i++) {
		if (i == d)
			continue;
		int nx = x + mov[type][i][0], ny = y + mov[type][i][1];

		solve(nx, ny, (type + 1) % 2, i, cnt - 1);
	}

	check[x][y] = false;
}

int main(void) {
	scanf("%d", &n);
	
	check[50][50] = true;
	solve(50, 51, 1, 0, n);

	printf("%d\n", result);
}