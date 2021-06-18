#include <stdio.h>
#include <algorithm>
#include <set>

struct node {
	int x, y, bitmask;
	node(int x, int y, int bitmask) : x(x), y(y), bitmask(bitmask) {}
};

bool operator<(node a, node b) {
	if (a.x == b.x) {
		if (a.y == b.y)
			return a.bitmask < b.bitmask;
		return a.y < b.y;
	}
	return a.x < b.x;
}

int r, c, result, mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
char map[21][21];
std::set<node> check;

void solve(int x, int y, int bitmask) {
	if (check.find(node(x, y, bitmask)) != check.end())
		return;
	check.insert(node(x, y, bitmask));
	int cnt = 0;
	for (int i = 0; i < 26; i++) {
		if ((bitmask & (1 << i)) != 0)
			cnt++;
	}

	result = std::max(result, cnt);
	for (int i = 0; i < 4; i++) {
		int nx = x + mov[i][0], ny = y + mov[i][1];

		if (!(1 <= nx && nx <= r && 1 <= ny && ny <= c))
			continue;

		if ((bitmask & (1 << map[nx][ny])) != 0)
			continue;

		solve(nx, ny, bitmask | (1 << map[nx][ny]));
	}
}

int main(void) {
	scanf("%d %d", &r, &c);

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			scanf(" %c", &map[i][j]);
			map[i][j] -= 'A';
		}
	}

	solve(1, 1, 1 << map[1][1]);
	printf("%d\n", result);
}