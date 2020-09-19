#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

std::pair<int, int> folding[21];
int map[40][40];

int main(void) {
	while (1) {
		int n, m, t, p;
		scanf("%d %d %d %d", &n, &m, &t, &p);
		if (n == 0)
			break;

		memset(map, 0, sizeof(map));
		for (int i = 1; i <= t; i++)
			scanf("%d %d", &folding[i].first, &folding[i].second);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int x = 0, y = 0, curx = i, cury = j;
				for (int k = 1; k <= t; k++) {
					if (folding[k].first == 2) {
						y += folding[k].second;
						if (y > cury) {
							cury = y + (y - cury) - 1;
						}
					}
					else {
						x += folding[k].second;
						if (x > curx) {
							curx = x + (x - curx) - 1;
						}
					}
				}
				map[curx - x][cury - y]++;
			}
		}
		for (int i = 1; i <= p; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			printf("%d\n", map[a][b]);
		}

	}
}